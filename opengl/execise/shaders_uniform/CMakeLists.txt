message(STATUS "======================================>")
message(STATUS "in module shader uniform")
message(STATUS "======================================>")

FILE(GLOB_RECURSE header "${CMAKE_CURRENT_SOURCE_DIR}/*.h*")
source_group_by_dir(header ${CMAKE_CURRENT_SOURCE_DIR})
FILE(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")
source_group_by_dir(src ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "src is ${src}")

add_executable(test_uniform
	${src}
	${headers}
  ${GLAD_SOURCE})

set(GLFW_LIBRARY glfw3.lib)
set(OPENGL_LIBRARY opengl32.lib)

target_link_libraries(test_uniform ${GLFW_LIBRARY} ${OPENGL_LIBRARY})