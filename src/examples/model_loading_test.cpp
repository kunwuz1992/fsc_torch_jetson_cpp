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
#include <cppflow/cppflow.h>
#include <iostream>
#include <chrono>
#include <numeric>

int main()
{
    const char test_string[] = "/home/fsc-jupiter/source/cppflow_test/st/model_loading/my_cat.jpg";
    // cppflow::tensor name = std::string("../../../st/model_loading/my_cat.jpg");
    TF_TString tstr[1];
    TF_TString_Init(&tstr[0]);
    TF_TString_Copy(&tstr[0], test_string, sizeof(test_string) - 1);
    cppflow::tensor name(static_cast<enum TF_DataType>(TF_STRING), (void *)tstr, sizeof(tstr), {});
    auto ff = cppflow::read_file(name);
    auto input = cppflow::decode_jpeg(ff);
    // auto input = cppflow::decode_jpeg(cppflow::read_file(std::string("../../../st/model_loading/my_cat.jpg")));

    input = cppflow::cast(input, TF_UINT8, TF_FLOAT);
    input = cppflow::expand_dims(input, 0);
    cppflow::model model("../../../st/model_loading/model_1");

    constexpr int n_loops{10};
    std::int64_t loop_time[n_loops];
    for (uint32_t i = 0; i < n_loops; i++) {
        auto tic = std::chrono::steady_clock::now();
        auto output = model(input);
        auto toc = std::chrono::steady_clock::now();
        loop_time[i] = std::chrono::duration_cast<std::chrono::nanoseconds>(toc - tic).count();
        std::cout << "It's a tiger cat: " << cppflow::arg_max(output, 1) << std::endl;
    }
    std::cout << "Average loop time of " << n_loops
              << " loops is: " << std::accumulate(loop_time, loop_time + n_loops, 0) / n_loops << "\n";
    TF_TString_Dealloc(tstr);
    return 0;
}