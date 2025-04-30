# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BookCatalog_autogen"
  "CMakeFiles/BookCatalog_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BookCatalog_autogen.dir/ParseCache.txt"
  )
endif()
