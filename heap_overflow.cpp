#include <iostream>
#include <cstdlib>
#include <cstring>

int main()
{
    char* a = (char*)malloc(16);
    char* b = (char*)malloc(16);

    std::cout << "Address of a: " << (void*)a << std::endl;
    std::cout << "Address of b: " << (void*)b << std::endl;

    std::cout << "Distance: " << (b - a) << std:: endl;
    //initialise b
    strcpy(b, "BBBBBBBBBBBBBBB");

    std::cout << "\nBefore overflow: " << std::endl;
    std::cout << "b: " << b << std::endl;

    // overflow a into b
    strcpy(a, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

    std::cout << "\nAfter overflow: " << std::endl;
    std::cout << "b: " << b << std::endl;

    free(a);
    free(b);

    return 0;

}

