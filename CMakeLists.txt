cmake_minimum_required(VERSION 4.1)

set(CMAKE_CXX_STANDARD 17)

option(PRODUCTION_BUILD "Make this a production build!" OFF)
option(JSON_USE_IMPLICIT_CONVERSIONS OFF)

project(mySnake)

# Raylib
add_subdirectory(lib/raylib EXCLUDE_FROM_ALL)

#JSON
set(JSON_BuildTests OFF CACHE INTERNAL "")

add_subdirectory(lib/json)

#add_library(foo lib/json/include/nlohmann)

#target_link_libraries(foo PRIVATE nlohmann_json::nlohmann_json)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE MY_HEADERS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")

add_executable("${CMAKE_PROJECT_NAME}")

if(PRODUCTION_BUILD)
	# setup the ASSETS_PATH macro to be in the root folder of your exe
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/") 

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1) 

else()
	# This is useful to get an ASSETS_PATH in your IDE during development
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0) 

endif()

target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES} ${MY_HEADERS})

target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lib/")
target_include_directories("${CMAKE_PROJECT_NAME}" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Link libraries statically
target_link_libraries("${CMAKE_PROJECT_NAME}" 
	raylib
	nlohmann_json::nlohmann_json
)