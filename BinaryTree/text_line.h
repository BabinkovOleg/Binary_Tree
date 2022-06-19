#pragma once

#include"raylib.h"


typedef struct line {
	Vector2 position;
	Vector2 boxSize;
	int fontSize;
	Color boxColor;
	Color textColor;
	Color contourColor;
	int length;
	char* currentStr;
	bool isActive;
} line;


int GetNumber(line* _line);

void DrawTextLine(line* _line);

void InputText(line* _line);

void LineActivation(line* _line);

void LineConstruct(line* _line);

void CleanTextLine(line* _line);