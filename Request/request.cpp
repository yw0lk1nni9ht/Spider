#include "request.h"

BaseRequest::BaseRequest(){

}
BaseRequest::~BaseRequest(){

}

std::string BaseRequest::GetRequestTest(){}
bool BaseRequest::TryToConnect(std::string url,std::string _target){}
int BaseRequest::GetResponseStatus(){}
std::string BaseRequest::GetMoveUrl(){}
std::string BaseRequest::GetBodyData(){}
