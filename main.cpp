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

using namespace std;
//using namespace boost;


int main()
{
    //string command_rd = "ifconfig";
    //system(command_rd.c_str());

    //http_request test2;
    https_request test2;
    test2.GetRequest();

}
