cmake_minimum_required(VERSION 3.16)
project(app.exe LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Рекурсивно собираем все .cpp файлы в папке src
# file(GLOB_RECURSE SOURCES "src/*.cpp")


# # Создаем исполняемый файл из всех собранных источников

# target_include_directories(app.exe PRIVATE src)

# target_link_libraries(app.exe PRIVATE 
# GTest::GTest
# GTest::main
# pthread)


# # Указываем .ui файл для обработки
# set(UI_FILES main_window.ui)
# qt_wrap_ui(QtUIExample ${UI_FILES})


# cmake_minimum_required(VERSION 3.14)

# # Находим gtest
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})

# # Основной исполняемый файл

# # # Рекурсивно собираем все .cpp файлы в папке src
# # file(GLOB_RECURSE SOURCES "src/*.cpp")
# # target_include_directories(app.exe PRIVATE src)

# # Тесты
# add_executable(app.exe tests/test_test.hpp)
# target_link_libraries(app.exe PRIVATE GTest::GTest GTest::Main pthread)


cmake_minimum_required(VERSION 3.14)
project(MyProject)

# Находим Google Test
find_package(GTest REQUIRED)
include(GoogleTest)

# Указываем пути к заголовочным файлам
include_directories(
    ${GTEST_INCLUDE_DIRS}
    /opt/homebrew/Cellar/googletest/1.16.0  # Путь где Homebrew устанавливает заголовки
)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Основное приложение
add_executable(app.exe src/main.cpp)

# Если нужно добавить тесты
add_executable(run_tests tests/test_test.cpp)
target_link_libraries(run_tests GTest::GTest GTest::Main)

# Автоматическая регистрация тестов
# gtest_discover_tests(run_tests)
