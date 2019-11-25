#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H
#include <iostream>
#include <boost/beast/http.hpp>
class https_request
{
public:
    https_request();
    std::string GetRequest(char* _host,char* _target);
};

#endif // HTTPS_REQUEST_H
