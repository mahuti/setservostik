add_executable(setservostik setservostik.cpp)
target_link_libraries(setservostik usb-1.0)
install(TARGETS setservostik DESTINATION bin)