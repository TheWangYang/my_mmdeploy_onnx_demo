PROJECT(ObjectDetection)
cmake_minimum_required(VERSION 3.20)
# 设置C++17标准
set(CMAKE_CXX_STANDARD 17)

# 包含需要编译得到的头文件
SET(LIBOD_SRC ./src/object_detection_batch_inference.cpp)
ADD_LIBRARY(onnx_inference SHARED ${LIBOD_SRC})

set(OpenCV_DIR "D:/opencv_3_4_6_build_from_exe/opencv/build")
find_package(OpenCV REQUIRED)
if(OpenCV_FOUND)
    target_include_directories(onnx_inference PUBLIC ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(onnx_inference PRIVATE ${OpenCV_LIBS})
endif()


# 添加mmdeploy编译需要的文件
if (NOT (${CMAKE_PROJECT_NAME} STREQUAL "MMDeploy"))
    find_package(MMDeploy REQUIRED)
endif ()

if (MMDEPLOY_BUILD_SDK_MONOLITHIC)
    target_link_libraries(onnx_inference PRIVATE mmdeploy)
else ()
    # Load MMDeploy modules
    mmdeploy_load_static(onnx_inference MMDeployStaticModules)
    mmdeploy_load_dynamic(onnx_inference MMDeployDynamicModules)
    # Link to MMDeploy libraries
    target_link_libraries(onnx_inference PRIVATE MMDeployLibs)
endif ()



