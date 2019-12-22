#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <string>

#include "StartControl/DefaultSearch.h"
#include "StartControl/PersonIdSearch.h"
using namespace std;


int main()
{
    //DefaultSearch::start();
    PersonIDSearch::start();
}
