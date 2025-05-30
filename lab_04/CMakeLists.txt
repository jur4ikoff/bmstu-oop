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
file(GLOB_RECURSE SOURCES "lift/*.cpp" "controller/*.cpp" "doors/*.cpp" "cabin/*.cpp" "buttons/*.cpp")
file(GLOB_RECURSE MAIN "main.cpp" "main_window.cpp")

# Создаем исполняемый файл из всех собранных источников

set(UI_FILES main_window.ui)
qt6_wrap_ui(UI_HEADERS ${UI_FILES})  

qt_add_executable(app.exe
    ${SOURCES} ${MAIN} ${UI_HEADERS}
)

target_include_directories(app.exe PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    lift/
    controller/
    buttons/
    doors/
    cabin/
    )

target_precompile_headers(app.exe
PRIVATE "pch.hxx"
)


target_link_libraries(app.exe PRIVATE Qt6::Core Qt6::Widgets Qt6::Gui)


# Добавляем цель debug с соответствующими флагами
add_custom_target(debug
    COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
    COMMENT "Setting up debug build"
)

# Устанавливаем флаги для отладочной сборки
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra")

# qt_wrap_ui(QtUIExample ${UI_FILES})

#target_sources(app.exe PRIVATE ${UI_HEADERS})  