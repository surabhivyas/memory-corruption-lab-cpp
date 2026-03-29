#include<iostream>
#include<cstdlib>
#include<cstring>

int main(){
    char* a = (char*)malloc(16);
    char* b = (char*)malloc(16);
    char* c = (char*)malloc(16);

    std::cout << "a: " << (void*)a << std::endl;
    std::cout << "b: " << (void*)b << std::endl;
    std::cout << "c: " << (void*)c << std::endl;

    strcpy(a, "AAAA");
    strcpy(b, "BBBB");
    strcpy(c, "CCCC");

    std::cout << "\nBefore free:\n";
    std::cout << "a:" << a  <<"\n";
    std::cout << "b:" << b  <<"\n";
    std::cout << "c:" << c  <<"\n";

    free(b);

    char* attacker = (char*)malloc(16);
    std::cout << "Attacker: " << (void*)attacker <<  std::endl;
    strcpy(attacker, "HACKED");

    std::cout << "\nAfter reuse: \n";
    std::cout << "Attacker: " << attacker <<  std::endl;
    std::cout << "\nCheck c: \n";
    std::cout << "c: " << c << std::endl;

    return 0;

}

