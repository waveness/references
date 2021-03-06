cmake_minimum_required(VERSION 3.0)

# put key value to map
MACRO(MAP_PUT _MAP _KEY _VALUE)
    SET("MAP_${_MAP}_${_KEY}" ${_VALUE})
ENDMACRO()

# get value int map
MACRO(MAP_GET _MAP _KEY _OUTPUT)
    SET(KEY "MAP_${_MAP}_${_KEY}")
    set(${_OUTPUT} "undefined")
    if (${KEY})
        set(${_OUTPUT} ${${KEY}})
    endif ()

ENDMACRO()

# load properties in file and put it into map
MACRO(LOAD_PROPERTY _MAP _FILENAME)
    FILE(READ ${_FILENAME} contents)
    STRING(REGEX REPLACE "\n" ";" lines "${contents}")
    foreach (line ${lines})
        if (NOT (${line} MATCHES "^(#|\t|\n| )"))
            STRING(REGEX REPLACE "\t+| +" ";" fields ${line})
            list(GET fields 0 KEY)
            list(GET fields 1 VALUE)
            MAP_PUT(${_MAP} ${KEY} ${VALUE})
        endif ()
    endforeach ()

ENDMACRO()


MACRO(GETLINES _LINES _FILENAME)
    FILE(READ ${_FILENAME} contents)
    STRING(REGEX REPLACE "\n" ";" ${_LINES} "${contents}")
ENDMACRO()

SET(PROPERTY_FILE "${CMAKE_CURRENT_SOURCE_DIR}/build.properties")
SET(PROPERTY_FILE_LOCAL "${CMAKE_CURRENT_SOURCE_DIR}/build.properties.local")
# load properties into ${PROPERTIES}
MACRO(READ_PROPERTIES PROPERTIES)
    if ((NOT (EXISTS ${PROPERTY_FILE})) AND (NOT (EXISTS ${PROPERTY_FILE_LOCAL})))
        message(FATAL_ERROR "CONFIG FILE `${PROPERTY_FILE}` and `${PROPERTY_FILE_LOCAL}` not EXISTS")
    endif () 
    if (EXISTS ${PROPERTY_FILE})
        message(STATUS "READ CONFIG FROM FILE:${PROPERTY_FILE}")
        LOAD_PROPERTY(${PROPERTIES} ${PROPERTY_FILE})
    endif ()
    if (EXISTS ${PROPERTY_FILE_LOCAL})
        message(STATUS "READ CONFIG FROM FILE:${PROPERTY_FILE_LOCAL}")
        LOAD_PROPERTY(${PROPERTIES} ${PROPERTY_FILE_LOCAL})
    endif ()
ENDMACRO()

# init build type
MACRO(INIT_TYPE PROPERTIES)
    MAP_GET(${PROPERTIES} build_type build_type)
    if (${build_type} STREQUAL "debug")
        set(CMAKE_BUILD_TYPE Debug)
        message(STATUS "BUILD TYPE:Debug")
        set(HOBOT_BUILD_DEBUG "TRUE")
    else ()
        set(CMAKE_BUILD_TYPE Release)
        message(STATUS "BUILD TYPE:Release")
    endif ()
ENDMACRO()

# init platform info from ${PROPERTIES}
MACRO(INIT_PLATFORM_INFO PROPERTIES)
    MAP_GET(${PROPERTIES} platform platform)
    if (${platform} STREQUAL "mac")
        set(PLATFORM_MAC TRUE)
    elseif (${platform} STREQUAL "linux")
        set(PLATFORM_LINUX TRUE)
        MAP_GET(${PROPERTIES} cmake_c_compiler C_COMPILER)
        MAP_GET(${PROPERTIES} cmake_cxx_compiler CXX_COMPILER)
        if (${C_COMPILER} STREQUAL "undefined")
        else ()
            SET(CMAKE_C_COMPILER ${C_COMPILER})
        endif ()
        if (${CXX_COMPILER} STREQUAL "undefined")
        else ()
            SET(CMAKE_CXX_COMPILER ${CXX_COMPILER})
        endif ()

    elseif (${platform} STREQUAL "win")
        SET(GRADLE_CMD ${GRADLE_WIN_CMD})
        set(PLATFORM_WIN TRUE)
    elseif (${platform} STREQUAL "android")
        set(PLATFORM_ANDROID TRUE)
        set(ANDROID_STL gnustl_static)
        set(CMAKE_VERBOSE_MAKEFILE ON)
        MAP_GET(${PROPERTIES} ANDROID_NDK ANDROID_NDK)
        if (${ANDROID_NDK} STREQUAL "undefined")
            message(FATAL_ERROR "ANDROID_NDK NOT SET")
        endif ()
        set(ANDROID_NDK ${ANDROID_NDK})
        set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/android.toolchain.cmake")
        message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")
        set(ANDROID_ABI armeabi-v7a)
        set(ANDROID_NATIVE_API_LEVEL android-21)
        message(STATUS "cmake -DPLATFORM_ANDROID=${PLATFORM_ANDROID} -DANDROID_STL=${ANDROID_STL} -DANDROID_NDK=${ANDROID_NDK} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DANDROID_ABI=${ANDROID_ABI} -DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL} ..")
    else ()
        message(FATAL_ERROR "platform `${platform}` not suppored, choose from [linux | android | win | mac]")
    endif ()
ENDMACRO()

function(test_function)
    foreach(arg ${ARGN})
        message( STATUS "args-->" ${arg} )
    endforeach()
endfunction()

READ_PROPERTIES(properties)
INIT_TYPE(properties)
INIT_PLATFORM_INFO(properties) 

