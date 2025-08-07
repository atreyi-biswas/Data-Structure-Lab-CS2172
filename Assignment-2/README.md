# 📚 Data Structure Lab Assignment 2 – Stack (CS 2172)

Welcome to **Assignment 2** of the **Data Structure Lab**! In this assignment, you'll implement an **integer stack** in C, simulate stack operations across two stacks, and check the correctness of mathematical expressions using parentheses. 🧠

> 🕒 **Deadline**: 1 Week &nbsp; | &nbsp; 💻 **Language**: C &nbsp; | &nbsp; 📂 **Course**: CS 2172

---

## 🚀 What You'll Build

### ✅ 1. Integer Stack Implementation
Implement a reusable integer stack with full functionality:

| 🔢 Function | 💡 Description |
|------------|----------------|
| `int initIntegerStack(stack s, int stackSize)` | Initializes a stack of size `stackSize`. |
| `int pushIntegerStack(stack s, int d)` | Pushes `d` into stack `s`. Returns `1` on success, `0` if full. |
| `int popIntegerStack(stack s, int *dp)` | Pops the top of stack `s` into `*dp`. Returns `1` on success, `0` if empty. |
| `int freeIntegerStack(stack s)` | Frees allocated memory. Returns `1` on success, `0` if invalid. |
| `int isIntegerStackFull(stack s)` | Returns `1` if full or invalid, `0` otherwise. |
| `int isIntegerStackEmpty(stack s)` | Returns `1` if empty or invalid, `0` otherwise. |

> 🔧 You'll also define a `typedef` for the stack structure to allow multiple instances.

---

### 🔁 2. Stack Simulation with Two Stacks

Simulate dynamic stack usage with two separate stacks:
- Create `stack1` and `stack2` of sizes `N` and `M`.
- Read integers from the user:
  - Push to `stack1` until full.
  - Then push to `stack2`.
- When `stack2` becomes full:
  - Pop and print all elements from `stack2` ➡️ then from `stack1`.

🎯 *Goal:* Simulate overflow and LIFO behavior across multiple stacks.

---
### 🧮 3. Parenthesis Matching (Sanity Check)

Use your stack to check if mathematical expressions have **balanced parentheses**.

✅ **Valid** examples:
- `{ ( A + B ) * C } + D`
- `( [ A + B ] - C )`

❌ **Invalid** examples:
- `[ ( A + B )`
- `( A + B ) } – ( C + D`

🎯 *Goal:* Apply your stack to a real-world use case — parsing expressions.

---


## 🧪 Demo Program

A sample `main()` should:
- Initialize a stack and demonstrate all six functions.
- Run the two-stack simulation.
- Take input of expressions and check for valid parentheses.

---

## 📌 Notes

- Use dynamic memory (`malloc` / `free`) for stack management.
- Use `scanf`/`printf` for input and output.
- Keep your code clean and well-commented 💬

---

> ⚠️ _This is an academic assignment. Please ensure your submission is original and well-documented._

