# Arrays,Strings,More Pointers

**Struct Clarification**:

- Struct definition:
  -Creates avariable type "struct foo", then declare the variable of that type

  ```C
  struct foo {
    // fields
  };
  struct foo my_foo;
  struct foo *my_foo_ptr;
  ```

- Joint struct definition and typedef
  - Don't need to name struct in this case
  
    ```C
    struct foo {
      // fields
    };
    typedef struct foo bar;
    bar my_bar;

    // or
    typedef struct foo {
      // fields
    } bar;
    bar my_bar;
    ```

## 1 Operator Precedence

| Operator | Description | Associativity |
| :---: | :---: | :---: |
| ++ -- | Suffix/postfix increment/decrement | Left to right |
| () | Function call | Left to right |
| [] | Array subscripting | Left to right |
| . | Structure and union member access | Left to right |
| -> | Structure and union member access through pointer | Left to right |
| (type){list} | Compound literal(C99) | Left to right |
| ++ -- | Prefix increment/decrement | Right to left |
| + - | Unary plus/minus | Right to left |
| ! ~ | Logical NOT/bitwise NOT | Right to left |
| (type) | Type cast | Right to left |
| * | Indirection(dereference) | Right to left |
| & | Address-of | Right to left |
| sizeof | Size-of | Right to left |
| _Alignof | Alignment requirement(C11) | Right to left |

**increment_decrement_example**:

```C
void increment_decrement_example() {
    int x = 1;
    int y = ++x; // x = 2, y = 2
    x--; // x = 1
    int z = x++; // z = 1, x = 2
}
```

### sizeof()

**sizeof_example**:

```C
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
```

#### struct

**sizeof_struct_example**:

```C
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
```

## 2 Arrays

- Declaration:

  ```C
  int ar[2]; // declares a 2-element integer array
  // just a block of memory

  int arr[] = {795, 635}; // declares and initializes a 2-element integer array
  ```

- Accessing elements:

  ```C
  ar[num]; // returns the num^th element of the array
  // zero-indexed
  ```

  ```C
  int ar[10];
  for (int i = 0; i < 10; i++) {...}
  // 使用了两个10，不好, 建议使用下面的写法
  const int ARRAY_SIZE = 10; // 单一事实来源，修改时只用修改一处
  int ar[ARRAY_SIZE];
  for (int i = 0; i < ARRAY_SIZE; i++) {...}
  ```

### Array and Pointer

- `ar[i]` is treated as `*(ar + i)`

  ```C
  // To zero an array, the following three ways are equivalent:
  // 1.
  for (i=0; i<SIZE; i++) {ar[i] = 0;}
  // 2.
  for (i=0; i<SIZE; i++) {*(ar + i) = 0;}
  // 3.
  for (p=ar; p<ar+SIZE; p++) {*p = 0;}
  ```

#### Arrays Stored Differently Than Pointers

**array_pointer_example**:

```C
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
```

## 3 Strings

- A string is an array of characters terminated by a null character `'\0'`

  ```C
  void string_example() {
      char str[] = "abcd"; // {'a', 'b', 'c', 'd', '\0'}
      const char letters[] = {'a', 'b', 'c', 'd', '\0'};
      printf("char str[] = \"abcd\"; const char letters[] = {'a', 'b', 'c', 'd', '\\0'};\n");
      printf("str_size: %zu, letters_size: %zu\n", sizeof(str), sizeof(letters));
  }
  ```

- But how do we know when the string ends?(because array in C don't know their size)
  - Last character is followed by a 0 byte ('\0') (a.k.a. "null terminator")
- How do you tell how long a C string is?
  - Count until you reach the null terminator

  ```C
  int strlen(char s[]) {
      int n = 0;
      while (s[n] != '\0') {n++}
      return n;
  }
  ```

- Danger What if there is no null terminator?
  - Undefined behavior
  - The program will keep reading memory until it finds a 0 byte

### String Standard Library Functions

- Accessible with `#include <string.h>`

  ```C
  size_t strlen(const char *s); // returns the length(not including '\0') of the string
  char *strcpy(char *dest, const char *src); // copies the string src to dest
  // Copy contents of src to the  memory at dest. Caller must ensure that dest has enough memory to hold the data to be copied
  char *strcat(char *dest, const char *src); // appends the string src to dest
  int strcmp(const char *s1, const char *s2); // compares two strings
  // returns 0 if s1 and s2 sre identical (how is this different from ==?)
  ```

**string_example**:

```C
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
```

## 4 More Pointers

### Pointer Arithmetic

- pointer $\pm$ number
  - e.g. pointer + 1 adds 1 something to the address
- Compare what happens: (assume a at address 100)

  ```C
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
  ```

  Adds 1 * sizeof(type) to the address
- Pointer arithmetic should be used with cautiously
- Pointer is just a memory address, so we can add to/subtract from it to move through an array
- p+1 correctly increments p by sizeof (*p)
  - i.e. moves to the next array element
- What about an array of structs?
  - Struct declaration tells C the size to use, so handled like basic types
- What is valid pointer arithmetic
  - Add an integer to a pointer
  - Subtract 2 pointers (in the same array)
  - Compare pointers (<, <=, ==, !=, >, >=)
  - Compare pointer to NULL (indicates that the pointer points to nothing)
- Everything else is illegal since it makes no sense:
  - Adding two pointers
  - Multiplying pointers
  - Subtract pointer from integer

**Increment and Dereference**:

```C
char *p = "hi";
char c = *p++; // c = 'h', p points to 'i'
c = *p; // c = 'i'
```

```C
char arr[] = "bye";
char *p = arr;
char c = (*p)++; // c = 'b', *p = 'c', arr = "cye"
c = *p; // c = 'c'
```

### Pointer Misc

#### struct and pointer

```C
struct Point {
    int x;
    int y;
    struct Point *p
};
struct Point pt1;
struct Point pt2;
struct Point *ptaddr;

// Valid operations
// dot notation
int h = pt1.x;
pt2.y = pt1.y;
// arrow notation
int h = ptaddr->x;
int h = (*ptaddr).x;
```

#### pointers to pointers

- What if want function to change a pointer?

```C
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
```

**Pointer to Pointer Example**:

```C
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
```
