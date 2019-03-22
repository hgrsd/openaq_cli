add_executable(openaq_test tests.c)

target_include_directories(openaq_test PRIVATE "../src")


target_link_libraries (openaq_test
						curl
						jansson
						openaq_lib)

add_test (NAME OpenAQ_tests COMMAND openaq_test)