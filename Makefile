# Makefile for Matrix Operations Program

# ----------------------------------------------------------------------
# Configuration
# ----------------------------------------------------------------------
CXX         = g++
CXXFLAGS    = -Wall -std=c++11 -O2
TARGET      = matrix_app
BUILD_DIR   = build
BIN_DIR     = bin
SRC_FILES   = io_matrix.cpp Gauss_Elimination.cpp permutation.cpp transpose.cpp multiply.cpp main.cpp determinant-Leibniz.cpp
OBJ_FILES   = $(patsubst %.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))
# Headers are in the current directory, so no need for -I
# ----------------------------------------------------------------------

# ----------------------------------------------------------------------
# Primary Targets
# ----------------------------------------------------------------------

.PHONY: all clean run

# 默认目标：编译所有文件并生成可执行文件
all: $(BIN_DIR)/$(TARGET)

# 生成最终的可执行文件
$(BIN_DIR)/$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	@echo "Linking executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^ 
	@echo "Build successful! Executable is in $(BIN_DIR)/$(TARGET)"

# ----------------------------------------------------------------------
# Build/Object File Rules
# ----------------------------------------------------------------------

# 规则：如何从 .cpp 文件生成 .o 文件，并放入 build 目录
$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ----------------------------------------------------------------------
# Directory Creation
# ----------------------------------------------------------------------

# 确保 build 目录存在
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 确保 bin 目录存在
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ----------------------------------------------------------------------
# Utility Targets
# ----------------------------------------------------------------------

# 清理生成的文件和目录
clean:
	@echo "Cleaning up build and binary directories..."
	$(RM) -r $(BUILD_DIR) $(BIN_DIR)

# 编译后直接运行程序 (需要先执行 make all)
run: all
	@echo "--- Running $(TARGET) ---"
	./$(BIN_DIR)/$(TARGET)