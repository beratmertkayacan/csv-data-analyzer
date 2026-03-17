# 📊 High-Performance Taxi Trip Analyzer (C++)

A highly optimized C++ engine designed for ingesting and analyzing large-scale urban transportation datasets. This tool processes millions of rows of CSV data to extract top-performing zones and peak activity time slots with minimal latency.

## 🚀 Technical Excellence & Optimizations

This project focuses on overcoming performance bottlenecks in data engineering through:

- **Ultra-Fast I/O Operations:** Implemented `ingestStdin` with `ios_base::sync_with_stdio(false)` and `cin.tie(nullptr)` to achieve high-speed data stream processing, bypassing slow standard file I/O.
- **Custom Composite Hashing:** Developed a specialized `SlotHash` and `SlotKey` structure to handle multidimensional data (Zone ID + Hour) with $O(1)$ average lookup complexity.
- **Proactive Memory Management:** Utilizes `.reserve()` on `unordered_map` and `vector` structures based on expected data volume to eliminate costly runtime reallocations.
- **Algorithmic Efficiency:** Employs `std::partial_sort` to retrieve Top-K results in $O(N \log K)$ time, ensuring the system scales efficiently even with millions of records.
- **Robust Parsing:** Built-in "Dirty Data" handling that robustly parses malformed CSV rows without interrupting the analysis flow.

## 🛠️ Tech Stack

- **Language:** C++17
- **Core Concepts:** Hash Maps, Memory Optimization, Time Complexity Analysis, Data Stream Parsing.


---

### 🎓 Academic Context & Attribution
This repository was developed as part of the **CMP2003 – Data Structures and algorithms** course. 

**Key Notes on Implementation:**
- **Core Files:** My primary contributions and technical optimizations are implemented within the `analyzer.h` and `analyzer.cpp` files.
- **Project Origin:** The project structure and initial requirements were provided by the Bahçeşehir University Computer Engineering department.
- **Independent Optimizations:** While the interface follows the course requirements, the performance-oriented architectural decisions (such as fast I/O and custom hashing) were independently developed to optimize the solution for large-scale datasets.
