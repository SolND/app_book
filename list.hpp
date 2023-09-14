#ifndef _LIST_H
#define _LIST_H

#include <string>
#include <iostream>

typedef struct record records;

class List 
{
public:
    List();
    List(const std::string &file);
    ~List();
    int add_record(std::string input_name, std::string input_address, int input_birth_year, std::string input_phone_number);
    int print_record(std::string input_name);
    int modify_record(std::string input_name, std::string input_address, std::string input_phone_number);
    void print_all_records();
    int delete_record(std::string input_name);
    void reverse_list();

private:
    records *start;
    std::string file_name;
    int read_file();
    int write_file();
    records* reverse_list(records* index);
    void delete_all_records();


};
#endif