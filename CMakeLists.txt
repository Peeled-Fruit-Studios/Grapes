cmake_minimum_required(VERSION 3.10)

project(Grapes VERSION 1.4)

option(BUILD_INSTALLER "Make Installer for Grapes" OFF)
option(DYNA_SVM "Make the SVM a Dynamic Library" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(svm)

configure_file(include/GrapesConf.h.in GrapesConf.h)

target_include_directories(Grapes PUBLIC "${PROJECT_BINARY_DIR}/include")

target_include_directories(Grapes PUBLIC "${PROJECT_BINARY_DIR}")

target_include_directories(Grapes PUBLIC "${PROJECT_SOURCE_DIR}/svm/include")

if(BUILD_INSTALLER)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${Grapes_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Grapes_VERSION_MINOR}")
set(CPACK_PACKAGE_CONTACT "Peeled Fruit Studios")
include(CPack)

endif()
