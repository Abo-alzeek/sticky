#include <SFML/Network.hpp>
#include <iostream>

int main(int argc, char ** argv) {
    sf::IpAddress ip = sf::IpAddress::getLocalAddress();
    sf::TcpSocket socket;
    char buffer[2000];
    std::size_t received;
    sf::TcpListener listener;
    listener.listen(2005);
    listener.accept(socket);
    
    socket.receive(buffer, sizeof(buffer), received);

    std::cout << buffer << std::endl;

    while(1) {
        socket.receive(buffer, sizeof(buffer), received);
        if (received > 0) {
            std::cout << "Received :" << buffer << std::endl;
        }
    }

    system("pause");
}
