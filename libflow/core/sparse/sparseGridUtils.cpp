// Copyright (C) 2016 EDF
// All Rights Reserved
// This code is published under the GNU Lesser General Public License (GNU LGPL)
#include <array>

namespace libflow
{

std::array<double, 23> deltaSparseMesh = {{
        1, 0.5, 0.25, 0.125, 0.0625, 0.03125, 0.015625, 0.0078125, 0.00390625, 0.001953125, 0.0009765625, 0.00048828125,
        0.000244140625, 0.0001220703125, 6.103515625e-05, 3.0517578125e-05, 1.52587890625e-05, 7.62939453125e-06,
        3.814697265625e-06, 1.9073486328125e-06, 9.5367431640625e-07, 4.76837158203125e-07, 2.384185791015625e-07
    }
};

std::array<unsigned int, 21> lastNode = {{0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575}};

std::array<int, 4> iNodeToFunc = {{0, 1, 1, 0}};

std::array<double, 2> weightParent = {{ -3. / 8., -1. / 8.}};
std::array<double, 2> weightGrandParent = {{ 1. / 32., -1. / 32.}};
std::array<double, 2> weightQuadraticParent = {{ -1. / 8., 1. / 8.}};
}
