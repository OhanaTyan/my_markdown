#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>


#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <csetjmp>
#include <memory>
#include <algorithm>

int buffer_size;

// 这个头文件可能会全部重写，因为如果不重写的话
// 就无法适配萌百的模板内容


class My_markdown_parser{
private:
//    std::ifstream   template_file;
    FILE*           template_file;
    std::ifstream   input_file;
    FILE*           output_file;
//    std::ofstream output_file;

    enum class text_state{
        none,
        context,        // 大段字符串，全部放在</p>中
        codeblock,
        ordered_list,
        unordered_list,
        indent          // 缩进
    };

    enum class style_type{
        none    = 0,
        black   = 1,    // 粗体
        italic  = 2,    // 斜体
        del     = 3,    // 删除线
        templat = 4
    };

    enum class error_type{
        unpaired_black  = 1,    // 粗体不配对
        unpaired_italic = 2,    // 斜体不配对
        unpaired_delete = 3,    // 删除线不配对
        unpaired_templat= 4     // 模板不配对
    };

    std::string             line_raw;
    std::string             output_raw;
    std::vector<text_state> list_state; 
    // 将列表当做栈使用
    text_state              cur_state = text_state::none;
    std::string             temp_codeblock_raw;
    std::string             temp_text;
    std::string             temp_list;
    std::vector<std::string>temp_list_raw;

    // 下面变量用于错误处理
    jmp_buf                 env;
    char*                   cur_pchar;
    std::string             error_message;

    int line_num = 0;

public:
    My_markdown_parser(const My_markdown_parser&&)    = delete;

    My_markdown_parser(
        const char* template_file_name,
        const char* input_file_name,
        const char* output_file_name
    ):  //template_file(template_file_name),
        input_file(input_file_name)
    {
        template_file = fopen(template_file_name, "r");
        if (template_file == nullptr){
            std::cerr << "Unable to open  " << template_file_name << "\n";
        }
    //   if (template_file.fail()){
    //       std::cout << "Unable to open " << template_file_name << "\n";
    //       exit(-1);
    //   }

        if (input_file.fail()){
            // printf("Unable to open %s\n", input_file);
            std::cerr << "Unable to open " << input_file_name << "\n";
            exit(-1);
        }

        output_file = fopen(output_file_name, "w");
        if (output_file == nullptr){
            std::cerr << "Unable to open " << output_file_name << '\n';
            exit(-1);
        }
//        if (output_file.fail()){
//            std::cout << "Unable to open " << output_file_name << "\n";
//        }

        return;
    }

    void flush_text(){
        output_raw.append(temp_text);
        temp_text.clear();
    }

    static const char* get_error_message_by(error_type &e){
        // todo:
        switch(e){
        default: return "";
        }
    }

    void error_handle(error_type &e){
        flush();

        int nth_of_string = cur_pchar - line_raw.c_str();
        std::cerr   << "error: " 
                    << line_num 
                    << ":"
                    << nth_of_string
                    << get_error_message_by(e)
                    << '\n'
                    << line_raw
                    << '\n';
        for (int i=0; i<nth_of_string; i++){
            std::cerr<< ' ';
        }
        std::cerr   << "^~~~~~~~~" << std::endl;
    }

    void flush(){
        assert(cur_state != text_state::codeblock);
        switch(cur_state){
        case text_state::ordered_list:
        case text_state::unordered_list:
        // todo:清空列表
            break;
        case text_state::context:
            flush_text();
        }
        
    }    

    static std::string add_frame(
        const std::string &middle,
        const std::string &left, 
        const std::string &right
    )
    {
        return left+middle+right;
    }

    static std::string parse_template(const char* template_raw){
        // todo:
        return add_frame(template_raw, "<模板功能暂未完成>", "");

    }


    static std::string parse_head(const char* head_raw){
        const char* p = head_raw;
        int head_level = 0;
        for (; head_level<5; head_level++, p++){
            if (*p == '#') continue;
            else break;
        }
        // ### 标题
        //    ^ 操作完后，指针在这个位置
        if (*p == ' ') p++;

        char string_of_head_level[10];
        strcpy(
            string_of_head_level, 
            std::to_string(head_level).c_str()
        );

        std::string 
            frame_left = std::string("<h")
                .append(string_of_head_level)
                .append(" id=\"")
                .append(p)
                .append("\">"),
            frame_right=std::string(" </h")
                .append(string_of_head_level)
                .append(">\n");

        return add_frame(std::string(p), frame_left, frame_right);        
    }

    //  todo: 解析一个文段字符串
    static std::string parse_text(const char* text_raw){
    //  std::string             result;
        std::stack<std::string> string_stack;
        //std::string*            cur_buffer = nullptr; 
        const char*             p = text_raw;
        std::vector<style_type>style_stack;
        style_type             state = style_type::none;
    
    /*  该算法的算法描述如下
            修饰符：类似于* ''' ~~ 等，对文本起修饰作用的字符
        # 实现层级修饰操作
            首先维护一个栈结构，栈中的每个元素均为一个字符串
            每当读取到一个左修饰符时，则在栈中压入一个空字符串
            每当读取到一个配对的右修饰符时，将栈顶的字符串进行修饰处理
            将栈顶弹出，将修饰处理后的字符写入到此时的栈顶字符串后面

            由style_stack检查修饰符的合法性，和判断一个修饰符是左修饰符还是右修饰符
            如果出现非法字符串，则报错处理
    
    */
        string_stack.push(std::string());

        char c;
        for (; (c = *p)!='\0'; p++){
            switch(c){
            case '*':   // 斜体修饰符
                if (!style_stack.empty()){
                    if (style_stack.back() != style_type::italic){
                        // 检查是否有越界配对，也就是这种情况
                        // 斜体标记 粗体标记 (准备压入栈的)斜体标记
                        //          ^~~~~ 在界内部的修饰符
                        // auto iter = style_stack.begin();
                        auto iter = std::find(  style_stack.begin(), 
                                                style_stack.end(), 
                                                style_type::italic
                        );
                        if (iter == style_stack.end()) {
                            goto PUSH_STYLE_ITALIC;
                        } else { 
                            // 说明有越界配对
                            // 则抛出越界配对中，在界内部的修饰符类型作为错误类型
                            throw error_type(*iter);
                        }
                    } else {
                        // 说明栈顶是左斜体标记，则将栈顶字符串修饰后
                        // 将其弹出，将修饰后的字符串写入新的栈顶
                        style_stack.pop_back();
                        std::string temp = std::move(string_stack.top());
                        string_stack.pop();
                        string_stack.top().append(
                            add_frame(temp, "<em>", "</em>")
                        );
                    } 
                } else {
PUSH_STYLE_ITALIC: 
                    style_stack.push_back(style_type::italic);
                    string_stack.push(std::string());
                }
                break;

            case '\'':  // 可能是粗体修饰符
                if (*(p+1) == '\'' && *(p+2) == '\''){
                    // 可以确定是粗体修饰符
                    p += 2; // 移动指针
                    if (!style_stack.empty()){
                        if (style_stack.back() != style_type::black){
                            auto iter = style_stack.begin();
                            if ((iter = std::find(style_stack.begin(), style_stack.end(), style_type::black)) == style_stack.end()){
                                goto PUSH_STYLE_BLACK;
                            } else {
                                throw error_type(*iter);
                            }
                        } else { // 说明栈顶是左粗体标记，则将栈顶字符串修饰后弹出
                            style_stack.pop_back();
                            std::string temp = std::move(string_stack.top());
                            string_stack.pop();
                            string_stack.top().append(
                                add_frame(temp, "<strong>", "</strong>")
                            );
                        }
                    } else {
PUSH_STYLE_BLACK:
                        style_stack.push_back(style_type::black);
                        string_stack.push(std::string());
                    }
                } else { // 可以确定不是粗体修饰符
                    goto NOT_STYLE_WRAPPER;
                }
                break;

            case '~':   // 可能是删除线修饰符
                if (*(p+1) == '~'){
                    // 可以确定是删除修饰符
                    if (!style_stack.empty()){
                        if (style_stack.back() != style_type::del){
                            auto iter = style_stack.begin();
                            if ((iter = std::find(style_stack.begin(), style_stack.end(), style_type::del)) == style_stack.end()){
                                goto PUSH_STYLE_DELETE;
                            } else {
                                throw error_type(*iter);
                            }
                        } else { // 右配对
                            style_stack.pop_back();
                            std::string temp = std::move(string_stack.top());
                            string_stack.pop();
                            string_stack.top().append(
                                add_frame(temp, "<s>", "</s>")
                            );
                        }
                    } else {
PUSH_STYLE_DELETE: 
                        style_stack.push_back(style_type::del);
                        string_stack.push(std::string());
                    }
                } else goto NOT_STYLE_WRAPPER;

            case '\\':  // 转义修饰符
                p++;
                if (*p != '\0'){
                    string_stack.top().push_back(*p);
                }
                break;
            case '{':   // 模板左修饰符
                style_stack.push_back(style_type::templat);
                string_stack.push(std::string());

            case '}':   // 模板右修饰符
                if (style_stack.empty()){
                    throw error_type::unpaired_templat;
                } else if (style_stack.back() == style_type::templat){
                    style_stack.pop_back();
                    std::string temp = std::move(string_stack.top());
                    string_stack.pop();
                    string_stack.top().append(
                        parse_template(temp.c_str())
                    );
                }
            default:    // 无修饰
NOT_STYLE_WRAPPER:
                string_stack.top().push_back(*p);
            }
        }

        // todo: 增加循环结束后的部分
        if (!style_stack.empty()){
            throw error_type(style_stack[0]);
        } else return string_stack.top();
    }

    void parse(){

        //while (1){
        for (line_num=1; ; line_num++){
            try {
                std::getline(input_file, line_raw);
                if (input_file.fail()) break;

                switch(line_raw[0]){ 
                case '\0': // 说明该行只有一个回车
                    cur_state = text_state::none;
                    break; 
                case '#': // 标题
                    if (cur_state == text_state::codeblock){
                        temp_codeblock_raw.append(line_raw);
                    } else {
                        flush();
                        output_raw.append(parse_head(line_raw.c_str()));
                    }
                    break;
                case '-': // 列表或分隔线
                    if (line_raw[1]==' '){ // 最简单的无序列表
                        flush();
                    }
                    break;

                case '*': // 列表或斜体
                    if (cur_state == text_state::codeblock){
                        temp_codeblock_raw.append(line_raw);
                    }

                case '+': // 列表
                    // todo:
                    break;
                case '`': // 代码或代码块
                    // todo:
                    break;
                case '>': // 缩进
                    // todo:
                    break;
                case ' ':
                case '\t':
                default: // 段落
DEFAULT:
                    if (cur_state == text_state::codeblock){ // 如果处于读取代码阶段
                        // 则仅将该行放入代码缓存区即可
                        temp_codeblock_raw.append(line_raw);
                        break;
                    } else {
                        temp_text.append(parse_text(line_raw.c_str()));
                    }
                    break;
                } // switch

                continue;
            } catch (error_type &e){
                error_handle(e);
            }

        }

        //std::unique_ptr<char> templat = std::make_unique<char>(new char[buffer_size]);
                
        // 把template_file的内容全部读入到一个字符串中
        // 代码来自 https://blog.csdn.net/weixin_44327262/article/details/105432942?spm=1001.2101.3001.6650.2&utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-2-105432942-blog-91410313.235%5Ev39%5Epc_relevant_3m_sort_dl_base1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7ECTRLIST%7ERate-2-105432942-blog-91410313.235%5Ev39%5Epc_relevant_3m_sort_dl_base1&utm_relevant_index=5

        // std::string templat(std::istreambuf_iterator<char>(template_file), std::istreambuf_iterator<char>());

        std::string templat;
        char c;
        while ((c = fgetc(template_file)) != EOF){
            templat.push_back(c);
        }
        
        fprintf(output_file, templat.c_str(), output_raw);
    }


};



