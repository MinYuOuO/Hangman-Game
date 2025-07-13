#pragma once
#include <iostream>
#include <SFML/Network.hpp>

class TcpServer {
public:
    TcpServer(unsigned short port);
    bool start();
    void update(); // Call this every frame/tick in the game loop
    void sendMessage(const std::string& message);

private:
    void listenForDiscovery();

    unsigned short port;
    sf::UdpSocket discoverySocket;
    sf::TcpListener listener;
    sf::TcpSocket client;
    sf::SocketSelector selector;
    bool clientConnected = false;
};

class TcpClient {
public:
    TcpClient(unsigned short port = 53000);
    bool connect();
    void update(); // Call in game loop
    void sendMessage(const std::string& message);
    bool discoverServer();

private:

    sf::IpAddress serverIp = sf::IpAddress::Any;
    unsigned short port;
    sf::TcpSocket socket;
};
