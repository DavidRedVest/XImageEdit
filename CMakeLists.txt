cmake_minimum_required(VERSION 3.16)

project(MyImageEdit VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        src/main.cpp
        src/myimageedit.cpp
        include/myimageedit.h
        src/ximage.cpp
        include/ximage.h
        src/xeditview.cpp
        include/xeditview.h
        src/myimageedit.ui
)
#new add
if(APPLE)

set(APP_ICON_MACOS "${CMAKE_CURRENT_SOURCE_DIR}/Resources/apple_logo.icns")
set_source_files_properties(${APP_ICON_MACOS} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PLATFORM_ICON ${APP_ICON_MACOS})
elseif(WIN32)
        # Windows 图标通过 .rc 文件嵌入
    set(PLATFORM_ICON "${CMAKE_CURRENT_SOURCE_DIR}/Resources/logo.rc")
endif()

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MyImageEdit
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PLATFORM_ICON} #new add
        include/xsubject.h src/xsubject.cpp
        include/iobserver.h
        include/xmodel.h src/xmodel.cpp
        include/icontroller.h src/icontroller.cpp
        include/icontrollerfactory.h
        include/iview.h
        include/xcontrollerfactory.h src/xcontrollerfactory.cpp
        include/igraph.h
        include/xpengraph.h src/xpengraph.cpp
        include/xerasegraph.h src/xerasegraph.cpp
        include/xrectgraph.h src/xrectgraph.cpp
        include/ximagegraph.h src/ximagegraph.cpp
        include/constants.h
        Resources/res.qrc
#        ximage.h ximage.cpp
#        xeditview.h xeditview.cpp
#        xsubject.h xsubject.cpp
#        iobserver.h
#        xmodel.h xmodel.cpp
#        icontroller.h icontroller.cpp
#        icontrollerfactory.h
#        iview.h
#        xcontrollerfactory.h xcontrollerfactory.cpp
#        igraph.h
#        xpengraph.h xpengraph.cpp
#        xerasegraph.h xerasegraph.cpp
#        xrectgraph.h xrectgraph.cpp
#        ximagegraph.h ximagegraph.cpp
#        res.qrc
#        logo.rc
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MyImageEdit APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MyImageEdit SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MyImageEdit
            ${PROJECT_SOURCES}
            ${MAC_ICON}
        )
    endif()
endif()

# 在设置了 C++17 标准之后添加：
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(MyImageEdit PRIVATE
        -Wall                   # 开启大部分警告
        -Wextra                 # 开启额外警告
        -Wpedantic              # 遵循严格的 ISO C++ 标准
        -Wshadow                # 警告变量隐藏
        -Wnon-virtual-dtor      # 警告含有虚函数但析构函数不是虚函数的类 (非常重要！)
    )
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(MyImageEdit PRIVATE /W4 /WX) # W4级别警告，并将警告视为错误
endif()

target_link_libraries(MyImageEdit PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MyImageEdit)
endif()
set_target_properties(MyImageEdit PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE_ICON_FILE "apple_logo.icns"
)

include(GNUInstallDirs)
install(TARGETS MyImageEdit
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MyImageEdit)
endif()

# ==========================================
# 添加一键格式化代码的 Custom Target
# ==========================================
# 1. 递归查找 src 和 include 目录下的所有 C++ 源文件和头文件
file(GLOB_RECURSE ALL_SOURCE_FILES
    "src/*.cpp"
    "src/*.h"
    "include/*.h"
)

# 2. 找到系统中的 clang-format 执行文件
find_program(CLANG_FORMAT_EXE clang-format)

if(CLANG_FORMAT_EXE)
    # 3. 创建一个名叫 "format" 的伪目标
    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ALL_SOURCE_FILES}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "正在使用 Clang-Format 格式化所有代码..."
    )
else()
    message(WARNING "未找到 clang-format，请确认是否已安装")
endif()
