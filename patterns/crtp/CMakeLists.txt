cmake_minimum_required(VERSION 3.16)
project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "*.cpp")

cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Указываем пути к заголовочным файлам
include_directories(
    ${GTEST_INCLUDE_DIRS}
    /usr/local/include
    ${CMAKE_CURRENT_SOURCE_DIR}          # Добавляем текущую директорию (если заголовки там)
)

add_executable(app.exe ${SOURCES})
target_link_libraries(app.exe)
