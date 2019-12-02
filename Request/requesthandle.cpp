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
int RequestHandle::Connect(std::string url,bool ishttps)
{
    BaseRequest * request = NULL;
    if(ishttps)
    {
        request = new https_request();
    }
    else {
        request = new http_request();
    }

    //判断URL是否可以连通
    bool IsConnected = request->TryToConnect(url,"/");
    if(IsConnected)
    {
        int ret = request->GetRes_Status();
        //获取返回值，重定向
        if (ret == (int)boost::beast::http::status::moved_permanently || ret == (int)boost::beast::http::status::found)
        {
            if(request->GetRes_MoveUrl().find("https") != std::string::npos)
            {
                Connect(request->GetRes_MoveUrl(),true);
            }
            else if(request->GetRes_MoveUrl().find("http") != std::string::npos)
            {
                Connect(request->GetRes_MoveUrl(),false);
            }
            else
            {
                return URL_ERROR;
            }
        }
        else if((ret >= (int)boost::beast::http::status::bad_request
                && ret <= (int)boost::beast::http::status::network_connect_timeout_error)
                || ret == (int)boost::beast::http::status::unknown)
        {
            //错误状态码 300-599 或 异常状态 status::unknown
            return URL_ERROR;
        }
        std::cout << request->GetRes_BodyData() << std::endl << std::endl << std::endl;
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



/**
 * @brief 获取返回值说明
 * @param rettonum    返回值
 *
 * @return 返回说明
 *     -<em>string</em>
 */
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
