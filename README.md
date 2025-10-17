# kramdb

A simple **in-RAM database system** written in C++.  
This library allows you to dynamically create tables, rows, cells, and variables during runtime.  
It is header-only (with one `.hpp` file) and easy to integrate into any C++17+ project via simple namespace. No API, or side processes.  

## 📥 Installation

Clone the repository or copy the file **`kramdb.hpp`** into your project:  

```bash
git clone https://github.com/krejciad/kramdb.git
```

Then include it in your source code:

```cpp
#include "kramdb.hpp"
```

No external dependencies are required beyond the C++ standard library.  

## 🚀 Quick Start

### 1. Create a new table
```cpp
DB::NEW();
```

Create a instance of table in vector as DB::TABLE[id], id starts on 0.

### 2. Add rows and cells
```cpp
DB::TABLE[0].NEW();
DB::TABLE[0].ROW[0].NEW();
```

Same system as with tables.

### 3. Add variables
```cpp
DB::TABLE[0].ROW[0].CELL[0].NEW(TYPE::Integer);
DB::TABLE[0].ROW[0].CELL[0].cellInteger[0] = 15;
```

Current supported TYPEs are Integer, Float, Boolean and String.

### 4. Print data
```cpp
std::cout << DB::PRINT(table);   // compact one-line output
std::cout << DB::TREE(table);    // pretty tree structure
```

And, of course, you can print the variables directly:

```cpp
std::cout << DB::TABLE[0].ROW[0].CELL[0].cellInteger;
```

## 📌 Examples

### Example 1: Creating and printing a table
```cpp
#include "kramdb.hpp"
#include <iostream>

int main() {
    DB::NEW();              // create table
    tableObj& t = DB::TABLE[0];

    t.NEW();                // row 0
    t.ROW[0].NEW();         // cell 0

    // add data
    t.ROW[0].CELL[0].NEW(TYPE::Integer);
    t.ROW[0].CELL[0].cellInteger[0] = 100;

    t.ROW[0].CELL[0].NEW(TYPE::String);
    t.ROW[0].CELL[0].cellString[0] = "User";

    // print results
    std::cout << DB::PRINT(t);
    std::cout << DB::TREE(t);
}
```

### Example 2: Removing items
```cpp
// Remove row 0 from the table
DB::REMOVE(t.ROW, 0);

// Remove cell 0 from row 0
DB::REMOVE(t.ROW[0].CELL, 0);
```

### Example 3: Demo table
The library provides a quick way to generate a sample table for testing:

```cpp
tableObj demo;
DB::createDemoTable(demo);

std::cout << DB::TREE(demo);
```

### Example 4: Easter Egg
```cpp
std::cout << DB::easterEgg(1);
```

## 🛠 Interface Overview

- `DB::NEW()` → create a new table in memory  
- `tableObj.NEW()` → add a new row to a table  
- `tableRowObj.NEW()` → add a new cell to a row  
- `tableCellObj.NEW(TYPE type)` → add a variable (Boolean, Integer, String, Float) to a cell  
- `DB::REMOVE(container, index)` → remove element from a vector (table, row, or cell)  
- `DB::PRINT(table)` → return compact string of table contents  
- `DB::TREE(table)` → return pretty-printed structure of table  
- `DB::createDemoTable(table)` → generate a pre-filled test table  
- `DB::easterEgg(n)` → print a fun easter egg  

## 📄 License
Licensed under **Creative Commons CC-BY-SA ©2025**.  
See [LICENCE.txt](LICENCE.txt).  
