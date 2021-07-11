#set the minimum cmake version required
cmake_minimum_required(VERSION 3.16.0)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

#set the name of the project
project(zelda)

#enable c++ 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
if (MSVC)
	add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

#produce clang tidy file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
