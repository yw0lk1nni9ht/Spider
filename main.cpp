#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <string>
#include "http_request.h"
#include "https_request.h"
#include "mycss/api.h"
using namespace std;
//using namespace boost;


int main()
{
    //string command_rd = "ifconfig";
    //system(command_rd.c_str());
    char *css = "#ident [name=\"best-name\"] {rgba(0, 0, 0, 0.1);}";

       // base init
       mycss_t *mycss = mycss_create();
       auto status = mycss_init(mycss);

       // current entry, work init
       mycss_entry_t *entry = mycss_entry_create();
       status = mycss_entry_init(mycss, entry);

       mycss_parse(entry, MyENCODING_UTF_8, css, strlen(css));

       // release resurces
       mycss_entry_destroy(entry, true);
       mycss_destroy(mycss, true);
    //http_request test2;
    https_request test2;
    boost::beast::http::response<boost::beast::http::string_body> response =  test2.GetRequest("www.nvshens.net","/") ;
    string a = response.body();
    std::cout << response.body() << std::endl;


}
