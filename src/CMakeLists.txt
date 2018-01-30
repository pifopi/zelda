#set the minimum cmake version required
cmake_minimum_required(VERSION 3.9.1)

#set the name of the project
project(zelda)

#enable c++ 17
set(CMAKE_CXX_STANDARD 17)

#set the root source directory as include directory
include_directories(${CMAKE_SOURCE_DIR})

#find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.4.2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})

#add all subdirectory
add_subdirectory(imgui)
add_subdirectory(rapidXML)

#enable warning and treat them as errors
if(CMAKE_COMPILER_IS_GNUCC)
	set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
elseif(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX")
endif()

file(GLOB MAIN_SOURCES
	*.cpp
	*.h
	*.hpp
)
add_executable(main ${MAIN_SOURCES})
set_target_properties(main PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(main imgui ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})

#copy needed files
file(GLOB FILES
	"../resources/*"
)
file(COPY ${FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
