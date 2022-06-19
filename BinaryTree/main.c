#include "node.h"
#include "text_line.h"
#include "raylib.h"
#include <malloc.h>
int main(void)
{
	const int screenWidth = 1600;
	const int screenHeight = 800;

	Node* tree = NULL;

	line line1;
	LineConstruct(&line1);
	line1.position.y = 30;
	
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		LineActivation(&line1);
		InputText(&line1);

		if (IsKeyPressed(KEY_ENTER) && line1.length != 0) {
			tree = AddNode(tree, GetNumber(&line1));
			CleanTextLine(&line1);
		}
		if (IsKeyPressed(KEY_SPACE) && line1.length != 0) {
			tree = DeleteNode(tree, GetNumber(&line1));
			CleanTextLine(&line1);
		}

		BeginDrawing();
		
		ClearBackground(RAYWHITE);

		DrawTextLine(&line1);

		tree = PrintTree(tree, tree, (Vector2) { screenWidth / 2, screenHeight }, screenWidth, screenHeight, 20, Depth(tree), 0);
		DrawText(TextFormat("Max depth %d", Depth(tree)), 20, 0, 20, RED);
		DrawText("LMB on number to delete it\nENTER to add value in box\nSPACE to delete value in box", 20, line1.position.y + line1.boxSize.y * 1.15f, 20, RED);

		EndDrawing();
	}
	DeleteTree(tree);

	CloseWindow();

	return 0;
}