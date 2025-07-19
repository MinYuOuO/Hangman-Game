#pragma once
#include <iostream>
#include <utility>
#include <string>
#include <SFML/Network.hpp>

using namespace std;

class Server {
public:
    virtual ~Server() = default;

    bool connected = false;

    virtual string update();
    virtual void sendMessage(const string& message) = 0;

    void sendingAck();
    bool waitForAck();
};

class TcpServer : public Server {
    unsigned short port = 53000;
    sf::TcpSocket socket;
    sf::UdpSocket discoverySocket;
    sf::TcpListener listener;
    sf::SocketSelector selector;

public:
    TcpServer(unsigned short port);
    bool start();
    void listenForDiscovery();

    string update() override;
    void sendMessage(const string& message) override;
};

class TcpClient : public Server {
    unsigned short port = 54000;
    sf::TcpSocket socket;
    sf::TcpListener listener;
    sf::SocketSelector selector;
    sf::IpAddress serverIp = sf::IpAddress::Any;

public:
    TcpClient(unsigned short port);
    bool connect();
    bool discoverServer();

    string update() override;
    void sendMessage(const string& message) override;
};
