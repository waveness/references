message(STATUS "======================================>")
message(STATUS "in module Mp4Recorder")
message(STATUS "======================================>")

FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")
source_group_by_dir(src ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "src is ${src}")
#message(STATUS "header is ${headers}")

add_executable(Mp4Recorder
	${src}
	${headers}
	)
	
set(OPENCV_LIBRARIES
   opencv_world310
	)
set(DL_LIBS "")

target_link_libraries(Mp4Recorder ${OPENCV_LIBRARIES})