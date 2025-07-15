#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <SFML/Network.hpp>

using namespace std;

class TcpServer {
public:
    TcpServer(unsigned short port);
    bool start();
    string update();
    void sendMessage(const string& message);

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
    string update();
    void sendMessage(const std::string& message);
    bool discoverServer();

private:
    sf::IpAddress serverIp = sf::IpAddress::Any;
    unsigned short port;
    sf::TcpSocket socket;
};
