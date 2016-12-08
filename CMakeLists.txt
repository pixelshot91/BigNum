cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER "g++")
set(CMAKE_C_FLAGS "-Wall -Wextra -std=c++14 -pedantic")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O3")
set(BIN_NAME "bistro")

set(SRC "src/main.cc")

include_directories(src)
                    
add_executable(${BIN_NAME} ${SRC})

add_custom_target(doc
                  COMMAND doxygen doxy &> /dev/null && chromium html/index.html
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/doc)


add_custom_target(check
                  COMMAND ./test.rb -b ${CMAKE_BINARY_DIR}/${BIN_NAME}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
                  DEPENDS ${BIN_NAME})

add_custom_target(echeck
                  COMMAND ./test.rb -e -b ${CMAKE_BINARY_DIR}/${BIN_NAME}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
                  DEPENDS ${BIN_NAME})

add_custom_target(scheck
                  COMMAND ./test.rb -s -b ${CMAKE_BINARY_DIR}/${BIN_NAME}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
                  DEPENDS ${BIN_NAME})

add_custom_target(escheck
                  COMMAND ./test.rb -s -e -b ${CMAKE_BINARY_DIR}/${BIN_NAME}
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/tests
                  DEPENDS ${BIN_NAME})
