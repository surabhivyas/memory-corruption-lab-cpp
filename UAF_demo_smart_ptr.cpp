#include<iostream>
#include<memory>
#include<cstring>

int main(){
    auto ptr = std::make_unique<char[]>(16);

    std::snprintf(ptr.get(), 16, "%s", "HELLO");
    std::cout << "Managed safely: " << ptr.get() << std::endl;

    //Automatic cleanup when ptr goes out of scope
    return 0;
}
