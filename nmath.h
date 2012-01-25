/**
    Copyright (c) 2011, Licker Nandor.
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Licker Nandor nor the names of its contributors
      may be used to endorse or promote products derived from this software
      without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
    THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef NMATH_H
#define NMATH_H

typedef float __attribute__((aligned(16))) mat[16];
typedef float __attribute__((aligned(16))) vec[4];

#define NMATH_PI                    3.141592

#define NMATH_ERR_NO_ERROR                0x00
#define NMATH_ERR_SSE_NOT_SUPPORTED       0x20


// Initialise the math library
extern int __cdecl mathInit();

// Load the zero vector
extern void __cdecl vecLoadZero(vec dest);

// Load a scalar value into a vector
extern void __cdecl vecLoadScalar(vec dest, float value);

// Compare two vectors
extern int  __cdecl vecCmp(vec op1, vec op2);

// Copy a vector into another
extern void __cdecl vecCopy(vec dest, vec src);

// Compute the cross product of two vectors
extern void __cdecl vecCross(vec dest, vec op1, vec op2);

// Compute the dot product of two vectors
extern float __cdecl vecDot(vec i, vec j);

// Normalize a vector
extern void __cdecl vecNormalize(vec i, vec j);

// Load zero into a matrix
extern void __cdecl matLoadZero(mat dest);

// Load a scalar value into a matrix
extern void __cdecl matLoadScalar(mat dest, float value);

// Load the identity matrix
extern void __cdecl matLoadIdentity(mat dest);

// Load a translation matrix
extern void __cdecl matLoadTranslation(mat des, float x, float y, float z);

// Load a rotation matrix around the x axis
extern void __cdecl matLoadRotationX(mat m, float f);

// Load a rotation matrix around the Y axis
extern void __cdecl matLoadRotationY(mat m, float f);

// Load a rotation matrix around the Z axis
extern void __cdecl matLoadRotationZ(mat m, float f);

// Compare two matrixes
extern int  __cdecl matCmp(mat a, mat b);

// Copy a matrix into another
extern void __cdecl matCopy(mat dest, mat source);

// Multiply two matrixes
extern void __cdecl matMultMat(mat dest, mat source);

// Multiply a matrix with a scalar
extern void __cdecl matMultScalar(mat dest, float v);

// Multiply a vector with a matrix
extern void __cdecl vecMultMat(vec dest, mat source);

// Scale
extern void __cdecl matScale(mat dest, float x, float y, float z);

// Rotate around the x axis by f radians
extern void matRotateX(mat m, float f);

// Rotate around the y axis by f radians
extern void matRotateY(mat m, float f);

// Rotate around the z axis by z radians
extern void matRotateZ(mat m, float f);

#endif /* NMATH_H */
