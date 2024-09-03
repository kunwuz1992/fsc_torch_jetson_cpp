add_executable(pytorch_tensor_definition pytorch_tensor_definition.cpp)
target_link_libraries(pytorch_tensor_definition "${TORCH_LIBRARIES}")
set_property(TARGET pytorch_tensor_definition PROPERTY CXX_STANDARD 17)

add_executable(pytorch_load_test pytorch_load_test.cpp)
target_link_libraries(pytorch_load_test "${TORCH_LIBRARIES}")
set_property(TARGET pytorch_load_test  PROPERTY CXX_STANDARD 17)

add_executable(pytorch_load_test_gpu pytorch_load_test_gpu.cpp)
target_link_libraries(pytorch_load_test_gpu "${TORCH_LIBRARIES}")
set_property(TARGET pytorch_load_test_gpu PROPERTY CXX_STANDARD 17)