message(STATUS "======================================>")
message(STATUS "in module 27_ChangeContrastAndBright")
message(STATUS "======================================>")

FILE(GLOB_RECURSE headers "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
FILE(GLOB_RECURSE src "${CMAKE_CURRENT_SOURCE_DIR}/*.c*")

source_group_by_dir(src ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "src is ${src}")

add_executable(test_change_contrast_bright
	${src}
	${header}
	)
	
set(OPENCV_LIBRARIES
	opencv_world310d
	)
	
set(DL_LIBS "")

target_link_libraries(test_change_contrast_bright ${OPENCV_LIBRARIES})