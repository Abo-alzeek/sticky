#include "../include/basic.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
void wait_a_bit() {
#ifdef WIN32
    Sleep(100);
#else
    usleep(50000);
#endif
}

void on_open(websocketpp::connection_hdl hdl, client* c, Listener* listener) {
    std::cout << "WebSocket connection opened!" << std::endl;
     websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
 
    if (ec) {
        std::cout << "Failed to get connection pointer: " << ec.message() << std::endl;
        return;
    }
        std::cout << "YAY\n";
        std::fstream f;
        f.open("something.txt");
        std::string player_id;
        f >> player_id;

        std::cout << "THE READ PLAYER ID IS: " << player_id << "\n";

        f.close();
        while (1) {
            try {
                json payload = {
                    {"type", "state"}, {"data",{
                        player_id, {
                            {"state", listener->get_snd_state().state},
                            {"lastFrameState", listener->get_snd_state().lastFrameState},
                            {"toUpdate", listener->get_snd_state().toUpdate}
                        }
                    }}
                };
                // websocketpp::lib::error_code ec;
                // client::connection_ptr con = c.get_connection(uri, ec);
                c->send(hdl, payload.dump(), websocketpp::frame::opcode::text,ec);

                if (ec) {
                    std::cout << "> Error sending message: " << ec.message() << std::endl;
                }
                else std::cout << "SENT: " << payload.dump() << '\n';
            } 
            catch (websocketpp::exception const & e) {
                std::cout << "WebSocket Exception: " << e.what() << std::endl;
            }
        }

    //c->send(con, payload, websocketpp::frame::opcode::text);
}

void on_message(websocketpp::connection_hdl, client::message_ptr msg) {
    std::cout << "Received message: " << msg->get_payload() << std::endl;
}

void on_fail(websocketpp::connection_hdl hdl) {
    std::cout << "WebSocket connection failed!" << std::endl;
}

void on_close(websocketpp::connection_hdl hdl) {
    std::cout << "WebSocket connection closed!" << std::endl;
}




std::string toString(int x) {
    std::string ret = "";

    while(x) {
        ret += (x % 10 + '0');
        x/= 10;
    }

    reverse(ret.begin(), ret.end());
    return ret;
}

Listener::Listener(): m_open(false),m_done(false) {
    std::fstream f;
    f.open("something.txt");
    f >> this->player_id;
    if (this->player_id == "player1") this->other_player = "player2";
    else this->other_player = "player1";
    // set up access channels to only log interesting things
    m_client.clear_access_channels(websocketpp::log::alevel::all);
    m_client.set_access_channels(websocketpp::log::alevel::connect);
    m_client.set_access_channels(websocketpp::log::alevel::disconnect);
    m_client.set_access_channels(websocketpp::log::alevel::app);

    // Initialize the Asio transport policy
    m_client.init_asio();

    // Bind the handlers we are using
    using websocketpp::lib::placeholders::_1;
    using websocketpp::lib::bind;
    m_client.set_open_handler(bind(&Listener::on_open,this,_1));
    m_client.set_close_handler(bind(&Listener::on_close,this,_1));
    m_client.set_fail_handler(bind(&Listener::on_fail,this,_1));
    m_client.set_message_handler(bind(&Listener::on_message,this, _1, _2));

    Run = [&] () -> void {
        client c;
        std::string hostname = "127.0.0.1:8000/ws/game";
        std::string uri = "ws://" + hostname;
        // Create a new connection to the given URI
        websocketpp::lib::error_code ec;
        client::connection_ptr con = m_client.get_connection(uri, ec);
        if (ec) {
            m_client.get_alog().write(websocketpp::log::alevel::app,
                    "Get Connection Error: "+ec.message());
            return;
        }

        // Grab a handle for this connection so we can talk to it in a thread
        // safe manor after the event loop starts.
        m_hdl = con->get_handle();

        // Queue the connection. No DNS queries or network connections will be
        // made until the io_service event loop is run.
        m_client.connect(con);

        // Create a thread to run the ASIO io_service event loop
        websocketpp::lib::thread asio_thread(&client::run, &m_client);

        // Create a thread to run the telemetry loop
        websocketpp::lib::thread loop_thread(&Listener::loop,this);

        asio_thread.join();
        loop_thread.join();
    };
}

CState Listener::get_state() {
    return rcv_state;
}

CState Listener::get_snd_state() {
    return snd_state;
}

void Listener::on_open(websocketpp::connection_hdl hdl) {
     m_client.get_alog().write(websocketpp::log::alevel::app,
            "Connection opened, starting telemetry!");

        scoped_lock guard(m_lock);
        m_open = true;
}

void Listener::on_close(websocketpp::connection_hdl hdl) {
 m_client.get_alog().write(websocketpp::log::alevel::app,
            "Connection closed, stopping telemetry!");

        scoped_lock guard(m_lock);
        m_done = true;
}

void Listener::on_fail(websocketpp::connection_hdl hdl) {
 m_client.get_alog().write(websocketpp::log::alevel::app,
            "Connection failed, stopping telemetry!");

        scoped_lock guard(m_lock);
        m_done = true;
}

void Listener::loop() {
    
    websocketpp::lib::error_code ec;

    while(1) {
        bool wait = false;

        {
            scoped_lock guard(m_lock);
            // If the connection has been closed, stop generating telemetry
            if (m_done) {break;}

            // If the connection hasn't been opened yet wait a bit and retry
            if (!m_open) {
                wait = true;
            }
        }

        if (wait) {
            wait_a_bit();
            continue;
        }

        json payload = {
            {"type", "state"}, {"data",{}}
        };
        payload["data"][player_id] = {
                    {"state", this->snd_state.state},
                    {"lastFrameState", this->snd_state.lastFrameState},
                    {"toUpdate", this->snd_state.toUpdate},
                    {"position", {
                        this->snd_state.position.x,this->snd_state.position.y
                    }},
                    {"hp", this->snd_state.hp}
                };

        m_client.get_alog().write(websocketpp::log::alevel::app, payload.dump());
        m_client.send(m_hdl,payload.dump(),websocketpp::frame::opcode::text,ec);

        // The most likely error that we will get is that the connection is
        // not in the right state. Usually this means we tried to send a
        // message to a connection that was closed or in the process of
        // closing. While many errors here can be easily recovered from,
        // in this simple example, we'll stop the telemetry loop.
        if (ec) {
            m_client.get_alog().write(websocketpp::log::alevel::app,
                "Send Error: "+ec.message());
            break;
        }

        wait_a_bit();
    }
}

void Listener::on_message(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
        << " and message: " << msg->get_payload()
        << std::endl;

    json payload = json::parse(msg->get_payload());

    CState s;
    if (payload["data"][other_player].contains("state")) {
        s.state = payload["data"][other_player]["state"];
        s.lastFrameState = payload["data"][other_player]["lastFrameState"];
        s.toUpdate = payload["data"][other_player]["toUpdate"];
        s.position.x = payload["data"][other_player]["position"][0];
        s.position.y = payload["data"][other_player]["position"][1];
        s.hp = payload["data"][other_player]["hp"];
    }
    this->set_state(s);
}

void Listener::set_state(CState &s) {
    this->rcv_state.state = s.state;
    this->rcv_state.lastFrameState = s.lastFrameState;
    this->rcv_state.toUpdate = s.toUpdate;
    this->rcv_state.position = s.position;
    this->rcv_state.hp = s.hp;
}

void Listener::set_sending_state(CState &s) {
    this->snd_state.state = s.state;
    this->snd_state.lastFrameState = s.lastFrameState;
    this->snd_state.toUpdate = s.toUpdate;
    this->snd_state.position = s.position;
    this->snd_state.hp = s.hp;
}
