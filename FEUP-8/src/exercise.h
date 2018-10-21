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

#include "studio.h"
#include "web_comunication_api.h"

typedef struct Exercise Exercise;

typedef struct UnitTest UnitTest;

struct UnitTest
{
	char* title;
	char* description;
	char* correctCode; //Would it be better to have only the expected output??
} ;

struct Exercise
{
	tic_mem* tic;

	tic_exercise* exe;

	struct UnitTest* unitTests;

	u8 testIndex : SFX_COUNT_BITS;

	enum
	{
		EXERCISE_OVERVIEW_TAB,
		EXERCISE_TESTS_TAB,
	} tab;

	struct History* history;

	void(*tick)(Exercise*);
	void(*event)(Exercise*, StudioEvent);
};

void initExercise(Exercise*, tic_mem* tic, tic_exercise* exe);
