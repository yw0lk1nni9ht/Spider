/**
* @projectName   Spider
* @brief         摘要
* @author        Ywin
* @date          2019-10-31
*/

#include "https_request.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
//md5
#include <fstream>
#include <openssl/md5.h>
//other
#include <iostream>
#include <cstdlib>
#include <string>
#include "stdio.h"

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

int get_file_md5(const std::string &file_name, std::string &md5_value);

https_request::https_request()
{
    port = "443";
}

https_request::~https_request()
{
    if(stream!= NULL)
    {
        //delete (beast::tcp_stream *)stream;
        delete stream;
        stream = NULL;
    }
}

/**
 * @brief https请求测试函数
 * @param _host     域名、主机名
 * @param _target   目标路径
 *
 * @return 返回说明
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
std::string https_request::GetRequestTest()
{
    try
    {
        auto const host = "www.nvshens.net";
        //auto host = _host;
        auto const port = "443";
        //auto target = _target;
        auto target = "/";
        int version = 11;

        // IO上下文
        net::io_context ioc;
        // SSL上下文是必需的，并保存证书
        ssl::context ctx(ssl::context::sslv23);


        /// 用命令行获取网站的ca证书
        /// command:openssl s_client -connect www.nvshens.net:443 </home/ywin  | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > remoteserver.pem
        //获取当前路径
        char buf[PATH_MAX];
        getcwd(buf, PATH_MAX);
        //拼接命令https_request
        std::string getPemFileCommand = "openssl s_client -connect ";
        getPemFileCommand.append(host);
        getPemFileCommand.append(":");
        getPemFileCommand.append(port);
        getPemFileCommand.append(" <");
        getPemFileCommand.append(buf);
        getPemFileCommand.append(" | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > ");
        getPemFileCommand.append(host);
        getPemFileCommand.append(".pem");
        FILE *wget;
        char ok_code[] = "ok";
        //char wget_content[1024];
        //wget=popen("openssl s_client -connect www.nvshens.net:443 </home/ywin/ | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > remoteserver.pem","r");
        wget = popen(getPemFileCommand.c_str(),"r");
        pclose(wget);

        /* CA证书的字符串
        //         // This holds the root certificate used for verification
        //         std::string const cert ="-----BEGIN CERTIFICATE-----\n"
        //                 "MIIFpzCCBI+gAwIBAgIQBGFzIoKLSce1CVmlIQdj8TANBgkqhkiG9w0BAQsFADBy\n"
        //                 "MQswCQYDVQQGEwJDTjElMCMGA1UEChMcVHJ1c3RBc2lhIFRlY2hub2xvZ2llcywg\n"
        //                 "SW5jLjEdMBsGA1UECxMURG9tYWluIFZhbGlkYXRlZCBTU0wxHTAbBgNVBAMTFFRy\n"
        //                 "dXN0QXNpYSBUTFMgUlNBIENBMB4XDTE5MDkyMDAwMDAwMFoXDTIwMDkxOTEyMDAw\n"
        //                 "MFowFjEUMBIGA1UEAxMLbnZzaGVucy5uZXQwggEiMA0GCSqGSIb3DQEBAQUAA4IB\n"
        //                 "DwAwggEKAoIBAQC6KYrMZUjPXXClE+lhbFAt85vwsLBYI9igHfVCHD/WOB83fDHb\n"
        //                 "ounb/WkNolM97hYGOGyjk3Z9vU4EvoMZMSkmO0+J+wcSRvglo7uDiIDHyqANCmZs\n"
        //                 "cl4xg0wpjHceMESAb2ya7g3oijIERLvaYe/e0EhPbGWgJtLTB1XcLH6B8ZHPO2ZK\n"
        //                 "wH/aCWJe7wplGMjlV/e0yY4BXI0hs5h+cPEl5AzT4ITvFl6JQc0PtvP8FBAGfmFL\n"
        //                 "+j97xVIh8SwVyjeT44dknH2rCaKnEkimwqXl8atDp/nqQ5IwU7rXOOqjRXmVcWaw\n"
        //                 "BRYyJ5FyCvsTAFCdjF/WJirsut45olw/lyvpAgMBAAGjggKTMIICjzAfBgNVHSME\n"
        //                 "GDAWgBR/05nzoEcOMQBWViKOt8ye3coBijAdBgNVHQ4EFgQUYnD9OiCMwf6kXsbV\n"
        //                 "Hos/Be0ALqcwJwYDVR0RBCAwHoILbnZzaGVucy5uZXSCD3d3dy5udnNoZW5zLm5l\n"
        //                 "dDAOBgNVHQ8BAf8EBAMCBaAwHQYDVR0lBBYwFAYIKwYBBQUHAwEGCCsGAQUFBwMC\n"
        //                 "MEwGA1UdIARFMEMwNwYJYIZIAiocYb9bAECMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8v\n"
        //                 "d3d3LmRpZ2ljZXJ0LmNvbS9DUFMwCAYGZ4EMAQIBMIGSBggrBgEFBQcBAQSBhTCB\n"
        //                 "gjA0BggrBgEFBQcwAYYoaHR0cDovL3N0YXR1c2UuZGlnaXRhbGNlcnR2YWxpZGF0\n"
        //                 "aW9uLmNvbTBKBggrBgEFBQcwAoY+aHR0cDovL2NhY2VydHMuZGlnaXRhbGNlcnR2\n"
        //                 "YWxpZGF0aW9uLmNvbS9UcnVzdEFzaWFUTFNSU0FDQS5jcnQwCQYDVR0TBAIwADCC\n"
        //                 "AQUGCisGAQQB1nkCBAIEgfYEgfMA8QB3ALvZ37wfinG1k5Qjl6qSe0c4V5UKq1Lo\n"
        //                 "GpCWZDaOHtGFAAABbU3AoPAAAAQDAEgwRgIhAOauUdn9A1AMPpIsk/WFXljOfKQv\n"
        //                 "Uh8e7qeTGD6jJz5JAiEA3/imwQovDVdjHnzUDc/2VMDqeLmkqAZ0iaRsRmKd9MwA\n"
        //                 "dgCHdb/nWXz4jEOZX73zbv9WjUdWNv9KtWDBtOr/XqCDDwAAAW1NwKFnAAAEAwBH\n"
        //                 "MEUCIErRyFF3A3XzgBzVQ7ndo0GRXOLiHMntuREgrzIAaa1sAiEAr1Y4fx3PV4jx\n"
        //                 "7A2z9wxi3XPJneGB3uRLboodtlUuIQowDQYJKoZIhvcNAQELBQADggEBAFviw0xU\n"
        //                 "ZvOAFdd8dauNp6Ezta0S8gN+5l56zbAybTvAR9oJdn3RP9zXmhdPKzdQfrEyrSnZ\n"
        //                 "jH6auvN6NdlLWsbKTDubclbvliocYChB2QiTzWn/D9DB+GrCaoJcEJQv/iy047ix3R+\n"
        //                 "taaO2CLUcH+dJZaBhANRxTVFxcTG9vwoOVhb7WVnPsLRXkEBzUcwroPSVItVTWk+\n"
        //                 "TySazAZdFEM2WVxaUl+TXRtz8K7G2Oq9aepeJ4kcGs0+Qe9DVkIZwiAROWlXtro4\n"
        //                 "DEz7U7+lyNJsvH0kIufH7luARValF/nQB4ptm8ovksbWWmWwXEj9QNh3mHahEZO3\n"
        //                 "OmGzGQ1NBwwqxrs=\n"
        //                 "-----END CERTIFICATE-----\n"
        //                 ;
        //         boost::system::error_code ec;
        //         ctx.add_certificate_authority(
        //             boost::asio::buffer(cert.data(), cert.size()), ec);         //load_root_certificates(ctx);
        */

        std::string targetPem = host;
        targetPem.append(".pem");
        ctx.load_verify_file((targetPem));

        // 验证远程服务器的证书
        ctx.set_verify_mode(ssl::verify_none);

        // TCP分解器
        tcp::resolver resolver(ioc);
        //创建TCP流式结构
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // 设置SNI主机名（许多主机需要此项才能成功握手）
        if(! SSL_set_tlsext_host_name(stream.native_handle(), host))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // 找到域名
        auto const results = resolver.resolve(host, port);
        // 连接
        beast::get_lowest_layer(stream).connect(results);

        // 执行SSL握手
        stream.handshake(ssl::stream_base::client);

        // 设置HTTP请求
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // 发送HTTP请求到远程主机
        http::write(stream, req);

        // 创建buffer用于读取和写入持久化
        beast::flat_buffer buffer;

        // 声明一个容器用于保存响应
        http::response<http::string_body> res;

        // 接受HTTP响应
        http::read(stream, buffer, res);

        // 输出显示
        std::cout << res << std::endl;

        // 关闭连接
        beast::get_lowest_layer(stream).close();
        beast::error_code ec2;
        stream.shutdown(ec2);
        if(ec2 == net::error::eof)
        {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec2 = {};
        }
        if(ec2)
        {

            return res.body();
            throw beast::system_error{ec2};
        }

        return res.body();
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}



/**
 * @brief 测试url是否有效，初始化成员stream
 * @param url       传入的url
 *
 * @return 返回说明
 *     -<em>false</em>  url无效
 *     -<em>true</em>   url有效
 */
bool https_request::TryToConnect(std::string url,std::string _target)
{
    try
    {
    host = url;
    target = _target;

    if (!GetSSLFile())
    {
        //下载SSL证书失败，或者
        return false;
    }

    // IO上下文
    net::io_context ioc;
    // SSL上下文是必需的，并保存证书
    ssl::context ctx(ssl::context::sslv23);

    //加载CA证书
    std::string targetPem = host;
    targetPem.append(".pem");
    ctx.load_verify_file((targetPem));

    // 选择验证远程服务器的证书的方式
    ctx.set_verify_mode(ssl::verify_none);

    // TCP分解器
    tcp::resolver resolver(ioc);
    //创建TCP流式结构
    if (stream == NULL)
    {
        stream = new beast::ssl_stream<beast::tcp_stream>(ioc,ctx);
    }

    // 设置SNI主机名（许多主机需要此项才能成功握手）
    if(! SSL_set_tlsext_host_name(((beast::ssl_stream<beast::tcp_stream>*)stream)->native_handle(), host.c_str()))
    {
        beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
        throw beast::system_error{ec};
    }

    // 找到域名
    auto const results = resolver.resolve(host, port);
    // 连接
    beast::get_lowest_layer(*((beast::ssl_stream<beast::tcp_stream>*)stream)).connect(results);

    // 执行SSL握手
    ((beast::ssl_stream<beast::tcp_stream>*)stream)->handshake(ssl::stream_base::client);

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
int https_request::GetResponseStatus()
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

        // 发送HTTP请求到远程主机
        http::write(*(beast::ssl_stream<beast::tcp_stream>*)stream, req);

        // 创建buffer用于读取和写入持久化
        beast::flat_buffer buffer;

        // 声明一个容器用于保存响应
        http::response<http::string_body> res;

        // 接受HTTP响应
        http::read(*(beast::ssl_stream<beast::tcp_stream>*)stream, buffer, res);

        // 输出显示
        //std::cout << res << std::endl;
        _body = res.body();

        // 如果响应状态为302 301则记录下重定向的url
        if (((http::response_header<>)res.base()).result() == http::status::moved_permanently ||
                ((http::response_header<>)res.base()).result() == http::status::found)
        {
            _moveurl = std::string((res.at(http::field::location)).data());
        }

        // 关闭连接
        beast::get_lowest_layer(*(beast::ssl_stream<beast::tcp_stream>*)stream).close();
        beast::error_code ec2;
        ((beast::ssl_stream<beast::tcp_stream>*)stream)->shutdown(ec2);
        if(ec2 == net::error::eof)
        {
            // Rationale:
            // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
            ec2 = {};
        }
        if(ec2)
        {
            return (int)res.base().result();
            throw beast::system_error{ec2};
        }
        return (int)res.base().result();
    }
    catch (std::exception e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (int)http::status::unknown;
    }
}



/**
 * @brief 下载网站CA证书
 *
 * @return 返回说明
 *     -<em>void</em> void
 */
bool https_request::GetSSLFile()
{
    std::string filename = host + ".pem";
    std::fstream _file;
    _file.open(filename, std::ios::in);
    if(_file)
    {
        //已经存在!
        _file.close();
        return true;
    }
    else
    {
        //没有被创建!
        _file.close();
    }

    /// 用命令行获取网站的ca证书
    /// command:openssl s_client -connect www.nvshens.net:443 </home/ywin  | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > remoteserver.pem
    //获取当前路径
    char buf[PATH_MAX];
    getcwd(buf, PATH_MAX);
    //拼接命令
    std::string getPemFileCommand = "openssl s_client -connect ";
    getPemFileCommand.append(host);
    getPemFileCommand.append(":");
    getPemFileCommand.append(port);
    getPemFileCommand.append(" <");
    getPemFileCommand.append(buf);
    getPemFileCommand.append(" | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > ");
    getPemFileCommand.append(host);
    getPemFileCommand.append(".pem");
    FILE *wget;
    char ok_code[] = "ok";
    //char wget_content[1024];
    //wget=popen("openssl s_client -connect www.nvshens.net:443 </home/ywin/ | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' > remoteserver.pem","r");
    wget = popen(getPemFileCommand.c_str(),"r");
    pclose(wget);

    std::ifstream is;
    is.open (filename, std::ios::binary);
    // 获取文件字节
    is.seekg (0, std::ios::end);
    int length = is.tellg();
    is.seekg (0, std::ios::beg);
    is.close();
    if (length <= 0)
    {
        remove(filename.c_str());
        return false;
    }
    else
    {
        return true;
    }
}



/**
 * @brief 获取文件的md5
 * @param index    参数1
 *
 * @return 返回说明
 *     -<em>false</em> fail
 *     -<em>true</em> succeed
 */
int get_file_md5(const std::string &file_name, std::string &md5_value)
{
    md5_value.clear();

    std::ifstream file(file_name.c_str(), std::ifstream::binary);
    if (!file)
    {
        return -1;
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);

    char buf[1024 * 16];
    while (file.good()) {
        file.read(buf, sizeof(buf));
        MD5_Update(&md5Context, buf, file.gcount());
    }

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5_Final(result, &md5Context);

    char hex[35];
    memset(hex, 0, sizeof(hex));
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    {
        sprintf(hex + i * 2, "%02x", result[i]);
    }
    hex[32] = '\0';
    md5_value = std::string(hex);

    return 0;
}



