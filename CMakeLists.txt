cmake_minimum_required(VERSION 3.0)
project(LibraryDataBase)

add_library(namespaces INTERFACE)
target_include_directories(namespaces INTERFACE LibraryNameSpaces)

add_library(libb Library.cpp Book.cpp BookType.cpp LibraryMember.cpp)
target_include_directories(libb PUBLIC ${CMAKE_CURRENT_SOURCE})
target_link_libraries(libb namespaces)

add_executable(LibraryDataBase LibraryDataBase.cpp)
target_link_libraries(LibraryDataBase PRIVATE libb)
