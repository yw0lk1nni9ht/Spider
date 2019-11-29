#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H
#include <iostream>
#include <boost/beast/http.hpp>
class https_request
{
public:
    https_request();
    std::string GetRequestTest(std::string _host,std::string _target);
};

#endif // HTTPS_REQUEST_H
