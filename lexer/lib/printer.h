#ifndef _PRINTER_H_
#define _PRINTER_H_

#include<iostream>

class Printer{
    bool _print;
    std::ostream &_os;
public:
    Printer(std::ostream &os, bool print=false);
    std::ostream &getOutputStream();
    bool isPrint();
};

#endif