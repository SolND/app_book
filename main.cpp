#include <iostream>
#include <string>
#include "book.hpp"

int main(int argc, char *argv[]) 
{

    if (argc > 1) 
    {
        std::cout << "Application does not take arguments." << std::endl;
        return -1;
    } 

    std::cout << "********************\n";
    std::cout << "Welcome User!\n";
    std::cout << "--------------------\n";
    run_program();
    std::cout << "--------------------\n";
    std::cout << "App terminated\n";
    std::cout << "********************\n";
    return 0;
}
