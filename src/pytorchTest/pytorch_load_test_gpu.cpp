/*************************************************************

Copyright (C) 2024  Longhao Qian

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.

*************************************************************/

// https://pytorch.org/tutorials/advanced/cpp_export.html

#include <torch/script.h>  // One-stop header.
#include <torch/torch.h>
#include <iostream>
#include <memory>
#include <chrono>

int main(int argc, const char *argv[])
{
    // if (argc != 2) {
    //     std::cout << "usage: example-app <path-to-exported-script-module>\n";
    //     return -1;
    // }

    torch::DeviceType device_type;
    if (torch::cuda::is_available() ) {
        std::cout<<"cuda is avaliable!\n";
        device_type = torch::kCUDA;
    } else {
        device_type = torch::kCPU;
    }

    std::cout<<device_type<<'\n';
    torch::Device device(device_type, 0);
    torch::jit::script::Module module_;
    try {
        // Deserialize the ScriptModule from a file using torch::jit::load().
        // module = torch::jit::load(argv[1]);
        module_ = torch::jit::load("../../../python/array_net_model.pt");
    } catch (const c10::Error &e) {
        std::cout << "error loading the model\n";
        return -1;
    }
    module_.to(device);
    module_.eval();
    std::cout << "ok\n";
    // Create a vector of inputs.
    std::vector<torch::jit::IValue> inputs;
    inputs.push_back(torch::tensor({1.0, 1.0, 1.0, 1.0, 1.0}).to(device));
    torch::jit::IValue output;
    // Execute the model and turn its output into a tensor.
    uint32_t numOfCalls = 1000;
    auto tic = std::chrono::steady_clock::now();
    for (uint32_t i = 0; i < numOfCalls; i++) {
        try {
            output = module_.forward(inputs);
        }
        catch (const c10::Error &e) {
            std::cout<<e.what()<<std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    auto toc = std::chrono::steady_clock::now();
    auto loop_time = std::chrono::duration_cast<std::chrono::nanoseconds>(toc - tic).count();
    std::cout << static_cast<double>(loop_time) / (numOfCalls * 1e6 * 1.0)<< "ms \n";
    std::cout << output << '\n';
}