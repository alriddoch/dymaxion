/*
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
 *               2010 Kristian Høgsberg <krh@bitplanet.net>
 *               2010 Alexandros Frantzis <alexandros.frantzis@linaro.org>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef MATRIX_H
#define MATRIX_H

void matrix_multiply(float *m, float const *n);
void matrix_rotate(float *m, float angle, float x, float y, float z);
void matrix_scale(float *m, float x, float y, float z);
void matrix_translate(float *m, float x, float y, float z);
void matrix_identity(float *m);
void matrix_transpose(float *m);
void matrix_invert(float *m);
void matrix_perspective(float *m, float fovy, float aspect,
                        float zNear, float zFar);
void matrix_ortho(float *m, float left, float right,
                  float bottom, float top, float near, float far);
void matrix_trim(float *m, float const * n);

#endif // MATRIX_H
