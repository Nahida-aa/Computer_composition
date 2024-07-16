# Intro,Pointers-Number

## 1 Overview

- Basic C Concepts
  - Compiler
  - variable Types
- C Syntax and Control Flow
- Pointers
  - Address vs. Value

**C Concepts**:

These concepts distinguish C from other programming languages that you may know:

| Concept | Description |
| --- | --- |
| Compiler | Creates useable programs from C source code. |
| Typed variables | Must declare the kind of data the variable will contain. |
| Typed functions | Must declare the kind of data the returned from the function. |
| Header files (.h) | Allows you to declare functions and variables in separate files. |
| Structs | Groups of related values |
| Enums | Lists of predefined values |
| Pointers | Aliases to other variables |

## 2 Compilation

- C is a **compiled** language
- C compilers map C program into architecture-specific machine code (string of 0s and 1s)
  - Unlike Java, which converts to architecture-independent bytecode (run by JVM)
  - Unlike Python, which directly Interprets the code
  - Main difference is when your program is mapped to low-level machine instructions

### Compilation Advantages

- **Excellent run-time performance**:
  Generally much faster than Python or Java for comparable code because it **optimizes for the given architecture**
- **Fair compilation time**:
  enhancements in compilation procedure (Makefile**s**) allow us to **recompile only the modified files**

### Compilation Disadvantages

- Compiled files, including the executable, are architecture-specific (CPU type and OS)
  - executable must be **rebuilt** on each new system
  - i.e "porting your code" to a new architecture
- **Edit -> Compile -> Run [repeat]** iteration cycle can be slow

## 3 Typed Variables in C

You must declare the type of data a variable will hold  
Declaration must come before or simultaneous with assignment

```c
int x; // declare x as an integer
x = 5; // assign 5 to x
float y = 618; // declare y as a float and assign 618
char z = 'A'; // declare z as a char and assign 'A'
```

| K&R | C90 | C99 |
| --- | --- | --- |
| int | signed | _Bool |
| long | void | _Complex |
| short |   | _Imaginary |
| unsigned |   |   |
| char |   |   |
| float |   |   |
| double |   |   |

| Type | Description | Size | Range | Example |
| --- | --- | --- | --- | --- |
| int | Integer | 4 Byte | -2,147,483,648 to 2,147,483,647 | 42,-12,0 |
| long | Long integer | 4 Bytes | -2,147,483,648 to 2,147,483,647 ||
| short | Short integer | 2 Bytes | -32,768 to 32,767 | |
| unsigned | 0 to 255 | 1 Byte | 0 to 255 | 0, 255 |
| signed | -128 to 127 | 1 Byte | -128 to 127 | -128, 127 |
| char | Character or small integer | 1 Byte | -128 to 127 or 0 to 255 | 'A', '6','?' |
| float | Single-precision floating point | 4 Bytes | 2E-38 to 3.4E+38 | 3.14, -0.5, 0 |
| double | Double-precision floating point | 8 Bytes | 2.3E-308 to 7E+308 | |
| long double | Extended-precision floating point | 10 Bytes | 3.4E-4932 to 1E+4932 | |
| _Bool | Boolean | 1 Byte | 0 to 1 | 0, 1 |
| void | No value | 0 Bytes | N/A | N/A |
| _Complex | Complex number | 8 Bytes | N/A | |
| _Imaginary | Imaginary number | 4 Bytes | N/A | |

- **Integer sizes are machine dependant!**
  - Common size is 4 or 8 bytes (32 / 64 bits), but can't ever assume this
- **Can add "unsigned" before int or char

### [Characters](./table/Characters.md)

- Encode characters as number, same as everything!
- ASCII (American Standard Code for Information Interchange) standard defines 128 different characters and their numeric encodings (<http://www.asciitable.com/>)
  - char representing the character 'a' contains the value 97
  - char c = 'a'; or char c = 97; are both valid

- <c style="color:red"><b>A</b> char <b>take up 1 byte of space<b></c>
  - 7 bits is enough to store a char ($2^7 = 128$), but we add a bit to round up to 1 byte since computers usually deal with multiples of bytes

### Typecasting in C

- C is "weakly" typed language
  - You can explicitly typecast from any type any type to any other:

    ```C
    int i = -1;
    if(i < 0)
        printf("This will print, and i is %d.\n", i); // -1
    if((unsigned int)i < 0)
        printf("This will not print, and i is %u.\n", i); // 2^32 - 1
    ```

- Can typecast anything, even if it doesn't make sense:

  ```C
  struct node n; // structs in a few slides
  int i = (int)n;
  ```

  - More freedom, but easier to shoot yourself in the foot

### Typed Function in C

- You have to declare the type of data you plan to return from a function
- Return type can be any C variable type ot void for no return value
  - Place on the left of function name
- Also necessary to define types for function arguments
- Declaring the "prototype" of a function allows you to use it before function' definition

  声明函数的“原型”允许您在函数定义之前使用它

```c
// function prototype
int my_func(int, int);
void sayHello();

// function definition
int my_func(int x, int y) {
    sayHello();
    return x*y;
}
void sayHello() {
    printf("Hello!\n");
}
```

### Structs in C

- Way of defining compound data types
- A structured group of variables, possibly including other structs
  - Think of it as an instruction to C on how to arrange a bunch of bits in a bucket

```C
typedef struct {
    int lengthInSeconds;
    int yearRecorded;
} Song;

Song song1;
song1.lengthInSeconds = 213;
song1.yearRecorded = 1994;

Song song2 = {248, 1988};
```

#### Structs Alignment and Padding in C

```c
Struct foo {
    int a;
    char b;
    struct foo *c;
};

printf("Size of struct foo: %lu\n", sizeof(struct foo));
```

- They provide enough space and **aligns** the data with padding!
- The actual layout on a 32 bit architecture would be:
  - 4 bytes for a
  - 1 byte for b
  - 3 bytes of padding
  - 4 bytes for c
  - Sizeof(struct foo) == 12 bytes

#### Unions in C

- A "union" is also an instruction to C on how to arrange a bunch of bits
- _

  ```c
    union foo {
        int a;
        char b;
        union foo *c;
    };

  printf("Size of union foo: %lu Byte\n", sizeof(union foo));
  ```

- Provides enough space for the **largest member**
- _

  ```C
  union foo f;
  f.a = 0xDEADB33F; // treat f as an integer and store that value
  f.c = &f;  // treat f as a pointer of type "union foo *" and store the address of f in itself
  ```

#### compare C and Java

| item | C | Java |
| --- | --- | --- |
| Type of Language | Function Oriented | Object Oriented |
| Programming Unit | Function | Class = Abstract Data Type |
| Compilation | Creates machine-dependent code | Creates machine-independent bytecode |
| Execution | Loads and executes program | JVM interprets bytecode |
| Hello World | #include<stdio.h><br>int main(void) {<br> $\quad$ printf("Hello\n");<br>$\quad$ return 0;<br>} | public class HelloWorld {<br> $\quad$ public static void main(String[] args) {<br> $\quad\quad$ System.out.printl("Hello");<br> $\quad$ }<br>} |
| Memory Management | Manual(malloc, free) | Automatic (Garbage Collection) |

## 4 C Syntax and Control Flow

### C Syntax

#### Generic C Program Layout

```c
#include <system_files>
#include "local_files"

#define macro_name macro_expr

// declare functions
// declare global variables and structs

int main(int argc, char *argv[]) {
    // the innards
    return 0;
}

// define other functions
```

#### main

- To get arguments to the main function, use:
  - `int argc`: number of arguments
  - `char *argv[]`: array of arguments
- What does this mean?
  - argc (argument count) contains the number of string on the command line (the executable path counts as one, plus one for each argument)
  - argv (argument vector) is an array of strings, each containing one of the arguments

**Example**:

./foo hello 87

- Here argc = 3 and the array argv contains pointers to the following strings:<br>
  argv[0] = "./foo/"<br>
  argv[1] = "hello"<br>
  argv[2] = "87"
- We will cover pointers and strings later

#### Variable Declarations

- All variable declarations must appear before they are used (e.g. at the beginning of a block of code)
- A variable may be initialized in its declaration; if not , it holds garbage!
- Variables of the same type may be declared on the same line
- Examples of declarations:
  - Correct:
  
    ```C
    int x;
    int a, b=10, c;
    ```

  - Incorrect:
  
    ```C
    short x=1, float y=1.0;
    ```

#### True or False

- No explicit Boolean type in C (unlike Java)
- What evaluates to False in C?
  - 0 (integer)
  - NULL (a special kind of pointer: more on this later)
- What evaluates to True in C?
  - Anything that isn't false is True
  - Same idea as in "Scheme": only #f is false, everything else is true

### Control Flow

- Should be similar to what you've seen before
  - if-else

    ```C
    if(expression) {/* do something*/} 
    ```

    ```C
    if(expression) {/* do something*/} 
    else {/* do something else*/}
    ```

  - while
  
      ```C
      while(expression) {
        /* do something*/
      }
      ```

      ```C
      do {
        /* do something*/
      } while(expression);
      ```

  - for
  
      ```C
      for(initialization; expression; update) {
        /* do something*/
      }
      ```

  - switch

      ```C
      switch(expression) {
        case constant1:
          /* do something*/
          break;
        case constant2:
          /* do something*/
          break;
        default:
          /* do something*/
      }
      ```

#### switch and break

- Case statement (switch) requires proper placement of break to work properly
  - "Fall through" effect: will execute all cases until a break is found

    ```c
    switch(ch) {
      case '+': /* does + and - */
      case '-':/*...*/ break;
      case '*': ... break;
      default: ...
    }
    ```

  - In certain cases, can take advantage of this

### Has there been an update to ANSI C?

- Yes! There have been a few.
- We use "C99" or "C9x" std
  - Use option `gcc -std=c99` at compilation
- References:
  - <http://en.wikipedia.org/wiki/C99>
  - <http://home.datacomm.ch/t_wolf/tw/c/c9x_changes.html>
- Highlights
  - Declarations in for loops, like Java (#15)
  - Java-like // comments (to end of line) (#10)
  - Variable-length non-global arrays (#33)
  - \<inttypes.h\> for explicit integer types (#38)
  - \<stdbool.h\> for boolean logic definitions (#35)

## 5 Pointers

### Address vs. Value

- Consider memory to be a single huge array
  - Each cell/entry of the array has an address
  - Each cell also stores some value
- Don't confuse the address referring to a memory location with the value stored there

### Pointers Syntax

```C
int *x; // declare variable x as the address of an integer
// 声明 a var x 为一个整数的地址
x = &y; // assign the address of y to x
// 取 y 的地址赋给 x
// & called the "address operator" in this context
z = *x; // assign the value at the address x to z
// 将地址为 x 的值赋给 z (解引用: get地址为x的值 赋给z)
// * called the "dereference operator" in this context
```

**pointer_example**:

```C
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
```

#### Pointer Type

- Pointers are used to point to one kink of data (`int`, `char`, a `struct`, etc.)
  - Pointers to pointers? Oh tes! (e.g. `int **pp`)
- Exception is the type `void *`, which can point to anything (generic pointer)
  - Use sparingly to help avoid program bugs and other bad things!
- Functions can return Pointers

  ```C
  char *aa() {
      return "Hello World";
  }
  ```

- placement of `*` does not matter to compiler, but might to you
  
    ```C
    int* x; // same as int *x;
    int *y, z, t; // is the same as int* y, z, t; but not the same int *y, *z, *t;
    ```

#### Pointers and Parameter Passing

- Java and C pass parameters "by value"
  - Procedure/function/method gets a copy of the parameter, so changing the copy does not change the original
- How do we get a function to change a value?
  - Pass "by reference": function accepts a pointer and then modifies value by dereferencing it

    ```C
    void func_parameter_example() {
        void add_one(int x) {
            x = x + 1;
        }
        int y = 3;
        add_one(y);
        printf("y is still %d\n", y); // y is still 3

        void add_one_fixed(int *p) {
            // p = &y;
            *p = *p + 1;
        }
        add_one_fixed(&y);
        printf("y is now %d\n", y); // y is now 4
    }
    ```

#### Pointers in C

- Why use pointers?
  - When passing a large struct or array, it's easier/faster to pass a pointer than a copy of the whole thing
  - In general, pointers allow cleaner, more compact code
- Careful: Pointers are likely the single largest source of bugs in C
  - Most problematic with dynamic memory management, which cover later
  - Dangling references and memory leaks
- Local variables in C are not initialized, they may contain anything (a.k.a. "garbage")
- Declaring a pointer just allocates space to hold the pointer-it does not allocate the thing being pointed to!

```C
void pointer_err_example() {
    // err1
    int *p, x;
    // p 的值是一个地址，但是这个地址是随机的，所以 p 指向的值也是随机的
    x = *p; // x is now garbage, 因此x会得到一个随机的值，存在安全问题

    // err2
    int *ptr; // ptr 是 random address
    *ptr = 5; // a random address 上的值被赋值为5，很危险
}
```

## Summary

- C is an efficient (compiled) language, but leaves safety to the programmer
  - Weak type safety, variables not auto-initialized
  - Use pointers with care: common source!
- Pointer is a C version (abstraction) of a data address
  - Each memory location has an address and a value stored in it
  - `*` "follows" a pointer to its value
  - `&` "gets" the address of a variable
- C functions "pass by value"

miscellaneous
