cmake_minimum_required(VERSION 3.5.0)
project(networking VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON)
FetchContent_MakeAvailable(SFML)

# Add the server executable
add_executable(server src/server.cpp)
target_link_libraries(server PRIVATE sfml-graphics sfml-network)
target_compile_features(server PRIVATE cxx_std_11)

# Add the client executable
add_executable(client src/client.cpp)
target_link_libraries(client PRIVATE sfml-graphics sfml-network)
target_compile_features(client PRIVATE cxx_std_11)

if(WIN32)
    add_custom_command(
        TARGET server client
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:server>
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:client>
        VERBATIM)
endif()
