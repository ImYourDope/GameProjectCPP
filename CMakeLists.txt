cmake_minimum_required(VERSION 3.23)
project(SoulSanctum)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")
set(SFML_STATIC_LIBRARIES TRUE)


add_executable(SoulSanctum main.cpp Game.cpp Game.h States/State.cpp States/Headers/State.h States/GameState.cpp States/Headers/GameState.h States/MainMenuState.cpp States/Headers/MainMenuState.h GUI/Button.cpp GUI/Headers/Button.h GUI/TextBox.cpp GUI/Headers/TextBox.h States/TutorialState.cpp States/Headers/TutorialState.h States/PauseState.cpp States/Headers/PauseState.h GUI/Socket.cpp GUI/Headers/Socket.h GUI/Icon.cpp GUI/Headers/Icon.h Entity/Entity.cpp Entity/Entity.h GUI/Line.cpp GUI/Headers/Line.h GUI/Headers/Includes.h)

set(SFML_DIR "SFML\\lib\\cmake\\SFML")

target_link_libraries(SoulSanctum sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2.5 REQUIRED graphics network audio window system)