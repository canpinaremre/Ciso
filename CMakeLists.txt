# set cmake minimum version
cmake_minimum_required(VERSION 3.0.0)

# set the project name
project("Ciso")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g3 -O0")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# project source directories to be compiled
set(project_source_dirs
	"src/core"
	"src/drivers"
	"lib/ImGui"
	"lib/ImPlot"
	)

# project include directories
set(project_include_dirs
	"src/core"
	"src/drivers"
	"lib/ImGui"
	"lib/ImPlot"
	"lib/GLFW"
	)

# project link directories
set(project_link_dirs
	"lib/SDL/lib"
	"lib/GLFW"
	)

# project link libraries
set(project_link_libraries
	"SetupAPI"
	"Ws2_32"
	"opengl32"
	"GLFW3"
	)

# set include directories
include_directories(${project_include_dirs})

# set link directories, library search paths
link_directories(${project_link_dirs})

# linked libraries
link_libraries(${project_link_libraries})

# search pattern for sources
foreach(dir ${project_source_dirs})
	list(APPEND project_sources_glob "${dir}/**.c*")
endforeach()

# find project source files
file(GLOB_RECURSE project_sources RELATIVE ${CMAKE_SOURCE_DIR} ${project_sources_glob})

# add the executable
add_executable(${PROJECT_NAME} ${project_sources})