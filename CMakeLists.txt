cmake_minimum_required(VERSION 3.5.0)
project(doc2svg VERSION 0.1.0 LANGUAGES C CXX)
add_definitions(-DPANDOC_EXE="pandoc")
add_definitions(-DPDFLATEX_EXE="pdflatex")
find_package(Qt6 REQUIRED COMPONENTS Widgets Core SvgWidgets)
qt_standard_project_setup()
qt_add_executable(doc2svg
    "src/main.cpp"
    "src/window/main_window.cpp"
)
target_include_directories(doc2svg PRIVATE "include")
target_link_libraries(doc2svg PRIVATE Qt6::Widgets Qt6::Core Qt6::SvgWidgets)
set_property(TARGET doc2svg PROPERTY CXX_STANDARD 20)
set_target_properties(doc2svg PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)