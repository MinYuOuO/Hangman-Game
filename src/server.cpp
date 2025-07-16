#include "server.h"

using namespace std;

std::string Server::update() {
    return "";
}

void Server::sendingAck() {
    sendMessage("ACK");
}

void Server::sendMessage(const std::string& message) {
    cerr << "Base Server::sendMessage should not be called.\n";
}

bool Server::waitForAck() {
    const float timeoutSeconds = 0.5f;  // Wait up to 5 seconds
    const int pollIntervalMs = 100;
    int waitedMs = 0;

    while (waitedMs < timeoutSeconds * 1000) {
        string message = update();

        if (message == "ACK") {
            return true;  //ACK received
        }

        if (message != "false" && !message.empty()) {
            cout << "Received unexpected message while waiting for ACK: " << message << endl;
            return false;
        }

        sf::sleep(sf::milliseconds(pollIntervalMs));
        waitedMs += pollIntervalMs;
    }
    return false;
}

TcpServer::TcpServer(unsigned short port) : port(port) {}

bool TcpServer::start() {
    if (discoverySocket.bind(port) != sf::Socket::Status::Done) {
        cerr << "Failed to bind UDP discovery socket.\n";
        return false;
    }
    discoverySocket.setBlocking(false);

    if (listener.listen(53000) != sf::Socket::Status::Done) {
        cerr << "Failed to bind server to port.\n";
        return false;
    }

    selector.add(listener);

    cout << "Server started on port " << port << "\n";
    return true;
}

void TcpServer::listenForDiscovery() {
    char buffer[128];
    size_t received = 0;
    optional<sf::IpAddress> senderIp;
    unsigned short senderPort;

    if (discoverySocket.receive(buffer, sizeof(buffer), received, senderIp, senderPort) == sf::Socket::Status::Done) {
        std::string message(buffer, received);
        if (message == "DISCOVER_SERVER") {
            std::string reply = "SERVER_HERE";
            if (senderIp.has_value() && discoverySocket.send(reply.c_str(), reply.size(), *senderIp, senderPort) != sf::Socket::Status::Done) {
                std::cerr << "Failed to send discovery response.\n";
            } else {
                std::cout << "Discovery ping received from " << *senderIp << "\n";
            }
        }
    }
}

string TcpServer::update() {
    if (selector.wait(sf::milliseconds(10))) {
        if (selector.isReady(listener)) {
            // New connection
            if (listener.accept(socket) == sf::Socket::Status::Done) {
                cout << "Client connected!\n";
                socket.setBlocking(false);
                selector.add(socket);
                connected = true;
            }
        } else if (connected && selector.isReady(socket)) {
            // Handle client message
            char buffer[1024];
            size_t received;
            sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);

            switch (status) {
                case sf::Socket::Status::Done: {
                    string message(buffer, received);
                    return message;
                }
                case sf::Socket::Status::NotReady:
                    cerr << "[Server::update] Not ready\n";
                    return "false";
                case sf::Socket::Status::Disconnected:
                    cerr << "[Server::update] Client disconnected.\n";
                    socket.disconnect();
                    return "false";
                case sf::Socket::Status::Error:
                default:
                    cerr << "[Server::update] Error while receiving from client.\n";
                    return "false";
            }
        }
    }
    return "false";
}

void TcpServer::sendMessage(const string& message) {
    size_t totalSent = 0;
    const char* data = message.c_str();
    size_t toSend = message.size();

    while (totalSent < toSend) {
        size_t sentThisTime;
        sf::Socket::Status status = socket.send(data + totalSent, toSend - totalSent, sentThisTime);

        if (status == sf::Socket::Status::Done) {
            totalSent += sentThisTime;
            connected = true;
        } else if (status == sf::Socket::Status::Partial) {
            totalSent += sentThisTime;
            continue; // try again to send remaining bytes
        } else if (status == sf::Socket::Status::NotReady) {
            cerr << "Client: Socket not ready to send.\n";
            connected = false;
            break;
        } else if (status == sf::Socket::Status::Disconnected) {
            cerr << "Client: Disconnected from server.\n";
            connected = false;
            break;
        } else {
            cerr << "Client: Failed to send message.\n";
            break;
        }
    }
    return;
}

TcpClient::TcpClient(unsigned short port) : port(port) {}

bool TcpClient::connect() {
    sf::Socket::Status status = socket.connect(serverIp, port);
    if (status != sf::Socket::Status::Done) {
        cerr << "Connection to server failed.\n";
        return false;
    }

    socket.setBlocking(false);

    if (listener.listen(54000) != sf::Socket::Status::Done) {
        cerr << "Failed to bind server to port.\n";
        return false;
    }

    selector.add(listener);

    cout << "Connected to game server!\n";
    return true;
}

bool TcpClient::discoverServer() {
    sf::UdpSocket udp;
    udp.setBlocking(true);

    if (udp.bind(sf::Socket::AnyPort) != sf::Socket::Status::Done) {
        cerr << "Failed to bind UDP socket for discovery.\n";
        return false;
    }

    string message = "DISCOVER_SERVER";
    if (udp.send(message.c_str(), message.size(), sf::IpAddress::Broadcast, 54000) != sf::Socket::Status::Done) {
        cerr << "Failed to send discovery broadcast.\n";
        return false;
    }

    char response[128];
    unsigned short senderPort;
    size_t received = 0;
    optional<sf::IpAddress> senderIp;

    if (udp.receive(response, sizeof(response), received, senderIp, senderPort) == sf::Socket::Status::Done) {
        string reply(response, received);
        if (reply == "SERVER_HERE" && senderIp.has_value()) {
            serverIp = senderIp.value();
            std::cout << "Discovered server at: " << serverIp << std::endl;
            return true;
        }
    }

    cerr << "No discovery response received.\n";
    return false;
}

string TcpClient::update() {
    char buffer[1024];
    size_t received;
    sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);

    switch (status) {
        case sf::Socket::Status::Done: {
            string message(buffer, received);
            return message;
        }
        case sf::Socket::Status::NotReady:
            return "false";
        case sf::Socket::Status::Disconnected:
            cerr << "[Client::update] Disconnected from server.\n";
            socket.disconnect();
            return "false";
        case sf::Socket::Status::Error:
        default:
            cerr << "[Client::update] Error while receiving from server.\n";
            return "false";
            }
    return "false";
}

void TcpClient::sendMessage(const string& message) {
    size_t totalSent = 0;
    const char* data = message.c_str();
    size_t toSend = message.size();

    while (totalSent < toSend) {
        size_t sentThisTime;
        sf::Socket::Status status = socket.send(data + totalSent, toSend - totalSent, sentThisTime);

        if (status == sf::Socket::Status::Done) {
            totalSent += sentThisTime;
            connected = true;
        } else if (status == sf::Socket::Status::Partial) {
            totalSent += sentThisTime;
            continue; // try again to send remaining bytes
        } else if (status == sf::Socket::Status::NotReady) {
            cerr << "Client: Socket not ready to send.\n";
            connected = false;
            break;
        } else if (status == sf::Socket::Status::Disconnected) {
            cerr << "Client: Disconnected from server.\n";
            connected = false;
            break;
        } else {
            cerr << "Client: Failed to send message.\n";
            break;
        }
    }
    return;
}