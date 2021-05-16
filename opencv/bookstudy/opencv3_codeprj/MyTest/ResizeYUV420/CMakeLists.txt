message(STATUS "======================================>")
message(STATUS "in module ResizeYUV")
message(STATUS "======================================>")

FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")
source_group_by_dir(src ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "src is ${src}")
#message(STATUS "header is ${headers}")

link_directories(
	D:\\ProgramFiles\\Opencv\\opencv\\build\\x64\\vc14\\bin
	D:\\ProgramFiles\\Opencv\\opencv\\build\\x64\\vc14\\lib
)
include_directories(
	D:\\ProgramFiles\\Opencv\\opencv\\build\\include
)
add_executable(test_resizeyuv_directly
	${src}
	${headers}
	)
	
set(OPENCV_LIBRARIES
   opencv_world410d
	)
set(DL_LIBS "")

target_link_libraries(test_resizeyuv_directly ${OPENCV_LIBRARIES})