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
    // input = cppflow::cast(input, TF_UINT8, TF_FLOAT);
    // input = cppflow::expand_dims(input, 0);
    cppflow::model model("../../../python/test_function");
    auto operations = model.get_operations();
    for (auto &t : operations) {
        std::cout << t << '\n';
    }
    // get output
    // auto input = cppflow::tensor({1.0f});
    auto input = cppflow::fill({1, 1}, 1.0f);
    std::cout << "reached here \n";
    // serving_default_input_2
    auto output = model({{"serving_default_input_2", input}}, {"StatefulPartitionedCall"});
    // auto output = model(input);
    std::cout << "Result is: " << output << '\n';
    // TF_TString_Dealloc(tstr);
    return 0;
}