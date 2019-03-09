include_directories({OpenAQ_CLI_SOURCE_DIR}/src)

add_executable(openaq_test tests.c)

target_link_libraries (openaq_test
						curl
						jansson
						openaq_lib)

add_test (NAME OpenAQ_tests COMMAND openaq_test)