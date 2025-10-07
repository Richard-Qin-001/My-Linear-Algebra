# ----------------------------------------------------------------------
# CMakeLists.txt
# ----------------------------------------------------------------------

# 1. 最小版本要求
cmake_minimum_required(VERSION 3.16)

# 2. 项目名称
project(MyLinearAlgebraApp VERSION 0.2.0 LANGUAGES CXX)
# 3. 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH "D:\\Qt\\6.9.3\\mingw_64\\")
set(Qt6_DIR "${CMAKE_PREFIX_PATH}lib\\cmake\\Qt6")
set(Qt6Widgets_DIR "${CMAKE_PREFIX_PATH}lib\\cmake\\Qt6Widgets")

# 4. 寻找 Qt 库 (使用 Qt 6 或 Qt 5)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    ${CMAKE_CURRENT_BINARY_DIR}  # 添加构建目录，UI 头文件会生成在这里
)

# 5. 定义源代码文件列表 (包括您的核心逻辑和新的 Qt 文件)

# UI 和 Qt 文件 (将被自动处理)
set(UI_FORMS ${CMAKE_CURRENT_SOURCE_DIR}/src/MyLinearAlgebra.ui)
set(GUI_SOURCES src/mainwindow.h src/mainwindow.cpp)

# 核心 C++ 文件
set(CORE_SOURCES
    src/main.cpp
    src/io_matrix.cpp
    src/io_matrix_json.cpp
    src/elimination.cpp
    src/permutation.cpp
    src/transpose.cpp
    src/multiply.cpp
    src/determinant-Leibniz.cpp
    src/determinant-Gauss.cpp
    src/lu_decomposition.cpp
    src/inverse.cpp
    src/identity.cpp
    # 确保所有的 .cpp 文件都在这里
)

# 6. 添加可执行文件 (启动 GUI 应用程序)
qt_add_executable(MyLinearAlgebraApp
    ${CORE_SOURCES}
    ${GUI_SOURCES}
    ${UI_FORMS}
)

# 7. 链接所需的 Qt 模块
target_link_libraries(MyLinearAlgebraApp PRIVATE
    Qt::Core
    Qt::Widgets
)

# 8. 额外的依赖 (对于 nlohmann/json 库)
# 由于 json.hpp 是一个头文件，它默认包含在内。
# 如果它是一个外部库，需要添加 
# target_link_libraries(MyLinearAlgebraApp PRIVATE nlohmann_json)

# 9. 设置生成的可执行文件的输出目录
set_target_properties(MyLinearAlgebraApp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)