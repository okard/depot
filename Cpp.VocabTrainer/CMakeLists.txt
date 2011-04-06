#########################################
# Main cmake file
#########################################
cmake_minimum_required(VERSION 2.8)

project(VocabTrainer)


find_package(Qt4 REQUIRED)

# include dirs
include(${QT_USE_FILE})


# Sources
set(VocabTrainer_src
    src/main.cpp
    src/Application.cpp
    src/VocableDisplay.cpp
)

# UI Files
set(VocabTrainer_ui 
    src/ui/VocableDisplay.ui
)

# Resources
set(VocabTrainer_qrc
)

# auto moc
qt4_automoc(${VocabTrainer_src})
# generate ui header
qt4_wrap_ui(VocabTrainer_ui_h ${VocabTrainer_ui})
# generate resources
qt4_add_resources(VocabTrainer_qrc_gen ${VocabTrainer_qrc})

# include generated ui header
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# the editor application
add_executable(VocabTrainer ${VocabTrainer_src} ${VocabTrainer_ui_h} ${VocabTrainer_qrc_gen})
target_link_libraries(VocabTrainer ${QT_LIBRARIES})


