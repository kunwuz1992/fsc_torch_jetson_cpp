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

#include <torch/script.h>  // One-stop header.
#include <torch/torch.h>
#include <iostream>
#include <memory>
#include <chrono>


torch::Tensor phi_arg(torch::Tensor state_tensor){
    auto wx = state_tensor.index({0, 10});
    auto wy = state_tensor.index({0, 11});
    auto wz = state_tensor.index({0, 12});

    auto wxwy = wx * wy;
    auto wxwz = wx * wz;
    auto wywz = wy * wz;
    auto wxwx = wx * wx;
    auto wywy = wy * wy;
    auto wzwz = wz * wz;

    auto arg_state = torch::stack({wxwy, wxwz, wywz, wxwx, wywy, wzwz},1);
    return torch::stack({state_tensor,arg_state},0);

}


int main(int argc, const char *argv[])
{

        // if (argc != 2) {
    //     std::cout << "usage: example-app <path-to-exported-script-module>\n";
    //     return -1;
    // }

    torch::DeviceType device_type;
    if (torch::cuda::is_available()) {
        std::cout << "cuda is avaliable!\n";
        device_type = torch::kCUDA;
    } else {
        device_type = torch::kCPU;
    }

    std::cout << device_type << '\n';
    torch::Device device(device_type, 0);
    
    torch::jit::script::Module module_;
    torch::jit::script::Module encoder_module_;
    torch::jit::script::Module decoder_module_;

    std::cout << "loading encoder model\n";

    encoder_module_ = torch::jit::load("/home/kunwu/Documents/Github/fsc_torch_jetson_cpp/python/best_mlp_encoder.pt");

    // try {
    //     encoder_module_ = torch::jit::load("/home/kunwu/Documents/Github/fsc_torch_jetson_cpp/python/best_mlp_encoder.pt");
    // } catch (const c10::Error &e) {
    //     std::cout << "error loading the encoder model\n";
    //     return -1;
    // }
    std::cout << "loading decoder model\n";
    try {
        decoder_module_ = torch::jit::load("/home/kunwu/Documents/Github/fsc_torch_jetson_cpp/python/best_mlp_decoder.pt");
    } catch (const c10::Error &e) {
        std::cout << "error loading the decoder model\n";
        return -1;
    }
    
    encoder_module_.to(device);
    encoder_module_.eval();

    decoder_module_.to(device);
    decoder_module_.eval();

    std::cout << "ok\n";
    // Create a vector of inputs.
    std::vector<torch::jit::IValue> inputs;
    // inputs.push_back(torch::tensor({1.0, 1.0, 1.0, 1.0, 1.0}).to(device));
    // auto input_tensor = torch::tensor({1.0, 1.0, 1.0, 1.0, 1.0}).unsqueeze(0).to(device);
    auto input_tensor = phi_arg(torch::randn({1,13}).to(device));
    
    inputs.push_back(input_tensor);
    torch::jit::IValue encoder_output;
    torch::jit::IValue decoder_output;
    // Execute the model and turn its output into a tensor.
    uint32_t numOfCalls = 1000;
    auto tic = std::chrono::steady_clock::now();
    for (uint32_t i = 0; i < numOfCalls; i++) {
        try {
            encoder_output = encoder_module_.forward(inputs);
            std::vector<torch::jit::IValue> decoder_inputs;
            decoder_inputs.push_back(encoder_output);
            decoder_output = decoder_module_.forward(decoder_inputs);
        } catch (const c10::Error &e) {
            std::cout << e.what() << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    auto toc = std::chrono::steady_clock::now();
    auto loop_time = std::chrono::duration_cast<std::chrono::nanoseconds>(toc - tic).count();
    std::cout << static_cast<double>(loop_time) / (numOfCalls * 1e6 * 1.0) << "ms \n";
    std::cout << decoder_output << '\n';
}