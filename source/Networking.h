#ifndef NETWORKING_H
#define NETWORKING_H

#include <SFML/Network.hpp>
#include <string>

class Networking
{
public:
    Networking();
    sf::TcpSocket socket;
    std::string local_name;
    std::string remote_name;
    enum UserType
    {
        Host, Client
    } user_type;
    bool connected = 0;
    void connectHost(std::string local_name, unsigned short port);
	void connectClient(std::string local_name, unsigned short port, sf::IpAddress adress);
private:
    sf::TcpListener listener;
    unsigned short last_port;
};

#endif
