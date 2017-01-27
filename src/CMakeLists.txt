project(src)

include_directories(Public)
set(SOURCE_FILES EntryPoint.cpp Public/MyMath.h Public/Object.h Public/Material.h)
add_executable(Raytracer ${SOURCE_FILES})
