#include<iostream>
#include<cstdlib>
#include<cstring>

int main(){
    const size_t BUF_SIZE = 16;
    char* buffer = (char*)malloc(BUF_SIZE);

    if(!buffer){
        std::cerr << "Memory allocation failed\n";
        return 1;
    }

    std::cout << "enter input (max " << BUF_SIZE - 1 << "characters): ";
    
    //Safe input: reads at most BUF_SIZE-1 characters + null terminator
    if((fgets(buffer, BUF_SIZE, stdin)) == NULL) {
        std::cerr << "Input error\n";
        free(buffer);
    }
    
    //Remove newline if present
    buffer[strcspn(buffer, "\n")] = '\0';

    std::cout << "Stored safely: " << buffer << std::endl;

    free(buffer);
    return 0;

}
