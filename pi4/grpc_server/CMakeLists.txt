cmake_minimum_required(VERSION 3.8)

project(HelloWorld C CXX)

include(common.cmake)

set(prodject_name "helloworld")
set(grpc_proto_name "robotarm_server")
set(target "helloworld")

# Proto file
get_filename_component(hw_proto "${grpc_proto_name}.proto" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/${grpc_proto_name}.pb.cc")
set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${grpc_proto_name}.pb.h")
set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/${grpc_proto_name}.grpc.pb.cc")
set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/${grpc_proto_name}.grpc.pb.h")
add_custom_command(
      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
      COMMAND ${_PROTOBUF_PROTOC}
      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${hw_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${hw_proto}"
      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# hw_grpc_proto
add_library(hw_grpc_proto
  ${hw_grpc_srcs}
  ${hw_grpc_hdrs}
  ${hw_proto_srcs}
  ${hw_proto_hdrs})
target_link_libraries(hw_grpc_proto
  ${_REFLECTION}
  ${_GRPC_GRPCPP}
  ${_PROTOBUF_LIBPROTOBUF})


add_executable(helloworld helloworld.cc)
target_Compile_options(helloworld PRIVATE -Wall -Wextra -pedantic)
target_link_libraries(helloworld hw_grpc_proto)
target_link_libraries(helloworld absl::flags)
target_link_libraries(helloworld absl::flags_parse)
target_link_libraries(helloworld ${_REFLECTION})
target_link_libraries(helloworld ${_GRPC_GRPCPP})
target_link_libraries(helloworld ${_PROTOBUF_LIBPROTOBUF})



