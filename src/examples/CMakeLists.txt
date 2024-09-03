add_single_exc(
    TARGET build_test
    SOURCE build_test.cpp
    LIBRARIES ${LASAN} cppflow
    COMPILE_OPTIONS ${COMPILE_FLAGS}
)

add_single_exc(
    TARGET model_loading_test
    SOURCE model_loading_test.cpp
    LIBRARIES ${LASAN} cppflow
    COMPILE_OPTIONS ${COMPILE_FLAGS}
)

add_single_exc(
    TARGET tensor_test
    SOURCE tensor_test.cpp
    LIBRARIES ${LASAN} cppflow
    COMPILE_OPTIONS ${COMPILE_FLAGS}
)

add_single_exc(
    TARGET load_simple_network
    SOURCE load_simple_network.cpp
    LIBRARIES ${LASAN} cppflow
    COMPILE_OPTIONS ${COMPILE_FLAGS}
)