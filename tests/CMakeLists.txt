file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(tests ${SOURCES})

target_link_libraries(tests modulation BasicOrbitAlgo gtest gmock_main)
