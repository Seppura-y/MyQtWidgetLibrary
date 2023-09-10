#cmake -S . -B build -A x64 -D CMAKE_INSTALL_PREFIX=./ -D QT5=G:/application/Qt/Qt5.15/5.15.2/msvc2019_64
#cmake --build build --config Release
#cmake --install build --config Release
cmake_minimum_required(VERSION 3.22)
project(MyQtWidgetLibrary_Build)

set(STARTUP_PROJ "" CACHE STRING "set the vs startup project")

set(PROJECT_FRAMELESS_WIDGET        FALSE CACHE BOOL "add project frameless widget ?")
set(PROJECT_FRAMELESS_WIDGET2       FALSE CACHE BOOL "add project frameless widget2 ?")
set(PROJECT_ROUND_WIDGET            FALSE CACHE BOOL "add project round widget ?")
set(PROJECT_MENU_BUTTON             FALSE CACHE BOOL "add project menu button ?")
set(PROJECT_VOLUME_BUTTON           FALSE CACHE BOOL "add project volume button ?")
set(PROJECT_TITLE                   FALSE CACHE BOOL "add project title ?")
set(PROJECT_MAIN_WIDGET             FALSE CACHE BOOL "add project main widget ?")
set(PROJECT_CAMERA_MENU             FALSE CACHE BOOL "add project camera menu ?")
set(PROJECT_SCREEN_CAPTURE_DIALOG   FALSE CACHE BOOL "add project screen capture dialog ?")
set(PROJECT_DISPLAY_WIDGET          FALSE CACHE BOOL "add project display widget ?")
set(PROJECT_PLAYER_BASE             FALSE CACHE BOOL "add project player base ?")
set(PROJECT_DIALOG_BASE             FALSE CACHE BOOL "add project dialog base ?")
set(PROJECT_MEDIA_PLAYER_VLC        FALSE CACHE BOOL "add project media player vlc ?")
set(PROJECT_CONTROL_BAR             FALSE CACHE BOOL "add project contron bar ?")
set(PROJECT_MULTIDISPLAY_PLAYER     FALSE CACHE BOOL "add project multidisplay player ?")
set(PROJECT_SCREEN_SPLITTER         FALSE CACHE BOOL "add project screen splitter ?")
set(PROJECT_CAMERA_PREVIEW          FALSE CACHE BOOL "add project camera preview ?")
set(PROJECT_DOUBLE_SLIDER           FALSE CACHE BOOL "add project double slider ?")
set(PROJECT_DONUT_QGL_ENGINE        FALSE CACHE BOOL "add project donut qgl engine ?")
set(PROJECT_OFFSCREEN_RENDERER      FALSE CACHE BOOL "add project offscreen renderer ?")
set(PROJECT_CEF_WIDGET              FALSE CACHE BOOL "add project CEF Widget ?")

if(PROJECT_FRAMELESS_WIDGET)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/FramelessWidget)
endif()

if(PROJECT_FRAMELESS_WIDGET2)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/FramelessWidget2)
endif()

if(PROJECT_ROUND_WIDGET)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/RoundWidget)
endif()

if(PROJECT_MENU_BUTTON)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/MenuButton)
endif()

if(PROJECT_VOLUME_BUTTON)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/VolumeButton)
endif()

if(PROJECT_TITLE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/Title)
endif()

if(PROJECT_MAIN_WIDGET)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/MainWidget)
endif()

if(PROJECT_CAMERA_MENU)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/CameraMenu2)
endif()

if(PROJECT_SCREEN_CAPTURE_DIALOG)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/ScreenCaptureDialog)
endif()

if(PROJECT_DISPLAY_WIDGET)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/DisplayWidget)
endif()

if(PROJECT_PLAYER_BASE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/PlayerBase)
endif()

if(PROJECT_DIALOG_BASE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/DialogBase)
endif()

if(PROJECT_MEDIA_PLAYER_VLC)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/MediaPlayerVLC)
endif()

if(PROJECT_CONTROL_BAR)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/ControlBar)
endif()

if(PROJECT_MULTIDISPLAY_PLAYER)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/MultiDisplayPlayer)
endif()

if(PROJECT_SCREEN_SPLITTER)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/ScreenSplitter)
endif()

if(PROJECT_CAMERA_PREVIEW)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/CameraPreview)
endif()

if(PROJECT_DOUBLE_SLIDER)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/DoubleSlider)
endif()

if(PROJECT_DONUT_QGL_ENGINE)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/DonutQGLEngine)
endif()

if(PROJECT_OFFSCREEN_RENDERER)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/OffscreenRenderer)
endif()

if(PROJECT_CEF_WIDGET)
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/CefWidget)
endif()

if(STARTUP_PROJ)
    set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR} PROPERTY VS_STARTUP_PROJECT ${STARTUP_PROJ})
endif()


# add_dependencies(DonutEditorFramework)
