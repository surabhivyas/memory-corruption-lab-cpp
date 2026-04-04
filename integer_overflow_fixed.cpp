#include<iostream>
#include<cstdlib>
#include<cstdint>
#include<climits>

int main(){
    size_t count = (SIZE_MAX / sizeof(int)) + 1;

    std::cout << "Requested element count: " << count << std::endl;

    //Prevent integer overflow before multiplication 
    if(count > SIZE_MAX / sizeof(int)) {
        std::cerr << "Integer overflow detected in allocation size calculation \n";
        return 1;
    }

    size_t alloc_size = count * sizeof(int);

    int* arr = (int*)malloc(alloc_size);
    if(!arr) {
        std::cerr << "Allocation failed \n";
        return 1;
    }

    std::cout << "Safe allocation size: " << alloc_size << " bytes" << std::endl;

    free(arr);
    return 0;
}
