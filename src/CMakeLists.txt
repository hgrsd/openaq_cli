project (OpenAQ_CLI)
add_executable (openaq_cli
				main.c
				data.c
				string_util.c
				json.c
				api_calls.c)
target_link_libraries (openaq_cli
						curl
						jansson)

