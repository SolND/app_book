#ifndef _RECORD_H
#define _RECORD_H
#include <string>

struct record 
{
    std::string name;
    std::string address;
    int birth_year;
    std::string phone_number;
    struct record* next;
};
#endif