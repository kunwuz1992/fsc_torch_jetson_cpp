add_executable(pytorch_test_1 pytorch_test_1.cpp)
target_link_libraries(pytorch_test_1 "${TORCH_LIBRARIES}")
set_property(TARGET pytorch_test_1  PROPERTY CXX_STANDARD 17)

add_executable(pytorch_load_test pytorch_load_test.cpp)
target_link_libraries(pytorch_load_test "${TORCH_LIBRARIES}")
set_property(TARGET pytorch_load_test  PROPERTY CXX_STANDARD 17)

add_executable(pytorch_load_test_gpu pytorch_load_test_gpu.cpp)
target_link_libraries(pytorch_load_test_gpu "${TORCH_LIBRARIES}")
set_property(TARGET pytorch_load_test_gpu PROPERTY CXX_STANDARD 17)