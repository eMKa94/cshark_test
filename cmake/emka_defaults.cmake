# Application default compile & linking options

message("EMKA CMAKE BUILD SYSTEM")

include(${CMAKE_SOURCE_DIR}/cmake/emka_macros.cmake)

enable_language(C CXX ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("Target platform [ ${TARGET_PLATFORM} ]")

get_commit_hash(GIT_COMMIT_HASH)
message("GIT HASH [ ${GIT_COMMIT_HASH} ]")

# clear default flags for Release
# set(CMAKE_C_FLAGS_RELEASE_INIT "")
# set(CMAKE_CXX_FLAGS_RELEASE_INIT "")
# set(CMAKE_ASM_FLAGS_RELEASE_INIT "")

# set custom flags
set(CMAKE_ASM_FLAGS_DEBUG "-Og -g3")
set(CMAKE_C_FLAGS_DEBUG "-Og -g3")
set(CMAKE_CXX_FLAGS_DEBUG "-Og -g3")

# set(CMAKE_ASM_FLAGS_RELEASE "-O2")
# set(CMAKE_C_FLAGS_RELEASE "-Os")
# set(CMAKE_CXX_FLAGS_RELEASE "-Os")

set(MCU_FAMILY STM32G4xx)
set(MCU_MODEL STM32G431xx)

set(ARM_DEFAULT_C_FLAGS

    -ffunction-sections
    -fdata-sections
    --specs=nano.specs
    --specs=nosys.specs
    -fstack-usage
    # -flto
    -mthumb
    
    -Wall
    -Wextra 
    -Wpedantic
    # -Werror
    -Wno-unused-parameter
    -Wno-missing-field-initializers

    -DUSE_HAL_DRIVER
    -DUSE_FULL_LL_DRIVER
    # -DCOMMIT_HASH=${GIT_COMMIT_HASH}
    -DULOG_ENABLED
    
)

set(ARM_DEFAULT_CPP_FLAGS

    -flto
    -fno-exceptions
    -fno-rtti
    -fno-use-cxa-atexit
    # -Wuseless-cast
    -Wsuggest-override
)

set(ARM_DEFAULT_LD_FLAGS

    ${ARM_DEFAULT_C_FLAGS}
    -Wl,--gc-sections
    -static
    -Wl,--start-group
    -lc
    -flto
    -lm
    -lstdc++
    -lsupc++
    -Wl,--end-group
    -Wl,--print-memory-usage
    
)


set(ARM_CM4F_FLAGS

    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard

)

set(ARM_CM0_FLASG

    -mcpu=cortex-m0

)

if("${TARGET_PLATFORM}" STREQUAL "UNIT_TESTS")

    add_subdirectory(cpputest)
    add_subdirectory(tests)

endif()