#include<iostream>
#include<cstdlib>
#include<cstdint>
#include<climits>


int main(){
    size_t count = (SIZE_MAX / sizeof(int)) + 1;
    std::cout << "Requested element count: " << count << std::endl;
  
    //Integer overflow in size calculation
    size_t alloc_size = count * sizeof(int);

    std::cout << "Computed allocation size: " << alloc_size << " bytes" << std::endl;
    
    int* arr = (int*)malloc(alloc_size);

    if(!arr) {
        std::cerr << "Allocation failed\n" << std::endl;
        return 1;
    }

    std::cout << "Memory allocated at: " << arr << std::endl;
    std::cout << "Warning: integer overflow can produce an undersized allocation. \n" << arr << std::endl;
 
    free(arr);
    return 0;
}

