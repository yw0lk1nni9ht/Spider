#ifndef RESPONSE_PARSE_H
#define RESPONSE_PARSE_H
#include <iostream>
#include <modest/finder/finder.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

class response_parse
{
public:
    response_parse();
    void parse(std::string response,int id);
private:
    myhtml_tag_id_t _tag_id = MyHTML_TAG__UNDEF;
    std::string Tag = "";
    mystatus_t ResolveTag(const char* data, size_t len, void* ctx);
    void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection);
};

#endif // RESPONSE_PARSE_H
