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
*/
.intel_syntax noprefix
.align 2

.data
cstFpOne: .float 1

.text
/*
    Init the library
*/
.globl _mathInit
_mathInit:
    finit

    cpuid

    test edx, 25
    jz _mathInitEnd

    fld1
    fst dword ptr [cstFpOne]

    mov eax, dword ptr 0
    ret

    _mathInitEnd:
        mov eax, dword ptr 20
        ret

/*
    Load the identity matrix
*/
.globl _matLoadIdentity
_matLoadIdentity:
    mov edx, [esp + 4]
    xorps xmm0, xmm0

    movaps [edx], xmm0
    movaps [edx + 0x10], xmm0
    movaps [edx + 0x20], xmm0
    movaps [edx + 0x30], xmm0

    mov eax, [cstFpOne]
    mov [edx +   0], eax
    mov [edx +  20], eax
    mov [edx +  40], eax
    mov [edx +  60], eax

    ret

/*
    Load the null matrix
*/
.globl _matLoadZero
_matLoadZero:

    mov edx, [esp + 4]

    xorps xmm0, xmm0

    movaps [edx], xmm0
    movaps [edx + 0x10], xmm0
    movaps [edx + 0x20], xmm0
    movaps [edx + 0x30], xmm0

    ret

/*
    Load the value into the matrix
*/
.globl _matLoadScalar
_matLoadScalar:
    mov edx, [esp + 4]

    movss xmm0, [esp + 8]
    shufps xmm0, xmm0, 0

    movaps [edx], xmm0
    movaps [edx + 0x10], xmm0
    movaps [edx + 0x20], xmm0
    movaps [edx + 0x30], xmm0

    ret

/*
    Multiply the matrix with a scalar value
*/
.globl _matMultScalar
_matMultScalar:
    mov edx, [esp + 4]

    movss xmm1, [esp + 8]
    shufps xmm1, xmm1, 0

    movaps xmm0, [edx]
    mulps xmm0, xmm1
    movaps [edx], xmm0

    movaps xmm0, [edx + 0x10]
    mulps xmm0, xmm1
    movaps [edx + 0x10], xmm0

    movaps xmm0, [edx + 0x20]
    mulps xmm0, xmm1
    movaps [edx + 0x20], xmm0

    movaps xmm0, [edx + 0x30]
    mulps xmm0, xmm1
    movaps [edx + 0x30], xmm0

    ret

/*
    Copy a matrix into another
*/
.globl _matCopy
_matCopy:
    push esi
    push edi

    mov edi, [esp + 12]
    mov esi, [esp + 16]

    movaps xmm0, [esi]
    movaps [edi], xmm0

    movaps xmm0, [esi + 0x10]
    movaps [edi + 0x10], xmm0

    movaps xmm0, [esi + 0x20]
    movaps [edi + 0x20], xmm0


    movaps xmm0, [esi + 0x30]
    movaps [edi + 0x30], xmm0

    pop edi
    pop esi
    ret

/*
    Multiply two matrixes
*/
.globl _matMult
_matMult:
    push esi
    push edi

    mov edi, [esp + 12]
    mov esi, [esp + 16]

    pop edi
    pop esi
    ret
/*
    Compare two matrixes
*/
.globl _matCmp
_matCmp:
    push ebx
    push esi
    push edi

    mov esi, [esp + 16]
    mov edi, [esp + 20]

    mov ecx, 16
    _matCmpLoop:
        mov ebx, [esi]
        xor ebx, edi

        jnz _matCmpLoopNotEqu

        add esi, 4
        add edi, 4

    loop _matCmpLoop
    mov eax, 1

    pop edi
    pop esi
    pop ebx
    ret

    _matCmpLoopNotEqu:
        mov eax, 0
        pop edi
        pop esi
        ret

/*
    Load a scalar into a vector
*/
.globl _vecLoadScalar
_vecLoadScalar:
    mov edx, [esp + 4]

    movss xmm0, [esp + 8]
    shufps xmm0, xmm0, 0

    movaps [edx], xmm0
    ret

/*
    Load null into a vector
*/
.globl _vecLoadZero
_vecLoadZero:
    mov edx, [esp + 4]

    xorps xmm0, xmm0
    movaps [edx], xmm0

/*
    Compare two vectors
*/
.globl _vecCmp
_vecCmp:
    mov edx, [esp + 4]
    movaps xmm0, [edx]

    mov edx, [esp + 8]
    movaps xmm1, [edx]

    xorps xmm0, xmm1

    pextrw eax, xmm0, 0
    test eax, eax
    jnz _vecCompNotEqu

    pextrw eax, xmm0, 1
    test eax, eax
    jnz _vecCompNotEqu

    pextrw eax, xmm0, 2
    test eax, eax
    jnz _vecCompNotEqu

    pextrw eax, xmm0, 3
    test eax, eax
    jnz _vecCompNotEqu

    mov eax, dword ptr 1
    ret

    _vecCompNotEqu:
        mov eax, dword ptr 0
        ret

/*
    Copy a vector into another
*/
.globl _vecCopy
_vecCopy:
    push esi
    push edi

    mov edi, [esp + 12]
    mov esi, [esp + 16]

    movaps xmm0, [esi]
    movaps [edi], xmm0

    pop edi
    pop esi
    ret

/**
    Multiple a vector with a matrix
*/
.globl _vecMultMat
_vecMultMat:

    mov eax, [esp + 4]
    mov edx, [esp + 8]

    movaps xmm0, [eax]
    shufps xmm0, [eax], 0
    mulps xmm0, [edx]

    movaps xmm1, [eax]
    shufps xmm1, [eax], 0x55
    mulps xmm1, [edx + 0x10]
    addps xmm0, xmm1

    movaps xmm1, [eax]
    shufps xmm1, [eax], 0xaA
    mulps xmm1, [edx + 0x20]
    addps xmm0, xmm1

    movaps xmm1, [eax]
    shufps xmm1, [eax], 0xFF
    mulps xmm1, [edx + 0x30]
    addps xmm0, xmm1

    movaps [eax], xmm0

    ret


/**
    Multiple two matrixes
*/
.globl _matMultMat
_matMultMat:
    push ebx

    mov eax, [esp + 8]
    mov edx, [esp + 12]

    mov ebx, 0
    mov ecx, 4

    _matMultLoop:
        movaps xmm0, [eax + ebx]
        shufps xmm0, [eax + ebx], 0
        mulps xmm0, [edx]

        movaps xmm1, [eax + ebx]
        shufps xmm1, [eax + ebx], 0x55
        mulps xmm1, [edx + 0x10]
        addps xmm0, xmm1

        movaps xmm1, [eax + ebx]
        shufps xmm1, [eax + ebx], 0xaA
        mulps xmm1, [edx + 0x20]
        addps xmm0, xmm1

        movaps xmm1, [eax + ebx]
        shufps xmm1, [eax + ebx], 0xFF
        mulps xmm1, [edx + 0x30]
        addps xmm0, xmm1

        movaps [eax + ebx], xmm0
        add ebx, 0x10
        loop _matMultLoop

    pop ebx
    ret

/**
    Load a translation matrix
*/
.globl _matLoadTranslation
_matLoadTranslation:
    mov edx, [esp + 4]
    xorps xmm0, xmm0

    movaps [edx], xmm0
    movaps [edx + 0x10], xmm0
    movaps [edx + 0x20], xmm0
    movaps [edx + 0x30], xmm0

    mov eax, [cstFpOne]
    mov [edx +   0], eax
    mov [edx +  20], eax
    mov [edx +  40], eax
    mov [edx +  60], eax

    mov eax, [esp + 8]
    mov [edx + 48], eax

    mov eax, [esp + 12]
    mov [edx + 52], eax

    mov eax, [esp + 16]
    mov [edx + 56], eax

    ret
