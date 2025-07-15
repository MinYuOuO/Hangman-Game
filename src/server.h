#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <SFML/Network.hpp>

using namespace std;

class TcpServer {
public:
    TcpServer(unsigned short port = 53000);
    bool start();
    string update();
    void sendMessage(const string& message);
    bool clientConnected = false;
    void listenForDiscovery();

private:
    unsigned short port;
    sf::UdpSocket discoverySocket;
    sf::TcpListener listener;
    sf::TcpSocket client;
    sf::SocketSelector selector;
};

class TcpClient {
public:
    TcpClient(unsigned short port = 54000);
    bool connect();
    string update();
    void sendMessage(const std::string& message);
    bool discoverServer();
    bool serverConnected = false;

private:
    sf::IpAddress serverIp = sf::IpAddress::Any;
    unsigned short port;
    sf::TcpSocket socket;
};
