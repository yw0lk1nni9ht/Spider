/**
* @projectName   Spider
* @brief         摘要
* @author        Ywin
* @date          2019-10-31
*/

#include "https_request.h"
#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <string>

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
namespace ssl = net::ssl;       // from <boost/asio/ssl.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>


https_request::https_request()
{

}

boost::beast::http::response<boost::beast::http::string_body> https_request::GetRequest(char* _host,char* _target)
{
    try
    {
        //auto const host = "www.nvshens.net";
        auto host = _host;
        auto const port = "443";
        //auto const target = "/";
        auto target = _target;
        int version = 11;

        // The io_context is required for all I/O
        net::io_context ioc;
        // The SSL context is required, and holds certificates
        ssl::context ctx(ssl::context::sslv23);


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
        //                 "MEwGA1UdIARFMEMwNwYJYIZIAYb9bAECMCowKAYIKwYBBQUHAgEWHGh0dHBzOi8v\n"
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
        //                 "jH6auvN6NdlLWsbKTDubclbvlYChB2QiTzWn/D9DB+GrCaoJcEJQv/iy047ix3R+\n"
        //                 "taaO2CLUcH+dJZaBhANRxTVFxcTG9vwoOVhb7WVnPsLRXkEBzUcwroPSVItVTWk+\n"
        //                 "TySazAZdFEM2WVxaUl+TXRtz8K7G2Oq9aepeJ4kcGs0+Qe9DVkIZwiAROWlXtro4\n"
        //                 "DEz7U7+lyNJsvH0kIufH7luARValF/nQB4ptm8ovksbWWmWwXEj9QNh3mHahEZO3\n"
        //                 "OmGzGQ1NBwwqxrs=\n"
        //                 "-----END CERTIFICATE-----\n"
        //                 ;
        //         boost::system::error_code ec;
        //         ctx.add_certificate_authority(
        //             boost::asio::buffer(cert.data(), cert.size()), ec);         //load_root_certificates(ctx);

        std::string targetPem = host;
        targetPem.append(".pem");
        //ctx.load_verify_file("nvshens_net.pem");
        ctx.load_verify_file((targetPem));

        // Verify the remote server's certificate
        ctx.set_verify_mode(ssl::verify_none);

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::ssl_stream<beast::tcp_stream> stream(ioc, ctx);

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if(! SSL_set_tlsext_host_name(stream.native_handle(), host))
        {
            beast::error_code ec{static_cast<int>(::ERR_get_error()), net::error::get_ssl_category()};
            throw beast::system_error{ec};
        }

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(stream).connect(results);

        // Perform the SSL handshake

        stream.handshake(ssl::stream_base::client);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{http::verb::get, target, version};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::string_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;
        // Gracefully close the stream
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

            return res;
            throw beast::system_error{ec2};
        }
        // If we get here then the connection is closed gracefully
        return res;
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        //return "faile";
    }
    //return "success";
}
