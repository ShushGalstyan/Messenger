#ifndef PACKAGING_H
#define PACKAGING_H

#include <string>
#include <sstream>
#include <deque>
#include <vector>
#include <iterator>
class Packaging {
public:
    Packaging();
    Packaging(const std::string& receiver, std::size_t pckglength, const std::string& message, const std::string& sender);
    Packaging(std::size_t pckglength, const std::string& message, const std::string& sender);
    virtual ~Packaging();

    std::string createLoginPackage(const std::string& username);

    std::string createSimplePackage();

    std::string createDisconnectPackage();

    std::string createGlobalPackage(const std::string& message, const std::string& sender);

    std::string createPivatePackage(const std::string& receiver, const std::string& message, const std::string& sender);

    std::string createOnlineUsersPackage(const std::vector<std::string>& onlineUsers);


    void parsePackage(std::string package);


    std::string identifyRequest(std::string package);

    std::string getMessage() const { return message; }
    std::string getSender() const { return sender; }
    std::string getReceiver() const { return receiver; }
    size_t getPckglength() const { return pckglength; }

private:
    std::string receiver;
    std::size_t pckglength;
    std::string message;
    std::string sender;

    const char glue = '|';

    std::string constructPackage();
};

#endif /* PACKAGING_H */
