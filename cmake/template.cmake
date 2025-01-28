cmake_minimum_required(VERSION 3.20)


if("${TARGET_PLATFORM}" STREQUAL "EMBEDDED")
message(FOO)
elseif("${TARGET_PLATFORM}" STREQUAL "HOST")
message(BAR)
elseif("${TARGET_PLATFORM}" STREQUAL "UNIT_TESTS")
message(BAZ)
endif()



