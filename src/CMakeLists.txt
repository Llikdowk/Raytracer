project(src)

include_directories(Public)
include_directories(${meml_SOURCE_DIR}/include)

set(SOURCE_FILES EntryPoint.cpp)
add_executable(Raytracer ${SOURCE_FILES})
link_libraries(Raytracer meml)

add_subdirectory(tests)

