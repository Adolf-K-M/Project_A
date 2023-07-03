cmake_minimum_required(VERSION 3.25)
project(project_chatgpt)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
        main.cpp
        )

# 设置头文件路径
include_directories(D:/msys64/mingw64/include)
# 设置库路径
link_directories(D:/msys64/mingw64/lib)

include_directories(${CMAKE_SOURCE_DIR}/libs/easyx/include)
link_directories(${CMAKE_SOURCE_DIR}/libs/easyx/lib64)

add_executable(project ${SOURCE_FILES})
# 链接 Curl 库
# 链接 EasyX 库
# 链接 gtest 库
target_link_libraries(project PRIVATE libcurl.dll.a gtest easyx)
