project(src)

include_directories(Public)
set(SOURCE_FILES EntryPoint.cpp)
add_executable(Raytracer ${SOURCE_FILES})

add_subdirectory(tests)

