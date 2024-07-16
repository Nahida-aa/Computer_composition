# Memory

- [1 Memory Layout](#1-memory-layout)
- [2 Addressing and Endianness](#2-addressing-and-endianness)
- [3 Dynamic Memory Allocation](#3-dynamic-memory-allocation)
- [4 Common Memory Problems](#4-common-memory-problems)
- [5 Wrap-up: Link List Example](#5-wrap-up-link-list-example)

## 1 Memory Layout

- Stack: 存放函数的局部变量、函数参数、返回地址等信息。

- Static Data: 存放全局变量、静态变量等。

- Code: 存放程序的指令。

<div style="display: flex;">
  <table>
    <tr>
      <td>Stack</td>
    </tr>
    <tr style="border-top: 2px dashed;">
      <td style="height:60px;">
        <div style="text-align: center; margin-top: -10px;">&darr;</div>
        <br><br>
        <div style="text-align: center; margin-bottom: -10px;">&uarr;</div>
      </td>
    </tr>
    <tr style="border-top: 2px dashed;">
      <td>Heap</td>
    </tr>
    <tr>
      <td>Static Data</td>
    </tr>
    <tr>
      <td style="height:35px;">Code</td>
    </tr>
  </table>
  <div style="margin-left: 20px; height:100%;">
    <div style="margin-top: 0px;">~FFFF FFFF<sub>hex</sub></div>
    <br><br><br><br><br><br><br><br>
    <div style="margin-bottom: 0px;">~0<sub>hex</sub></div>
  </div>
</div>

OS prevents accesses between stack and heap. (via virtual memory)

- Program's address space contains 4 regions:
  - Stack: local variables, grows downward
  - Heap: space requested via `malloc()` and used with pointers; resizes dynamically, grows upward
  - Static Data: global and static variables, does not grow or shrink
  - Code: loaded when program starts, does not change

**Where Do the variables Go?**:

```C
#include <stdio.h>

int global_var; // Static Data

int main() {
    int local_var; // Stack
    int *dynamic_var = (int *)malloc(sizeof(int)); // Heap
}
```

### stack

- Each stack frame is a contiguous black of memory bolding the local variables of a single procedure
- A stack frame includes:
  - Location of caller function
  - Function arguments
  - Space for local variables
- Stack pointer (SP) tells where lowest(current) stack frame is
- When procedure ends, stack pointer is moved back (but data remains(garbage!));frees memory for future stack frames

## 2 Addressing and Endianness

## 3 Dynamic Memory Allocation

- Heap

## 4 Common Memory Problems

## 5 Wrap-up: Link List Example
