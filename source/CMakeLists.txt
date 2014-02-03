SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")

add_executable(dicom-extracter
        main.cpp

	dir.cpp
        dicom/field.cpp
        dicom/date_field.cpp
        dicom/integer_field.cpp
        dicom/name_field.cpp
        dicom/dicom.cpp

	logxx/logxx.cpp
)
