#include <iostream>
#include <cstdlib>
#include <cstring>

int main()
{
    char* ptr = (char*)malloc(16);
    
    strcpy(ptr, "HELLO");
    std::cout << "Before free: " << ptr << std::endl;

    free(ptr);
    
    // Allocate again
    char* attacker = (char*)malloc(16);
    strcpy(attacker, "HACKED");

    // Use-after-free
    std::cout << "After free (UAF): " << ptr << std::endl;

    return 0;

}
