#include<iostream>
#include<cstdlib>
#include<cstring>

int main(){
    const size_t BUF_SIZE = 16;
    
    char* a = (char*)malloc(BUF_SIZE);
    char* b = (char*)malloc(BUF_SIZE);

    if(!a || !b){
        std::cerr << "Allocation failed\n";
        free(a);
        free(b);
        return 1;
    }

    std::cout << "Address of a: " << (void*)a << std::endl;
    std::cout << "Address of b: " << (void*)b << std::endl; 
    std::cout << "Distance: " << (b - a) << std::endl;

    //Initialise b safely
    std::snprintf(b, BUF_SIZE, "%s", "BBBBBBBBBBBBBBB");
    
    std::cout << "\nBefore safe write:\n";
    std::cout << "b: " << b << std::endl; 

    const char* input = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";

    //Safe write: truncate to fit allocated size
    std::snprintf(a, BUF_SIZE, "%s", input);

    std::cout << "\nAfter safe write:\n";            
    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl; 

    free(a);
    free(b);

}  
