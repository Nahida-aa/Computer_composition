#include<stdio.h>

void example_2_1() {
    int i = -1;
    if(i < 0)
        printf("This will print, and i is %d\n", i);
    if((unsigned int)i < 0)
        printf("This will not print\n");
    if ((unsigned int)i > 0)
        printf("This will print, and i = %u\n", i);
        printf("This will print, and i = %u\n", (unsigned int)i);
}

void example_2_2() {
    struct foo {
        int a;
        char b;
        struct foo *c;
    };
    printf("Size of struct foo: %zu Byte\n", sizeof(struct foo));
    // %zu is the format specifier for size_t
}

void example_2_3() {
  union foo {
      int a;
      char b;
      union foo *c;
  };
  printf("Size of union foo: %zu Byte\n", sizeof(union foo));
}

void pointer_example() {
    int *p;
    int x; int y;
    printf("----int *p; int x; int y;----\n");
    // %p is the format specifier for addresses
    printf("p_addr: %p, x_addr: %p, y_addr: %p\n", &p, &x, &y);
    printf("p: %p, x: %d, y: %d\n", p, x, y);
    x=3; y=4;
    printf("----x=3; y=4;----\n");
    printf("p_addr: %p, x_addr: %p, y_addr: %p\n", &p, &x, &y);
    printf("p: %p, x: %d, y: %d\n", p, x, y);
    p = &x;
    printf("----p = &x; 引用{get x_addr} and Assign{x_addr to p},即 p 指向 x, p的值为 x的addr----\n");
    printf("p_addr: %p, x_addr: %p, y_addr: %p\n", &p, &x, &y);
    printf("p: %p, x: %d, y: %d\n", p, x, y);
    *p = 5;
    printf("----*p = 5; 解引用{get addr==p(==x_addr)上的值} and Assign{5 to 解引用}, 即成功修改了x的值----\n");
    printf("p_addr: %p, x_addr: %p, y_addr: %p\n", &p, &x, &y);
    printf("p: %p, x: %d, y: %d\n", p, x, y);
    y = *p;
    printf("----y = *p; 解引用{get addr==p(==x_addr)上的值} 赋值 to y----\n");
    printf("p_addr: %p, x_addr: %p, y_addr: %p\n", &p, &x, &y);
    printf("p: %p, x: %d, y: %d\n", p, x, y);
}

void sizeof_example() {
    int x;
    int *x_ptr;
    unsigned int y;
    unsigned int *y_ptr;
    printf("----int x; int *x_ptr; unsigned int y; unsigned int *y_ptr;----\n");
    printf("Size of x: %zu\n", sizeof(x)); // 4
    printf("Size of int: %zu\n", sizeof(int)); // 4
    printf("Size of int pointer: %zu\n", sizeof(x_ptr)); // 8
    printf("Size of y: %zu\n", sizeof(y)); // 4
    printf("Size of unsigned int: %zu\n", sizeof(unsigned int)); // 4
    printf("Size of unsigned int pointer: %zu\n", sizeof(y_ptr)); // 8
    printf("Size of int *: %zu\n", sizeof(int *)); // 8
    printf("Size of char *: %zu\n", sizeof(char *)); // 8
    printf("Size of char: %zu\n", sizeof(char)); // 1
}

void sizeof_struct_example() {
    struct foo {
        int a; // 4
        char chr; // 1+3*padding
        short sht; // 2+2*padding
        char *chr_ptr; // 8
        char char_end;// 1+3*padding
    };
    printf("struct foo {----\n");
    printf("    int a;\n");
    printf("    char chr;\n");
    printf("    short sht;\n");
    printf("    char *chr_ptr;\n");
    printf("    char char_end;\n");
    printf("}----\n");
    printf("Size of struct foo: %zu\n", sizeof(struct foo)); // 16?应该是24
}

void sizeof_struct_example2() {
    // 重新排列变量以减少size
    struct foo {
        int a; // 4
        char chr; // 1+1(char_end)+2(sht)
        char char_end;// 1
        short sht; // 2
        char *chr_ptr; // 8
    };
    struct foo my_foo;
    printf("struct foo {----\n");
    printf("    int a;\n");
    printf("    char chr;\n");
    printf("    char char_end;\n");
    printf("    short sht;\n");
    printf("    char *chr_ptr;\n");
    printf("}----\n");
    printf("Size of struct foo: %zu\n", sizeof(my_foo)); // 16
}

void addr_example() {
    int a[4];
    int x;
    int y;
    int *p;
    printf("----int a[4]; int x; int y; int *p;----\n");
    printf("a_addr: %p, x_addr: %p, y_addr: %p, p_addr: %p\n",&a, &x, &y, &p);
    printf("a[0]_addr: %p, a[1]_addr: %p, a[2]_addr: %p, a[3]_addr: %p\n", &a[0], &a[1], &a[2], &a[3]);
    printf("a: %p, a+1: %p, a+2: %p, a+3: %p\n", a, a+1, a+2, a+3);
    printf("a(lld): %lld, a+1(lld): %lld, a+2(lld): %lld, a+3(lld): %lld\n", a, a+1, a+2, a+3);
    // p = &x;
    // for (int i = 0; i < 4; i++) { a[i] = i; }
    // x = 4;
}

// 函数声明
void printRepeatedChar(char ch, int count);

void array_pointer_example() {
    int *p, a[4], x;
    printf("----int *p, a[4], x;----\n");
    printf("p_size: %zu, a_size: %zu, x_size: %zu\n", sizeof(p), sizeof(a), sizeof(x));
    printf("p_addr: %p, a_addr: %p, x_addr: %p\n", &p, &a, &x);
    p = &x; // p = x_addr
    p[0] = 1; // or *p = 1; x = 1
    printRepeatedChar('-', 12);
    printf(" p = &x; p[0] = 1;\n");
    printf("*p: %d, p: %p, p_addr: %p, x: %d, x_addr: %p\n", *p, p, &p, x, &x);
    *a = 2; // a[0] = 2
    printRepeatedChar('-', 12);
    printf("*a = 2;\n");
    printf("a[0]: %d, a: %p, a_addr: %p\n", a[0], a, &a);
}

int my_strlen(char s[]) {
    int n = 0;
    while (s[n] != '\0') {n++;}
    return n;
}
void string_example() {
    char str[] = "abcd";
    const char letters[] = {'a', 'b', 'c', 'd', '\0'};
    printf("char str[] = \"abcd\"; const char letters[] = {'a', 'b', 'c', 'd', '\\0'};\n");
    printf("str_size: %zu, letters_size: %zu\n", sizeof(str), sizeof(letters));
    printf("str_len: %d\n", my_strlen(str));
}

void equal_example() {
    int a = 1;
    int b = 2;
    int c = b-1;
    printf("a_addr: %p, c_addr: %p\n", &a, &c);
    if (a == c) {
        printf("a == c\n");
    } else {
        printf("a != c\n");
    }

    char char_a = 'a';
    char char_b = 'b';
}

void string_ptr_example() {
    char str1[] = "abcd", str2[10], str3[]="hello", *str4="world";
    const char letters[] = {'a', 'b', 'c', 'd', '\0'};
    printf("char str1[] = \"abcd\", str2[10], str3[]='hello', *str4=\"world\";\n");
    printf("const char letters[] = {'a', 'b', 'c', 'd', '\\0'};\n");
    printRepeatedChar('-', 12);

    printf("*str1: %c\n", *str1);
    printf("*(str1+1): %c\n", *(str1+1));
    printf("*(str4): %c\n", *str4);
    printf("*(str4+1): %c\n", *(str4+1));
    printf("*(str4+2): %c\n", *(str4+2));
    printf("*(str4+3): %c\n", *(str4+3));
    printf("*(str4+4): %c\n", *(str4+4));
    if (*(str4+5) == '\0') {
        printf("*(str4+5) == '\\0'\n");
    }
    printRepeatedChar('-', 12);
}

size_t max_sizeof_str(char *str1, char *str2) {
    return sizeof(str1) > sizeof(str2) ? sizeof(str1) : sizeof(str2);
}
#include <string.h>
int my_strcmp(char *s1, char *s2) {
    int i = 0;
    while (s1[i] == s2[i]) {
        if (s1[i] == '\0') {return 0;}
        i++;
    }
    return s1[i] - s2[i];
}
void string_example_p() {
    char str1[] = "abcd", str2[10], str3[]="hello", *str4="world";
    const char letters[] = {'a', 'b', 'c', 'd', '\0'};
    printf("char str1[] = \"abcd\", str2[10], str3[]='hello', *str4=\"world\";\n");
    printf("const char letters[] = {'a', 'b', 'c', 'd', '\\0'};\n");
    printRepeatedChar('-', 12);

    printf("str_size: %zu, letters_size: %zu\n", sizeof(str1), sizeof(letters));
    printf("strlen(str): %zu, strlen(letters): %zu\n", strlen(str1), strlen(letters));
    
    strcpy(str1, "hi");
    strcpy(str2, "hi");
    printf("strcpy(str1, \"hi\"); strcpy(str2, \"hi\");\n");
    printf("str1[]: %s, str2[]: %s\n", str1, str2);
    printf("str2_size: %zu,str2_len: %zu\n", sizeof(str2), strlen(str2));
    if (strcmp(str1, str2) == 0) {
        printf("str1 and str2 are identical\n");
    }

    // if (str1 == str2) {printf("str1 == str2\n");}
    // 这个做法是在比较两个str的addr因为，字符串是数组，变量对应的是数组的首地址
    if (my_strcmp(str1, str2) == 0) {
        printf("str1 and str2 are identical\n");
    }

    if (strcmp(str1, letters) == 0) {
        printf("str1 and letters are identical\n");
    } else {
        printf("str1 and letters are different\n");
    }

    printRepeatedChar('-', 12);
    strcpy(str2, str3);
    printf("str2_size: %zu,str2_len: %zu\n", sizeof(str2), strlen(str2));
    strcat(str2, str4);
    printf("strcpy(str2, str3); strcat(str2, str4);\n");
    printf("str2: %s\n", str2); // helloworld
    printf("str2_size: %zu,str2_len: %zu\n", sizeof(str2), strlen(str2));
}

void pointer_arithmetic_example() {
    char chr='d', *chr_p=&chr;
    printf("char chr='d', *chr_p=&chr;\n");
    printf("chr_p: %p, chr_p+1: %p\n", chr_p, chr_p+1);
    int char_addr_diff = chr_p+1 - chr_p;
    printf("chr_p+1 - chr_p: %d\n", char_addr_diff);

    int int_=100, *int_p=&int_;
    printf("int int_=100, *int_p=&int_;\n");
    printf("int_p: %p, int_p+1: %p\n", int_p, int_p+1);
    int int_addr_diff = (char *)(int_p+1) - (char *)int_p;
    printf("(char *)int_p+1 - (char *)int_p: %d\n", int_addr_diff);
}

void pointer_add1(int **p) {
    *p = *p + 1;
}
void change_pointer_example() {
    int a[3] = {10, 20, 30};
    printf("int a[3] = {10, 20, 30};\n");
    printRepeatedChar('-', 12);

    printf("a[]_addr: %p\n", a);
    int *a_ptr;
    a_ptr = a; // or int *a_ptr = a;
    printf("int *a_ptr; a_ptr = a;\n");
    printRepeatedChar('-', 12);

    printf("a_ptr: %p\n, &a_ptr: %p\n", a_ptr, &a_ptr);
    pointer_add1(&a_ptr);
    printf("pointer_add1(&a_ptr);\n");
    printf("a_ptr: %p\n, &a_ptr: %p, *a_ptr: %d, a[0]: %d\n", a_ptr, &a_ptr, *a_ptr, a[0]);
}

void pointer_to_pointer_example() {
    int x[] = {2, 4, 6, 8, 10};
    int *p = x; // p points to x[0] or p = &x[0]
    int **pp = &p; // pp = &p
    (*pp)++; // p += 1, p points to x[1]
    (*(*pp))++; // x[1] += 1
    printf("int x[] = {2, 4, 6, 8, 10};\n");
    printf("int *p = x; int **pp = &p; (*pp)++; (*(*pp))++;\n");
    printf("x[0]: %d, *p: %d, **pp: %d\n", x[0], *p, **pp);
}

int main() {
    pointer_to_pointer_example();
    return 0;
}

void printRepeatedChar(char ch, int count) {
    for(int i = 0; i < count; i++) {
        printf("%c", ch);
    }
    printf("\n");
}