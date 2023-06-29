#include <iostream>
// stdlib = std(standard) + lib(library)
#include <stdlib.h>
// stdio = std(standard) + io(input/output) 标准输入输出
#include <stdio.h> // printf / scanf / puts / putchar

// 字符串相关
#include <string.h>

class Animal {
public:
    Animal() {
        std::cout << "Anminal" << std::endl;
    }

    ~Animal() {
        std::cout << "Bye Anminal" << std::endl;
    }
};

class Cat : public Animal {
public:
    Cat(const char *name) {
        printf("Cat(name)\n");
        this->set_name(name);
    }

    Cat() {
        printf("Cat\n");
    }

    void set_name(const char *name) {
        this->buf = (char *) malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(this->buf, name);
    }


    ~Cat() {
        printf("Bye [%s]\n", this->buf);
        free(this->buf);
    }

private:
    char *buf;
};

// 错误的，返回了临时变量(buf)的地址(数组名就是数组第一个元素的地址)
//const char * say() {
//    char buf[] = {'h', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd'};
//    return buf;
//}

// 正确的
// 内存有四个区域
// 代码:
//      保存可执行文件代码的内存区域，不可修改
//
// 栈(stack):
//      保存函数实参和临时变量，在函数调用结束后，栈内的变量会被销毁，因此，不能返回临时变量的地址
//
// 常量:
//      全局变量，静态变量，常量字符串
//const char *say() {
//    const char *buf = "hello world";
//    return buf;
//}

char *say(const char *name) {
    // hello ${name}
    // 最终字符串长度 = 6 + strlen(name) ;
    //     内存字节数 = 最终字符串长度 + 1

    // 把 sizeof(char) 替换为 1，被称作 hard code
    char *buf = (char *) malloc(sizeof(char) * (6 + strlen(name) + 1));
    memset(buf, 0, (6 + strlen(name) + 1) * sizeof(char));
    strcpy(buf, "hello ");
    strcat(buf, (char *) name);
    return buf;
}

void buffer_overflow() {
    // buf     buf2
    // 0 1 2 3 4 5 6 7 8 9 10 11
    // h e l l o   w o r l  d \0
    char buf[4] = {'\0'};
    char buf2[5] = {'\0'};
    memset(buf, 0, (sizeof(buf) / sizeof(buf[0])) * sizeof(char));
    strcpy(buf, "hello world");
    printf("buf = '%s'\n", buf);
    printf("buf2 = '%s'\n", buf2);
}


//
//int &foo() {
//    int a = 10;
//    return a;
//}
//
//int * bar() {
//    int a = 10;
//    int* b = &a;
//    return b;
//}

int main() {

#define COUNT 3

    Cat cats[COUNT] = {};
    for (int i = 0; i < COUNT; i++) {
        cats[i].set_name("abcdefghijlkmnopqrstuvwxyz");
    }


    return 0;
}

