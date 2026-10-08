cmake_minimum_required(VERSION 3.20)
project(DecryptionPassword)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenMP REQUIRED)

add_executable(DecryptionPassword main.cpp
        decryptSequential.cpp
        decryptSequential.h
)
add_executable(Preprocess preprocess.cpp)

target_link_libraries(DecryptionPassword PRIVATE OpenMP::OpenMP_CXX)