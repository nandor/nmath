/**
    @file
    @author Licker Nandor licker.nandor@gmail.com
    @version 0.1a

    @section LICENSE

    Copyright (c) 2012 Licker Nandor.
    All rights reserved.

    Redistribution and use in source and binary forms are permitted
    provided that the above copyright notice and this paragraph are
    duplicated in all such forms and that any documentation,
    advertising materials, and other materials related to such
    distribution and use acknowledge that the software was developed
    by Licker Nandor.  The name of the
    University may not be used to endorse or promote products derived
    from this software without specific prior written permission.
    THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
    WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

    @section DESCRIPTION

    4d vector and 4x4 matrix manipulation library optimized using SSE

    This library implements C routines for initializing and multiplying
    4d vectors with 4x4 matrixes. The functions are implemented in SSE.
    Before using the library call math_init() and check for errors.

    Example:

        vec v;
        mat m;

        v[0] = 1.0f; v[1] = 2.0f; v[2] = 3.0f; v[3] = 1.0f;

        matLoadTranslation(m, 2.0f, 3.0f, 10.0f);
        vecMultMat(v, m);   // v becomes {2.0f, 5.0f, 13.0f, 1.0f}

*/

#ifndef NMATH_H
#define NMATH_H

typedef float __attribute__((aligned(16))) mat[16];
typedef float __attribute__((aligned(16))) vec[4];

#define NMATH_PI                    3.141592

#define NMATH_ERR_NO_ERROR                0x00
#define NMATH_ERR_SSE_NOT_SUPPORTED       0x20

/**
    Initialise the math library

    @return ERR_NO_ERROR on success
*/
extern int __cdecl mathInit();

/**
    Set a vector to zero

    @param i            Pointer to input vector
*/
extern void __cdecl vecLoadZero(vec i);

/**
    Set all the elements of a vector to a scalar

    @param i            Pointer to the vector
    @param f            Value
*/
extern void __cdecl vecLoadScalar(vec j, float f);

/**
    Compare two vectors

    @param i            Pointer to the first vector
    @param j            Pointer to the second vector

    @return             1 if they're equal, 0 otherwise
*/
extern int  __cdecl vecCmp(vec i, vec j);

/**
    Copy a vector into another
    dest <- vec

    @param i            Destination
    @param j            Source
*/
extern void __cdecl vecCopy(vec i, vec j);

/**
    Compute the cross product of a two vector
    dest <- dest x source

    @param i            Destination
    @param j            Source
*/
extern void __cdecl vecCross(vec i, vec j);

/**
    Compute the dot product of two vectors

    @param i            First vector
    @param j            Second vector

    @return             Dot product
*/
extern float __cdecl vecDot(vec i, vec j);

/**
    Normalize a vector

    @param i            Vector to be normalized
*/
extern void __cdecl vecNormalize(vec i, vec j);

/**
    Load the zero value into a matrix

    @param m            Pointer to the matrix
*/
extern void __cdecl matLoadZero(mat m);

/**
    Set all elements of a matrix to a value

    @param m            Pointer to the matrix
    @param f            Scalar value
*/
extern void __cdecl matLoadScalar(mat m, float f);

/**
    Load the identity matrix

    @param m            Pointer to destination matrix
*/
extern void __cdecl matLoadIdentity(mat m);

/**
    Load a translation matrix

    @param m            Pointer to the destination matrix
    @param x            Translation on x
    @param y            Translation on y
    @param z            Translation on z
*/
extern void __cdecl matLoadTranslation(mat m, float x, float y, float z);


/**
    Load a rotation matrix around the x axis

    @param m            Matrix
    @param f            Angle
*/
extern void __cdecl matLoadRotationX(mat m, float f);

/**
    Load a scaling matrix

    @param m            Pointer to the matrix
    @param x            Scale on x
    @param y            Scale on y
    @param z            Scale on z
*/
extern void __cdecl matLoadScale(mat m, float x, float y, float z);

/**
    Compare two matrixes

    @param a            First matrix
    @param b            Second matrix

    @return             a == b
*/
extern int  __cdecl matCmp(mat a, mat b);

/**
    Copy a matrix into another
    dest <- source

    @param a            Destination
    @param b            Source
*/
extern void __cdecl matCopy(mat a, mat b);

/**
    Multiply two matrixes
    dest <- dest * source

    @param a            Destinatoin
    @param b            Source
*/
extern void __cdecl matMultMat(mat a, mat b);

/**
    Multiply a matrix with a scalar value
    dest <- dest * scalar

    @param m            Destination
    @param f            Scalar
*/
extern void __cdecl matMultScalar(mat m, float f);

/**
    Multiply a vector with a matrix
    v <- v * m

    @param v            Vector
    @param m            Matrix
*/
extern void __cdecl vecMultMat(vec v, mat m);

#endif /* NMATH_H */
