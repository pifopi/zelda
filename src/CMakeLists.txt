#set the minimum cmake version required
cmake_minimum_required(VERSION 3.15)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#set the name of the project
project(zelda)

#enable c++ 17
set(CMAKE_CXX_STANDARD 17)

#set the root source directory as include directory
include_directories(${CMAKE_SOURCE_DIR})

#add all subdirectory
set(BUILD_SHARED_LIBS FALSE)
set(SFML_USE_STATIC_STD_LIBS TRUE)
add_subdirectory(SFML)
set(IMGUI_SFML_FIND_SFML FALSE)
add_subdirectory(imgui-sfml)
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
add_executable(zelda ${MAIN_SOURCES})
set_target_properties(zelda PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(zelda ImGui-SFML::ImGui-SFML)

#copy needed files
file(GLOB FILES
	"../resources/*"
)
file(COPY ${FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
