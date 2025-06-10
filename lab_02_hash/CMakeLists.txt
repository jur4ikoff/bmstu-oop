cmake_minimum_required(VERSION 3.16)
project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем пути к заголовочным файлам
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/container  # Добавляем папку с вашими заголовками
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/concepts
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator
    ${CMAKE_CURRENT_SOURCE_DIR}/hash_map
    ${CMAKE_CURRENT_SOURCE_DIR}          # Добавляем текущую директорию (если заголовки там)
)

file(GLOB CONTAINER "container/*.cpp")
file(GLOB MAIN_SOURCES "*.cpp")  # Assuming your main.cpp is in the root directory


# Если нужно добавить тесты
add_executable(app.exe ${CONTAINER} ${MAIN_SOURCES})
target_link_libraries(app.exe)
