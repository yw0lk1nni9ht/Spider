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

std::string http_request::GetRequest()
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

bool http_request::TryToConnect(std::string url)
{
    try
    {
        host = url;
        auto const port = "80";
        target = "/";

        // The io_context is required for all I/O
        net::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        //beast::tcp_stream stream(ioc);
        //_stream = (void*)&stream;
        stream = new beast::tcp_stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);
        // Make the connection on the IP address we get from a lookup
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

int http_request::GetRetData()
{
    try
    {
        if (stream == NULL)
        {
            throw "stream is NULL";
        }
        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
        //std::cout << req << std::endl;

        // Send the HTTP request to the remote host
        http::write(*((beast::tcp_stream*)stream), req);

        // This buffer is used for reading and must be writepersisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::string_body> res;

        // Receive the HTTP responsewrite
        http::read(*((beast::tcp_stream*)stream), buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;
        //std::cout << (int)(((http::response_header<>)res.base()).result()) << std::endl;
        if (((http::response_header<>)res.base()).result() == http::status::moved_permanently ||
                ((http::response_header<>)res.base()).result() == http::status::found)
        {
            //_moveurl = ((http::response_header<>)res.base()).reason();
            std::cout << res[http::field::location] << std::endl;
        }
        // Gracefully close the socket
        beast::error_code ec;
        ((beast::tcp_stream*)stream)->socket().shutdown(tcp::socket::shutdown_send, ec);
        if (ec)
        {
            std::cout << "An error occurred in shutdown socket." << std::endl;
        }
        return (int)((http::response_header<>)res.base()).result();
        //return res.body();
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
