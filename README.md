# 📘 Student Record Manager (C++)

The Student Record Manager is a simple C++ console application that allows users to add, list, search, and delete student records. The program stores all data in a text file (`records.txt`) so the records remain available even after closing the app. This project demonstrates file handling, structs, vectors, and menu-driven command-line programming.

---

## 📝 Description

A lightweight menu-based C++ application that manages student records using persistent text storage. Users can add a student's ID, Name, and GPA, view all records in a formatted table, search by ID, and delete specific entries. Ideal for learning C++ file I/O and basic data management.

---

## ✅ Features

- Add student record (ID, Name, GPA)  
- List all stored records  
- Search for records by ID  
- Delete a student by ID  
- Data saved in `records.txt`  
- Clean, easy-to-use CLI interface  

---

## 🛠️ Technologies Used

- **C++11**  
- File I/O (`ifstream`, `ofstream`)  
- STL (`vector`, `string`, `iomanip`)  

---

## ▶️ How to Compile & Run

### Compile
```bash
g++ -std=c++11 main.cpp -o student_manager
