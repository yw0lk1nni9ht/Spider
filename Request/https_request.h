#ifndef HTTPS_REQUEST_H
#define HTTPS_REQUEST_H
#include "request.h"
#include <iostream>


class https_request:public BaseRequest
{
public:
    https_request();
    ~https_request();
    std::string GetRequestTest() override;
    bool TryToConnect(std::string url,std::string _target) override;
    int GetResponseStatus() override;

private:
    bool GetSSLFile();
};

#endif // HTTPS_REQUEST_H
