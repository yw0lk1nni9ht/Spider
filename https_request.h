#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H
#include <iostream>
#include <boost/beast/http.hpp>
class https_request
{
public:
    https_request();
    boost::beast::http::response<boost::beast::http::dynamic_body> GetRequest(char* _host,char* _target);
};

#endif // HTTPS_REQUEST_H
