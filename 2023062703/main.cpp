#include <stdlib.h>
#include <string.h> // #include <string>

#include <iostream>

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
        // c 使用 NULL， cpp 使用 nullptr
        if (nullptr != this->buf) {
            printf("Bye [%s]\n", this->buf);
            free(this->buf);
        } else {
            printf("Bye [\\anonymous]\n");
        }
    }

//private:
    char *buf;
};

// 动态分配整形数组，count 为数量，需要在 malloc 中乘以每一个元素占用的内存大小，计算出
// 总内存使用。
int *create_array(int count) {
    size_t size = sizeof(int) * count;
//    printf("count = %d, size = %zu\n", count, size);
    return (int *) malloc(size);
}

// 创建一个 Cat 类型的数组
Cat *create_cats_with_malloc(int count) {
    size_t size = sizeof(Cat) * count;
//    printf("count = %d, size = %zu\n", count, size);
    return (Cat *) malloc(size);
}

Cat *create_cat_with_new(int count) {
    return new Cat[count];
}


int main() {
    // 错误使用方法:
    //  使用 malloc 分配的数组，不会调用构造函数(与 malloc 为对象分配内存时一样)
//  Cat* cats= create_cats_with_malloc(10);
//  free(cats);

    // 正确使用方法:
    //      类似于 malloc / free 函数对，可以使用
    //      new / delete 操作符，申请/释放动态分配的 对象
    Cat *cats = create_cat_with_new(12);

    // 错误用法:
    //      当使用 new Cat[10] 的语法，动态创建对象数组时，
    // 如果使用 delete 释放对象内存，会出现错误(exit code 6)
    // delete cats;

    // 这里输出动态分配的 cats 的地址 (%p 是输出地址)
    printf("pointer at %p\n", cats);

    // 将 cats 指针，强制转换为 (long*)，因为 cats 的本质是一个地址(指针)
    // 所以可以将 cats 转为 long 的指针(long *)，因为地址占用的长度与 long
    // 相同。(long*)cats-1 就是读取 cats 前面，长度为 long，的位置的地址
    // *((long*)cats-1) 是对上面的地址解引用
    // 最终发现，这个数值与 数组长度相同
    printf("value = %ld\n", *((long*)cats-1));


    // 正确用法:
    delete[] cats;


}