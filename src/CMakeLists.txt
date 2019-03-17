add_library (openaq_lib
			core.c
			data.c
			string_util.c
			json.c
			api_calls.c
			args.c
			io.c
			date_util.c)

add_executable (openaq_cli openaq_cli.c)

target_link_libraries (openaq_cli
						curl
						jansson
						openaq_lib)

