#include <stdio.h>
#include <stdlib.h>

#include <set>

/*
* 该文件主要是用于测试文件编码问题
* 为了避免比如从一个正常的utf-8文件读取
* 会不会因为文件编码问题读取到不应该读取到的内容
* 比如一个文件本来没有大于号
* 但因为某个字符的编码是多个字节，而其中一个字节的值和大于号相等
* 这类问题
*/


int main(){
    std::set<char> s{'*', '<', '>', '#', '+', '-', '{', '}'};

    for (signed char c0=1; c0!=0; c0++){
        for (signed char c1=1; c1!=0; c1++){
           // for (signed char c2=1; c2!=0; c2++){
            //    for (signed char c3=1; c3!=0; c3++){
                    if ( 
                        
                        s.find(c0) != s.end() ||
                        s.find(c1) != s.end() 
                    //    s.find(c2) != s.end() ||
                    //    s.find(c3) != s.end()
                    ){
                        //printf("%d\t%d\t%d\t%d\n", c0, c1, c2, c3);
                        //printf("%c %c %c %c\t", c0, c1, c2, c3);
                        //printf("%d %d %d %d\t", c0, c1, c2, c3);
                        //printf("%c%c%c%c\n", c0, c1, c2, c3);
                        printf("%c %c \t", c0, c1);
                        printf("%d %d \t", c0, c1);
                        printf("%c%c\n", c0, c1);
                    } else {
                        continue;
                    }
                }
            }
    //    }       
   // }
    return 0;
}

