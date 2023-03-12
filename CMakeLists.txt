#cmake -S . -B build -A x64 -D CMAKE_INSTALL_PREFIX=./ -D QT5=G:/application/Qt/Qt5.15/5.15.2/msvc2019_64
#cmake --build build --config Release
#cmake --install build --config Release
cmake_minimum_required(VERSION 3.22)
project(QtCourse51_Build)


set(PROJECT_FRAMELESS_WIDGET FALSE CACHE BOOL "add project frameless widget ?")
set(PROJECT_FRAMELESS_WIDGET2 FALSE CACHE BOOL "add project frameless widget2 ?")

if(PROJECT_FRAMELESS_WIDGET)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/FramelessWidget)
    set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY VS_STARTUP_PROJECT FramelessWidget)
endif(PROJECT_FRAMELESS_WIDGET)

if(PROJECT_FRAMELESS_WIDGET2)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/FramelessWidget2)
    set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY VS_STARTUP_PROJECT FramelessWidget2)
endif(PROJECT_FRAMELESS_WIDGET2)

# add_dependencies(DonutEditorFramework)

# set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY VS_STARTUP_PROJECT DonutEditorFramework)