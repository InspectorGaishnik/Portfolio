# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\myFirstApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\myFirstApp_autogen.dir\\ParseCache.txt"
  "myFirstApp_autogen"
  )
endif()
