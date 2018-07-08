cmake_minimum_required(VERSION 3.7)
set(PROJECT_NAME Warhammer_II)

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp
        mainGame/gameConstants.h
        mainGame/Game.h
        mainGame/stringHelper.h
        mainGame/stringHelper.inl
        mainGame/Game.cpp
        mainGame/loadFiles/load.inl
        mainGame/loadFiles/loader.h
        mainGame/units/Unit.h
        mainGame/units/Unit.cpp
        mainGame/units/unitAdds.inl
        mainGame/units/healthBar/healthBar.h
        mainGame/units/healthBar/healthBar.cpp
        mainGame/MainMenu.h
        mainGame/MainMenu.cpp
        mainGame/ChoosingScreen.h
        mainGame/ChoosingScreenInitLoad.inl
        mainGame/ChoosingScreen.cpp
        mainGame/betterChoosingScreen.h
        mainGame/betterChoosingScreen.cpp)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES} mainGame/loadFiles/loader.h)
else ()
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} mainGame/loadFiles/loader.h)
endif ()

set(SFML_ROOT E:/Tools/SFML)
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML 2 REQUIRED COMPONENTS audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    link_directories("E:/Tools/SFML/lib")
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()