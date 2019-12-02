#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H
#include "request.h"
#include <iostream>


class http_request:public BaseRequest
{
public:
    http_request();
    ~http_request();
     std::string GetRequestTest() override;
     bool TryToConnect(std::string url,std::string _target) override;
     int GetResponseStatus() override;
};

#endif // HTTP_REQUEST_H
