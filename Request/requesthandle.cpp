#include "requesthandle.h"
#include "http_request.h"
#include "https_request.h"
#include "request.h"
#include <boost/beast/http.hpp>

enum ReturnNum {
    SUCCESS                 = 0x000,
    URL_ERROR               = 0x001,
    MyHTML_TAG__TEXT               = 0x001,
    MyHTML_TAG__COMMENT            = 0x002,
    MyHTML_TAG__DOCTYPE            = 0x003,
    MyHTML_TAG_A                   = 0x004
};

RequestHandle::RequestHandle()
{

}

/**
 * @brief 请求连接
 * @param url       参数1
 *
 * @return 返回说明
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
int RequestHandle::Connect(std::string url)
{
    //判断URL是否可以连通
    BaseRequest * request = new http_request();
    bool http_connect = request->TryToConnect(url,"/");
    if(http_connect)
    {
        int ret = request->GetResponseStatus();
        //获取返回值 ，重定向
        if (ret == (int)boost::beast::http::status::moved_permanently || ret == (int)boost::beast::http::status::found)
        {
            std::cout << request->GetMoveUrl() << std::endl;
            delete request;
            request = NULL;
            request = new https_request();
            (https_request*)request->TryToConnect(url,"/");
            (https_request*)request->GetResponseStatus();
            std::cout << request->GetBodyData() << std::endl;

        }
        else if((ret >= (int)boost::beast::http::status::bad_request
                && ret <= (int)boost::beast::http::status::network_connect_timeout_error)
                || ret == (int)boost::beast::http::status::unknown)
        {
            //错误状态码 300-599 或 异常状态 status::unknown
            return URL_ERROR;
        }
    }
    else
    {
//        bool https_connect = testhttps.TryToConnect(url);
//        if (https_connect)
//        {

//        }
//        else {
//            return URL_ERROR;
//        }
    }

    //boost::beast::http::status
    //判断url合法
    return SUCCESS;
}

std::string RequestHandle::GetRetMessage(int rettonum)
{
    std::string ret = "";
    switch (rettonum)
    {
        case SUCCESS:
            ret = "url可成功连接";
            break;
        case URL_ERROR:
            ret = "URL无法访问,检查是否正确";
            break;
        default:
            break;
    }
    return ret;
}
