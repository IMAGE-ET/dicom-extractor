set (DATA_DIR "${CMAKE_SOURCE_DIR}/data")
configure_file (
	"config.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.h"
)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(dicom-extracter
        main.cpp
	field.cpp
	logxx/logxx.cpp
)
