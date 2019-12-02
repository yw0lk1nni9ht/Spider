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
    virtual std::string GetRes_MoveUrl();
    virtual std::string GetRes_BodyData();
    virtual int GetRes_Status();
protected:
    virtual int GetResponseStatus();
    std::string host;
    std::string port;
    std::string target = "/";
    int const version = 11;
    void * stream = NULL;
    std::string _moveurl = "";
    std::string _body = "";
    int _status = 0;
};
#endif // REQUEST_H


