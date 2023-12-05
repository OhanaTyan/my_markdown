#include <cstdio>
#include <cstdlib>

int main(){
    FILE* fl = fopen("test03.txt", "w");
    
    fputc(-68, fl);
    fputc(123, fl);

    fclose(fl);
    return 0;
}