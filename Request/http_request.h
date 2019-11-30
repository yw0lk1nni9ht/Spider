
#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include "request.h"
#include <iostream>
//#include <boost/beast/core.hpp>
//#include <boost/beast/http.hpp>

class http_request:public BaseRequest
{
public:
    http_request();
    ~http_request();
     std::string GetRequestTest() override;
     bool TryToConnect(std::string url,std::string _target) override;
     int GetResponseStatus() override;
     std::string GetMoveUrl() override;
     std::string GetBodyData() override;
//private:
//    std::string host;
//    std::string port = "80";
//    std::string target = "/";
//    int const version = 11;
//    void * stream = NULL;
//    std::string _moveurl = "";
//    std::string _body = "";
};

#endif // HTTP_REQUEST_H
