add_executable(${PROJECT_NAME} setservostik.cpp)
set_property(
   TARGET ${PROJECT_NAME}
   PROPERTY CXX_CLANG_TIDY clang-tidy;-checks=*;-warnings-as-errors=*)
target_link_libraries(${PROJECT_NAME} usb-1.0)

install(TARGETS setservostik DESTINATION bin)