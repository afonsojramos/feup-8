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

#include "exercise.h"
#include "history.h"

#include <ctype.h>

#define TEXT_BUFFER_HEIGHT ((TIC80_HEIGHT - TOOLBAR_SIZE - STUDIO_TEXT_HEIGHT) / STUDIO_TEXT_HEIGHT)

// #define TRACKER_ROWS (exercise_PATTERN_ROWS / 4)

/**
* draw code in fixed mode
*
* @param exercise a pointer to the exercise loaded
* @param text a pointer to the text to be drawn 
* @param color to start the display
* @param xStart x_position to start the display
* @param x      x_position to iterate the display
* @param y      y_position to start the display
* @param xEnd   x_position to end the display
*/
static void drawCode(Exercise *exercise, char *text, u8 color, s32 xStart, s32 x, s32 y, s32 xEnd)
{
	char *pointer = text;

	while (*pointer)
	{
		char symbol = *pointer;

		if (x >= -TIC_FONT_WIDTH && x <= xEnd && y >= -TIC_FONT_HEIGHT && y < TIC80_HEIGHT)
		{
			exercise->tic->api.draw_char(exercise->tic, symbol, x + 1, y + 1, color, false);
		}

		if (symbol == '\n' || ((x + TIC_FONT_WIDTH) > xEnd))
		{
			x = xStart;
			y += STUDIO_TEXT_HEIGHT;
		}
		else
			x += TIC_FONT_WIDTH;

		pointer++;
	}
}

/**
* draw code in scroll mode
*
* @param exercise a pointer to the exercise loaded
* @param text a pointer to the text to be drawn in scroll
* @param color to start the display
* @param x      x_position to iterate the display
* @param y      y_position to start the display
* @param xEnd   x_position to end the display
* @param yEnd   y_position to end the display
*/
static void drawCodeScroll(Exercise *exercise, char *text, u8 color, s32 x, s32 y, s32 xEnd, s32 yEnd)
{
	s32 xStart = x;
	x -= -exercise->scroll.x * TIC_FONT_WIDTH;
	s32 yStart = y;
	y -= -exercise->scroll.y * STUDIO_TEXT_HEIGHT;

	char *pointer = text;

	while (*pointer)
	{
		char symbol = *pointer;

		if (x >= -TIC_FONT_WIDTH && x <= xEnd && y >= yStart && y <= yEnd)
		{
			exercise->tic->api.draw_char(exercise->tic, symbol, x, y, color, false);
		}

		if (symbol == '\n' || ((x + TIC_FONT_WIDTH) > xEnd))
		{
			x = xStart;
			y += STUDIO_TEXT_HEIGHT;
		}
		else if (symbol == '\t')
			x += (TIC_FONT_WIDTH * 2);
		else 
			x += TIC_FONT_WIDTH;

		pointer++;
	}
}

/**
 * Draw Border For Rectangle
 * 
 */ 
static void drawDownBorder(Exercise *exercise, s32 x, s32 y, s32 w, s32 h)
{
	tic_mem *tic = exercise->tic;

	tic->api.rect(tic, x, y - 1, w, 1, tic_color_dark_gray);
	tic->api.rect(tic, x - 1, y, 1, h, tic_color_dark_gray);
	tic->api.rect(tic, x, y + h, w, 1, tic_color_light_blue);
	tic->api.rect(tic, x + w, y, 1, h, tic_color_light_blue);
}

/**
* Proccess keyboard
*
* @param exercise a pointer to the exercise loaded
*/
static void processKeyboard(Exercise *exercise)
{
	tic_mem *tic = exercise->tic;

	bool ctrl = tic->api.key(tic, tic_key_ctrl);

	if (ctrl)
	{
		if (keyWasPressed(tic_key_up))
			printf("UP\n");
		else if (keyWasPressed(tic_key_down))
			printf("DOWN\n");
	}
}

/**
* count lines of the text to be scrolled 
*
* @param exercise a pointer to the exercise loaded
* @param text to display/process scroll
*/
static s32 getLinesCount(Exercise *exercise, char *text)
{
	s32 count = 0;

	while (*text)
		if (*text++ == '\n')
			count++;

	return count;
}

/**
* normalized scroll
*
* @param exercise a pointer to the exercise loaded
* @param text to display/process scroll
*/
static void normalizeScroll(Exercise *exercise, char *text)
{
	if (exercise->scroll.x > 0)
		exercise->scroll.x = 0;
	if (exercise->scroll.y > 0)
		exercise->scroll.y = 0;
	else
	{
		s32 lines = getLinesCount(exercise, text);
		if (exercise->scroll.y > lines)
			exercise->scroll.y = lines;
	}
}

/**
* centered scroll
*
* @param exercise a pointer to the exercise loaded
* @param text to display/process scroll
*/
static void centerScroll(Exercise *exercise, char *text)
{
	s32 col, line;
	exercise->scroll.x = col - TIC80_WIDTH / TIC_FONT_WIDTH / 2;
	exercise->scroll.y = line - TEXT_BUFFER_HEIGHT / 2;

	normalizeScroll(exercise, text);
}

/**
* process mouse for scroll
*
* @param exercise a pointer to the exercise loaded
* @param text to display/process scroll
*/
static void processMouse(Exercise *exercise, char *text)
{
	tic_mem *tic = exercise->tic;

	if (checkMousePos(&exercise->rect))
	{
		if (exercise->scroll.active)
		{
			if (checkMouseDown(&exercise->rect, tic_mouse_right))
			{
				exercise->scroll.x = (exercise->scroll.start.x - getMouseX()) / TIC_FONT_WIDTH;
				exercise->scroll.y = (exercise->scroll.start.y - getMouseY()) / STUDIO_TEXT_HEIGHT;

				normalizeScroll(exercise, text);
			}
			else
				exercise->scroll.active = false;
		}
		else
		{
			if (checkMouseDown(&exercise->rect, tic_mouse_left))
			{
				s32 mx = getMouseX();
				s32 my = getMouseY();

				s32 x = (mx - exercise->rect.x) / TIC_FONT_WIDTH;
				s32 y = (my - exercise->rect.y) / STUDIO_TEXT_HEIGHT;
			}

			if (checkMouseDown(&exercise->rect, tic_mouse_right))
			{
				exercise->scroll.active = true;

				exercise->scroll.start.x = getMouseX() + exercise->scroll.x * TIC_FONT_WIDTH;
				exercise->scroll.start.y = getMouseY() + exercise->scroll.y * STUDIO_TEXT_HEIGHT;
			}
		}
	}
}

/**
* draw exercise details in the overview layout 
*
* @param exercise a pointer to the exercise loaded
*/
static void drawExerciseDetails(Exercise *exercise){

	int titleLength = TIC80_WIDTH / 16 + strlen("-- title: ") * TIC_FONT_WIDTH;
	int authorLength = TIC80_WIDTH / 16 + strlen("-- author: ") * TIC_FONT_WIDTH;

	drawCode(exercise, "-- title: ", tic_color_orange, TIC80_WIDTH / 16, TIC80_WIDTH / 16, TIC80_HEIGHT / 8, TIC80_WIDTH);
	drawCode(exercise, exercise->tic->exe.title, tic_color_white, titleLength, titleLength, TIC80_HEIGHT / 8, TIC80_WIDTH);

	drawCode(exercise, "-- author: ", tic_color_orange, TIC80_WIDTH / 16, TIC80_WIDTH / 16, TIC80_HEIGHT / 5.25, TIC80_WIDTH);
	drawCode(exercise, exercise->tic->exe.creator_name, tic_color_white, authorLength, authorLength, TIC80_HEIGHT / 5.25, TIC80_WIDTH);

	drawCode(exercise, "-- description: ", tic_color_orange, TIC80_WIDTH / 16, TIC80_WIDTH / 16, TIC80_HEIGHT / 4, TIC80_WIDTH);

	exercise->tic->api.rect(exercise->tic, (TIC80_WIDTH / 16 - 2), (TIC80_HEIGHT / 3 - 0.5), (TIC80_WIDTH - 25), (TIC80_HEIGHT - 55), tic_color_gray);
	drawDownBorder(exercise, (TIC80_WIDTH / 16 - 2), (TIC80_HEIGHT / 3 - 0.5), (TIC80_WIDTH - 25), (TIC80_HEIGHT - 55));

	if (strlen(exercise->tic->exe.description) < 150)
		drawCode(exercise, exercise->tic->exe.description, tic_color_white, TIC80_WIDTH / 16, TIC80_WIDTH / 16, TIC80_HEIGHT / 3 + 1, TIC80_WIDTH - 15);
	else
	{
		tic80_input *input = &exercise->tic->ram.input;

		if (input->mouse.scrolly)
		{
			enum
			{
				Scroll = 3
			};
			s32 delta = input->mouse.scrolly > 0 ? -Scroll : Scroll;
			exercise->scroll.y += delta;

			normalizeScroll(exercise, exercise->tic->exe.description);
		}

		processMouse(exercise, exercise->tic->exe.description);

		drawCodeScroll(exercise, exercise->tic->exe.description, tic_color_white, TIC80_WIDTH / 16, TIC80_HEIGHT / 3 + 1, TIC80_WIDTH - 17, TIC80_HEIGHT - 10);
	}
}

/**
 * 
 * @param exercise a pointer to the exercise loaded
 */
static char* generateTestsOutputString(Exercise *exercise)
{
	
	char str[33];
	switch (exercise->exe->tests_global_state)
	{
		case -1:
		{
			sprintf(str,"YOU\nHAVE\nERRORS\n");
			break;
		}
		case -2:
		{
			sprintf(str, "TESTS\nTIMED\nOUT\n");
			break;
		}
		default:
		{
			sprintf(str, "%d/%d \nPASSED\nTESTS\n", (exercise->exe->number_of_exercise_tests - exercise->exe->tests_global_state), exercise->exe->number_of_exercise_tests);
			break;
		}
	}
	return str;
}

/**
* Draw general output of tests, to see the general state of the tests ran
*
* @param exercise a pointer to the exercise loaded
*/
static void drawGeneralTestsOutput(Exercise *exercise)
{
	s32 xInit = (TIC80_WIDTH * 4 / 5.0 - 3);
	exercise->tic->api.rect(exercise->tic, xInit, 15, (TIC80_WIDTH - 12 - xInit), (TIC80_HEIGHT / 5.5), tic_color_red);
	drawDownBorder(exercise, xInit, 15, (TIC80_WIDTH - 12 - xInit), (TIC80_HEIGHT / 5.5));

	char *text = generateTestsOutputString(exercise);

	drawCode(exercise, text, tic_color_white, (xInit + 1), (xInit + 1), 17, (TIC80_WIDTH - 10));
}

/**
* Draw the overview layout when the overview tab is selected (default)
*
* @param exercise a pointer to the exercise loaded
*/
static void drawOverviewLayout(Exercise *exercise)
{
	exercise->tic->api.clear(exercise->tic, (tic_color_gray));

	exercise->tic->api.rect(exercise->tic, 5, 12, (TIC80_WIDTH - 10), (TIC80_HEIGHT - 17), tic_color_dark_red);
	drawDownBorder(exercise, 5, 12, (TIC80_WIDTH - 10), (TIC80_HEIGHT - 17));

	if (exercise->tic->exe.title == NULL)
	{
		drawCode(exercise, "No Exercise Loaded!", tic_color_red, TIC80_WIDTH / 4, TIC80_WIDTH / 4, TIC80_HEIGHT / 3, TIC80_WIDTH);
		return;
	}

	drawExerciseDetails(exercise);

	if(exercise->exe->tests_global_state > -3)
		drawGeneralTestsOutput(exercise);
}

/** 
* Start running of tests 
*
* @param exercise a pointer to the exercise loaded
*/
static void runTests(Exercise *exercise)
{
	sendCodeToServerAndGetTestsResults(exercise->tic->exe.id, exercise->tic->cart.code.data, exercise);
}

/** 
* draw the buttons to accionate/stop tests for running in the Exercise Toolbar
*
* @param exercise a pointer to the exercise loaded
*/
static void drawPlayTestButtons(Exercise *exercise)
{
	static const u8 Icons[] =
		{

			0b00000000,
			0b00100000,
			0b00110000,
			0b00111000,
			0b00110000,
			0b00100000,
			0b00000000,
			0b00000000

		};

	enum
	{
		Offset = TIC80_WIDTH - 52,
		Width = 7,
		Height = 7,
		Rows = 8,
		Count = sizeof Icons / Rows
	};

	for (s32 i = 0; i < Count; i++)
	{
		tic_rect rect = {Offset + Width * i, 0, Width, Height};

		bool over = false;

		if (checkMousePos(&rect))
		{
			setCursor(tic_cursor_hand);
			over = true;

			static const char *Tooltips[] = {"PLAY TESTS"};
			showTooltip(Tooltips[i]);

			static void (*const Handlers[])(Exercise *) = {runTests};

			if (checkMouseClick(&rect, tic_mouse_left))
				Handlers[i](exercise);
		}

		drawBitIcon(rect.x, rect.y, Icons + i * Rows, over ? (tic_color_dark_gray) : (tic_color_light_blue));
	}
}

/**
* draw the switch with the arrows and the correct index
*
* @param exercise a pointer to the exercise loaded
* @param x x_position of where to draw the switch
* @param y y_position of where to draw the switch
* @param label for the switch (ex: 'Test ')
* @param value of the label (ex: index of Test in display)
* @param function_set of exercise and delta to upgrade index/test display
*/
static void drawSwitch(Exercise *exercise, s32 x, s32 y, const char *label, s32 value, void (*set)(Exercise *, s32))
{
	static const u8 LeftArrow[] =
		{
			0b00010000,
			0b00110000,
			0b01110000,
			0b00110000,
			0b00010000,
			0b00000000,
			0b00000000,
			0b00000000,
		};

	static const u8 RightArrow[] =
		{
			0b01000000,
			0b01100000,
			0b01110000,
			0b01100000,
			0b01000000,
			0b00000000,
			0b00000000,
			0b00000000,
		};

	exercise->tic->api.text(exercise->tic, label, x, y, (tic_color_white), false);

	{
		x += (s32)strlen(label) * TIC_FONT_WIDTH;

		tic_rect rect = {x, y, TIC_FONT_WIDTH, TIC_FONT_HEIGHT};

		if (exercise->tic->exe.number_of_exercise_tests > 1)
		{
			if (checkMousePos(&rect))
			{
				setCursor(tic_cursor_hand);

				if (checkMouseClick(&rect, tic_mouse_left))
					set(exercise, -1);
			}

			drawBitIcon(rect.x, rect.y, LeftArrow, (tic_color_dark_gray));
		}

	}

	{
		char val[] = "99";
		sprintf(val, "%02i", value);
		exercise->tic->api.fixed_text(exercise->tic, val, x += TIC_FONT_WIDTH, y, (tic_color_white), false);
	}

	{
		x += 2 * TIC_FONT_WIDTH;

		tic_rect rect = {x, y, TIC_FONT_WIDTH, TIC_FONT_HEIGHT};

		if (exercise->tic->exe.number_of_exercise_tests > 1)
		{
			if (checkMousePos(&rect))
			{
				setCursor(tic_cursor_hand);

				if (checkMouseClick(&rect, tic_mouse_left))
					set(exercise, +1);
			}

			drawBitIcon(rect.x, rect.y, RightArrow, (tic_color_dark_gray));
		}
			
	}
}

/**
* set Index for number of tests to switch
*
* @param exercise a pointer to the exercise loaded
* @param delta number to switch
*/
static void setIndex(Exercise *exercise, s32 delta)
{
	if (exercise->testIndex < exercise->tic->exe.number_of_exercise_tests && exercise->testIndex > 1)
		exercise->testIndex += delta;
	else if (exercise->testIndex == exercise->tic->exe.number_of_exercise_tests && delta < 0)
		exercise->testIndex += delta;
	else if (exercise->testIndex == 1 && delta > 0)
		exercise->testIndex += delta;
}

/**
* draw test switch panel, to switch between existent tests
*
* @param exercise a pointer to the exercise loaded
* @param x x_position of where to begin the switch panel
* @param y y_position of where to begin the switch panel
*/
static void drawTestsPanel(Exercise *exercise, s32 x, s32 y)
{
	enum
	{
		Gap = 2
	};

	drawSwitch(exercise, x, y += Gap + TIC_FONT_HEIGHT, "Test", exercise->testIndex, setIndex);
}

/**
* draw each unit test in a box
*
* @param exercise a pointer to the exercise loaded
* @param test a pointer to the unit test to be displayed
*/
static void drawTestBox(Exercise *exercise, ExerciseTest *test)
{
	u8 color = tic_color_blue;

	switch (test->passed)
	{
	case 0:
		color = tic_color_red;
		break;
	case 1:
		color = tic_color_green;
		break;
	case -2:
		color = tic_color_dark_gray;
		break;
	}
	exercise->tic->api.rect(exercise->tic, 14, 30, (TIC80_WIDTH - 28), (TIC80_HEIGHT - 50), color);
	drawDownBorder(exercise, 14, 30, (TIC80_WIDTH - 28), (TIC80_HEIGHT - 50));

	exercise->tic->api.fixed_text(exercise->tic, test->title, 16, 35, (tic_color_black), false);

	if (strlen(test->test_code) < 100)
		drawCode(exercise, test->test_code, tic_color_white, 16, 16, 45, (TIC80_WIDTH - 28));
	else
	{
		tic80_input *input = &exercise->tic->ram.input;

		if (input->mouse.scrolly)
		{
			enum
			{
				Scroll = 3
			};
			s32 delta = input->mouse.scrolly > 0 ? -Scroll : Scroll;
			exercise->scroll.y += delta;

			normalizeScroll(exercise, test->test_code);
		}

		processMouse(exercise, test->test_code);

		drawCodeScroll(exercise, test->test_code, tic_color_white, 16, 45, (TIC80_WIDTH - 15), (TIC80_HEIGHT - 25));
	}

	if (test->passed == 0 && test->hint != NULL){

		exercise->tic->api.rect(exercise->tic, 14, (TIC80_HEIGHT - 18), (TIC80_WIDTH - 28), 12, tic_color_dark_blue);
		drawDownBorder(exercise, 14, (TIC80_HEIGHT - 18), (TIC80_WIDTH - 28), 12);

		drawCode(exercise, test->hint, tic_color_white, 16, 16, (TIC80_HEIGHT - 17), TIC80_WIDTH - 28);
	}
}

/**
* Draws the tests layout when the tests tab is selected
*
* @param exercise a pointer to the exercise loaded
*/
static void drawTestsLayout(Exercise *exercise)
{
	exercise->tic->api.clear(exercise->tic, (tic_color_gray));

	if (exercise->tic->exe.title == NULL)
	{
		drawCode(exercise, "No Exercise Loaded!", tic_color_dark_blue, TIC80_WIDTH / 4, TIC80_WIDTH / 4, TIC80_HEIGHT / 3, TIC80_WIDTH);
		return;
	}
	
	drawTestsPanel(exercise, (TIC80_WIDTH / 2 - 25), 10);

	drawTestBox(exercise, &(exercise->tic->exe.exerciseTests[exercise->testIndex - 1]));
}

/**
* Draws Exercise tabs, 1st containing
* the general loaded exercises overview
* while the 2nd has the unit tests
*
* @param exercise a pointer do the currently loaded
* exercise
*/
static void drawModeTabs(Exercise *exercise)
{
	static const u8 Icons[] =
		{
			0b00000000,
			0b00111100,
			0b00100100,
			0b00100100,
			0b00100100,
			0b00111100,
			0b00000000,
			0b00000000,

			0b00000000,
			0b00111110,
			0b00001000,
			0b00001000,
			0b00001000,
			0b00001000,
			0b00000000,
			0b00000000,
		};

	enum
	{
		Width = 9,
		Height = 7,
		Rows = 8,
		Count = sizeof Icons / Rows
	};

	for (s32 i = 0; i < Count; i++)
	{
		tic_rect rect = {TIC80_WIDTH - Width * (Count - i), 0, Width, Height};

		static const s32 Tabs[] = {EXERCISE_OVERVIEW_TAB, EXERCISE_TESTS_TAB};

		bool over = false;

		if (checkMousePos(&rect))
		{
			setCursor(tic_cursor_hand);
			over = true;

			static const char *Tooltips[] = {"OVERVIEW MODE", "TESTS MODE"};
			showTooltip(Tooltips[i]);

			if (checkMouseClick(&rect, tic_mouse_left))
				exercise->tab = Tabs[i];
		}

		if (exercise->tab == Tabs[i])
		{
			exercise->tic->api.rect(exercise->tic, rect.x, rect.y, rect.w, rect.h, (tic_color_gray));
			drawBitIcon(rect.x, rect.y + 1, Icons + i * Rows, tic_color_black);
		}

		drawBitIcon(rect.x, rect.y, Icons + i * Rows, exercise->tab == Tabs[i] ? (tic_color_white) : over ? (tic_color_dark_gray) : (tic_color_light_blue));
	}
}

/** 
* draw Exercise Toolbar with the buttons to accionate/stop tests for running 
*
* @param exercise a pointer to the exercise loaded
*/
static void drawExerciseToolbar(Exercise *exercise)
{
	exercise->tic->api.rect(exercise->tic, 0, 0, TIC80_WIDTH, TOOLBAR_SIZE, (tic_color_white));

	drawPlayTestButtons(exercise);
	drawModeTabs(exercise);
}

/**
* tick function called every second to display exercise
*
* @param exercise a pointer to the exercise loaded
*/
static void tick(Exercise *exercise)
{
	switch (exercise->tab)
	{
	case EXERCISE_OVERVIEW_TAB:
		drawOverviewLayout(exercise);
		break;
	case EXERCISE_TESTS_TAB:
		drawTestsLayout(exercise);
		break;
	}

	processKeyboard(exercise);
	drawExerciseToolbar(exercise);
	drawToolbar(exercise->tic, (tic_color_gray), false);
}

/**
* init an Exercise
*
* @param exercise a pointer to the exercise to load
* @param tic a pointer to the tic_mem (memory)
* @param exe a pointer to the exercise info to load on exercise struct 
*/
void initExercise(Exercise *exercise, tic_mem *tic, tic_exercise *exe)
{
	if (exercise->history)
		history_delete(exercise->history);

	*exercise = (Exercise){
		.tic = tic,
		.tick = tick,
		.exe = exe,
		.tab = EXERCISE_OVERVIEW_TAB,
		//.history = history_create(tic->exe.title , sizeof(tic->exe)),
		.testIndex = 1,
		.scroll = {0, 0, {0, 0}, false},
	};
}
