#include<iostream>
#include<string>

int main(){
    std::string input;
    
    std::cout << "enter input: ";
    std::getline(std::cin, input);
 
    if(input.length() > 15){
        std::cout << "Input too long, truncating to 15 characters\n";
        input = input.substr(0, 15);
    }

    std::cout << "Stored safely: " << input << std::endl;

    return 0;
}
