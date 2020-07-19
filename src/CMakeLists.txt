add_subdirectory(helper)

add_subdirectory(modulation)

add_subdirectory(BasicOrbitAlgo)

file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} httplib modulation helper BasicOrbitAlgo)
