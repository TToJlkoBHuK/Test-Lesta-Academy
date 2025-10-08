cmake_minimum_required(VERSION 3.10)
project(RPG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --------------------------------------------------------------------

set(SOURCES
    Game.cpp
    main.cpp
    Monster.cpp
    obj_game.cpp
    Player.cpp
    WeaponType.cpp
    DamageType.cpp
    TypeRegistry.cpp
    CharacterClass.cpp
)

add_executable(RPG ${SOURCES})

target_include_directories(RPG PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})