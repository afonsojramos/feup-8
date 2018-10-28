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

#include "surf_exercise.h"
#include "fs.h"
#include "console.h"


#include "ext/gif.h"

#include <string.h>

#define MAIN_OFFSET 4
#define MENU_HEIGHT 10
#define MAX_CARTS 256
#define ANIM 10
#define COVER_WIDTH 140
#define COVER_HEIGHT 116
#define COVER_Y 5
#define COVER_X (TIC80_WIDTH - COVER_WIDTH - COVER_Y)

#if defined(__TIC_WINDOWS__) || defined(__TIC_LINUX__) || defined(__TIC_MACOSX__)
#define CAN_OPEN_URL 1
#endif

typedef struct
{
	s32 start;
	s32 end;
	s32 duration;

	s32* val;
} Anim;

typedef struct Movie Movie;

struct Movie
{
	Anim** items;

	s32 time;
	s32 duration;
	s32 count;

	Movie* next;
	void (*done)(SurfExercises* surf);
};

static struct
{
	s32 topBarY;
	s32 bottomBarY;
	s32 menuX;
	s32 menuHeight;
} AnimVar;

static Anim topBarShowAnim = {0, MENU_HEIGHT, ANIM, &AnimVar.topBarY};
static Anim bottomBarShowAnim = {0, MENU_HEIGHT, ANIM, &AnimVar.bottomBarY};

static Anim topBarHideAnim = {MENU_HEIGHT, 0, ANIM, &AnimVar.topBarY};
static Anim bottomBarHideAnim = {MENU_HEIGHT, 0, ANIM, &AnimVar.bottomBarY};

static Anim menuLeftHideAnim = {0, -240, ANIM, &AnimVar.menuX};
static Anim menuRightHideAnim = {0, 240, ANIM, &AnimVar.menuX};
static Anim menuHideAnim = {MENU_HEIGHT, 0, ANIM, &AnimVar.menuHeight};

static Anim menuLeftShowAnim = {240, 0, ANIM, &AnimVar.menuX};
static Anim menuRightShowAnim = {-240, 0, ANIM, &AnimVar.menuX};
static Anim menuShowAnim = {0, MENU_HEIGHT, ANIM, &AnimVar.menuHeight};

static Anim* MenuModeShowMovieItems[] =
{
	&topBarShowAnim,
	&bottomBarShowAnim,
	&menuRightShowAnim,
	&menuShowAnim,
};

static Anim* MenuModeHideMovieItems[] =
{
	&topBarHideAnim,
	&bottomBarHideAnim,
	&menuLeftHideAnim,
	&menuHideAnim,
};

static Anim* MenuLeftHideMovieItems[] =
{
	&menuLeftHideAnim,
	&menuHideAnim,
};

static Anim* MenuRightHideMovieItems[] =
{
	&menuRightHideAnim,
	&menuHideAnim,
};

static Anim* MenuLeftShowMovieItems[] =
{
	&menuLeftShowAnim,
	&menuShowAnim,
};

static Anim* MenuRightShowMovieItems[] =
{
	&menuRightShowAnim,
	&menuShowAnim,
};

static Movie EmptyState;
static Movie MenuModeState;

#define DECLARE_MOVIE(NAME, NEXT) static Movie NAME ## State = \
{ \
	.items = NAME ## MovieItems, \
	.count = COUNT_OF(NAME ## MovieItems), \
	.duration = ANIM, \
	.next = & NEXT ## State, \
}

DECLARE_MOVIE(MenuModeShow, MenuMode);
DECLARE_MOVIE(MenuModeHide, Empty);
DECLARE_MOVIE(MenuLeftShow,  MenuMode);
DECLARE_MOVIE(MenuRightShow, MenuMode);
DECLARE_MOVIE(MenuLeftHide, MenuLeftShow);
DECLARE_MOVIE(MenuRightHide, MenuRightShow);

typedef struct MenuItem MenuItem;

struct MenuItem
{
	char* label;
	const char* name;
	const char* hash;
	s32 id;
	tic_screen* cover;
	bool dir;
	bool project;
};

typedef struct
{
	ExerciseSimplified* items;
	s32 count;
	SurfExercises* surf;
} AddMenuItem;


/**
* Resets background animation.
* @param surf stuct with all the information in surf_exercise.
* @param movie movie to reset.
* @param password The password to login with.
* @param done pointer to a function to check if the movie is done or not.
*/
static void resetMovie(SurfExercises* surf, Movie* movie, void (*done)(SurfExercises* surf))
{
	surf->state = movie;

	movie->time = 0;
	for(s32 i = 0; i < movie->count; i++)
	{
		Anim* anim = movie->items[i];
		*anim->val = anim->start;
	}

	movie->time = 0;
	movie->done = done;
}


/**
* Draws the top bar in surf_exercise mode.
* @param surf stuct with all the information in surf_exercise.
* @param x x value to start drawing the toolbar in the screen.
* @param y y value to start drawing the toolbar in the screen.
*/
static void drawTopToolbar(SurfExercises* surf, s32 x, s32 y)
{
	tic_mem* tic = surf->tic;

	enum{Height = MENU_HEIGHT};

	tic->api.rect(tic, x, y, TIC80_WIDTH, Height, tic_color_blue);
	tic->api.rect(tic, x, y + Height, TIC80_WIDTH, 1, tic_color_black);
	{
		char label[FILENAME_MAX];

		sprintf(label, "%s", "FEUP-8 EXERCISES");

		s32 xl = x + MAIN_OFFSET;
		s32 yl = y + (Height - TIC_FONT_HEIGHT)/2;
		tic->api.text(tic, label, xl, yl+1, tic_color_black, false);
		tic->api.text(tic, label, xl, yl, tic_color_white, false);
	}

	enum{Gap = 10, TipX = 150, SelectWidth = 54};

	u8 colorkey = 0;
	tic->api.sprite_ex(tic, &getConfig()->cart->bank0.tiles, 12, TipX + SelectWidth, y+1, 1, 1, &colorkey, 1, 1, tic_no_flip, tic_no_rotate);
	{
		static const char Label[] = "SELECT";
		tic->api.text(tic, Label, TipX + Gap +5 , y+3, tic_color_black, false);
		tic->api.text(tic, Label, TipX + Gap +5, y+2, tic_color_white, false);
	}

}

/**
* Draws the bottom bar in surf_exercise mode.
* @param surf stuct with all the information in surf_exercise.
* @param x x value to start drawing the toolbar in the screen.
* @param y y value to start drawing the toolbar in the screen.
*/
static void drawBottomToolbar(SurfExercises* surf, s32 x, s32 y)
{
	tic_mem* tic = surf->tic;

	enum{Height = MENU_HEIGHT};

	tic->api.rect(tic, x, y, TIC80_WIDTH, Height, tic_color_blue);
	tic->api.rect(tic, x, y + Height, TIC80_WIDTH, 1, tic_color_black);
	{
		char label[FILENAME_MAX];
		char dir[FILENAME_MAX];
		fsGetDir(surf->fs, dir);
	}

		enum{Gap = 10, TipX = 15, SelectWidth = 54};

		u8 colorkey = 0;

			static char Label[30]="";

			int progress=	surf->menu.items[surf->menu.pos].progress;
			sprintf(Label,"percentage done: %d",progress);



			tic->api.text(tic, Label, TipX, y +3, tic_color_black, false);
			tic->api.text(tic, Label, TipX, y +2, tic_color_white, false);


}

/**
* Draws a rect from x,y with width w and height h
* @param tic stuct with all the information about tic.
* @param x initial x value to start drawing.
* @param y initial y value to start drawing.
* @param w with of the rect to draw.
* @param h height of the rect to draw.
*/
static void drawInverseRect(tic_mem* tic, s32 x, s32 y, s32 w, s32 h)
{
	if(x < 0)
	{
		w += x;
		x = 0;
	}

	if(y < 0)
	{
		h += y;
		y = 0;
	}

	w += x;
	h += y;

	if(w > TIC80_WIDTH)
		w = TIC80_WIDTH;

	if(h > TIC80_HEIGHT)
		h = TIC80_HEIGHT;

	for(s32 j = y; j < h; j++)
	{
		for(s32 i = x; i < w; i++)
		{
			s32 index = i + j*TIC80_WIDTH;
			u8 color = tic_tool_peek4(tic->ram.vram.screen.data, index);
			tic_tool_poke4(tic->ram.vram.screen.data, index, color % 4);
		}
	}
}


/**
* Draws the bottom bar in surf_exercise mode.
* @param surf stuct with all the information in surf_exercise.
* @param x x value to start drawing the menu in the screen.
* @param y y value to start drawing the menu in the screen.
* @param bg defines if menu has background or not.
*/
static void drawMenu(SurfExercises* surf, s32 x, s32 y, bool bg)
{
	tic_mem* tic = surf->tic;

	enum {Height = MENU_HEIGHT};

	if(bg)
	{
		if(AnimVar.menuHeight)
			drawInverseRect(tic, 0, y + (MENU_HEIGHT - AnimVar.menuHeight)/2 - 1, TIC80_WIDTH, AnimVar.menuHeight+2);
	}
	else
	{
		tic->api.rect(tic, 0, y + (MENU_HEIGHT - AnimVar.menuHeight)/2, TIC80_WIDTH, AnimVar.menuHeight, tic_color_red);
	}

	for(s32 i = 0; i < surf->menu.count; i++)
	{
		const char* name = surf->menu.items[i].title;

		s32 ym = Height * i + y - surf->menu.pos*MENU_HEIGHT - surf->menu.anim + (MENU_HEIGHT - TIC_FONT_HEIGHT)/2;

		if(bg)
		{
			s32 size = tic->api.text(tic, name, 0, -TIC_FONT_HEIGHT, 0, false);

			drawInverseRect(tic, x + MAIN_OFFSET - 1, ym-1, size+1, TIC_FONT_HEIGHT+2);
		}
		else
		{
			tic->api.text(tic, name, x + MAIN_OFFSET, ym + 1, tic_color_black, false);
			tic->api.text(tic, name, x + MAIN_OFFSET, ym, tic_color_white, false);
		}
	}
}

/**
* Draws the menu background.
* @param surf stuct with all the information in surf_exercise.
*/
static void drawBG(SurfExercises* surf)
{
	tic_mem* tic = surf->tic;

	enum{Size = 16, Width = TIC80_WIDTH/Size+1, Height = TIC80_HEIGHT/Size+1};

	s32 offset = surf->ticks % Size;
	s32 counter = 0;

	for(s32 j = 0; j < Height + 1; j++)
		for(s32 i = 0; i < Width + 1; i++)
			if(counter++ % 2)
				tic->api.sprite_ex(tic, &getConfig()->cart->bank0.tiles, 34, i*Size - offset, j*Size - offset, 2, 2, 0, 0, 1, tic_no_flip, tic_no_rotate);
}


static bool hasExt(const char* name, const char* ext)
{
	return strcmp(name + strlen(name) - strlen(ext), ext) == 0;
}



/**
* Gets all the exercises from the web server.
*/
static void getAllExercises(){
  ExerciseSimplified *exercises;
  size_t number_of_exercises;
  getExercisesListRequest(&exercises, &number_of_exercises);
}

/**
* Add an exercise to menu list.
* @param name exercise name.
* @param id eercise id.
* @param ptr pointer to the struct AddMenuItem that contains the info to a new info
* @param dir if the exercise is a directory or not.
*/
static bool addMenuItem(const char* name, int id, int percentage,  void* ptr, bool dir)
{
	AddMenuItem* data = (AddMenuItem*)ptr;

	static const char CartExt[] = CART_EXT;

	if(dir
		|| hasExt(name, CartExt)
#if defined(TIC80_PRO)
		|| hasExt(name, PROJECT_LUA_EXT)
		|| hasExt(name, PROJECT_MOON_EXT)
		|| hasExt(name, PROJECT_JS_EXT)
		|| hasExt(name, PROJECT_WREN_EXT)
#endif
		)
	{
		ExerciseSimplified* item = &data->items[data->count++];

		item->title = strdup(name);
		item->id = id;
		item->progress =percentage;
	}

	return data->count < MAX_CARTS;
}

/**
* Resets menu.
* @param surf stuct with all the information in surf_exercise.
*/
static void resetMenu(SurfExercises* surf)
{
	if(surf->menu.items)
	{
		for(s32 i = 0; i < surf->menu.count; i++)
		{
			const char* label = surf->menu.items[i].title;
			if(label) free((void*)label);
		}

		free(surf->menu.items);

		surf->menu.items = NULL;
		surf->menu.count = 0;
	}

	surf->menu.pos = 0;
	surf->menu.anim = 0;
}


/**
* Initalizes menu.
* @param surf stuct with all the information in surf_exercise.
*/
static void initMenu(SurfExercises* surf)
{
	resetMenu(surf);

	// TODO: calc files count before
	enum{Count = MAX_CARTS, Size = sizeof(ExerciseSimplified) * Count};

	AddMenuItem data =
	{
		.items = malloc(Size),
		.count = 0,
		.surf = surf,
	};

	char dir[FILENAME_MAX];
	fsGetDir(surf->fs, dir);

	addMenuItem("hello", 1, 10, &data, true);
	addMenuItem("bye", 2, 25, &data, true);
	addMenuItem("adios", 3, 100, &data, true);
	surf->menu.items = data.items;
	surf->menu.count = data.count;
}

/**
* proesses the background animation.
* @param surf stuct with all the information in surf_exercise.
*/
static void processAnim(SurfExercises* surf)
{
	enum{Frames = MENU_HEIGHT};

	{
		if(surf->state->time > surf->state->duration)
		{
			if(surf->state->done)
				surf->state->done(surf);

			if(surf->state->next)
				resetMovie(surf, surf->state->next, NULL);
		}

		for(s32 i = 0; i < surf->state->count; i++)
		{
			Anim* anim = surf->state->items[i];

			if(surf->state->time < anim->duration)
			{
				*anim->val = anim->start + (anim->end - anim->start) * surf->state->time / anim->duration;
			}
			else
			{
				*anim->val = anim->end;
			}
		}

		surf->state->time++;

	}

	if(surf->menu.anim)
	{
		if(surf->menu.anim < 0) surf->menu.anim--;
		if(surf->menu.anim > 0) surf->menu.anim++;

		if(surf->menu.anim <= -Frames)
		{
			surf->menu.anim = 0;
			surf->menu.pos--;

			if(surf->menu.pos < 0)
				surf->menu.pos = surf->menu.count-1;
		}

		if(surf->menu.anim >= Frames)
		{
			surf->menu.anim = 0;
			surf->menu.pos++;

			if(surf->menu.pos >= surf->menu.count)
				surf->menu.pos = 0;
		}
	}
}

/**
* proesses the keys pressed by the user.
* @param surf stuct with all the information in surf_exercise.
*/
static void processGamepad(SurfExercises* surf)
{
	tic_mem* tic = surf->tic;

	enum{Frames = MENU_HEIGHT};

	{
		enum{Hold = 20, Period = Frames};

		enum
		{
			Up, Down, Left, Right, A, B, X, Y
		};

		if(tic->api.btnp(tic, Up, Hold, Period))
		{
			surf->menu.anim = -1;

			playSystemSfx(2);
		}

		if(tic->api.btnp(tic, Down, Hold, Period))
		{
			surf->menu.anim = 1;

			playSystemSfx(2);
		}

		if(tic->api.btnp(tic, A, -1, -1))
		{
			ExerciseSimplified* item = &surf->menu.items[surf->menu.pos];
			//TODO: load do exercise
			surf->console->onConsoleLoadExerciseCommand(surf->console, (int)item->id);
		//	item->dir ? changeDirectory(surf, item->name) : loadCart(surf);
		}

	}

}

/**
* function that is called automatically to render the surf_exercise.
* @param surf stuct with all the information in surf_exercise.
*/
static void tick(SurfExercises* surf)
{
	if(!surf->init)
	{
		initMenu(surf);

		resetMovie(surf, &MenuModeShowState, NULL);

		surf->init = true;
	}

	surf->ticks++;

	tic_mem* tic = surf->tic;
	tic->api.clear(tic, TIC_COLOR_BG);

	drawBG(surf);

	if(surf->menu.count > 0)
	{
		processAnim(surf);

		if(surf->state == &MenuModeState)
		{
			processGamepad(surf);
		}

		drawMenu(surf, AnimVar.menuX, (TIC80_HEIGHT - MENU_HEIGHT)/2, false);

		drawTopToolbar(surf, 0, AnimVar.topBarY - MENU_HEIGHT);
		drawBottomToolbar(surf, 0, TIC80_HEIGHT - AnimVar.bottomBarY);
	}
	else
	{
		static const char Label[] = "You don't have any files...";
		s32 size = tic->api.text(tic, Label, 0, -TIC_FONT_HEIGHT, tic_color_white, false);
		tic->api.text(tic, Label, (TIC80_WIDTH - size) / 2, (TIC80_HEIGHT - TIC_FONT_HEIGHT)/2, tic_color_white, false);
	}
}

/**
* resumes the surf_exercise mode previous state of the background animation.
* @param surf stuct with all the information in surf_exercise.
*/
static void resume(SurfExercises* surf)
{
	resetMovie(surf, &MenuModeShowState, NULL);
}

void initSurfExercises(SurfExercises* surf, tic_mem* tic, struct Console* console)
{
	*surf = (SurfExercises)
	{
		.tic = tic,
		.console = console,
		.fs = console->fs,
		.tick = tick,
		.ticks = 0,
		.state = &EmptyState,
		.init = false,
		.resume = resume,
		.menu =
		{
			.pos = 0,
			.anim = 0,
			.items = NULL,
			.count = 0,
		},
	};

	fsMakeDir(surf->fs, TIC_CACHE);
}
