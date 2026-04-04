#include<iostream>
#include<cstdlib>
#include<cstring>

int main(){
    char* ptr = (char*)malloc(16);
    if(!ptr){
        std::cerr << "Allocation failed\n";
        return 1;
    }

    std::snprintf(ptr, 16, "%s", "HELLO");   //bounded write with snprintf
    std::cout << "Before free: " << ptr << std::endl;

    free(ptr);
    ptr = nullptr;     //invalidate stale pointer

    //Safe behaviour: do not use ptr after free
    if(ptr == nullptr){
        std::cout << "Pointer invalidated after free; no further access performed" << std::endl;
    }
   
    return 0;

}
