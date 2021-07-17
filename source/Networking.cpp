#include "Networking.h"

Networking::Networking()
{
    listener.setBlocking(1);
    socket.setBlocking(1);
}

void Networking::connectHost(std::string local_name, unsigned short port)
{
    if (port != last_port)
	{
		listener.listen(port);
		last_port = port;
	}
	if (listener.accept(socket) == sf::Socket::Done)
	{
		user_type = UserType::Host;
		this->local_name = local_name;
		connected = 1;
		return;
	}
	connected = 0;
}

void Networking::connectClient(std::string local_name, unsigned short port, sf::IpAddress adress)
{
    if (socket.connect(adress, port) == sf::Socket::Done)
	{
		user_type = UserType::Client;
		this->local_name = local_name;
		connected = 1;
		return;
	}
	connected = 0;
}
