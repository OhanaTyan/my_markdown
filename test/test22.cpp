#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>

enum class a{
    aa,
    bb,
    cc
};
/*
int main(){
    std::vector<int> v{1, 2, 3, 4, 5};
    if (std::find(v.begin(), v.end(), 2) != v.end()){
        printf("2 in v\n");
    } else {
        printf("2 not in v\n");
    }
    return 0;
}
*/

int main(){
    std::vector<a> v{a::aa, a::bb};
    if (std::find(v.begin(), v.end(), a::cc) != v.end()){
        printf("cc in v\n");
    } else { 
        printf("cc not in v\n");
    }
    return 0;
}