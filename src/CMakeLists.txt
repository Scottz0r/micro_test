add_library(micro_test STATIC micro_test.c)

target_include_directories(micro_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
