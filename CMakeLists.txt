# project(object_detector_on_image_cpp)
# cmake_minimum_required(VERSION 3.22)

# set(CMAKE_CXX_STANDARD 17)

# SET(OPENCV_CPP_REQUIRED_DEPS opencv_core opencv_flann opencv_imgproc
#     opencv_highgui opencv_ml opencv_video opencv_objdetect opencv_photo
#     opencv_features2d opencv_calib3d
#     opencv_stitching opencv_videostab)

# find_package(OpenCV REQUIRED )
# include_directories(${OpenCV_INCLUDE_DIRS})

# add_executable(object_detector_on_image_cpp src/brisk-detector.cpp)
# target_link_libraries(object_detector_on_image_cpp ${OpenCV_LIBS} ${OPENCV_CPP_REQUIRED_DEPS})

set(OPENCV_DIR "/opt/homebrew/Cellar/opencv")

cmake_minimum_required(VERSION 3.22)
project(object_detector_on_image_cpp)

# Use C++ 11 by default
set(CMAKE_CXX_STANDARD 17)

# Set Release as default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

# Needed for opencv2/opencv.hpp
include_directories("${OPENCV_DIR}/include")

# Needed by opencv.hpp for opencv2/opencv_modules.hpp
include_directories("${OPENCV_DIR}/build_wasm")

# Needed by opencv_modules.hpp for every module
file(GLOB opencv_include_modules "${OPENCV_DIR}/modules/*/include")
include_directories(${opencv_include_modules})

# Our hello world executable
add_executable(object_detector_on_image_cpp src/brisk-detector.cpp)

# Link to opencv.js precompiled libraries
file(GLOB OpenCV_LIBS "${OPENCV_DIR}/build_wasm/lib/*.a")
target_link_libraries(object_detector_on_image_cpp ${OpenCV_LIBS})

SET(OPENCV_CPP_REQUIRED_DEPS opencv_core opencv_flann opencv_imgproc
    opencv_highgui opencv_ml opencv_video opencv_objdetect opencv_photo
    opencv_features2d opencv_calib3d
    opencv_stitching opencv_videostab)

include_directories(${OpenCV_INCLUDE_DIRS})

# There is an issue regarding the order in which libraries
# are passed to the compiler - pass libopencv_core.a last
# https://answers.opencv.org/question/186124/undefined-reference-to-cvsoftdoubleoperator/
# file(GLOB opencv_lib_core "${OPENCV_DIR}/build_wasm/lib/libopencv_core.a")
# target_link_libraries(object_detector_on_image_cpp ${opencv_lib_core})
target_link_libraries(object_detector_on_image_cpp ${OpenCV_LIBS} ${OPENCV_CPP_REQUIRED_DEPS})



# Specify linker arguments
set_target_properties(object_detector_on_image_cpp PROPERTIES LINK_FLAGS "-s EXPORTED_RUNTIME_METHODS=cwrap -s EXPORTED_FUNCTIONS=_free -s MODULARIZE=1 -s EXPORT_NAME=createHelloModule")
