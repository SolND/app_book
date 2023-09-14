#include "book.hpp"
#include "record.h"
#include "list.hpp"
#include <string>

void run_program()
{
    List records(get_file_name());
    std::string input_name = "";
    std::string input_address = "";
    std::string input_phone = "";
    std::string dummy = "";
    int input_year = 0;
    int menu_select = 0;

    display_commands();
    do
    {
        menu_select = get_menu_select();
        switch(menu_select)
        {
            case 1: 
                std::cout << "--------------------\n";
                std::cout << "Thêm bản ghi mới\n";
                input_name = get_name();
                input_address = get_address();
                input_year = get_birth_year();
                input_phone = get_phone_number();
                records.add_record(input_name, input_address, input_year, input_phone);
                break;
            case 2: 
                std::cout << "--------------------\n";
                std::cout << "In dữ liệu với tên đã cho\n";
                input_name = get_name();
                records.print_record(input_name);
                break; 
            case 3: 
                std::cout << "--------------------\n";
                std::cout << "Sửa đổi dữ liệu với tên đã cho\n";
                input_name = get_name();
                input_address = get_address();
                std::getline(std::cin, dummy);
               
                input_phone = get_phone_number();
                records.modify_record(input_name, input_address, input_phone);
                break; 
            case 4: 
                std::cout << "--------------------\n";
                std::cout << "In tất cả trong danh sách...\n";
                records.print_all_records();
                break;
            case 5: 
                std::cout << "--------------------\n";
                std::cout << "Xóa tên hiện có\n";
                input_name = get_name();
                records.delete_record(input_name);
                break; 
            case 6: 
                std::cout << "--------------------\n";
                std::cout << "Đảo ngược từ danh sách liên kết...\n";
                records.reverse_list();
        }
        if (menu_select != 7) {
            display_commands();
        }
    }while(menu_select != 7);
}

void display_commands() 
{
    std::cout << "Cách sử dụng:\n";
    std::cout << "\t1: Thêm bản ghi mới vào cơ sở dữ liệu.\n";
    std::cout << "\t2: In thông tin về bản ghi sử dụng tên làm khóa. \n";
    std::cout << "\t3: Sửa đổi một bản ghi trong cơ sở dữ liệu bằng cách sử dụng tên làm khóa. \n";
    std::cout << "\t4: In tất cả thông tin trong cơ sở dữ liệu.\n";
    std::cout << "\t5: Xóa bản ghi hiện có khỏi cơ sở dữ liệu.\n";
	std::cout << "\t6: Đảo ngược thứ tự của tất cả các bản ghi hiện có trong cơ sở dữ liệu.\n";
    std::cout << "\t7: Thoát khỏi chương trình.\n";

    return; 
}

std::string get_name()
{
    std::string name = "";
    
    std::cin.clear();
    // std::cin.ignore(256, '\n');
    std::cout << "Xin vui lòng nhập tên của người dùng: ";
    std::getline(std::cin, name);

    return name;
}

std::string get_address()
{
    std::string addr = "";

    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cout << "Xin vui lòng nhập địa chỉ của người dùng(Nhập ; khi đã hoàn tất): ";
    std::getline(std::cin, addr, ';');

    return addr;
}

int get_birth_year()
{
    int birth_year = 0;

    std::cout << "Xin vui lòng nhập năm sinh của người dùng: ";
    std::cin >> birth_year;
    while (std::cin.fail()) 
    {
        std::cout << "Không phải là số nguyên, xin vui lòng nhập lại: ";
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> birth_year;
    }
    std::cin.clear();
    std::cin.ignore(256, '\n');
    return birth_year;
}

std::string get_phone_number()
{
    std::string phone_number = "";

    std::cin.clear();
    std::cout << "Xin vui lòng nhập số điện thoại liên hệ của người dùng: ";
    std::getline(std::cin, phone_number);
    return phone_number;
}

std::string get_file_name()
{
    std::string file_name = "";
    int count;

    std::cin.clear();
    std::cout << "Xin vui lòng nhập tệp tin của bạn(đuôi file là '.txt' sẽ đuợc tự động thêm vào: ";
    std::getline(std::cin, file_name);
    file_name += ".txt";

    return file_name;
}

int get_menu_select()
{
    int select = 0;
    std::cout << "Nhap su lua chon cua ban: ";
    std::cin >> select;

    while(std::cin.fail() || select < 1 || select > 7)
    {
        if(std::cin.fail())
        {
            std::cout << "Lỗi! Xin vui lòng nhập một số nguyên: ";

        }
        else if(select < 1 || select > 7)
        {
            std::cout << "Lựa chọn không hợp lệ.\n";
            display_commands();
        }
        std::cin.clear();
        std::cin.ignore(256, '\n');
        std::cin >> select;
    }
    std::cin.clear(); //clear buffer
    return select;
}
