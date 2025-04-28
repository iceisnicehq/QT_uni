# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/lr2_dop3_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/lr2_dop3_autogen.dir/ParseCache.txt"
  "lr2_dop3_autogen"
  )
endif()
