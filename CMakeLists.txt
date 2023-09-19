cmake_minimum_required(VERSION 3.26)
project(CppDatabaeOrm)

set(CMAKE_CXX_STANDARD 23)

add_executable(CppDatabaeOrm main.cpp
        Model/User.cpp)

find_package(SqliteOrm REQUIRED)

target_link_libraries(CppDatabaeOrm PRIVATE sqlite_orm::sqlite_orm)
