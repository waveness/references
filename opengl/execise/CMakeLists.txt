cmake_minimum_required(VERSION 2.8.11)

project(opengl_exercise)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/prebuild/glfw/include
  ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/glad/include
  ${CMAKE_CURRENT_SOURCE_DIR}/prebuild
  ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/stb
  ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/glm)

link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/prebuild/glfw/lib)
	
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

#file(GLOB_RECURSE exercise_cxx "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*")
#source_group_by_dir(exercise_cxx ${CMAKE_CURRENT_SOURCE_DIR})

set(GLAD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/prebuild/glad/src/glad.c)

add_subdirectory(firstproject)
add_subdirectory(hello_triangle)
add_subdirectory(shaders_uniform)
add_subdirectory(textures_combined)
add_subdirectory(transformations)