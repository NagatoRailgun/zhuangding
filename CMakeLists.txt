cmake_minimum_required(VERSION 3.5)

project(zhuangding VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
# Component File
        #主页
        component/mainwindow/mainwindow.ui
        component/mainwindow/mainwindow.cpp
        component/mainwindow/mainwindow.h
        #页基类
        component/basicpage/basicpage.h
        component/basicpage/basicpage.cpp
        #图形按钮基类
        component/basicbuttonwidget/basicbuttonwidget.h
        component/basicbuttonwidget/basicbuttonwidget.cpp
        #抽奖页
        component/catchpage/catchpage.h
        component/catchpage/catchpage.cpp
        component/catchpage/catchpage.ui
        #载入页
        component/loadpage/loadpage.h
        component/loadpage/loadpage.cpp
        component/loadpage/loadpage.ui
        #班级按钮控件
        component/loadpage/classwidget.h
        component/loadpage/classwidget.cpp
        component/loadpage/classwidget.ui
        #设置页
        component/optionpage/optionpage.h
        component/optionpage/optionpage.cpp
        component/optionpage/optionpage.ui
        #历史页
        component/histroypage/histroypage.h
        component/histroypage/histroypage.cpp
        component/histroypage/histroypage.ui
        #随机数页
        component/numberpage/numberpage.h
        component/numberpage/numberpage.cpp
        component/numberpage/numberpage.ui
# Service File
        #服务基类
        service/basicservice/basicservice.h
        service/basicservice/basicservice.cpp
        #抽丁服务
        service/catchservice/catchservice.h
        service/catchservice/catchservice.cpp
        #学生服务
        service/studentservice/studentservice.h
        service/studentservice/studentservice.cpp
        #读取Excel服务
        service/loadservice/loadservice.h
        service/loadservice/loadservice.cpp
        #本地存取服务
        service/fileservice/fileservice.h
        service/fileservice/fileservice.cpp
        #历史记录服务
        service/histroyservice/histroyservice.h
        service/histroyservice/histroyservice.cpp
        #选项设置服务
        service/optionservice/optionservice.h
        service/optionservice/optionservice.cpp
# Class File
        #班级类
        class/classclass/classclass.h
        class/classclass/classclass.cpp
        #学生类
        class/studentclass/studentclass.h
        class/studentclass/studentclass.cpp
        #选项设置类
        class/optionclass/optionclass.h
        class/optionclass/optionclass.cpp
)

include_directories(service)
include_directories(component)
include_directories(class)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(zhuangding
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET zhuangding APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(zhuangding SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(zhuangding
            ${PROJECT_SOURCES}
        )
    endif()
endif()

set(BUILD_PACKAGE OFF CACHE BOOL "Disable QXlsx CPack package")
add_subdirectory(QXlsx EXCLUDE_FROM_ALL)

target_link_libraries(zhuangding
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    QXlsx::QXlsx)

set_target_properties(zhuangding PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS zhuangding
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(zhuangding)

endif()
