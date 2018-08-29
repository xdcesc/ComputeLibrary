/*
 * Copyright (c) 2017-2018 ARM Limited.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#ifdef __aarch64__

#include "../std_transforms_fixed.hpp"

namespace arm_gemm {

// Actual kernel implementations
void a64_gemm_s16_asimd_12x8(const int16_t *, const int16_t *, int32_t *, int, int, int);

// 12x8 SGEMM "strategy" class.
//
// This describes the characteristics of a family of kernels, in terms of
// the required interleave properties and the output block size.
//
// All kernels in the family must share these characteristics.  The actual
// kernel to be used can be chosen at runtime, based on the CPU_type
// structure.
class gemm_s16_12x8 {
public:
    typedef int16_t operand_type;
    typedef int32_t result_type;

    typedef void (*kern_type)(const int16_t *, const int16_t *, int32_t *, int, int, int);

    /* Kernel blocking parameters */
    static int out_width() {
        return 12;
    }

    static int out_height() {
        return 8;
    }

    static int k_unroll() {
        return 1;
    }

    // Use the standard fixed size transforms.
    StdTransformsFixed<operand_type, result_type, 8, 12> transforms = {};

    kern_type kernel = a64_gemm_s16_asimd_12x8;

    gemm_s16_12x8(const CPUInfo *ci) { }
};

} // namespace arm_gemm

#endif // __aarch64__
