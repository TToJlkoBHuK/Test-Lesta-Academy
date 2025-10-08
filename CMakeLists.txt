cmake_minimum_required(VERSION 3.10)
project(RPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# --------------------------------------------------------------------

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Monster.cpp
    src/obj_game.cpp
    src/Player.cpp
    src/WeaponType.cpp
    src/DamageType.cpp
    src/TypeRegistry.cpp
    src/CharacterClass.cpp
)

add_executable(RPG ${SOURCES})

target_include_directories(RPG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)