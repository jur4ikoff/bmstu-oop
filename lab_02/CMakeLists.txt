cmake_minimum_required(VERSION 3.16)
project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


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
)

file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "tests/*.cpp")

# Если нужно добавить тесты
add_executable(app.exe ${SOURCES} ${TESTS})
target_link_libraries(app.exe GTest::GTest GTest::Main)
