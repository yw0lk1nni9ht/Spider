
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include <iostream>
//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>

class http_request
{
public:
    http_request();
    ~http_request();
    std::string GetRequestTest();
    bool TryToConnect(std::string url,std::string _target);
    int GetResponseStatus();
    std::string GetMoveUrl();
    std::string GetBodyData();
private:
    std::string host;
    std::string target = "/";
    int const version = 11;
    void * stream = NULL;
    std::string _moveurl = "";
    std::string _body = "";
};

#endif // HTTP_REQUEST_H
