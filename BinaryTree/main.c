#include "node.h"
#include "raylib.h"
#include <malloc.h>
int main(void)
{
	const int screenWidth = 1600;
	const int screenHeight = 800;

	Node* tree = NULL;

	Camera2D camera = { 0 };
	camera.target = (Vector2) { screenWidth / 2, screenHeight / 2 };
	camera.offset = (Vector2) { screenWidth / 2.0f, screenHeight / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		if (IsKeyPressed(KEY_SPACE))
			tree = DeleteNode(tree, GetRandomValue(0, 30));
		if (IsKeyPressed(KEY_A))
			tree = AddNode(tree, GetRandomValue(0, 30));
		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		tree = PrintTree(tree, tree, (Vector2) { screenWidth / 2, screenHeight }, screenWidth, screenHeight, 20, Depth(tree), 0);
		DrawText(TextFormat("Max depth %d", Depth(tree)), 0, 0, 20, RED);

		EndDrawing();
	}

	CloseWindow();

	return 0;
}