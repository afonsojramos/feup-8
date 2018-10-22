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

// #define TRACKER_ROWS (MUSIC_PATTERN_ROWS / 4)

static void drawCode(Exercise* exercise,char * text, u8 color)
{
	s32 xStart = TIC80_WIDTH/8;
	s32 x = xStart;
	s32 y = TIC80_HEIGHT/8;
	char* pointer = text;

	//u8* colorPointer = exercise->colorBuffer;


	while(*pointer)
	{
		char symbol = *pointer;

		if(x >= -TIC_FONT_WIDTH && x < TIC80_WIDTH && y >= -TIC_FONT_HEIGHT && y < TIC80_HEIGHT )
		{

				exercise->tic->api.draw_char(exercise->tic, symbol, x+1, y+1, color, false);

			//code->tic->api.draw_char(code->tic, symbol, x, y, *colorPointer, code->altFont);
		}

		if(symbol == '\n')
		{
			x = xStart;
			y += STUDIO_TEXT_HEIGHT;
			color++;
		}
		else x +=TIC_FONT_WIDTH;

		pointer++;
	}

	// if(code->cursor.position == pointer)
	// 	cursor.x = x, cursor.y = y;
	//
	// if(withCursor && cursor.x >= 0 && cursor.y >= 0)
	// 	drawCursor(code, cursor.x, cursor.y, cursor.symbol);
}

static void processKeyboard(Exercise* exercise)
{
	tic_mem* tic = exercise->tic;

	// switch(getClipboardEvent())
	// {
	// case TIC_CLIPBOARD_CUT: copyToClipboard(music, true); break;
	// case TIC_CLIPBOARD_COPY: copyToClipboard(music, false); break;
	// case TIC_CLIPBOARD_PASTE: copyFromClipboard(music); break;
	// default: break;
	// }

	bool ctrl = tic->api.key(tic, tic_key_ctrl);

	if (ctrl)
	{
		 if(keyWasPressed(tic_key_up))
		 printf("UP\n");
		else if(keyWasPressed(tic_key_down))
		printf("DOWN\n");
	}
	// else
	// {
	// 	music->tracker.row >= 0
	// 		? processTrackerKeyboard(music)
	// 		: processPatternKeyboard(music);
	// }
}


static void undo(Exercise* exercise)
{
	history_undo(exercise->history);
}

static void redo(Exercise* exercise)
{
	history_redo(exercise->history);
}

static void drawOverviewLayout(Exercise* exercise)
{
	exercise->tic->api.clear(exercise->tic, (tic_color_dark_red));
	char * text;
	text = calloc(2000,sizeof(char));
	//TODO: MUDAR ISTO NO FUTURO
	char title[500]="-- title: ";
	char author[500]="-- author: ";
	char description[500]="-- description: ";
	//strcat(title,exercise->tic->exe.title);
	strcat(text,title);
	strcat(text,"\n");
	//strcat(author,exercise->tic->exe.creator_name);
	strcat(text,author);
	strcat(text,"\n");
	//strcat(description,exercise->tic->exe.description);
	strcat(text,description);
	strcat(text,"\n");
	static char buf[40];
	strcpy(buf,title);
	//exercise->tic->api.fixed_text(exercise->tic, buf, (TIC80_WIDTH - (sizeof buf - 1) * TIC_FONT_WIDTH) / 3, TIC80_HEIGHT / 8, (tic_color_red), false);
	strcpy(buf,author);
//	exercise->tic->api.fixed_text(exercise->tic, buf, (TIC80_WIDTH - (sizeof buf - 1) * TIC_FONT_WIDTH) / 3, 2 *(TIC80_HEIGHT / 8), (tic_color_green), false);
	strcpy(buf,description);
	//exercise->tic->api.fixed_text(exercise->tic, buf, (TIC80_WIDTH - (sizeof buf - 1) * TIC_FONT_WIDTH) / 3, 3 *(TIC80_HEIGHT / 8), (tic_color_white), false);
	drawCode(exercise, text,tic_color_red);
	free(text);
}

/**
 * Draws Exercise tabs, 1st containing
 * the general loaded exercises overview
 * while the 2nd has the unit tests
 *
 * @param exercise a pointer do the currently loaded
 * exercise
*/
static void drawModeTabs(Exercise* exercise)
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

	enum { Width = 9, Height = 7, Rows = 8, Count = sizeof Icons / Rows };

	for (s32 i = 0; i < Count; i++)
	{
		tic_rect rect = { TIC80_WIDTH - Width * (Count - i), 0, Width, Height };


		static const s32 Tabs[] = { EXERCISE_OVERVIEW_TAB, EXERCISE_TESTS_TAB };

		bool over = false;

		if (checkMousePos(&rect))
		{
			setCursor(tic_cursor_hand);
			over = true;

			static const char* Tooltips[] = { "OVERVIEW MODE", "TESTS MODE" };
			showTooltip(Tooltips[i]);

			if (checkMouseClick(&rect, tic_mouse_left))
				exercise->tab = Tabs[i];
		}

		if (exercise->tab == Tabs[i])
		{
			exercise->tic->api.rect(exercise->tic, rect.x, rect.y, rect.w, rect.h, (tic_color_gray));
			drawBitIcon(rect.x, rect.y + 1, Icons + i*Rows, tic_color_black);
		}

		drawBitIcon(rect.x, rect.y, Icons + i*Rows, exercise->tab == Tabs[i] ? (tic_color_white) : over ? (tic_color_dark_gray) : (tic_color_light_blue));
	}
}

static void drawExerciseToolbar(Exercise* exercise)
{
	exercise->tic->api.rect(exercise->tic, 0, 0, TIC80_WIDTH, TOOLBAR_SIZE, (tic_color_white));

	//drawPlayButtons(exercise);
	drawModeTabs(exercise);
}

 static void drawTestsLayout(Exercise* exercise)
 {
 	tic_mem* tic = exercise->tic;

	char tabTitle[] = "Tests";

	exercise->tic->api.fixed_text(exercise->tic, tabTitle, (TIC80_WIDTH - (sizeof tabTitle - 1) * TIC_FONT_WIDTH) / 3, TIC80_HEIGHT / 8, (tic_color_black), false);


	//tic->api.rect(tic, 50, 20, TIC80_WIDTH, TOOLBAR_SIZE, (tic_color_white));

 	tic->api.clear(tic, (tic_color_gray));

 }


static void tick(Exercise* exercise)
{
		char * name;
		char * author;
		char * description;
		name = malloc(64);
		author = malloc(64);
		description = malloc(64);
		memcpy(name,"exercicio de teste",sizeof("exercicio de teste"));
		memcpy(author,"professor Jorge",sizeof("professor Jorge"));
	 	memcpy(description,"Este exercicio\n nao tem nada e serve apenas \n para teste", sizeof("Este exercicio\n nao tem nada e serve apenas \n para teste"));
		// ex.id=1;
	 	//exercise->tic->exe.title=name;
		//exercise->tic->exe.creator_name=author;
		//exercise->tic->exe.description=description;
	// ex.description=description;
//	drawExerciseLayout(exercise,ex);


	switch (exercise->tab)
	{
		case EXERCISE_OVERVIEW_TAB: drawOverviewLayout(exercise); break;
		case EXERCISE_TESTS_TAB: drawTestsLayout(exercise); break;
	}
	free(name);
	free(author);
	free(description);

	processKeyboard(exercise);
	drawExerciseToolbar(exercise);
	drawToolbar(exercise->tic, (tic_color_gray), false);
}

static void onStudioEvent(Exercise* exercise, StudioEvent event)
{
	switch (event)
	{
	case TIC_TOOLBAR_CUT: /*copyToClipboard(exercise, true);*/ break;
	case TIC_TOOLBAR_COPY: /* copyToClipboard(exercise, false); */ break;
	case TIC_TOOLBAR_PASTE: /* copyFromClipboard(exercise); */ break;
	case TIC_TOOLBAR_UNDO:/*  undo(exercise); */ break;
	case TIC_TOOLBAR_REDO: /* redo(exercise); */ break;
	default: break;
	}
}



//resetSelection(exercise);

void initExercise(Exercise* exercise, tic_mem* tic, tic_exercise* exe)
{
	if (exercise->history) history_delete(exercise->history);

	*exercise = (Exercise)
	{
		.tic = tic,
		.tick = tick,
		.exe = exe,
		.unitTests = malloc(4 * sizeof(UnitTest)), //Mock
		.tab = EXERCISE_OVERVIEW_TAB,
		//.history = history_create(tic->exe.title , sizeof(tic->exe)),
		.event = onStudioEvent,
	};


	//DELETE
	exercise->unitTests[0] = (UnitTest)
	{
		.title = "Test 1",
		.description = "Description test 1",
		.correctCode = "lorem ipsum sid dolore..... 1",
	};

	exercise->unitTests[1] = (UnitTest)
	{
		.title = "Test 2",
		.description = "Description test 2",
		.correctCode = "lorem ipsum sid dolore..... 2",
		};

	exercise->unitTests[2] = (UnitTest)
	{
		.title = "Test 3",
		.description = "Description test 3",
		.correctCode = "lorem ipsum sid dolore..... 3",
		};

	exercise->unitTests[3] = (UnitTest)
	{
		.title = "Test 4",
		.description = "Description test 4",
		.correctCode = "lorem ipsum sid dolore.....  4",
	};


	//resetSelection(exercise);
}