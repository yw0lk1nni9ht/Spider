#include "request.h"

BaseRequest::BaseRequest(){

}
BaseRequest::~BaseRequest(){

}

std::string BaseRequest::GetRequestTest(){}



bool BaseRequest::TryToConnect(std::string url,std::string _target){}



int BaseRequest::GetResponseStatus(){}



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
