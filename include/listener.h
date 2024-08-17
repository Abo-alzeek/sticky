#ifndef LISTENER_H_
#define LISTENER_H_

#include "basic.h"

class Listener {
public:
    typedef websocketpp::client<websocketpp::config::asio_client> client;
    typedef websocketpp::lib::lock_guard<websocketpp::lib::mutex> scoped_lock;
    typedef websocketpp::config::asio_client::message_type::ptr message_ptr;
    Listener();

    std::function<void()> Run;

    void set_state(CState &);
    void set_sending_state(CState &);
    CState get_state();
    CState get_snd_state();

    bool connected;

    void loop();
    void on_open(websocketpp::connection_hdl);
    void on_close(websocketpp::connection_hdl);
    void on_fail(websocketpp::connection_hdl);
    void on_message(websocketpp::connection_hdl hdl, message_ptr msg);
    bool m_open;
    bool m_done;
private:
    CState snd_state, rcv_state;
    client m_client;
    std::string player_id;
    std::string other_player;
    websocketpp::connection_hdl m_hdl;
    websocketpp::lib::mutex m_lock;
    

};

#endif
