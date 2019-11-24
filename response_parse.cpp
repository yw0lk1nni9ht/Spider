#include "response_parse.h"
#include <iostream>
#include <modest/finder/finder.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

mystatus_t serialization_callback(const char* data, size_t len, void* ctx);
mystatus_t serialization_callback2(const char* data, size_t len, void* ctx);
void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection);
std::string GetTagValue(const char* _attributeName);
std::string Tag = "";
myhtml_tag_id_t _tag_id = MyHTML_TAG__UNDEF;
response_parse::response_parse()
{

}

void response_parse::parse(std::string response)
{
    _tag_id = MyHTML_TAG_IMG;

    // basic init
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    // init tree
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    // parse html
    myhtml_parse(tree, MyENCODING_UTF_8, response.c_str(), strlen(response.c_str()));

    // get and print
    myhtml_collection_t *titles_list = myhtml_get_nodes_by_tag_id(tree, NULL, _tag_id, NULL);

    print_found_result("In First tree" , tree , titles_list);
}

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

mystatus_t serialization_callback2(const char* data, size_t len, void* ctx)
{
    std::string temp = std::string(data);
    Tag.append(temp);
    if(temp.compare(">") == 0)
    {
        // Get URL
        // example::  <a href="/girl/17886/" target="_blank">
        if (_tag_id == MyHTML_TAG_A)
        {
            std::cout << GetTagValue("href=\"") << std::endl;
        }

        //Get IMG url
        //example::  <img src="img/grey.gif" data-original="img/example.jpg" width="640" heigh="480">
        if (_tag_id == MyHTML_TAG_IMG)
        {
            //if exist "data-original" then get it, if not : get "src"
            std::string ret = GetTagValue("data-original=\"");
            if (ret == "")
            {
                ret = GetTagValue("src=\"");
            }
            std::cout << ret << std::endl;
        }
        std::cout << Tag << std::endl << std::endl;
        Tag = "";
    }

    return MyCORE_STATUS_OK;
}

void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection)
{
    if(collection) {
        printf("%s:\n", caption);

        for(size_t i = 0; i < collection->length; i++) {
            //printf("\n");
            myhtml_serialization_node_callback(collection->list[i], serialization_callback2, NULL);
        }

        printf("\n");
    }
    else {
        printf("%s: empty\n", caption);
    }
}

std::string GetTagValue(const char* _attributeName)
{
    if (Tag.find(_attributeName) != std::string::npos)
    {
        std::string temp = Tag.substr(Tag.find(_attributeName) + strlen(_attributeName));
        return temp.substr(0,temp.find("\""));
    }
    else
        return "";
}
