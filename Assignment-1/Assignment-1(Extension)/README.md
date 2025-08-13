# 📌 Data Structure Lab – Assignment 1 Extension (CS 2172) – Dynamic Memory Allocation  

## 📜 Overview  
This assignment extends the **Student Register Management System** from Assignment 1 by using **dynamic memory allocation**.  
It removes the fixed-size constraints and allocates memory **at runtime** based on actual user input.  

---

## 🏗️ Data Structures  

### **Student Structure**
```c
typedef struct Student {  
    char *name;        // dynamically allocated to exact length of name  
    int roll;  
    char telephone[11];  
    char *address;     // dynamically allocated to exact length of address  
} Student;
```

### **Student Register Structure (Dynamic)**
```c
typedef struct SReg {  
    int maxStuds;      // maximum number of students (runtime input)  
    int count;         // number of student records  
    Student **arrStudPtr; // dynamically allocated array of Student pointers  
} SReg;
```

---

## 🛠️ Functional Requirements  

| Function | Description |
|----------|-------------|
| `Student * createStudentRecord(...)` | Dynamically allocates memory for a new `Student`, takes user input, allocates exact-length memory for `name` and `address`. Returns pointer to `Student` or `NULL` on failure. |
| `Student * createStudentRecordFromFile(...)` | Creates a `Student` record from file data (allocates memory accordingly). |
| `void freeStudentRecord(Student *sp)` | Frees all memory allocated for a `Student` record. |
| *(All original Assignment-1 register functions)* | Should be modified to work with dynamically allocated student records. |

---

## 📂 Files in Repository  

| File | Description |
|------|-------------|
| `assignment1_ext_dynamic.c` | Full implementation of dynamic student register with all features. |

---

## ⚙️ Compilation & Execution  
```bash
gcc assignment1_ext_dynamic.c -o assignment1_ext_dynamic
./assignment1_ext_dynamic
```

---

## 🎯 Learning Outcomes  
- Understanding **dynamic memory allocation** in C.  
- Using `malloc`, `calloc`, and `free` effectively.  
- Managing **arrays of pointers to structures**.  
- Implementing **memory-efficient string storage** for struct fields.  
- Extending a fixed-size program into a **scalable dynamic program**.  

