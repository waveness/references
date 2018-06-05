message(STATUS "======================================>")
message(STATUS "in module textures combined")
message(STATUS "======================================>")

FILE(GLOB_RECURSE header "${CMAKE_CURRENT_SOURCE_DIR}/*.h*")
source_group_by_dir(header ${CMAKE_CURRENT_SOURCE_DIR})
FILE(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")
source_group_by_dir(src ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "src is ${src}")

set(STB_IMG ${PROJECT_SOURCE_DIR}/prebuild/stb/stb_image.h)
add_executable(test_texture
	${src}
	${headers}
  ${GLAD_SOURCE}
  ${STB_IMG})

set(GLFW_LIBRARY glfw3.lib)
set(OPENGL_LIBRARY opengl32.lib)

target_link_libraries(test_texture ${GLFW_LIBRARY} ${OPENGL_LIBRARY})