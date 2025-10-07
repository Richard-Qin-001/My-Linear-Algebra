# My Linear Algebra - GUI Linear Algebra Tool

A graphical linear algebra calculator developed using **C++** and **Qt6**, providing comprehensive matrix operations with an intuitive user interface.

## Project Overview

This project represents my **first C++ project on GitHub** with two primary objectives:

1. **Familiarize myself with C++ syntax and best programming practices**
2. **Reinforce my understanding of Linear Algebra concepts**, inspired by **MIT 18.06 Linear Algebra**

The project has evolved from a simple console application to a fully-featured GUI application. Thank you for your interest and support!

## ✨ Current Features

### Core Matrix Operations
- **Matrix Transposition** (Aᵀ)
- **Matrix Multiplication** (A × B)
- **Gauss Elimination**
- **Gauss-Jordan Elimination**
- **Matrix Inversion**
- **Determinant Calculation** (Leibniz method and Gauss elimination method)
- **LU Decomposition** (PA = LU)

### Data Input/Output
- **Graphical Matrix Input** - Intuitive matrix data entry through table interface
- **JSON File Support** - Import matrix data from JSON files
- **Real-time Results Display** - Calculation results displayed in formatted tables

### User Interface
- **Modern Dark Theme**
- **Responsive Layout** - Adaptive window resizing
- **Operation Status Indicators** - Real-time calculation status and error messages

## 🚀 Quick Start

### System Requirements
- **Windows** (tested) or **Linux** (supported for compilation)
- **Qt 6.9.3** or higher
- **CMake 3.16** or higher
- **C++17** compatible compiler

### Building Steps

#### Method 1: Using CMake (Recommended)
```bash
# Clone repository
git clone https://github.com/Richard-Qin-001/My-Linear-Algebra.git
cd My-Linear-Algebra

# Create build directory
mkdir build && cd build

# Configure project
cmake ..

# Compile
make -j4

# Run application
cd ../bin
./MyLinearAlgebraApp
```

#### Method 2: Using VSCode
1. Open project root directory in VSCode
2. Install CMake Tools extension
3. Press `Ctrl+Shift+P`, select "CMake: Configure"
4. Press `Ctrl+Shift+P`, select "CMake: Build"

### Pre-built Version
For Windows users, we provide pre-compiled executables:
1. Download the latest release
2. Extract to any directory
3. Run `MyLinearAlgebraApp.exe`

## 📖 User Guide

### Basic Operations
1. **Input Matrix**: Enter matrix data in the main table, or load JSON files via menu
2. **Adjust Size**: Use row/column input boxes to resize matrix
3. **Select Operation**: Choose desired matrix operation from dropdown menu
4. **Execute Calculation**: Click "Process" button to view results

### JSON File Format
Supports matrix import from JSON files, format example:
```json
[[1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]]
```

## 🛠️ Technology Stack

- **Programming Language**: C++17
- **GUI Framework**: Qt6
- **Build System**: CMake
- **Compiler**: MinGW (Windows) / GCC (Linux)

## 📁 Project Structure

```
My-Linear-Algebra/
├── src/                 # Source code directory
│   ├── main.cpp         # Program entry point
│   ├── mainwindow.cpp   # Main window logic
│   └── *.cpp           # Various matrix operation implementations
├── resources/           # Resource files
│   └── MyLinearAlgebra.ui  # Qt UI file
├── scripts/             # Build and packaging scripts
├── build/               # Build directory
└── bin/                 # Output directory
```

## 🔮 Future Plans

- [ ] **Eigenvalues and Eigenvectors** calculation
- [ ] **Singular Value Decomposition** (SVD)
- [ ] **QR Decomposition**
- [ ] **Matrix Visualization** features
- [ ] **Linear Equation System** solver
- [ ] **Complex Matrix** support
- [ ] **Performance Optimization** and parallel computing

## 🤝 Contributing

Welcome to submit Issues and Pull Requests! For new feature suggestions or bug reports, please provide detailed descriptions.

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📞 Contact

For questions or suggestions, please contact through:
- GitHub Issues: [Project Issues Page](https://github.com/Richard-Qin-001/My-Linear-Algebra/issues)

---

*If this project helps you, please give it a ⭐!*
```