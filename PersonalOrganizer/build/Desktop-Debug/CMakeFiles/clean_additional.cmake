# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/PersonalOrganizer_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/PersonalOrganizer_autogen.dir/ParseCache.txt"
  "PersonalOrganizer_autogen"
  )
endif()
