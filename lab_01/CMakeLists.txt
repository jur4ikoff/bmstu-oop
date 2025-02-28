cmake_minimum_required(VERSION 3.16)

project(app.exe LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)
qt_standard_project_setup()

# Рекурсивно собираем все .cpp файлы в папке src
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Создаем исполняемый файл из всех собранных источников
# add_executable(MyQtApp ${SOURCES})

qt_add_executable(app.exe
    ${SOURCES}
)

target_precompile_headers(app.exe
PRIVATE "pch.hxx"
)

# qt_add_uic(UI_FILES src/main_window.ui)
target_link_libraries(app.exe PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)

# Указываем .ui файл для обработки
set(UI_FILES main_window.ui)
qt_wrap_ui(QtUIExample ${UI_FILES})