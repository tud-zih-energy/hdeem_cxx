cmake_minimum_required(VERSION 3.11)
project(hdeem_cxx VERSION 1.0)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(FreeIPMI REQUIRED)
find_package(HDEEM REQUIRED)

add_library(hdeem_cxx INTERFACE)

target_include_directories(hdeem_cxx INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(hdeem_cxx INTERFACE cxx_std_14)

set_target_properties(hdeem_cxx PROPERTIES EXPORT_NAME cxx)
add_library(hdeem::cxx ALIAS hdeem_cxx)

target_link_libraries(hdeem_cxx INTERFACE hdeem::hdeem FreeIPMI::FreeIPMI)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    target_compile_options(hdeem_cxx INTERFACE $<$<CONFIG:Debug>:-Wall -pedantic -Wextra>)

    add_subdirectory(examples)
endif()
