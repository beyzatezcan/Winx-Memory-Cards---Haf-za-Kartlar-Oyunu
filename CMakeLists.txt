cmake_minimum_required(VERSION 3.26)
project(helloRaylib CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Raylib'i bul ve dahil et
find_package(raylib REQUIRED)

# Derlenen dosyaları belirt
add_executable(helloRaylib main.cpp
        loading_screen.cpp
        loading_screen.h
        result_screen.h
        result_screen.cpp)
file(COPY gorseller DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Raylib kütüphanesini hedefin bağımlılığı olarak tanımla
target_link_libraries(helloRaylib raylib)
