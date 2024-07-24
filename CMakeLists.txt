cmake_minimum_required(VERSION 3.19...3.28)
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/vcpkg/scripts/buildsystems/vcpkg.cmake")
project(App VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(fmt CONFIG REQUIRED)
find_package(argparse CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include(grpc.cmake)

add_executable(${CMAKE_PROJECT_NAME})

target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
        src/main.cc
        src/application.cc
        src/mib/base.cc
        src/cmd_print.cc
        src/cmd_start.cc
        src/echo_server.cc
)

target_include_directories(${CMAKE_PROJECT_NAME}
    PRIVATE
        include/
)

target_compile_options(${CMAKE_PROJECT_NAME}
    PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>: -Wall>
)

target_link_libraries(${CMAKE_PROJECT_NAME}
    PRIVATE
        bcg_grpc_proto
        fmt::fmt
        argparse::argparse
        nlohmann_json::nlohmann_json
)