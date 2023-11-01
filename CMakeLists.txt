cmake_minimum_required(VERSION 3.22)

project(KitsunView)

string(TOLOWER ${PROJECT_NAME} LIB_NAME)

add_subdirectory(firstparty)

if(WIN32)
    set(PLATTFORM_TYPE "win32")
endif()

add_library(${LIB_NAME}
    source/window.cpp
    source/window_${PLATTFORM_TYPE}.cpp
)

target_include_directories(${LIB_NAME} PUBLIC include firstparty/libkitsune/include)
target_link_libraries(${LIB_NAME} PRIVATE libkitsune)

set(KITSUNVIEW_EXAMPLE ON)
if(KITSUNVIEW_EXAMPLE)
    add_executable(example_view example/example.cpp)
        
    target_include_directories(example_view PUBLIC include firstparty/libkitsune/include)
    target_link_libraries(example_view PRIVATE ${LIB_NAME} libkitsune)
endif()