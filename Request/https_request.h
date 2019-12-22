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
    bool MakeConnect(std::string url) override;
    int SendRequest(std::string url,std::string _target) override;
    int SendRequestWithParam(std::string url,std::string _target,std::string _param) override;
    void CloseConnect() override;
private:
    bool GetSSLFile();
};

#endif // HTTPS_REQUEST_H
