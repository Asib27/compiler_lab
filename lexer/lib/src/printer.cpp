#include"printer.h"

Printer::Printer(std::ostream &os, bool print)
        : _print(print), _os(os)
    {

    }

std::ostream &Printer::getOutputStream(){
    return _os;
}

bool Printer::isPrint(){
    return _print;
}