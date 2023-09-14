#include <fstream>
#include "record.h"
#include "list.hpp"
#include "book.hpp"

List::List()
{
    int record_read = 0;

    start = NULL;

    file_name = "note.txt";

    record_read = read_file();

    if(record_read < 0)
    {
        std::cout << "'" << file_name << " không tìm thấy.\n";
         std::cout << "Do đó, không có bản ghi nào được thêm vào danh sách và '" << file_name << "' sẽ được tạo.\n";
    } 
    else if (record_read == 0) 
    {
         std::cout << "'" << file_name << "' đã được tìm thấy nhưng trống.\n";
         std::cout << "Do đó, không có bản ghi nào được thêm vào cơ sở dữ liệu.\n";
    } else { 
         std::cout << "'" << file_name << "' đã được đọc. " << record_read << " các bản ghi đã được thêm vào cơ sở dữ liệu.\n";
    } 
    std::cout << "--------------------\n";
}

List::List(const std::string &file)
{
    int record_read = 0;

    start = NULL;

    file_name = file;

    record_read = read_file();

    if(record_read < 0)
    {
        std::cout << "'" << file_name << " không tìm thấy.\n";
         std::cout << "Do đó, không có bản ghi nào được thêm vào danh sách và '" << file_name << "' sẽ được tạo.\n";
    } else if (record_read == 0) 
    {
         std::cout << "'" << file_name << "' đã được tìm thấy nhưng trống.\n";
         std::cout << "Do đó, không có bản ghi nào được thêm vào cơ sở dữ liệu.\n";
    } else { 
         std::cout << "'" << file_name << "' đã được đọc. " << record_read << " các bản ghi đã được thêm vào cơ sở dữ liệu.\n";
     } 
    std::cout << "--------------------\n";
}

List::~List()
{
    write_file();
    delete_all_records();
}

int List::read_file()
{
    std::ifstream read_file(file_name.c_str());
    records *temp = NULL;
    records *index = NULL;
    records *previous = NULL;
    int file_length = 0;
    int record_count = 0;
    std::string dummy = "";

    if(!read_file.is_open())
    {
        read_file.close();
        return -1;
    }

    read_file.seekg(0, read_file.end); // move read pointer to end of file
    file_length = read_file.tellg(); // return file pointer position
    if (file_length == 0) {
        read_file.close();
        return 0;
    }
    read_file.seekg(0, read_file.beg);
    do {
        temp = new record;
        index = start;
        std::getline(read_file, temp->name);
        std::getline(read_file, temp->address, '$');
        read_file >> temp->birth_year;
        std::getline(read_file, dummy);
        std::getline(read_file, temp->phone_number);
        std::getline(read_file, dummy);
        ++record_count;

        while (index != NULL) {
            previous = index;
            index = index->next;
        } 

        if (previous == NULL) {
            temp->next = start;
            start = temp;
        } 
        else { 
            previous->next = temp;
            temp->next = index;
        } 
    } while (!read_file.eof());
    read_file.close();
    return record_count;
}

int List::write_file() 
{
    std::ofstream write_file(file_name.c_str());
    records *index = start;
    int record_count = 0;

    if (start == NULL) {
        std::cout << "Cơ sở dữ liệu trống rỗng. Do đó, không có bản ghi nào được thêm vào file: " << file_name << '\n';
        write_file.close();
        return -1;
    }
    do {
        write_file << index->name << "\n";
        write_file << index->address << "$" << "\n";
        write_file << index->birth_year << "\n";
        if (index->next != NULL) {
            write_file << index->phone_number << "\n\n";
        } else { 
            write_file << index->phone_number << "\n";
        } 
        index = index->next;
        ++record_count;
    } while (index != NULL); 
    std::cout << record_count << " hồ sơ đã được ghi vào file " << file_name << "\n";
    write_file.close();
    return 0;
}

records* List::reverse_list(records *index) 
{

    records *next = NULL;

    if (index->next == NULL) {
        start = index;
        return start;
    }
    reverse_list(index->next);
    next = index->next;
    index->next = NULL;
}

void List::delete_all_records() 
{
    records *temp = start;
    records *index = NULL;
    int records_deleted = 0;

    std::cout << "--------------------\n";
    if (start != NULL) {
        while (index != NULL) {
            temp = index;
            index = index->next;
            start = index;
            delete temp;
            ++records_deleted;
        } 
        std::cout << records_deleted << " bản ghi bị xóa khỏi bộ nhớ.\n";
    } else { 
        std::cout << "Cơ sở dữ liệu trống. Vì vậy, không có hồ sơ nào bị xóa.\n";
    }
    std::cout << "--------------------\n";
    return; 
}
int List::add_record(std::string input_name, std::string input_address, int input_birth_year, std::string input_phone_number) 
{
    records *temp = NULL;
    records*index = start;
    records *previous = NULL;

    temp = new record;
    temp->name = input_name;
    temp->address = input_address;
    temp->birth_year = input_birth_year;
    temp->phone_number = input_phone_number;
    while (index != NULL) {
        previous = index;
        index = index->next;
    }
    if (previous == NULL) {
        temp->next = start;
        start = temp;
    } else { 
        previous->next = temp;
        temp->next = index;
    } 
    std::cout << "--------------------\n";
    std::cout << "Bản ghi đã được thêm vào.\n";
    std::cout << "--------------------\n";
    return 1; 
}

int List::print_record(const std::string &input_name) {
    records *index = start;
    int records_printed = 0;

    std::cout << "--------------------\n";
    if (start == NULL) {
        std::cout << "Cơ sở dữ liệu trống. Vì vậy, không có hồ sơ nào " << input_name << " tồn tại.\n";
        std::cout << "--------------------\n";
        return -1;
    } 
    while (index != NULL) {
        if (input_name == index->name) {
            ++records_printed;
            std::cout << "====================\n";
            std::cout << "Record #" << records_printed << " of:\n";
            std::cout << "Name: " << index->name << "\n";
            std::cout << "Address: " << index->address << '\n';
            std::cout << "Year of Birth: " << index->birth_year << '\n';
            std::cout << "Telephone Number: " << index->phone_number << '\n';
        } 
        index = index->next;
    } 

    if (records_printed == 0) {
        std::cout << "Không tìm thấy hồ sơ của " << input_name << ".\n";
    } else { 
        std::cout << records_printed << " hồ sơ của " << input_name << " in." << '\n';
    } 
    std::cout << "--------------------\n";
    return 1; 
}

int List::modify_record(std::string input_name, std::string input_address, std::string input_phone_number) 
{
    records *index = start;
    int records_modified = 0;

    std::cout << "--------------------\n";
    if (start == NULL) {
        std::cout << "Cơ sở dữ liệu trống. Vì vậy, không có hồ sơ nào về " << input_name << " tồn tại.\n";
        std::cout << "--------------------\n";
        return -1;
    }
    while (index != NULL) {
        if (input_name == index->name) {
            index->address = input_address;
            index->phone_number = input_phone_number;
            ++records_modified;
        } 
        index = index->next;
    } 
    if (records_modified == 0) {
        std::cout << "Không tìm thấy hồ sơ của " << input_name << ".\n";
    } else {
        std::cout << records_modified << " hồ sơ của " << input_name << " hồ sơ được sửa đổi.\n";
    } 
    std::cout << "--------------------\n";
    return 1; 
}

void List::print_all_records() {

    records *index = start;
    int record_count = 0;

    std::cout << "--------------------\n";
    if (start == NULL) {
        std::cout << "Cơ sở dữ liệu trống. Vì vậy, không có bản ghi nào được in.\n";
        std::cout << "--------------------\n";
        return; 
    } 
    while (index != NULL) {
        ++record_count;
        std::cout << "====================\n";
        std::cout << "Record #" <<  record_count << '\n';
        std::cout << "Name: " <<  index->name << '\n';
        std::cout << "Address: " <<  index->address << '\n';
        std::cout << "Year of Birth: " << index->birth_year << '\n';
        std::cout << "Telephone Number: " << index->phone_number << '\n';
        index = index->next;
    }
    std::cout << record_count << " Records printed.\n";
    std::cout << "--------------------\n";
    return;
}

int List::delete_record(std::string input_name) 
{
    records *temp = NULL;
    records *index = start;
    records *previous = NULL;
    int records_deleted = 0;

    std::cout << "--------------------\n";
    if (start == NULL) {
        std::cout << "Cơ sở dữ liệu trống. Vì vậy, không có hồ sơ nào về " << input_name << " tồn tại.\n";
        std::cout << "--------------------\n";
        return -1; 
    }
    while (index != NULL) {
        if (input_name == index->name) {
            temp = index;
            if (index == start) { 
                index = index->next;
                start = index;
            } else { 
                index = index->next;
                previous->next = index;
            } 
            delete temp;
            ++records_deleted;
        } else { 
            previous = index;
            index = index->next;
        } 
    } 
    if (records_deleted == 0) {
        std::cout << "Không tìm thấy hồ sơ của " << input_name << " .\n";
    } else { 
        std::cout << records_deleted << " hồ sơ của " << input_name << " hồ sơ đã bị xóa.\n";
    }
    std::cout << "--------------------\n";
    return 1; 
}

void List::reverse_list() 
{
    std::cout << "--------------------\n";
    if (start == NULL) {
        std::cout << "Cơ sở dữ liệu trống. Vì vậy, không có bản ghi nào có thể đảo ngược danh sách.\n";
    } else if (start->next == NULL) {
        std::cout << "Chỉ có một bản ghi tồn tại trong cơ sở dữ liệu. Tại sao bạn lại cố gắng đảo ngược một bản ghi?.\n";
    } else { 
        reverse_list(start);
        std::cout << "Tất cả hồ sơ đã bị đảo ngược.\n";
    }
    std::cout << "--------------------\n";
    return; 
}
