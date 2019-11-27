
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
    std::string GetRetData();
private:
    std::string host;
    std::string target = "";
    int const version = 11;
    //boost::beast::tcp_stream *stream = NULL;
    void * stream = NULL;
};

#endif // HTTP_REQUEST_H
