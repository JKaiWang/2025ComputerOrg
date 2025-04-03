# Homework 1

## 第一題 Array Sort 
### inline Assembly 說明
1. ``` slli t0, %[j], 2 ```
   * to multiply index j by 4 to convert it into a byte offset(since each int is 4 byte)
2. ``` add t1, %[base], t0 ```
   * Add the base address of the array to the offset to get the memory address of arr[j]
3. ```lw t2, 0(t1)```
    * Load the value of arr[j] into register **t2**
4. ``` lw ,t3 , 4(t1) ```
    * load the value of arr[j] into register t2
5. ``` blt t2, t3, 1f ```
    * if arr[j] < arr[j+1], jump to the label11 to skip the swap 
6. ``` sw t3, 0(t1) ```
    * store the value of arr[j+1] into arr[j]
7. ``` sw t2, 4(t1) ```
   * store the original value of arr[j] into arr[j+1], completing the swap
8. 1: 
    * A label for conditinal branching
  
### Challenge and Solutions 
1. Incorrect Offset Calculation 
   * Issue : Initially forgot to multiply the array index by4, leading to wrong memory addresses.
   * Solution : Used slli to shift the index left by 2 bits(equivalent to multiplying by 4) ensuring proper byte addressing 
2. Incorrect Addressing of Next Element 
   * Issue: Incorrectly assumed that the next element was at +1, Instead of +4 byte
   * Solution: Used ``` lw t3, 4(t1) ``` to correctly load arr[j+1]
3. Inverted Swap Condition
    * Issue: Used incorrect conditional branch instructions, causing incorrect swaps
    * Solution: Used ``` blt t2, t3, 1f ``` to only execute the swap when arr[j] > arr[j+1]. 
4. Missing Clobbered Register declarations
    * Issue: Compiler optimizations caused unexpected behavior sue to missing clobber lists.
    * Solutions: Declared "t0", "t1", "t2", "t3", "memory" as clobbered in the asm volatile() statement to ensure correctness.
### Reflection 
This exercise gave me a deeper appreciation of how high-level logic in C translates to low-level operations in assembly. Although Bubble Sort is conceptually simple, implementing it in inline RISC-V assembly exposed the underlying complexity of even basic memory operations and conditional logic.

One of the biggest challenges was debugging inline assembly. Unlike debugging regular C code, there are no clear error messages or line numbers when something goes wrong. Instead, I had to reason about each instruction carefully, check memory behavior manually, and isolate logic using controlled test cases. This forced me to slow down, think in terms of data movement and memory layout, and develop a more disciplined approach to debugging.

Another key takeaway was how important it is to declare clobbered registers and understand how the compiler interacts with inline assembly. I learned that without specifying registers and memory dependencies, the compiler might optimize around them in unexpected ways.

Overall, this assignment not only taught me the syntax and semantics of RISC-V instructions, but also made me appreciate the "invisible work" the compiler does in normal C programs. It sharpened my understanding of memory layout, byte addressing, and the importance of precise control when programming close to the hardware.

## 第二題 array search 
### inline assembly 說明
