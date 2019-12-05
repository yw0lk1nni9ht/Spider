#include "request.h"

BaseRequest::BaseRequest(){

}
BaseRequest::~BaseRequest(){

}

std::string BaseRequest::GetRequestTest(){}



bool BaseRequest::MakeConnect(std::string url){}



int BaseRequest::SendRequest(std::string url,std::string _target){}



void BaseRequest::CloseConnect(){}



bool BaseRequest::GetConnected(){
    return IsConnect;
}



std::string BaseRequest::GetConnectedHost()
{
    return host;
}



std::string BaseRequest::GetRes_MoveUrl()
{
    return _moveurl;
}



std::string BaseRequest::GetRes_BodyData()
{
    return _body;
}



int BaseRequest::GetRes_Status(){
    return _status;
}
