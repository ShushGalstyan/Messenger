#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User() {} 
    User(const std::string& username) { this->username = username;}
    virtual ~User() {} 

    std::string getUsername() const { return username; }

private:
    std::string username = " ";
};

#endif /* USER_H */
