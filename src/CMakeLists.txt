set(src_dir "${CMAKE_CURRENT_SOURCE_DIR}")
#set(incl_dir "${src_dir}/../include")

file(GLOB main_src ${src_dir}/*.cpp)
file(GLOB main_hdr ${src_dir}/*.h)

# imagemagick
find_package(ImageMagick COMPONENTS MagickCore Magick++)
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16)
include_directories(${ImageMagick_INCLUDE_DIRS})

#add_definitions("-ldl")
add_executable(oscdraw ${main_src} ${main_hdr})
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")
target_link_libraries(oscdraw ${AUDIO_LIBRARIES} ${ImageMagick_LIBRARIES} -ljpeg -lpng)


