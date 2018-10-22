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

// #define TRACKER_ROWS (exercise_PATTERN_ROWS / 4)


/**
 * 
 * 
 */ 
static void drawCode(Exercise *exercise, char *text, u8 color, s32 xStart, s32 x, s32 y, s32 xEnd)
{
	char *pointer = text;

	//u8* colorPointer = exercise->colorBuffer;

	while (*pointer)
	{
		char symbol = *pointer;

		if (x >= -TIC_FONT_WIDTH && x < xEnd && y >= -TIC_FONT_HEIGHT && y < TIC80_HEIGHT)
		{

			exercise->tic->api.draw_char(exercise->tic, symbol, x + 1, y + 1, color, false);

			//code->tic->api.draw_char(code->tic, symbol, x, y, *colorPointer, code->altFont);
		}

		if (symbol == '\n' || (x + 1) >= xEnd)
		{
			x = xStart;
			y += STUDIO_TEXT_HEIGHT;
			color++;
		}
		else
			x += TIC_FONT_WIDTH;

		pointer++;
	}

	// if(code->cursor.position == pointer)
	// 	cursor.x = x, cursor.y = y;
	//
	// if(withCursor && cursor.x >= 0 && cursor.y >= 0)
	// 	drawCursor(code, cursor.x, cursor.y, cursor.symbol);
}

/**
 * 
 * 
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
 * 
 * 
 */
static void drawOverviewLayout(Exercise *exercise)
{
	exercise->tic->api.clear(exercise->tic, (tic_color_dark_red));
	
	//TODO: MUDAR ISTO NO FUTURO

	int titleLength = TIC80_WIDTH / 12 + strlen("-- title: ") * TIC_FONT_WIDTH;
	int authorLength = TIC80_WIDTH / 12 + strlen("-- author: ") * TIC_FONT_WIDTH;

	drawCode(exercise, "-- title: ", tic_color_black, TIC80_WIDTH / 12, TIC80_WIDTH / 12, TIC80_HEIGHT / 8, TIC80_WIDTH);
	drawCode(exercise, exercise->tic->exe.title, tic_color_red, titleLength, titleLength, TIC80_HEIGHT / 8, TIC80_WIDTH);

	drawCode(exercise, "-- author: ", tic_color_black, TIC80_WIDTH / 12, TIC80_WIDTH / 12, TIC80_HEIGHT / 5.25, TIC80_WIDTH);
	drawCode(exercise, exercise->tic->exe.creator_name, tic_color_red, authorLength, authorLength, TIC80_HEIGHT / 5.25, TIC80_WIDTH);

	drawCode(exercise, "-- description: ", tic_color_black, TIC80_WIDTH / 12, TIC80_WIDTH / 12, TIC80_HEIGHT / 4, TIC80_WIDTH);
	drawCode(exercise, exercise->tic->exe.description, tic_color_red, TIC80_WIDTH / 12, TIC80_WIDTH / 12, TIC80_HEIGHT / 3, TIC80_WIDTH - 10);
}

static void runTests(Exercise *exercise)
{
	//exercise->tic->api.exercise(exercise->tic, exercise->track, -1, -1, true);
}

static void stopTests(Exercise *exercise)
{
	//exercise->tic->api.exercise(exercise->tic, -1, -1, -1, false);
}

/**
 * 
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
			0b00000000,

			0b00000000,
			0b01111100,
			0b01111100,
			0b01111100,
			0b01111100,
			0b01111100,
			0b00000000,
			0b00000000,

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

			static const char *Tooltips[] = {"PLAY TESTS", "STOP [enter]"};
			showTooltip(Tooltips[i]);

			static void (*const Handlers[])(Exercise *) = {runTests, stopTests};

			if (checkMouseClick(&rect, tic_mouse_left))
				Handlers[i](exercise);
		}

		// if (i == 0 /*&& exercise->tracker.follow*/)
		// 	drawBitIcon(rect.x, rect.y, Icons + i * Rows, over ? (tic_color_peach) : (tic_color_red));
		// else
	    drawBitIcon(rect.x, rect.y, Icons + i * Rows, over ? (tic_color_dark_gray) : (tic_color_light_blue));
	}
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
 * 
 * 
 */
static void drawExerciseToolbar(Exercise *exercise)
{
	exercise->tic->api.rect(exercise->tic, 0, 0, TIC80_WIDTH, TOOLBAR_SIZE, (tic_color_white));

	drawPlayTestButtons(exercise);
	drawModeTabs(exercise);
}

/**
* 
* 
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

		if (checkMousePos(&rect))
		{
			setCursor(tic_cursor_hand);

			if (checkMouseClick(&rect, tic_mouse_left))
				set(exercise, -1);
		}

		drawBitIcon(rect.x, rect.y, LeftArrow, (tic_color_dark_gray));
	}

	{
		char val[] = "99";
		sprintf(val, "%02i", value);
		exercise->tic->api.fixed_text(exercise->tic, val, x += TIC_FONT_WIDTH, y, (tic_color_white), false);
	}

	{
		x += 2 * TIC_FONT_WIDTH;

		tic_rect rect = {x, y, TIC_FONT_WIDTH, TIC_FONT_HEIGHT};

		if (checkMousePos(&rect))
		{
			setCursor(tic_cursor_hand);

			if (checkMouseClick(&rect, tic_mouse_left))
				set(exercise, +1);
		}

		drawBitIcon(rect.x, rect.y, RightArrow, (tic_color_dark_gray));
	}
}

/**
* 
* 
*/
static void setIndex(Exercise *exercise, s32 delta)
{
	if (exercise->testIndex < (sizeof(exercise->unitTests) / 2) && exercise->testIndex > 1)
		exercise->testIndex += delta;
	else if (exercise->testIndex == (sizeof(exercise->unitTests) / 2) && delta < 0)
		exercise->testIndex += delta;
	else if (exercise->testIndex == 1 && delta > 0)
		exercise->testIndex += delta;
}

/**
* 
* 
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
* 
* 
*/
static void drawTestBox(Exercise *exercise, UnitTest *test)
{
	exercise->tic->api.rect(exercise->tic, 14, 30, (TIC80_WIDTH - 27), (TIC80_HEIGHT - 50), (tic_color_white));

	exercise->tic->api.fixed_text(exercise->tic, test->title, 16, 35, (tic_color_black), false);
	exercise->tic->api.fixed_text(exercise->tic, test->description, 16, 45, (tic_color_gray), false);

	drawCode(exercise, test->correctCode, tic_color_blue, 16, 16, 55, TIC80_WIDTH);
}

/**
* 
* 
*/
static void drawTestsLayout(Exercise *exercise)
{
	tic_mem *tic = exercise->tic;

	tic->api.clear(tic, (tic_color_gray));

	drawTestsPanel(exercise, (TIC80_WIDTH/2 - 25), 10);

	UnitTest *test = &(exercise->unitTests[exercise->testIndex-1]);
	drawTestBox(exercise, test);
}

/**
* 
* 
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
* 
* 
*/
void initExercise(Exercise *exercise, tic_mem *tic, tic_exercise *exe)
{
	if (exercise->history)
		history_delete(exercise->history);

	*exercise = (Exercise){
		.tic = tic,
		.tick = tick,
		.exe = exe,
		.unitTests = malloc(4 * sizeof(UnitTest)), //Mock
		.tab = EXERCISE_OVERVIEW_TAB,
		//.history = history_create(tic->exe.title , sizeof(tic->exe)),
		.testIndex = 1, 
	};

	/*
	* Mock 
	*/

	char *name;
	char *author;
	char *description;
	name = malloc(64);
	author = malloc(64);
	description = malloc(20000);
	memcpy(name, "exercicio de teste", sizeof("exercicio de teste"));
	memcpy(author, "professor Jorge", sizeof("professor Jorge"));
	memcpy(description, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus scelerisque, dolor in varius ullamcorper, massa metus maximus lorem, sed fermentum justo velit viverra dui. Vestibulum nec lacus ac felis eleifend cursus sit amet vel nulla. Fusce eget mi sed neque pulvinar sollicitudin non id justo. Donec facilisis eget ex ac auctor. Suspendisse in metus vel tortor eleifend blandit nec vitae eros. Pellentesque rutrum commodo fermentum. Nunc vehicula eleifend neque ac convallis. Nunc elementum tincidunt risus. Aenean augue lectus, molestie eget enim sed, suscipit cursus eros. Morbi a egestas arcu. Aliquam sem orci, sodales ac posuere vitae, eleifend eget urna.\nNullam sit amet sollicitudin libero. Vestibulum sem enim, pretium a lobortis quis, mattis in nibh. Phasellus non pretium magna, id venenatis neque. Nulla accumsan eleifend consequat. Donec eu leo tortor. Quisque posuere elit ornare, malesuada nulla at, fermentum enim. Sed tellus felis, dignissim nec feugiat ac, suscipit et diam.\nMorbi ac augue eu purus vestibulum ultrices. Nullam vel magna at justo ullamcorper vulputate. Phasellus justo nulla, elementum sed lorem et, auctor malesuada libero. Integer ac erat eu eros ornare ultricies. Cras mattis quis risus id egestas. Phasellus porttitor diam sit amet ante ullamcorper, eu rhoncus massa mattis. Aliquam a sollicitudin diam. Pellentesque congue mauris nec nisl mattis, eu venenatis enim tincidunt. In blandit ut sem et faucibus. Cras ut eros faucibus, finibus leo eget, placerat mi. Aliquam erat volutpat. Morbi pretium vehicula iaculis. ",
		   sizeof("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus scelerisque, dolor in varius ullamcorper, massa metus maximus lorem, sed fermentum justo velit viverra dui. Vestibulum nec lacus ac felis eleifend cursus sit amet vel nulla. Fusce eget mi sed neque pulvinar sollicitudin non id justo. Donec facilisis eget ex ac auctor. Suspendisse in metus vel tortor eleifend blandit nec vitae eros. Pellentesque rutrum commodo fermentum. Nunc vehicula eleifend neque ac convallis. Nunc elementum tincidunt risus. Aenean augue lectus, molestie eget enim sed, suscipit cursus eros. Morbi a egestas arcu. Aliquam sem orci, sodales ac posuere vitae, eleifend eget urna.\nNullam sit amet sollicitudin libero. Vestibulum sem enim, pretium a lobortis quis, mattis in nibh. Phasellus non pretium magna, id venenatis neque. Nulla accumsan eleifend consequat. Donec eu leo tortor. Quisque posuere elit ornare, malesuada nulla at, fermentum enim. Sed tellus felis, dignissim nec feugiat ac, suscipit et diam.\nMorbi ac augue eu purus vestibulum ultrices. Nullam vel magna at justo ullamcorper vulputate. Phasellus justo nulla, elementum sed lorem et, auctor malesuada libero. Integer ac erat eu eros ornare ultricies. Cras mattis quis risus id egestas. Phasellus porttitor diam sit amet ante ullamcorper, eu rhoncus massa mattis. Aliquam a sollicitudin diam. Pellentesque congue mauris nec nisl mattis, eu venenatis enim tincidunt. In blandit ut sem et faucibus. Cras ut eros faucibus, finibus leo eget, placerat mi. Aliquam erat volutpat. Morbi pretium vehicula iaculis. "));

	exercise->tic->exe.title = malloc(strlen(name) + 1);
	strcpy(exercise->tic->exe.title, name);
	exercise->tic->exe.creator_name = malloc(strlen(author) + 1);
	strcpy(exercise->tic->exe.creator_name, author);
	exercise->tic->exe.description = malloc(strlen(description) + 1);
	strcpy(exercise->tic->exe.description, description);

	free(name);
	free(author);
	free(description);

	//DELETE
	exercise->unitTests[0] = (UnitTest){
		.title = "Test 1",
		.description = "Description test 1",
		.correctCode = "function testAddPositive()\n\tluaunit.assertEquals(add(1, 1), 2)\nend",
	};

	exercise->unitTests[1] = (UnitTest){
		.title = "Test 2",
		.description = "Description test 2",
		.correctCode = "function testAddZero()\n\tluaunit.assertEquals(add(1, 0), 0)\n\tluaunit.assertEquals(add(0, 5), 0)\n\tluaunit.assertEquals(add(0, 0), 0)\nend",
	};

	exercise->unitTests[2] = (UnitTest){
		.title = "Test 3",
		.description = "Description test 3",
		.correctCode = "lorem ipsum sid dolore..... 3",
	};

	exercise->unitTests[3] = (UnitTest){
		.title = "Test 4",
		.description = "Description test 4",
		.correctCode = "lorem ipsum sid dolore.....  4",
	};

	//resetSelection(exercise);
}
