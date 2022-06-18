#pragma once

#include "raylib.h"

typedef struct Node {
	int value;
	struct Node* left;
	struct Node* right;
} Node;

Node* AddNode(Node* tree, int newValue);
Node* DeleteNode(Node* tree, int value);
Node* PrintTree(Node* originTree, Node* tree, Vector2 pos, float width, float height, float size, int totalDepth, int currentDepth);
int Depth(Node* tree);
void DeleteTree(Node* tree);