# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src\\QLineEditSearch\\CMakeFiles\\CMakeQtDemo_autogen.dir\\AutogenUsed.txt"
  "src\\QLineEditSearch\\CMakeFiles\\CMakeQtDemo_autogen.dir\\ParseCache.txt"
  "src\\QLineEditSearch\\CMakeQtDemo_autogen"
  )
endif()
