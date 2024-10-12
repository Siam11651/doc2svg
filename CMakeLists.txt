cmake_minimum_required(VERSION 3.5.0)
project(doc2tex VERSION 0.1.0 LANGUAGES C CXX)
add_definitions(-DPANDOC_EXE="./pandoc")
find_package(Qt6 REQUIRED COMPONENTS Widgets Core)
qt_standard_project_setup()
qt_add_executable(doc2tex
    "src/main.cpp"
    "src/window/main_window.cpp"
)
target_include_directories(doc2tex PRIVATE "include")
target_link_libraries(doc2tex PRIVATE Qt6::Widgets Qt6::Core)
set_property(TARGET doc2tex PROPERTY CXX_STANDARD 20)
set_target_properties(doc2tex PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)