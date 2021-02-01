#include "complex/complex.h"
#include <iostream>
#include <sstream>
bool testParse(const std::string &str)
{
    std::istringstream istrm(str);
    Complex z;
    istrm >> z;
    if (istrm.good())
    {
        std::cout << "Read success: " << str << " -> " << z << std::endl;
    }
    else
    {
        std::cout << "Read error : " << str << " -> " << z << std::endl;
    }
    return istrm.good();
}

int main()
{
    Complex temp;
    Complex z(2, 5);
    std::cout << "Putting (2,5) Complex number: " << z << std::endl;
    std::cout << "Putting -4 Complex number: " << Complex(-4) << std::endl;
    std::cout << "Putting Nothing Complex number: " << Complex() << std::endl;
    temp = z;
    z += Complex(-8.0);
    std::cout << temp << " += " << Complex(-8.0) << " = " << z << " (Complex + Complex)" << std::endl;
    temp = z;
    z -= Complex(5, -3);
    std::cout << temp << " -= " << Complex(5, -3) << " = " << z << " (Complex - Complex)" << std::endl;
    temp = z;
    z -= 1.0;
    std::cout << temp << " -= " << 1.0 << " = " << z << " (Complex - double)" << std::endl;
    temp = z;
    z *= Complex(3, 5);
    std::cout << temp << " *= " << Complex(3, 5) << " = " << z << " (Complex * Complex)" << std::endl;
    temp = z;
    z *= 2.0;
    std::cout << temp << " *= " << 2.0 << " = " << z << " (Complex * double)" << std::endl;
    std::cout << "Let's try devide by std::numeric_limits<double>::epsilon()\n";
    try
    {
        z /= std::numeric_limits<double>::epsilon();
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << "Exception caught with reason '" << ex.what() << "'\n";
    }
    testParse("{8.9,9}");
    testParse("{8.9, 9}");
    testParse("{8.9,9");
    return 0;
}