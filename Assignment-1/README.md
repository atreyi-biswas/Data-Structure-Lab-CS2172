# 📚 Assignment 1 – Array Concepts  
**Course**: Data Structure Lab (CS 2172)  
**Language Used**: C  
**Topic**: Structure & Array of Structures  
**Duration**: 1 week  

---

## 📌 Problem Statement

You are required to implement a simple **Student Register** using a static data structure in C. The register should support basic CRUD operations and file handling functionalities *without using dynamic memory allocation*. Example and other details included in the pdf.

---

## 🧱 Structure Definitions

```c
#define MAX_STUDENTS 10

struct Student {
    char name[20];       // Format: "LastName, FirstName"
    int roll;            // 6-digit unique integer, non-zero start
    char telephone[11];  // Non-empty string
    char address[20];    // Can be empty
};

struct SReg {
    int count; // Initially 0
    struct Student studentArray[MAX_STUDENTS];
};

