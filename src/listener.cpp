#include "../include/basic.h"

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_open(websocketpp::connection_hdl hdl, client* c) {
    std::cout << "WebSocket connection opened!" << std::endl;
     websocketpp::lib::error_code ec;
    client::connection_ptr con = c->get_con_from_hdl(hdl, ec);
 
    if (ec) {
        std::cout << "Failed to get connection pointer: " << ec.message() << std::endl;
        return;
    }
    std::string payload = "{\"userKey\":\"API_KEY\", \"symbol\":\"EURUSD,GBPUSD\"}";
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

Listener::Listener() {
    Run = [&] () -> void {
        client c;
        std::string hostname = "127.0.0.1:8000/ws/game";
        std::string uri = "ws://" + hostname;

        try {
            c.set_access_channels(websocketpp::log::alevel::all);
            c.clear_access_channels(websocketpp::log::alevel::frame_payload);
            c.set_error_channels(websocketpp::log::elevel::all);
            c.init_asio();
        
            c.set_message_handler(&on_message);
            //c.set_tls_init_handler(bind(&on_tls_init));
        
            c.set_open_handler(bind(&on_open, ::_1, &c));
            c.set_fail_handler(bind(&on_fail, ::_1));
            c.set_close_handler(bind(&on_close, ::_1));
            c.set_error_channels(websocketpp::log::elevel::all);  // Enable detailed error logging
            websocketpp::lib::error_code ec;
            client::connection_ptr con = c.get_connection(uri, ec);
            if (ec) {
                std::cout << "Could not create connection because: " << ec.message() << std::endl;
                return;
            }
            c.connect(con);
        
            websocketpp::lib::thread asio_thread(&client::run, &c);
            asio_thread.detach();
        } catch (websocketpp::exception const & e) {
            std::cout << "WebSocket Exception: " << e.what() << std::endl;
        }

        std::cout << "YAY\n";
        std::fstream f;
        f.open("something.txt");
        std::string player_id;
        f >> player_id;

        std::cout << "THE READ PLAYER ID IS: " << player_id << "\n";

        f.close();
        try {
        while (1) {
          json payload = {
                {"type", "state"}, {"data",{
                    player_id, {
                        {"state", this->snd_state.state},
                        {"lastFrameState", this->snd_state.lastFrameState},
                        {"toUpdate", this->snd_state.toUpdate}
                    }
                }}
            };
            websocketpp::lib::error_code ec;
            client::connection_ptr con = c.get_connection(uri, ec);
            c.send(con->get_handle(),payload.dump(), websocketpp::frame::opcode::text,ec);
            if (ec) {
                std::cout << "> Error sending message: " << ec.message() << std::endl;
                return;
            }
            else std::cout << "SENT: " << payload.dump() << '\n';
        } } catch (websocketpp::exception const & e) {
            std::cout << "WebSocket Exception: " << e.what() << std::endl;
        }
    };
}

CState Listener::get_state() {
    return rcv_state;
}

void Listener::set_state(CState &s) {
    this->snd_state.state = s.state;
    this->snd_state.lastFrameState = s.lastFrameState;
    this->snd_state.toUpdate = s.toUpdate;
}
