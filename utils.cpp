#include "utils.h"

int castStringToInt(std::string input)
{
    int output = 0;
    std::stringstream ss;
    ss << input;
    ss >> output;
    return output;
}


bool xuatHienTrongDSSach(std::string ten, std::string ds[])
{
    int dem = 0;
    int arrSize = *(&ds + 1) - ds;
    for (int i = 0; i < arrSize - 1; i++)
    {
        if (ten == ds[i])
            dem++;
    }
    return dem > 0;
}

int viTrixuatHienTrongDSSach(std::string ten, std::string ds[])
{
    int viTri = -1;
    int arrSize = *(&ds + 1) - ds;
    for (int i = 0; i < arrSize - 1; i++)
    {
        if (ten == ds[i])
            viTri = i;
    }
    return viTri;
}