## OpenAQ_CLI
OpenAQ_CLI is a command-line API wrapper for OpenAQ (http://www.openaq.org): the world's first open, real-time and historical air quality platform, aggregating government-measured and research-grade data - entirely open-source.

OpenAQ_CLI is written in C, using libcurl for HTTP requests (https://curl.haxx.se/libcurl/) and jansson (http://www.digip.org/jansson/) for JSON functionality.

## Building OpenAQ_CLI

* Make sure you have the required libraries (curl and jansson) installed.
* Create makefiles for your system using CMake:
  * e.g. cmake -G "Unix Makefiles" -B build/  (run from root directory)
* If you're using unix makefiles, run `make all` from within newly created `build` folder


## Running tests

Run `make test` from the `build` folder, or `make all test` to build and test at the same time.
