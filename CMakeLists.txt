cmake_minimum_required(VERSION 3.14)

project(10csvTest LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

include_directories(
  "D:\\Program Files\\MATLAB\\R2022b\\extern\\include"
  "D:\\Program Files\\MATLAB\\R2022b\\extern\\include\\win64"
  "F:\\MatlabTest\\SemiCL6Func_vc19\\SemiCL6Func\\for_redistribution_files_only"
)

link_directories(
  "D:\\Program Files\\MATLAB\\R2022b\\extern\\lib\\win64\\microsoft"
  "F:\\MatlabTest\\SemiCL6Func_vc19\\SemiCL6Func\\for_redistribution_files_only"
)

add_executable(10csvTest main.cpp)

set(LIB_PROJ
    "libmex.lib"
    "libmx.lib"
    "libmat.lib"
    "libeng.lib"
    "mclmcr.lib"
    "mclmcrrt.lib"
    "SemiCL6Func.lib")

target_link_libraries(10csvTest Qt${QT_VERSION_MAJOR}::Core ${LIB_PROJ})

install(
  TARGETS 10csvTest
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
