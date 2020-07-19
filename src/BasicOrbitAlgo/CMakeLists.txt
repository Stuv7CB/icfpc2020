file(GLOB SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)

add_library(BasicOrbitAlgo OBJECT ${SOURCES})

target_include_directories(BasicOrbitAlgo PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(BasicOrbitAlgo helper)
