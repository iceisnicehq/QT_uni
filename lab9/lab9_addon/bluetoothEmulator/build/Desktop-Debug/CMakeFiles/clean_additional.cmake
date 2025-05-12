# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/bluetoothEmulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/bluetoothEmulator_autogen.dir/ParseCache.txt"
  "bluetoothEmulator_autogen"
  )
endif()
