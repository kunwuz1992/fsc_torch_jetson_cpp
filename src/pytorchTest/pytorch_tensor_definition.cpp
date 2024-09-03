/*************************************************************

Copyright (C) 2024  FSC

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

#include <torch/torch.h>
#include <iostream>

int main()
{
    // define a random tensor (1x2 matrix)
    torch::Tensor a = torch::rand({1, 2});
    std::cout << a << '\n';
    // define a tensor with specific data
    torch::Tensor b = torch::tensor({1.0, 1.0});
    // adding two tensors
    torch::Tensor c = a + b;
    std::cout << c << '\n';
    // get the size of a tensor
    std::cout << a.sizes() << '\n';
    // accessing tensor elements
    double c0 = c[0][0].item<double>();
    std::cout << c0 << '\n';
    return 0;
}