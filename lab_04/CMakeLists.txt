cmake_minimum_required(VERSION 3.16)
project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


cmake_minimum_required(VERSION 3.14)
project(MyProject)


# Указываем пути к заголовочным файлам
include_directories(
    ${GTEST_INCLUDE_DIRS}
    /opt/homebrew/Cellar/googletest/1.16.0  # Путь где Homebrew устанавливает заголовки
    /usr/local/include
# ${CMAKE_CURRENT_SOURCE_DIR}/container  # Добавляем папку с вашими заголовками
    ${CMAKE_CURRENT_SOURCE_DIR}          # Добавляем текущую директорию (если заголовки там)
)

# file(GLOB CONTAINER "container/*.cpp")

# Если нужно добавить тесты
file(GLOB MAIN "main.cpp")

add_executable(app.exe ${MAIN})
target_link_libraries(app.exe)
