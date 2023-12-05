#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "my_markdown.h"

void invalid_input(char** argv){
    std::cout 
        << argv[0]
        << ": buffer_size template.wrapper_html input_file.md output_file.html"
        << std::endl;
    exit(-1);
    return;
}

void set_buffer_size(char** argv){
    int a=0;
    a = atoi(argv[1]);
    if (a <= 0) {
        std::cout 
            <<  "Invalid buffer size\n"
                "The buffer size you've input is"
            <<  argv[1]
            <<  std::endl;
        exit(-1);
    }
    else buffer_size = a;
}

int main(int argc, char** argv){
    if (argc <= 4){
        invalid_input(argv);
    }

    set_buffer_size(argv);

    My_markdown_parser my_markdown_parser(argv[2], argv[3], argv[4]);

    my_markdown_parser.parse();
    return 0;
}



