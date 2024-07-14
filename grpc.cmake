
# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
option(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")


set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Proto file
get_filename_component(bcg_proto "protos/echo.proto" ABSOLUTE)
get_filename_component(bcg_proto_path "${bcg_proto}" PATH)
message(STATUS "Using proto ${bcg_proto} with path ${bcg_proto_path}")

# Generated sources
set(bcg_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.cc")
set(bcg_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.pb.h")
set(bcg_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.cc")
set(bcg_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/echo.grpc.pb.h")
add_custom_command(
      OUTPUT "${bcg_proto_srcs}" "${bcg_proto_hdrs}" "${bcg_grpc_srcs}" "${bcg_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${bcg_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${bcg_proto}"
      DEPENDS "${bcg_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# bcg_grpc_proto
add_library(bcg_grpc_proto
  ${bcg_grpc_srcs}
  ${bcg_grpc_hdrs}
  ${bcg_proto_srcs}
  ${bcg_proto_hdrs})
target_link_libraries(bcg_grpc_proto
  absl::check
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})