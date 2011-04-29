#########################################
# CMake File for td editor
######################################### 
cmake_minimum_required(VERSION 2.8)
project(editor)

find_package(Qt4 REQUIRED)

# include dirs
include(${QT_USE_FILE})
include_directories(include)

# src
set(editor_src
    src/main.cpp
    src/MainWindow.cpp
    src/EditorWidget.cpp
)

# header for moc
set(editor_h_moc
    include/editor/MainWindow.hpp
    include/editor/EditorWidget.hpp
)

# uis
set(editor_ui
    ui/MainWindow.ui
)

#qt resources
set(editor_qrc
)

# auto moc
#qt4_automoc(${editor_src})
# manual moc
qt4_wrap_cpp(editor_moc ${editor_h_moc} )
# generate ui header
qt4_wrap_ui(editor_ui_h ${editor_ui})
# generate resources
qt4_add_resources(editor_qrc_gen ${editor_qrc})

# include generated ui header
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# the editor application
add_executable(editor ${editor_src} ${editor_moc} ${editor_ui_h} ${editor_qrc_gen})
target_link_libraries(editor ${QT_LIBRARIES} "qscintilla2")






