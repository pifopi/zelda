file(GLOB_RECURSE IMGUI_SOURCES
	*.cpp
	*.h
	*.hpp
)
add_library(imgui ${IMGUI_SOURCES})
set_target_properties(imgui PROPERTIES LINKER_LANGUAGE CXX)
