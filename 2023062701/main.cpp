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
        printf("Cat(%s)\n", name);
        this->set_name(name);
    }

    Cat() {
        printf("Cat\n");
    }

    Cat(Cat &c) {
        // 在构造函数中，有两个 Cat 类对象
        // 第一个是传进来的 c，我们期望在这个函数中根据 c 的样子创建一个新的对象(照猫画虎)
        // 第二个是 this，表示我们正在画的这只猫

        // 方案1：
        // 如下代码为 this->buf 分配内存，并将 c.name 复制到 this->buf
        // 代码取消注释
        //        this->buf = (char *) malloc(sizeof(char) * (strlen(c.buf) + 1));
        // 注意调用函数时，每一个参数的含义
        // 什么时候使用 -> 或者 .
        //    当对象的类型为 **类的指针(是一个类的指针)** 时使用 '->' 操作符获取其成员变量，或者函数
        //    当对象的类型为 **类(字面意思)** 时 使用 '.'
        // 代码取消注释
        //        strcpy(this->buf, c.buf);

        // 方案2:
        //    strdup 是方案 1 中两行代码的整体，返回一个通过 malloc 申请的内存的指针，需要使用 free 释放(重点)
        //        this->buf = strdup(c.buf);

        // 方案3：
        //     this 是指向当前对象的指针，可以调用类中的所有方法
        this->set_name(c.buf);

        // 下面是一种常见错误写法:
        // 直接将指针赋值，会导致多个对象指向同一块内存
        // 在析构函数中被反复释放(鞭尸)
        // this->buf = c.buf;
    }

    void set_name(const char *name) {
        this->buf = (char *) malloc(sizeof(char) * (strlen(name) + 1));
        strcpy(this->buf, name);
    }


    ~Cat() {
        printf("Bye [%s]\n", this->buf);
        free(this->buf);
    }

//private:
    char *buf;
};

int main() {

#define COUNT 3
    Cat ragdoll = Cat("Ragdoll");

    Cat ragdoll_copy = ragdoll;


    return 0;
}

