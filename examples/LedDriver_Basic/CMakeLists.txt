# The following lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)

# Only TESTING for build in current example folder
set(EXTRA_COMPONENT_DIRS ../../.)
# For use when component is in {ProjectName}/components Folder 
# set(EXTRA_COMPONENT_DIRS .)
# For use when component is in an shared location for multible Projects
# set(EXTRA_COMPONENT_DIRS {ABSOLUT_PATH})

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(LedDriver_Basic)
