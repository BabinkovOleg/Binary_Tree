#include "text_line.h"

#define MAX_INPUT_LENGTH 3

#define MAX_FIELD_SIZE 20

int GetNumber(line* _line) {
	return atoi(_line->currentStr);
}

void DrawTextLine(line* _line) {
	DrawRectangleV(_line->position, _line->boxSize, _line->contourColor);
	DrawRectangle(_line->position.x + 1, _line->position.y + 1, _line->boxSize.x - 2, _line->boxSize.y - 2, _line->boxColor);

	char* str = _line->currentStr;
	if (_line->isActive) {
		str = TextFormat("%s_", _line->currentStr);
	}
	DrawText(str, _line->position.x + 5, _line->position.y + (_line->boxSize.y - _line->fontSize) / 2, _line->fontSize, _line->textColor);
}

void InputText(line * _line) {
	if (_line->isActive) {
		int keyChar = GetCharPressed();
		int key = GetKeyPressed();

		if (keyChar >= 48 && keyChar <= 57 && _line->length < MAX_INPUT_LENGTH) {
			_line->currentStr[_line->length] = (char)keyChar;
			_line->currentStr[_line->length + 1] = '\0';
			_line->length += 1;
		}

		if (key == 259 && _line->length > 0) {
			_line->length -= 1;
			_line->currentStr[_line->length] = '\0';
		}
	}
}

void LineActivation(line * _line) {
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
		if (CheckCollisionPointRec(GetMousePosition(), (Rectangle) { _line->position.x, _line->position.y, _line->boxSize.x, _line->boxSize.y }))
			_line->isActive = true;
		else
			_line->isActive = false;
	}
}

void LineConstruct(line* _line) {
	_line->position.x = 20;
	_line->position.y = 0;
	_line->boxSize.y = 40;
	_line->boxSize.x = 200;
	_line->currentStr = (char*)malloc(sizeof(char) * (MAX_INPUT_LENGTH + 1));
	_line->currentStr[0] = '\0';
	_line->fontSize = 40;
	_line->length = 0;
	_line->boxColor = LIGHTGRAY;
	_line->textColor = RED;
	_line->contourColor = RED;
	_line->isActive = false;
}

void CleanTextLine(line* _line) {
	while (_line->length > 0) {
		_line->length -= 1;
		_line->currentStr[_line->length] = '\0';
	}
}