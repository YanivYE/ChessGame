#pragma once

#include <iostream>
#include <SFML/Network.hpp>

#define DEFAULT_PORT 8200
#define LOCAL_HOST "127.0.0.1"

class GraphicHandeler
{
private:
	sf::TcpSocket _socket;

public:

	GraphicHandeler()
	{
		sf::IpAddress ip = LOCAL_HOST;
		unsigned short port = DEFAULT_PORT;

		// Create a socket and connect to the server
		_socket.connect(ip, port);
	}

	bool connectToGraphics()
	{
		sf::IpAddress ip = LOCAL_HOST;
		unsigned short port = DEFAULT_PORT;

		_socket.connect(ip, port);

		if (_socket.getRemoteAddress() != sf::IpAddress::None)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool sendMessageToGraphics(std::string msg)
	{
		_socket.send(msg.c_str(), msg.length());

		return true;
	}

	std::string getMessageFromGraphics()
	{
		char buffer[1024];
		std::size_t received;
		_socket.receive(buffer, sizeof(buffer), received);

		// Extract the message from the packet
		std::string receivedMessage;
		receivedMessage = std::string(buffer, received);

		return receivedMessage;
	}

	void dsiconnect()
	{
		_socket.disconnect();
	}

};
