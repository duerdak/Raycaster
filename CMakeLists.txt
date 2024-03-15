cmake_minimum_required(VERSION 3.5)
project(Raycaster VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.hpp src/*.cpp)
add_executable(Raycaster ${SRC_FILES})
target_include_directories(Raycaster PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(Raycaster PRIVATE $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main> $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)
target_link_libraries(Raycaster PRIVATE $<IF:$<TARGET_EXISTS:SDL2_image::SDL2_image>,SDL2_image::SDL2_image,SDL2_image::SDL2_image-static>)
target_link_libraries(Raycaster PRIVATE glm::glm)