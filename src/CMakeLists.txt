cmake_minimum_required(VERSION 3.13)

if(APPLE)
	link_directories(/usr/local/lib)
	include_directories(/usr/local/include)
endif()

project (OpenAQ_CLI)
add_executable (openaq_cli
				openaq_cli.c
				core.c
				data.c
				string_util.c
				json.c
				api_calls.c
				args.c)
target_link_libraries (openaq_cli
						curl
						jansson)

