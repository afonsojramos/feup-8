// MIT License

// Copyright (c) 2017 Vadim Grigoruk @nesbox // grigoruk@gmail.com

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "fs.h"

typedef struct Net Net;

typedef struct
{
	u8* data;
	s32 size;
}Buffer;


Net* createNet();
char *buildHttpParameter(const char *key, const char *value);
char* concateStrings(const char *string1, const char *string2);
static Buffer sendHttpRequest(const char* address, int port, const char* path, char *message, int messageSize, s32 timeout);
Buffer sendHttpGetRequest(const char* address, int port, const char* path, Buffer *dataToSend, char *additionalHeaderString, s32 timeout);
Buffer sendHttpPostRequest(const char* address, int port, const char* path, Buffer *dataToSend, char *additionalHeaderString, s32 timeout);
void* netGetRequest(Net* net, const char* path, s32* size);
void closeNet(Net* net);
