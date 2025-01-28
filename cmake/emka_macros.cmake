# add_mab_executable is meant to be used only inside add_mab_app macro
macro(add_arm_executable app_name)

    set(${app_name}_ELF_FILE ${app_name}.elf)
    set(${app_name}_HEX_FILE ${app_name}.hex)
    set(${app_name}_BIN_FILE ${app_name}.bin)
    set(${app_name}_EFW_FILE ${app_name}.efw)
    set(${app_name}_MAP_FILE ${app_name}.map)

    add_executable(${app_name} ${ARGN})

    set_target_properties(${app_name} PROPERTIES OUTPUT_NAME "${app_name}.elf")

    target_link_options(${app_name} PRIVATE 
        -Wl,-Map=${app_name}.map
    )

    add_custom_command(
        OUTPUT ${${app_name}_HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${${app_name}_ELF_FILE} ${${app_name}_HEX_FILE}
        DEPENDS ${app_name}
    )

    add_custom_command(
        OUTPUT ${${app_name}_BIN_FILE}
        COMMAND ${CMAKE_OBJCOPY} -O binary ${${app_name}_ELF_FILE} ${${app_name}_BIN_FILE}
        DEPENDS ${app_name}
    )

    # add_custom_command(
    #     OUTPUT ${${app_name}_EFW_FILE}
    #     COMMAND python3 ${CMAKE_SOURCE_DIR}/utils/generate_fw_header.py ${${app_name}_BIN_FILE} ${${app_name}_EFW_FILE}
    #     DEPENDS ${${app_name}_BIN_FILE}
    # )

    add_custom_target(
        ${app_name}_CROSS_COMPILE
        ALL
        DEPENDS ${${app_name}_HEX_FILE}
        DEPENDS ${${app_name}_BIN_FILE}
    )

    configure_file(
    ${CMAKE_SOURCE_DIR}/firmware_metadata.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/firmware_metadata/firmware_metadata.h
    @ONLY
    )

    target_include_directories(${app_name} PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}/firmware_metadata
    )


endmacro(add_arm_executable)

macro(add_board_lib board_name board_MCU board_LS_FILE)

    add_library(${board_name} ${lib_type} ${ARGN})
    
    target_compile_options(${board_name} PUBLIC
        ${ARM_DEFAULT_C_FLAGS}
        $<$<COMPILE_LANGUAGE:CXX>:${ARM_DEFAULT_CPP_FLAGS}>    
    )
    target_link_libraries(${BOARD_NAME} PRIVATE stm32_cube_G4)
    # add_dependencies(${BOARD_NAME} drivers_${board_MCU})

    set(${board_name}_LS_FILE ${board_LS_FILE} PARENT_SCOPE)
    set(${board_name}_MCU ${board_MCU} PARENT_SCOPE)

endmacro(add_board_lib)

macro(add_arm_app app_name board_name)

    message("_________ Configuring app _________")
    message("name       [ ${app_name} ]")
    message("board      [ ${board_name} ]")
    add_arm_executable(${app_name} ${ARGN})

    target_link_libraries(${app_name} PUBLIC ${board_name})
    add_dependencies(${app_name} ${board_name})

endmacro(add_arm_app app_name)

macro(add_unit_test test_suite_name)

    add_executable(
        ${test_suite_name}
        ${ARGN}
    )

    target_link_libraries(${test_suite_name} PRIVATE
        CppUTest
        CppUTestExt
        CppUTestRunner
    )

    set_target_properties(${test_suite_name}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test_runners"
        OUTPUT_NAME "test_${test_suite_name}"
    )

    target_compile_options(${test_suite_name} PRIVATE

        # Temporary workaround of the issue
        # https://cpputest.github.io/manual.html#memory_leak_detection
        -DCPPUTEST_MEM_LEAK_DETECTION_DISABLED
        -DTEST_BUILD

    )

    set_property(TARGET ${test_suite_name} PROPERTY CXX_STANDARD 20)
endmacro(add_unit_test)
# Gets current commit hash and stores in "commit_hash_var" var name
macro(get_commit_hash commit_hash_var)
    
    execute_process(
        COMMAND git rev-parse --short HEAD
        OUTPUT_VARIABLE ${commit_hash_var}
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

endmacro(get_commit_hash)
