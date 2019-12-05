#ifndef REQUEST_H
#define REQUEST_H
#include<iostream>

class BaseRequest
{
public:
    BaseRequest();
    ~BaseRequest();
    virtual std::string GetRequestTest();
    virtual bool MakeConnect(std::string url);
    virtual int SendRequest(std::string url,std::string _target);
    virtual void CloseConnect();
    virtual bool GetConnected();
    virtual std::string GetConnectedHost();

    virtual std::string GetRes_MoveUrl();
    virtual std::string GetRes_BodyData();
    virtual int GetRes_Status();
protected:
    std::string host;
    std::string port;
    std::string target = "/";
    int const version = 11;
    void * stream = NULL;
    std::string _moveurl = "";
    std::string _body = "";
    int _status = 0;
    bool IsConnect = false;
};
#endif // REQUEST_H


