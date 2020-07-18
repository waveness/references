cmake_minimum_required(VERSION 2.8.11)

project(opencv3_exercise)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/output")

message(STATUS "===>CMAKE_INSTALL_PREFIX=" ${CMAKE_INSTALL_PREFIX})

set(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")

include_directories(
	inc
	D:/ProgramFiles/Opencv/opencv3.10/build/include
	)
link_directories(
	D:/ProgramFiles/Opencv/opencv3.10/build/x64/vc14/lib
	)
macro(source_group_by_dir all_files strip_path)
    #message("${strip_path}")
    if(MSVC)    
        foreach(single_file ${${all_files}})
            #message("${single_file}")
            string(REGEX REPLACE "(${strip_path})/(.*)$" \\2 relative_fpath ${single_file})
            string(REGEX MATCH "^(.*)/(.*)\\.[^.]*$" dummy ${relative_fpath})
            set(file_path ${CMAKE_MATCH_1})
            #message("${file_path}")
            string(REPLACE "/" "\\" file_group_name ${file_path})
            #message("group name: ${file_group_name}")
            source_group(${file_group_name} FILES ${single_file})
        endforeach(single_file)
    endif(MSVC)
endmacro(source_group_by_dir)

function(wrap_target_link_libraries target)
  foreach (lib ${ARGN})
    target_link_libraries(${target} debug "${lib}${DEBUG_POSTFIX}" optimized ${lib})
  endforeach ()
endfunction()
	
file(GLOB_RECURSE exercise_cxx "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")
source_group_by_dir(exercise_cxx ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES
	${exercise_cxx}
)

add_subdirectory(Chapter5/25_ImageBlending)
add_subdirectory(Chapter5/24_14WaysToAccessPixel)
add_subdirectory(Chapter5/26_MultiChannelImageBlending)
add_subdirectory(Chapter5/27_ChangeContrastAndBright)
add_subdirectory(Chapter6/31_boxFilter)
add_subdirectory(Chapter6/49_floodFill)
add_subdirectory(MyTest/BGR2YUV)
add_subdirectory(Calibration)
add_subdirectory(MyTest/Disparity)
add_subdirectory(MyTest/Mp4Recorder)
add_subdirectory(MyTest/YUVReader)
add_subdirectory(MyTest/LearnMatDefine)
add_subdirectory(MyTest/PackJpegExport)
add_executable(main_entry ${SOURCE_FILES})
