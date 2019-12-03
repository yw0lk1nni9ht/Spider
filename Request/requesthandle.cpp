#include "requesthandle.h"
#include "http_request.h"
#include "https_request.h"
#include "request.h"
#include <boost/beast/http.hpp>

typedef void (*CallbackFun)(std::string data);
int UseToConnect(RequestHandle * _handle,CallbackFun _callback,BaseRequest * request,std::string host,std::string target);

RequestHandle::RequestHandle()
{

}



/**
 * @brief 请求连接处理
 * @param _callback     回调参数
 * @param url           url
 * @param ishttps       是否启用https
 *
 * @return 返回说明
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
int RequestHandle::Connect(CallbackFun _callback,std::string url,bool ishttps)
{
    //判断url最后的字符是否为/
    if(url[url.length()-1] != '/')
    {
        url.append("/");
    }

    // 初始化请求类实例,默认使用http
    BaseRequest * request = NULL;
    if(ishttps)
    {
        request = new https_request();
    }
    else {
        request = new http_request();
    }

    // 分离协议 主机 路径
    std::string host = "";
    std::string target = "/";
    if (url.find("://") != std::string::npos)
    {
        std::string del_head = url.substr(url.find("://") + 3);
        int host_end = del_head.find("/");
        host = del_head.substr(0,host_end);
        target  = del_head.substr(host_end);
    }
    else
    {
        int host_end = url.find("/");
        host = url.substr(0,host_end);
        target  = url.substr(host_end);
    }

    //尝试连接
    int RetConnect = UseToConnect(this,_callback,request,host,target);
    if (RetConnect != SUCCESS)
    {
        //连接失败则尝试使用另一种方式请求
        if(request != NULL)
        {
            delete request;
            request = NULL;
        }
        if(ishttps)
        {
            request = new http_request();
        }
        else {
            request = new https_request();
        }
        int RetSecdConnect = UseToConnect(this,_callback,request,host,target);
        if(RetSecdConnect != SUCCESS)
        {
            if(request != NULL)
            {
                delete request;
            }
            //判断url合法
            return URL_ERROR;
        }
        _callback(request->GetRes_BodyData());
        //std::cout << request->GetRes_BodyData() << std::endl;
    }
    else
        _callback(request->GetRes_BodyData());
        //std::cout << request->GetRes_BodyData() << std::endl;

    //结束释放资源
    if(request != NULL)
    {
        delete request;
    }
    //boost::beast::http::status
    //判断url合法
    return SUCCESS;
}



/**
 * @brief 请求连接
 * @param _handle       获取this指针，用于调用一些方法
 * @param _callback     回调方法,用于返回数据
 * @param request       请求连接实例
 * @param host          主机名
 * @param target        路径
 *
 * @return 返回说明
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
int UseToConnect(RequestHandle * _handle,CallbackFun _callback,BaseRequest * request,std::string host,std::string target)
{
    //判断URL是否可以连通
    bool IsConnected = request->TryToConnect(host,target);
    if(IsConnected)
    {
        int ret = request->GetRes_Status();
        //获取返回值，重定向
        if (ret == (int)boost::beast::http::status::moved_permanently || ret == (int)boost::beast::http::status::found)
        {
            if(request->GetRes_MoveUrl().find("https") != std::string::npos)
            {
                _handle->Connect(_callback,request->GetRes_MoveUrl(),true);
            }
            else if(request->GetRes_MoveUrl().find("http") != std::string::npos)
            {
                _handle->Connect(_callback,request->GetRes_MoveUrl(),false);
            }
            else
            {
                return _handle->URL_ConnectFail;
            }
            return _handle->URL_301_302;
        }
        else if((ret >= (int)boost::beast::http::status::bad_request
                && ret <= (int)boost::beast::http::status::network_connect_timeout_error)
                || ret == (int)boost::beast::http::status::unknown)
        {
            //错误状态码 300-599 或 异常状态 status::unknown
            return _handle->URL_ConnectFail;
        }
        return _handle->SUCCESS;
    }
    else {
        return _handle->URL_ConnectFail;
    }
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
        case URL_ConnectFail:
            ret = "URL连接失败";
            break;
        default:
            break;
    }
    return ret;
}
