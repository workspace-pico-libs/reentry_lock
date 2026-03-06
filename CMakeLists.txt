# Name of library in variable
set(LIB_NAME reentry_lock)

# Collect sources
file(GLOB LIB_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/private/src/*.c
)

# Create STATIC library
add_library(${LIB_NAME} STATIC ${LIB_SOURCES})

# Define headers- public and private
target_include_directories(${LIB_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/public/inc

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/private/inc
)

# Zależności biblioteki
target_link_libraries(${LIB_NAME}
    PUBLIC
        common_compile_options
        FreeRTOS-Kernel
)

#reset something after changename LOL
# get_target_property(TEST_INC reentry_lock INTERFACE_INCLUDE_DIRECTORIES)
# message(STATUS "REENTRY INC: ${TEST_INC}")