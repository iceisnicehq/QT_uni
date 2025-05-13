# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/appWeatherApp_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/appWeatherApp_autogen.dir/ParseCache.txt"
  "appWeatherApp_autogen"
  )
endif()
