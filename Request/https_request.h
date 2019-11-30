#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H
#include <iostream>
#include <boost/beast/http.hpp>
class https_request
{
public:
    https_request();
    std::string GetRequestTest(std::string _host,std::string _target);
    bool TryToConnect(std::string url,std::string _target);
    int GetResponseStatus();
private:
    void GetSSLFile();

    std::string host;
    std::string port = "443";
    std::string target = "/";
    int const version = 11;
    void * stream = NULL;
    std::string _moveurl = "";
    std::string _body = "";
};

#endif // HTTPS_REQUEST_H
