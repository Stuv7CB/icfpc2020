add_executable(tests main.cpp)

target_link_libraries(tests httplib gtest gmock_main)