cmake_minimum_required(VERSION 3.16)
project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)           
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Обязательно использовать этот стандарт

cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Находим Google Test
find_package(GTest REQUIRED)
include(GoogleTest)


# Указываем пути к заголовочным файлам
include_directories(
    ${GTEST_INCLUDE_DIRS}
    /opt/homebrew/Cellar/googletest/1.16.0  # Путь где Homebrew устанавливает заголовки
    /usr/local/include
    ${CMAKE_CURRENT_SOURCE_DIR}/container  # Добавляем папку с вашими заголовками
    ${CMAKE_CURRENT_SOURCE_DIR}/exceptions
    ${CMAKE_CURRENT_SOURCE_DIR}/iterator
    ${CMAKE_CURRENT_SOURCE_DIR}/reverse_iterator
    ${CMAKE_CURRENT_SOURCE_DIR}          # Добавляем текущую директорию (если заголовки там)
)

file(GLOB CONTAINER "container/*.cpp")
file(GLOB TESTS "tests/*.cpp")


# Если нужно добавить тесты
add_executable(app.exe ${SOURCES} ${TESTS} ${CONTAINER})
target_link_libraries(app.exe GTest::GTest GTest::Main)
