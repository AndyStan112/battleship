#pragma once
#include "utils/node.h"
#include "engine.h"

void ComputeDimensions(Node* root, int MAX_WIDTH);

void ComputePositions(Node* root);

void Render(Node* root, sf::RenderWindow& window);

void ComputeLayout(Node* root, int MAX_WIDTH, sf::RenderWindow& window);