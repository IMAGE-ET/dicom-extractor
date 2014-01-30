set (TEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
configure_file (
	"config.h.in"
	"${CMAKE_CURRENT_BINARY_DIR}/config.h"
)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(dicom-extractor-test
        main.cpp

	../source/logxx/logxx.cpp

	../source/dicom/field.cpp
        ../source/dicom/date_field.cpp
        ../source/dicom/name_field.cpp
        ../source/dicom/integer_field.cpp
        ../source/dicom/dicom.cpp

)
