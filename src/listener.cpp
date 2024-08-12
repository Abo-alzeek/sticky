#include "../include/basic.h"

Listener::Listener() {
    Run = [&] (){
        while(1) {
            char buffer[2000];
            std::size_t received;
            sf::TcpSocket socket;
            
            std::string remoteAdress = "127.0.0.1";
            socket.connect(remoteAdress, 8000);
            socket.receive(buffer, sizeof(buffer), received);

            std::cout << buffer << std::endl;

            while(1) {
                socket.receive(buffer, sizeof(buffer), received);
                if (received > 0) {
                    std::cout << "Received :" << buffer << std::endl;
                }
            }
        }
    };
}

CState Listener::get_state() {
    return m_state;
    
}
