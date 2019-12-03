// To compile, run:
// g++ --std=c++11 main.cpp dialog_manager.cpp dialog_entry.cpp -I/usr/include/libxml2 -lxml2 -g -DDEBUG

#include "dialog_entry.h"
#include "dialog_manager.h"
#include "variable_manager.h"

#include <iostream>

int main(int argc, char **argv)
{
    int i = 0;
    DialogManager *de = DialogManager::Instance();
    VariableManager *ve = VariableManager::Instance();
    ve->registerVariable("myInt", &i);
    de->parse("dialog.xml");
    
    DialogEntry *temp = de->current();
    std::string input;
    while (temp) {
        std::cout << temp->text().c_str();
        getline(std::cin, input);
        i = atoi(input.c_str());
        temp = de->advance();
    }
    return 0;
}