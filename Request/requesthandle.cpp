#include "requesthandle.h"
#include "http_request.h"

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
    http_request testhttp;
    if(!testhttp.TryToConnect(url))
    {
        return URL_ERROR;
    }

    //获取返回值

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
