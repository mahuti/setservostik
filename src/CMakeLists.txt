add_executable(${PROJECT_NAME} setservostik.cpp)
set_property(
   TARGET ${PROJECT_NAME}
   PROPERTY CXX_CLANG_TIDY clang-tidy;-checks=*;-warnings-as-errors=*)
target_link_libraries(${PROJECT_NAME} usb-1.0)


set_target_properties(
  ${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_FLAGS "${WARNING_FLAGS}"
)

# if(CLANG_TIDY_EXE)
#   set_target_properties(
#     ${PROJECT_NAME} PROPERTIES
#     CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
#   )
# endif()

install(TARGETS setservostik DESTINATION bin)