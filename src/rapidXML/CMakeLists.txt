file(GLOB_RECURSE RAPIDXML_SOURCES
	*.cpp
	*.h
	*.hpp
)
add_library(rapidXML ${RAPIDXML_SOURCES})
set_target_properties(rapidXML PROPERTIES LINKER_LANGUAGE CXX)
