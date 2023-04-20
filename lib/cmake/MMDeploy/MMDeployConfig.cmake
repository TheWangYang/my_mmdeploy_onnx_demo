
####### Expanded from @PACKAGE_INIT@ by configure_package_config_file() #######
####### Any changes to this file will be overwritten by the next CMake run ####
####### The input file was MMDeployConfig.cmake.in                            ########

get_filename_component(PACKAGE_PREFIX_DIR "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

####################################################################################

cmake_minimum_required(VERSION 3.14)

include("${CMAKE_CURRENT_LIST_DIR}/MMDeployTargets.cmake")

set(MMDEPLOY_CODEBASES all)
set(MMDEPLOY_TASKS classifier;detector;segmentor;text_detector;text_recognizer;restorer;pose_detector;pose_tracker;rotated_detector;video_recognizer)
set(MMDEPLOY_TARGET_DEVICES cuda)
set(MMDEPLOY_TARGET_BACKENDS ort;trt)
set(MMDEPLOY_BUILD_TYPE Release)
set(MMDEPLOY_BUILD_SHARED OFF)
set(MMDEPLOY_BUILD_SDK_MONOLITHIC ON)
set(MMDEPLOY_VERSION_MAJOR 0)
set(MMDEPLOY_VERSION_MINOR 14)
set(MMDEPLOY_VERSION_PATCH 0)

if (NOT MMDEPLOY_BUILD_SHARED AND NOT MMDEPLOY_BUILD_SDK_MONOLITHIC)
    if ("cuda" IN_LIST MMDEPLOY_TARGET_DEVICES)
        find_package(CUDA REQUIRED)
        if(MSVC)
            set(CMAKE_CUDA_COMPILER ${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc.exe)
        else()
            set(CMAKE_CUDA_COMPILER ${CUDA_TOOLKIT_ROOT_DIR}/bin/nvcc)
        endif()
        set(CMAKE_CUDA_RUNTIME_LIBRARY Shared)
        enable_language(CUDA)
        find_package(pplcv REQUIRED)
    endif ()
endif ()

set(MMDEPLOY_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/modules")
list(APPEND CMAKE_MODULE_PATH ${MMDEPLOY_MODULE_PATH})

find_package(TENSORRT REQUIRED)
find_package(CUDNN REQUIRED)
find_package(ONNXRUNTIME REQUIRED)



list(REMOVE_ITEM CMAKE_MODULE_PATH ${MMDEPLOY_MODULE_PATH})

find_package(OpenCV REQUIRED)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include("${CMAKE_CURRENT_LIST_DIR}/MMDeploy.cmake")
