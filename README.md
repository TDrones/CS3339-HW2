# CS339 Homework 2 - Floating Point Overflow Checker

## Team Members
Tyrell Drones

## Overview
This program is designed to check for potential floating-point overflow in loops by comparing the exponents of two floating-point numbers using their IEEE-754 32-bit representations of two floating-point numbers provided as command-line arguments. The program checks for the correct number of arguments in which the first argument inputted represents the loop bound, while the second argument represents the loop counter increment. The program compares exponent bits of two floating-point numbers to detect possible overflow and prints the trheshold value in2 deciaml and IEEE-754 format.

## How to Compile
The program is written in C++ and can be compiled using the GNU C++ compiler.

```
g++ main.cpp -o fp_overflow_checker
```

## How to Run
After compiling the program, run the executable from the terminal. When running the program use two floating-point arguments. The first argument should be your loop bound floating-point number and the second argument should be your loop counter floating-point number.

```
./fp_overflow_checker <loop_bound> <loop_counter>
```