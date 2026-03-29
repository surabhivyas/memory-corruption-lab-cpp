#include<iostream>
#include<cstring>


void vulnerable(){
    char buffer[16];
    int marker = 12345;

    std::cout << "address of buffer: " << static_cast<void*>(buffer) << "\n";
    std::cout << "address of marker: " << &marker << "\n";

    std::cout << "enter input: ";
    
    std::cin >> buffer; // intentionally unsafe for demo;

    std::cout << "Buffer: " << buffer << "\n";
    std::cout << "Marker: " << marker << "\n";
}

int main(){
    vulnerable();
    return 0;

}


