
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
    std::string GetRequest();
    bool TryToConnect(std::string url);
    int GetRetData();
    std::string GetMoveUrl();
private:
    std::string host;
    std::string target = "/";
    int const version = 11;
    void * stream = NULL;
    std::string _moveurl = "";
};

#endif // HTTP_REQUEST_H
