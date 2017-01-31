project(src)

include_directories(Public)
include_directories(${meml_SOURCE_DIR}/include)

set(LIB_FILES Public/Color.h Public/Image.h Public/Material.h Public/MyMath.h Public/Object.h Public/Raytracer.h Public/Scene.h)
add_library(RaytracerLib ${LIB_FILES})
set_target_properties(RaytracerLib PROPERTIES LINKER_LANGUAGE CXX)


set(SOURCE_FILES EntryPoint.cpp)
add_executable(Raytracer ${SOURCE_FILES})
target_link_libraries(Raytracer meml RaytracerLib)

add_subdirectory(tests)

