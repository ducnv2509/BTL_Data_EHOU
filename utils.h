#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>

namespace patch
{
    template <typename T>
    std::string to_string(const T& n)
    {
        std::ostringstream stm;
        stm << n;
        return stm.str();
    }
}

int castStringToInt(std::string input);

bool xuatHienTrongDSSach(std::string ten, std::string ds[]);
int viTrixuatHienTrongDSSach(std::string ten, std::string ds[]);

#endif
