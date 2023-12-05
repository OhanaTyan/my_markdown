#include <cstdio>
#include <cstdlib>
#include <vector>

// 检查一个 vector 是否可以当做栈使用
// 结果：可以。但是使用的字段不一样
// 
int main(){
    std::vector<int> v;
    printf("%d\n", static_cast<int>(v.empty()));
    v.push_back(1);
    v.push_back(2);
    printf("%d\n", static_cast<int>(v.empty()));
    //v.pop_back();
    printf("%d\n", v.front());
    printf("%d\n", v.back());
    v.pop_back();
    printf("%d\n", v.front());
    printf("%d\n", static_cast<int>(v.empty()));
    v.pop_back();
    printf("%d\n", static_cast<int>(v.empty()));

    return 0;
}