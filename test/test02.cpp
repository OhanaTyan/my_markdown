#include <cstdio>
#include <cstdlib>

#include <set>

int main(){
    std::set<char> s{'*', '<', '>', '#', '+', '-', '{', '}'};
    FILE* fl = fopen("test02.txt", "r");
    char c;
    bool is_hash_exist = false;
    printf("%c%c%c\n", -43, 123);
    while ((c = getc(fl)) != EOF){
        if (s.find(c) != s.end()) is_hash_exist = true;
        printf("%c\n", c);
        printf("%d\n", int(c));
    }
    printf(
        "%s\n",
        is_hash_exist? "yes": "no"
    );

}

