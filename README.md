# fsc_torch_jetson_cpp

[![Maintenance](https://img.shields.io/badge/Maintained%3F-yes-green.svg)](https://GitHub.com/Naereen/StrapDown.js/graphs/commit-activity)

A tutorial and sample code for running a pytorch nerual network using c++ on Nvidia jetson nano computer.

# Author 

Dr. Longhao Qian

# How to use

- Read this [tutorial](documents//install_libtorch_jetson.md) about how to correctly install pytorch c++ lib on jetson nano.

- Run the ``python/verify_pytorch.py`` to verify whether pytorch c++ lib function correctly.

- run to train a simple neural network and save the trained network to ``.pt`` weights file.

- run to compile the ``src/pytorchTest/pytorch_load_test.cpp`` and ``src/pytorchTest/pytorch_load_test_gpu.cpp`` to get the execution files.

- run to ``build_release/pytorchTest/pytorch_load_test_gpu`` and ``build_release/pytorchTest/pytorch_load_test`` and observe the results.

# CMake settings

- read this tutorial about cmake commands to incooperate pytorch lib in compilation.

# Tensor definition in c++

- read this tutorial about tensor definition in c++

# CPU/GPU execution

- read this tutorial about CPU/GPU nerual network execution.

# Libtorch documentation

- using libtorch to load pytorch model is in this [link](https://pytorch.org/tutorials/advanced/cpp_export.html).