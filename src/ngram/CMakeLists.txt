cmake_minimum_required(VERSION 2.8)
project(ngram)
enable_language(C)


### Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfatal-errors -O0 -fPIC")



### Source files
set(SRC_FILES
	src/counts.c
	src/gen_noalloc2.c
	src/hash.c
	src/lex.c
	src/print.c
	src/process.c
	src/summary.c
	src/wordcmp.c
	src/rand/rng_interface.c
	src/rand/samplers.c
	src/rand/utils.c
	src/rand/mrg/rand_mrg.c
	src/rand/mt/rand_mt.c
)



### Make and install
add_library(ngram SHARED ${SRC_FILES})
add_library(ngram_static STATIC ${SRC_FILES})

add_executable(example examples/main.c ${SRC_FILES})
add_executable(test examples/test.c ${SRC_FILES})

set_target_properties(ngram PROPERTIES PREFIX "")
if(NOT WIN32)
  set_target_properties(ngram PROPERTIES SUFFIX ".so")
  install(TARGETS ngram LIBRARY DESTINATION ${CMAKE_SOURCE_DIR})
else(NOT WIN32)
  install(TARGETS ngram RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})
endif(NOT WIN32)

