project(minisexp)
cmake_minimum_required(VERSION 2.8)

set(LLVM_ROOT "/usr" CACHE PATH "Root of LLVM install.")

#if( NOT EXISTS ${LLVM_ROOT}/include/llvm )
#    message(FATAL_ERROR "LLVM_ROOT (${LLVM_ROOT}) is not a valid LLVM install")
#endif()

# We incorporate the CMake features provided by LLVM:
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${LLVM_ROOT}/share/llvm/cmake")
#include(HandleLLVMOptions)
#include(LLVM-Config)

#find_package(LLVM)
#if( NOT LLVM_FOUND )
#    message(FATAL_ERROR "LLVM package can't be found. Set CMAKE_PREFIX_PATH variable to LLVM's installation prefix.")
#endif()

#llvm_map_components_to_libraries(REQ_LLVM_LIBRARIES jit native engine)
#message(STATUS "Linking LLVM libraries: ${REQ_LLVM_LIBRARIES}")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules" "${LLVM_ROOT}/share/llvm/cmake")
find_package(LLVM REQUIRED)
include(HandleLLVMOptions)

find_llvm_libs( ${LLVM_CONFIG_EXECUTABLE} "native bitwriter linker bitreader jit interpreter support ipo" REQ_LLVM_LIBRARIES LLVM_NATIVE_OBJECTS )
exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --libdir OUTPUT_VARIABLE LLVM_LIBRARY_DIRS )
exec_program(${LLVM_CONFIG_EXECUTABLE} ARGS --includedir OUTPUT_VARIABLE LLVM_INCLUDE_DIRS )
message(STATUS "Project Name: ${PROJECT_NAME}")
message(STATUS "LLVM Shared Lib: ${LLVM_SHARED_LIB}")
message(STATUS "Linking LLVM libraries: ${REQ_LLVM_LIBRARIES}")
message(STATUS "Linking LLVM objects: ${LLVM_NATIVE_OBJECTS}")
message(STATUS "LLVM Definitions: ${LLVM_DEFINITIONS}")
message(STATUS "LLVM Include Dirs: ${LLVM_INCLUDE_DIRS}")
message(STATUS "LLVM Link Dirs: ${LLVM_LIBRARY_DIRS}")

add_definitions( ${LLVM_DEFINITIONS} )
include_directories( ${LLVM_INCLUDE_DIRS} )
link_directories( ${LLVM_LIBRARY_DIRS} )

aux_source_directory(. SRC_LIST)
#aux_source_directory(djvulibre/doc/minilisp MINILISP_SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST} ${LLVM_NATIVE_OBJECTS})
target_link_libraries(${PROJECT_NAME} ${REQ_LLVM_LIBRARIES})

