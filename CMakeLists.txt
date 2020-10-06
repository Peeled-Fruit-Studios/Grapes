cmake_minimum_required(VERSION 3.10)

project(Grapes VERSION 1.2)

option(BUILD_INSTALLER "Make Installer for Grapes" OFF)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(src)
add_subdirectory(include)

configure_file(include/GrapesConf.h.in GrapesConf.h)

target_include_directories(Grapes PUBLIC "${PROJECT_BINARY_DIR}/include")

if(BUILD_INSTALLER)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Grapes_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Grapes_VERSION_MINOR}")
set(CPACK_PACKAGE_CONTACT "Peeled Fruit Studios")
include(CPack)

endif()