cmake_minimum_required(VERSION 3.16)

project(particle_system LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ASSETS_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(ASSETS_DEST_DIR "${CMAKE_BINARY_DIR}/assets")
add_custom_command(
    OUTPUT ${ASSETS_DEST_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_SOURCE_DIR} ${ASSETS_DEST_DIR}
    COMMENT "Copying assets to build directory..."
    VERBATIM
)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(particle_system main.cpp
    particle.h
    particlesystem.h particlesystem.cpp
    render.h render.cpp
    force.h

    gravityforce.h gravityforce.cpp
    windforce.h windforce.cpp
    firegravity.h
    firegravity.cpp
)



target_link_libraries(particle_system SDL2::SDL2 SDL2::SDL2main SDL2_image::SDL2_image)

include(GNUInstallDirs)
install(TARGETS particle_system
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
