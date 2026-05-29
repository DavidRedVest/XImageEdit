# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MyImageEdit_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MyImageEdit_autogen.dir/ParseCache.txt"
  "MyImageEdit_autogen"
  )
endif()
