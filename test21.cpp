#include <iostream>
#include <fstream>

#include <cstdio>
#include <cstdlib>

#include <algorithm>

char s[10000];

int main(){
    FILE* file = fopen("test10.txt", "r");
    char c;
    char *p = s;
    while ((c = getc(file))!=EOF){
        *p = c;
        p++;
    }
    printf("%s\n", s);
    return 0;
}


