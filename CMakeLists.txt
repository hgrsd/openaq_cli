cmake_minimum_required(VERSION 3.13)

if(APPLE)
	link_directories(/usr/local/lib)
	include_directories(/usr/local/include)
endif()

project (OpenAQ_CLI)
add_subdirectory(src)

enable_testing ()
add_subdirectory(test)
