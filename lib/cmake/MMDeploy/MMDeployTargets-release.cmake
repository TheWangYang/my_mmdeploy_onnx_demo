#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "mmdeploy_trt_net" for configuration "Release"
set_property(TARGET mmdeploy_trt_net APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mmdeploy_trt_net PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/mmdeploy_trt_net.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "mmdeploy"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/mmdeploy_trt_net.dll"
  )

list(APPEND _cmake_import_check_targets mmdeploy_trt_net )
list(APPEND _cmake_import_check_files_for_mmdeploy_trt_net "${_IMPORT_PREFIX}/lib/mmdeploy_trt_net.lib" "${_IMPORT_PREFIX}/bin/mmdeploy_trt_net.dll" )

# Import target "mmdeploy_ort_net" for configuration "Release"
set_property(TARGET mmdeploy_ort_net APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mmdeploy_ort_net PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/mmdeploy_ort_net.lib"
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELEASE "mmdeploy"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/mmdeploy_ort_net.dll"
  )

list(APPEND _cmake_import_check_targets mmdeploy_ort_net )
list(APPEND _cmake_import_check_files_for_mmdeploy_ort_net "${_IMPORT_PREFIX}/lib/mmdeploy_ort_net.lib" "${_IMPORT_PREFIX}/bin/mmdeploy_ort_net.dll" )

# Import target "mmdeploy" for configuration "Release"
set_property(TARGET mmdeploy APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(mmdeploy PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/mmdeploy.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/mmdeploy.dll"
  )

list(APPEND _cmake_import_check_targets mmdeploy )
list(APPEND _cmake_import_check_files_for_mmdeploy "${_IMPORT_PREFIX}/lib/mmdeploy.lib" "${_IMPORT_PREFIX}/bin/mmdeploy.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
