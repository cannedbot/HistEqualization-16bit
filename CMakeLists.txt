cmake_minimum_required(VERSION 3.8)
project( HistEqualization-16bit )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( HistEqualization-16bit main.cpp )

add_library( HistEqualizationLib 
		HistEqualization.cpp )

target_link_libraries( HistEqualization-16bit
		${OpenCV_LIBS} 
		HistEqualizationLib )

add_executable( unitTest Unit-Test.cpp )
target_link_libraries( unitTest 
		${OpenCV_LIBS} 
		HistEqualizationLib )