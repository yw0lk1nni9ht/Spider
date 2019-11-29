/**
* @projectName   Spider
* @brief         摘要
* @author        Ywin
* @date          2019-10-31
*/

#include "http_request.h"
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>
http_request::http_request()
{
}
http_request::~http_request()
{
    if(stream!= NULL)
    {
        //delete (beast::tcp_stream *)stream;
        delete stream;
        stream = NULL;
    }
}

/**
 * @brief http请求测试函数
 *
 * @return 返回说明
 *     -<em>string</em> fail
 *     -<em>string</em> succeed
 */
std::string http_request::GetRequestTest()
{
    try
    {
        auto const host = "www.nvshens.com";
        auto const port = "80";
        auto const target = "/";
        int version = 11;

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // ... read and write as normal ...
        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        //std::cout << req << std::endl;
        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if(ec && ec != beast::errc::not_connected)
            throw beast::system_error{ec};

        // If we get here then the connection is closed gracefully
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return "faile";
    }
    return "success";
}



/**
 * @brief 测试url是否有效，初始化成员stream
 * @param url       传入的url
 *
 * @return 返回说明
 *     -<em>false</em>  url无效
 *     -<em>true</em>   url有效
 */
bool http_request::TryToConnect(std::string url,std::string _target)
{
    try
    {
        host = url;
        auto const port = "80";
        target = _target;

        // IO上下文
        net::io_context ioc;

        // TCP分解器
        tcp::resolver resolver(ioc);

        //创建TCP流式结构
        if (stream == NULL)
        {
            stream = new beast::tcp_stream(ioc);
        }

        // 找到endpoint
        auto const results = resolver.resolve(host, port);
        // 通过我们找到的endpoint，与之建立socket连接
        beast::error_code ec;
        ((beast::tcp_stream*)stream)->connect(results,ec);
        if (ec.failed())
        {
            return false;
        }
        return true;
    }
    catch(std::exception e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}



/**
 * @brief 获取HTTP响应码,若为302，则记录重定向的url；记录body
 *
 * @return 返回说明
 *     -<em>int</em> http响应状态值
 */
int http_request::GetResponseStatus()
{
    try
    {
        if (stream == NULL)
        {
            throw "error:stream is NULL";
        }
        // 设置HTTP请求
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        //std::cout << req << std::endl;

        // 发送HTTP请求到远程主机
        http::write(*((beast::tcp_stream*)stream), req);

        // 创建buffer用于读取和写入持久化
        beast::flat_buffer buffer;

        // 声明一个容器用于保存响应
        http::response<http::string_body> res;

        // 接受HTTP响应并写入
        http::read(*((beast::tcp_stream*)stream), buffer, res);

        // 输出显示
        //std::cout << res << std::endl;
        _body = res.body();

        // 如果响应状态为302 301则记录下重定向的url
        if (((http::response_header<>)res.base()).result() == http::status::moved_permanently ||
                ((http::response_header<>)res.base()).result() == http::status::found)
        {
            _moveurl = std::string((res.at(http::field::location)).data());
        }

        // 关闭stream的Socket连接
        beast::error_code ec;
        ((beast::tcp_stream*)stream)->socket().shutdown(tcp::socket::shutdown_send, ec);
        if (ec)
        {
            std::cout << "An error occurred in shutdown socket." << std::endl;
        }
        //return (int)((http::response_header<>)res.base()).result();
        return (int)res.base().result();
    }
    catch (std::exception e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (int)http::status::unknown;
    }
}



std::string http_request::GetMoveUrl()
{
    return _moveurl;
}



std::string http_request::GetBodyData()
{
    return _body;
}
