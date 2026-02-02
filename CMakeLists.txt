cmake_minimum_required(VERSION 3.20)
project(UniLabs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(ACTIVE_LAB "lab1" CACHE STRING "Lab target to build/run by default (e.g., lab1, lab2)")

# Define entry point overrides here (lab_name -> filename without extension)
# If not listed, defaults to main.cpp
set(LAB_ENTRY_POINTS
    "lab2:grade_calculator"
    "lab3:boolean"
    "lab4:plateaus_and_basins"
    "lab5:main"
    "lab6:test_functions"
)

# Parse overrides into a usable format
foreach(entry IN LISTS LAB_ENTRY_POINTS)
    string(REPLACE ":" ";" entry_parts "${entry}")
    list(GET entry_parts 0 lab_name)
    list(GET entry_parts 1 entry_file)
    set(ENTRY_POINT_${lab_name} "${entry_file}")
endforeach()

set(VALID_LABS "")

function(add_lab lab_name)
    set(lab_dir "${CMAKE_CURRENT_SOURCE_DIR}/${lab_name}")

    if(NOT IS_DIRECTORY "${lab_dir}")
        return()
    endif()

    # Check for custom entry point, default to main
    if(DEFINED ENTRY_POINT_${lab_name})
        set(entry_file "${ENTRY_POINT_${lab_name}}")
    else()
        set(entry_file "main")
    endif()

    set(entry_cpp "${lab_dir}/${entry_file}.cpp")

    # Hard requirement: entry point must exist
    if(NOT EXISTS "${entry_cpp}")
        message(STATUS "Skipping ${lab_name}: missing ${entry_cpp}")
        return()
    endif()

    # Start with entry point explicitly
    set(lab_sources "${entry_cpp}")

    # Add any other .cpp/.cc/.cxx files under labN/ (optional)
    file(GLOB_RECURSE extra_sources CONFIGURE_DEPENDS
        "${lab_dir}/*.cpp"
        "${lab_dir}/*.cc"
        "${lab_dir}/*.cxx"
        "${lab_dir}/*.CPP"
        "${lab_dir}/*.CC"
        "${lab_dir}/*.CXX"
    )
    list(REMOVE_ITEM extra_sources "${entry_cpp}")
    list(APPEND lab_sources ${extra_sources})

    add_executable(${lab_name} ${lab_sources})

    target_include_directories(${lab_name} PRIVATE "${lab_dir}")

    # Build only ACTIVE_LAB by default
    if(NOT "${lab_name}" STREQUAL "${ACTIVE_LAB}")
        set_target_properties(${lab_name} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()

    list(APPEND VALID_LABS "${lab_name}")
    set(VALID_LABS "${VALID_LABS}" PARENT_SCOPE)

    message(STATUS "${lab_name} entry: ${entry_file}.cpp | sources: ${lab_sources}")
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
        "Expected entry point in ${ACTIVE_LAB}/\n"
        "Discovered valid labs: ${VALID_LABS_STR}"
    )
endif()

add_custom_target(lab ALL DEPENDS ${ACTIVE_LAB})

add_custom_target(run
    COMMAND $<TARGET_FILE:${ACTIVE_LAB}>
    DEPENDS ${ACTIVE_LAB}
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)