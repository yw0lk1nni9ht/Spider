
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <iostream>

class http_request
{
public:
    http_request();
    std::string GetRequest();
    bool TryToConnect(std::string url);
    std::string GetRetData();
private:
    std::string host;
    std::string target = "";
    int const version = 11;
    void *stream;

};

#endif // HTTP_REQUEST_H
