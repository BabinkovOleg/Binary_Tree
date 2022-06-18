#include "node.h"
#include <malloc.h>

Node* AddNode(Node* tree, int newValue) {
	if (tree == NULL) {
		tree = (Node*)malloc(sizeof(Node));
		tree->value = newValue;
		tree->left = NULL;
		tree->right = NULL;
	}
	else {
		if (newValue < tree->value)
			tree->left = AddNode(tree->left, newValue);
		if(newValue > tree->value)
			tree->right = AddNode(tree->right, newValue);
	}
	return(tree);
}

int Depth(Node* tree) {
	if (tree == NULL)
		return 0;
	int leftDepth = Depth(tree->left);
	int rightDepth = Depth(tree->right);

	if (leftDepth > rightDepth)
		return leftDepth + 1;
	else
		return rightDepth + 1;
}

Node* DeleteNode(Node* tree, int value) {
	if (tree == NULL)
		return tree;

	if (value == tree->value) {

		Node* tmp;
		if (tree->right == NULL)
			tmp = tree->left;
		else {

			Node* ptr = tree->right;
			if (ptr->left == NULL) {
				ptr->left = tree->left;
				tmp = ptr;
			}
			else {

				Node* pmin = ptr->left;
				while (pmin->left != NULL) {
					ptr = pmin;
					pmin = ptr->left;
				}
				ptr->left = pmin->right;
				pmin->left = tree->left;
				pmin->right = tree->right;
				tmp = pmin;
			}
		}

		free(tree);
		return tmp;
	}
	else if (value < tree->value)
		tree->left = DeleteNode(tree->left, value);
	else
		tree->right = DeleteNode(tree->right, value);
	return tree;
}

void DeleteTree(Node* tree) {
	if (tree != NULL) {
		DeleteTree(tree->left);
		DeleteTree(tree->right);
		free(tree);
	}
}

Node* PrintTree(Node* originTree, Node* tree, Vector2 pos, float width, float height, float size, int totalDepth, int currentDepth) {
	if (tree != NULL) {
		if (totalDepth == 0)
			totalDepth = 1;
		
		if (tree->left != NULL) {
			DrawLine(pos.x, 30 + size + height * currentDepth / totalDepth + size / 2, pos.x - width / 4, 30 - size + height * (1 + currentDepth) / totalDepth + size / 2, BLUE);
			PrintTree(originTree, tree->left, (Vector2) { pos.x - width / 4, pos.y / 2 }, width / 2, height, size, totalDepth, currentDepth + 1);
		}

		if (tree->right != NULL) {
			DrawLine(pos.x, 30 + size + height * currentDepth / totalDepth + size / 2, pos.x + width / 4, 30 - size + height * (1 + currentDepth) / totalDepth + size / 2, BLUE);
			PrintTree(originTree, tree->right, (Vector2) { pos.x + width / 4 , pos.y / 2 }, width / 2, height, size, totalDepth, currentDepth + 1);
		}

		DrawCircle(pos.x, 30 + height * currentDepth / totalDepth + size / 2, size, BLACK);
		if (CheckCollisionPointCircle(GetMousePosition(), (Vector2) { pos.x, 30 + height * currentDepth / totalDepth + size / 2 }, size)) {
			DrawCircle(pos.x, 30 + height * currentDepth / totalDepth + size / 2, size * 9 / 10, GRAY);
			DrawText(TextFormat("%d", tree->value), pos.x - 7, 30 + height * currentDepth / totalDepth, size, RED);
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
				originTree = DeleteNode(originTree, tree->value);
		}
		else {
			DrawCircle(pos.x, 30 + height * currentDepth / totalDepth + size / 2, size * 9 / 10, (Color) { 220, 220, 220, 255 });
			DrawText(TextFormat("%d", tree->value), pos.x - 7, 30 + height * currentDepth / totalDepth, size, RED);
		}
	}
	return originTree;
}