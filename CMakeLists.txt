# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMakeQtDemo")



# 包含子项目。
#add_subdirectory (${CMAKE_SOURCE_DIR}/src/QLineEditSearch)QComboBoxFontColor
#add_subdirectory (${CMAKE_SOURCE_DIR}/src/QTableViewModelDelegate)
add_subdirectory (${CMAKE_SOURCE_DIR}/src/QComboBoxFontColor)

# 找到所有含有mian函数的cpp文件，保存在mians里
file(
    GLOB_RECURSE mains RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/QLineEditSearch/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/QTableViewModelDelegate/main.cpp"
)
# 循环遍历每个含main的文件，分别编译生成exe文件
foreach(mainfile IN LISTS mains)
    # Get file name without directory
    get_filename_component(mainname ${mainfile} NAME_WE)
    add_executable(${mainname} ${mainfile})
    # 添加库文件目录
    target_link_libraries(${mainname} mosquitto mosquittopp)#链接库文件
endforeach()
