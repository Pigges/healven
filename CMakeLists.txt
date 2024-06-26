cmake_minimum_required(VERSION 3.16)
project(healven LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(healven src/main.cpp
        src/RenderManager.cpp
        src/RenderManager.h
        src/EventListener.cpp
        src/EventListener.h
        src/EntityManager.cpp
        src/EntityManager.h
        src/Entity.cpp
        src/Entity.h
        src/SpriteEntity.cpp
        src/SpriteEntity.h
        src/GameEngine.cpp
        src/GameEngine.h
        src/Player.cpp
        src/Player.h
        src/Animation.cpp
        src/Animation.h
        src/Platform.cpp
        src/Platform.h)
target_link_libraries(healven PRIVATE sfml-graphics)
target_compile_features(healven PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
            TARGET healven
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:healven>
            VERBATIM)
endif()

install(TARGETS healven)