#########################################
# Main cmake file
#########################################
cmake_minimum_required(VERSION 2.8)

project(gui)

find_package(Qt4 REQUIRED)

# include dirs
include(${QT_USE_FILE})

# Core Lib Include
include_directories(../core/include)

# Sources
set(gui_src
    src/main.cpp
    src/MainWindow.cpp
    src/NewGameDialog.cpp
    src/GraphicsTokenItem.cpp
    src/GuiPlayer.cpp
    src/TokenWidget.cpp
    src/BoardScene.cpp
)

# UI Files
set(gui_ui 
    src/ui/MainWindow.ui
    src/ui/NewGameDialog.ui
    src/ui/TokenWidget.ui
)

# Resources
set(gui_qrc
    src/Resource.qrc
)

# auto moc
qt4_automoc(${gui_src})
# generate ui header
qt4_wrap_ui(gui_ui_h ${gui_ui})
# generate resources
qt4_add_resources(gui_qrc_gen ${gui_qrc})

# include generated ui header
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# the editor application
add_executable(gui ${gui_src} ${gui_ui_h} ${gui_qrc_gen})
target_link_libraries(gui core ${QT_LIBRARIES})