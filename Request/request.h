#ifndef REQUEST_H
#define REQUEST_H
#include<iostream>

class BaseRequest
{
public:
    BaseRequest();
    ~BaseRequest();
    virtual std::string GetRequestTest();
    virtual bool TryToConnect(std::string url,std::string _target);
    virtual int GetResponseStatus();
    virtual std::string GetMoveUrl();
    virtual std::string GetBodyData();
protected:
    std::string host;
    std::string port;
    std::string target = "/";
    int const version = 11;
    void * stream = NULL;
    std::string _moveurl = "";
    std::string _body = "";

};
#endif // REQUEST_H


