cmake_minimum_required(VERSION 3.20)
project(UniLabs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(ACTIVE_LAB "lab1" CACHE STRING "Lab target to build/run by default (e.g., lab1, lab2)")

set(VALID_LABS "")

function(add_lab lab_name)
  set(lab_dir "${CMAKE_CURRENT_SOURCE_DIR}/${lab_name}")
  set(main_cpp "${lab_dir}/main.cpp")

  if(NOT IS_DIRECTORY "${lab_dir}")
    return()
  endif()

  # Hard requirement: labN/main.cpp must exist
  if(NOT EXISTS "${main_cpp}")
    message(STATUS "Skipping ${lab_name}: missing ${main_cpp}")
    return()
  endif()

  # Start with main.cpp explicitly (prevents empty-source target)
  set(lab_sources "${main_cpp}")

  # Add any other .cpp/.cc/.cxx files under labN/ (optional)
  file(GLOB_RECURSE extra_sources CONFIGURE_DEPENDS
    "${lab_dir}/*.cpp"
    "${lab_dir}/*.cc"
    "${lab_dir}/*.cxx"
    "${lab_dir}/*.CPP"
    "${lab_dir}/*.CC"
    "${lab_dir}/*.CXX"
  )
  list(REMOVE_ITEM extra_sources "${main_cpp}")
  list(APPEND lab_sources ${extra_sources})

  add_executable(${lab_name} ${lab_sources})

  # So you can do: #include "lab1header.h" from files in labN/
  target_include_directories(${lab_name} PRIVATE "${lab_dir}")

  # Build only ACTIVE_LAB by default
  if(NOT "${lab_name}" STREQUAL "${ACTIVE_LAB}")
    set_target_properties(${lab_name} PROPERTIES EXCLUDE_FROM_ALL TRUE)
  endif()

  list(APPEND VALID_LABS "${lab_name}")
  set(VALID_LABS "${VALID_LABS}" PARENT_SCOPE)

  # Helpful configure-time debug
  message(STATUS "${lab_name} sources: ${lab_sources}")
endfunction()

file(GLOB labs RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "lab*")
foreach(lab IN LISTS labs)
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${lab}")
    add_lab("${lab}")
  endif()
endforeach()

if(NOT TARGET "${ACTIVE_LAB}")
  string(JOIN ", " VALID_LABS_STR ${VALID_LABS})
  message(FATAL_ERROR
    "ACTIVE_LAB='${ACTIVE_LAB}' is not a valid target.\n"
    "Expected: ${ACTIVE_LAB}/main.cpp\n"
    "Discovered valid labs: ${VALID_LABS_STR}"
  )
  
  add_custom_target(lab ALL DEPENDS ${ACTIVE_LAB})
  
  add_executable(${lab_name} ${lab_sources})
  
  target_include_directories(${lab_name} PRIVATE "${lab_dir}")
  
  add_custom_target(run_${lab_name}
    COMMAND $<TARGET_FILE:${lab_name}>
    DEPENDS ${lab_name}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
  )
  
endif()