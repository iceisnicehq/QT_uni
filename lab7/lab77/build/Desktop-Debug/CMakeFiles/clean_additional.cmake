# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/laba77_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/laba77_autogen.dir/ParseCache.txt"
  "laba77_autogen"
  )
endif()
