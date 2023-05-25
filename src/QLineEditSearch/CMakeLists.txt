# CMakeList.txt: CMakeQtDemo 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project(QLineEditSearch)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 将源代码添加到此项目的可执行文件。
add_executable (${CMAKE_PROJECT_NAME} WIN32
    "main.cpp"
    "mainwindow.h"
    "mainwindow.ui"
    "mainwindow.cpp"
    "../resources/img.qrc"
)

find_package(Qt5 COMPONENTS Core Widgets)
target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE
        Qt::Core
        Qt::Widgets
)

# 设置资源目录
set(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/resources)
# 添加资源文件
file(GLOB_RECURSE RESOURCES_FILES "${RESOURCES_DIR}/*.png" "${RESOURCES_DIR}/*.jpg")
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.qrc
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/resources"
    COMMAND ${Qt5_RCC_EXECUTABLE} -name resources ${RESOURCES_FILES} -o ${CMAKE_CURRENT_BINARY_DIR}/resources.qrc
    DEPENDS ${RESOURCES_FILES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)
# 生成资源文件
qt5_add_resources(RESOURCES ${CMAKE_CURRENT_BINARY_DIR}/resources.qrc)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

# TODO: 如有需要，请添加测试并安装目标。
