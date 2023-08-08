set(prefix _birthdaygift)

add_executable(${prefix}_main main.cpp main.h)
add_executable(${prefix}_tests tests.cpp main.h checker.h)
add_executable(${prefix}_stress stress.cpp checker.h main.h)

add_custom_command(OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/out.cpp
        COMMAND /Users/alexfetisov/dev/caide-cpp-inliner/src/cmake-build-release/cmd/caide-inliner -t ${CMAKE_CURRENT_BINARY_DIR} -s ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
        -o ${CMAKE_CURRENT_SOURCE_DIR}/out.cpp
        -- ${CLANG_INLINER_FLAGS} -I ${CMAKE_CURRENT_SOURCE_DIR}
        IMPLICIT_DEPENDS CXX ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

set_source_files_properties(out.cpp PROPERTIES GENERATED TRUE)
add_executable(${prefix}_out out.cpp)