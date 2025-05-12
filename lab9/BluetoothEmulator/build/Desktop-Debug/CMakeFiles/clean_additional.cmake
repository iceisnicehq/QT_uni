# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BluetoothEmulator_autogen"
  "CMakeFiles/BluetoothEmulator_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BluetoothEmulator_autogen.dir/ParseCache.txt"
  )
endif()
