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
     bool MakeConnect(std::string url) override;
     int SendRequest(std::string url,std::string _target) override;
     int SendRequestWithParam(std::string url,std::string _target,std::string _param) override;
     void CloseConnect() override;
private :
};

#endif // HTTP_REQUEST_H
