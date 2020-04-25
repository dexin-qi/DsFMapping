cmake_minimum_required(VERSION 3.2)
project(dsfmapping)

set(VERSION_MAJOR  1)
set(VERSION_MINOR  0)
set(VERSION_PATCH  1)
set(DSFMAPPING_VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})

option(BUILD_TEST "build dsfmapping test" true)

include("${PROJECT_SOURCE_DIR}/cmake/functions.cmake")

dustin_initialize_project()
dustin_enable_google_testing()

find_package(Abseil REQUIRED)
find_package(PCL REQUIRED QUIET COMPONENTS common)
find_package(Boost REQUIRED QUIET)
find_package(Ceres REQUIRED QUIET COMPONENTS SuiteSparse)
find_package(Eigen3 REQUIRED QUIET)
find_package(LuaGoogle REQUIRED QUIET)
find_package(Protobuf 3.0.0 REQUIRED QUIET)
find_package(OpenCV 3.2 REQUIRED QUIET)

include(FindPkgConfig)

set(DSFMAPPING_CONFIG_FILES_DIR ${CMAKE_INSTALL_PREFIX}/share/dsfmapping/configs CACHE PATH ".lua config files directory")
configure_file(${PROJECT_SOURCE_DIR}/dsfmapping/common/config.h.cmake ${PROJECT_BINARY_DIR}/dsfmapping/common/config.h)

install(DIRECTORY configs DESTINATION share/dsfmapping/)
install(DIRECTORY cmake DESTINATION share/dsfmapping/)

### grep source files
file(GLOB_RECURSE ALL_LIBRARY_HDRS "dsfmapping/*.h")
file(GLOB_RECURSE ALL_LIBRARY_SRCS "dsfmapping/*.cc")
file(GLOB_RECURSE ALL_TESTS "dsfmapping/*_test.cc")

if(${ALL_TESTS})
    list(REMOVE_ITEM ALL_LIBRARY_SRCS ${ALL_TESTS})
endif()
file(GLOB_RECURSE ALL_PROTOS "dsfmapping/*.proto")
set(INSTALL_SOURCE_HDRS ${ALL_LIBRARY_HDRS})

set(ALL_PROTO_SRCS)
set(ALL_PROTO_HDRS)
foreach(ABS_FIL ${ALL_PROTOS})
  file(RELATIVE_PATH REL_FIL ${PROJECT_SOURCE_DIR} ${ABS_FIL})
  get_filename_component(DIR ${REL_FIL} DIRECTORY)
  get_filename_component(FIL_WE ${REL_FIL} NAME_WE)

  list(APPEND ALL_PROTO_SRCS "${PROJECT_BINARY_DIR}/${DIR}/${FIL_WE}.pb.cc")
  list(APPEND ALL_PROTO_HDRS "${PROJECT_BINARY_DIR}/${DIR}/${FIL_WE}.pb.h")

  add_custom_command(
    OUTPUT "${PROJECT_BINARY_DIR}/${DIR}/${FIL_WE}.pb.cc"
    "${PROJECT_BINARY_DIR}/${DIR}/${FIL_WE}.pb.h"
    COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
    ARGS --cpp_out  ${PROJECT_BINARY_DIR} -I
    ${PROJECT_SOURCE_DIR} ${ABS_FIL}
    DEPENDS ${ABS_FIL}
    COMMENT "Running C++ protocol buffer compiler on ${ABS_FIL}"
    VERBATIM
  )
endforeach()

set(INSTALL_GENERATED_HDRS ${ALL_PROTO_HDRS})

set_source_files_properties(${ALL_PROTO_SRCS} ${ALL_PROTO_HDRS} PROPERTIES GENERATED TRUE)
list(APPEND ALL_LIBRARY_HDRS ${ALL_PROTO_HDRS})
list(APPEND ALL_LIBRARY_SRCS ${ALL_PROTO_SRCS})

## add library  
add_library(${PROJECT_NAME} STATIC ${ALL_LIBRARY_SRCS} ${ALL_LIBRARY_HDRS})
 
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC 
  "${EIGEN3_INCLUDE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${EIGEN3_LIBRARIES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  "${CERES_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${CERES_LIBRARIES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  "${LUA_INCLUDE_DIR}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${LUA_LIBRARIES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  "${Boost_INCLUDE_DIRS}")
target_link_libraries(${PROJECT_NAME} PUBLIC ${Boost_LIBRARIES})

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC
  ${PROTOBUF_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC ${PROTOBUF_LIBRARY} standalone_absl)

# PCL
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${PCL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${PCL_LIBRARIES})
set(BLACKLISTED_DEFINITIONS " -march=native -msse4.2 -mfpmath=sse ")
foreach(DEFINITION ${PCL_DEFINITIONS})
  list (FIND BLACKLISTED_DEFINITIONS "${DEFINITION}" DEFINITIONS_INDEX)
  if (${DEFINITIONS_INDEX} GREATER -1)
    continue()
  endif()
  set(TARGET_COMPILE_FLAGS "${TARGET_COMPILE_FLAGS} ${DEFINITION}")
endforeach()

# OpenCV
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${OpenCV_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${OpenCV_LIBS})


set(TARGET_COMPILE_FLAGS "${TARGET_COMPILE_FLAGS} ${DUSTIN_CXX_FLAGS}")
set_target_properties(${PROJECT_NAME} PROPERTIES
  COMPILE_FLAGS ${TARGET_COMPILE_FLAGS})

if(BUILD_TEST)
  foreach(ABS_FIL ${ALL_TESTS})
    file(RELATIVE_PATH REL_FIL ${PROJECT_SOURCE_DIR} ${ABS_FIL})
    get_filename_component(DIR ${REL_FIL} DIRECTORY)
    get_filename_component(FIL_WE ${REL_FIL} NAME_WE)
    # Replace slashes as required for CMP0037.
    string(REPLACE "/" "." TEST_TARGET_NAME "${DIR}/${FIL_WE}")
    dustin_test("${TEST_TARGET_NAME}" ${ABS_FIL})
    
    target_link_libraries(${TEST_TARGET_NAME} PUBLIC ${PROJECT_NAME})
  endforeach()
endif()

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT DsFMappingExport
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

foreach(HDR ${INSTALL_SOURCE_HDRS})
  file(RELATIVE_PATH REL_FIL ${PROJECT_SOURCE_DIR} ${HDR})
  get_filename_component(DIR ${REL_FIL} DIRECTORY)
  install(
    FILES ${HDR}
    DESTINATION include/${DIR}
  )
endforeach()

foreach(HDR ${INSTALL_GENERATED_HDRS})
  file(RELATIVE_PATH REL_FIL ${PROJECT_BINARY_DIR} ${HDR})
  get_filename_component(DIR ${REL_FIL} DIRECTORY)
  install(
    FILES ${HDR}
    DESTINATION include/${DIR}
  )
endforeach()

set(DSFMAPPING_CMAKE_DIR share/dsfmapping/cmake)
include(CMakePackageConfigHelpers)
configure_package_config_file(
  dsfmapping-config.cmake.in
  ${PROJECT_BINARY_DIR}/cmake/dsfmapping/dsfmapping-config.cmake
  PATH_VARS DSFMAPPING_CMAKE_DIR
  INSTALL_DESTINATION ${CMAKE_INSTALL_PREFIX}/share/dsfmapping
)

install(
  EXPORT DsFMappingExport
  DESTINATION share/dsfmapping/cmake/
  FILE DsFMappingTargets.cmake
)

install(
  FILES ${PROJECT_BINARY_DIR}/cmake/dsfmapping/dsfmapping-config.cmake
  DESTINATION share/dsfmapping/
)