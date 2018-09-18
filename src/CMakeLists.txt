add_executable(${PROJECT_NAME} setservostik.cpp)
target_link_libraries(${PROJECT_NAME} usb-1.0)
install(TARGETS setservostik DESTINATION bin)