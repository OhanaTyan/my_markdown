#include <iostream>
#include <fstream>
#include <string>
// 成功
int main(){
    const char* input_file_name = "test10.txt";
    std::ifstream input_file(input_file_name);
    if (input_file.fail()){
        std::cout << "Unable to open " << input_file_name << std::endl;
        return 0;
    }

    std::string s;
    while (1){
        std::getline(input_file, s); 
        //std::cout << s << std::endl;
        if (input_file.fail()) break;
        std::cout << s << std::endl;
        std::cout << int(s[0]) << std::endl;
    }
    return 0;
}
