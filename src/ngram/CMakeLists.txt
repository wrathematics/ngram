cmake_minimum_required(VERSION 2.8.8)
project(ngram)
enable_language(C)


### Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wfatal-errors -O2 -fPIC")



### Source files
set(NGRAM_FILES
	src/counts.c
	src/gen.c
	src/hash.c
	src/lex.c
	src/print.c
	src/process.c
	src/sorts.c
	src/summary.c
	src/wordcmp.c
)

set(RAND_FILES
	src/rand/rng_interface.c
	src/rand/samplers.c
	src/rand/utils.c
	src/rand/mrg/rand_mrg.c
	src/rand/mt/rand_mt.c
)


set(SRC_FILES ${NGRAM_FILES} ${RAND_FILES})



### Make and install
add_definitions(-DNEXTWORDS)

add_library(ngram_objs OBJECT ${SRC_FILES})

add_library(ngram SHARED $<TARGET_OBJECTS:ngram_objs>)
add_library(ngram_static STATIC $<TARGET_OBJECTS:ngram_objs>)

add_executable(example examples/main.c $<TARGET_OBJECTS:ngram_objs>)
add_executable(test examples/test.c $<TARGET_OBJECTS:ngram_objs>)

set_target_properties(ngram PROPERTIES PREFIX "")
if(NOT WIN32)
  set_target_properties(ngram PROPERTIES SUFFIX ".so")
  install(TARGETS ngram LIBRARY DESTINATION ${CMAKE_SOURCE_DIR})
else(NOT WIN32)
  install(TARGETS ngram RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})
endif(NOT WIN32)

