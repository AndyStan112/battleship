#include "engine.h"

void ComputeDimensions(Node* root, int MAX_WIDTH) {
    if(root == nullptr) return;

    int childrenSize = root->children.size();
    
    // if we reached a leaf or a node with a fixed "globalBoundsWidth" or "globalBoundsHeight"
    // also update the **box** of that node
    if(root->shape->getGlobalBounds().width || root->shape->getGlobalBounds().height) {
        root->box->setSize(sf::Vector2f(root->shape->getGlobalBounds().width, root->shape->getGlobalBounds().height));
        
        return;
    }
    if(childrenSize == 0) return;

    float rowWidth = root->padding.right, rowHeight = 0;

    for(int i = 0; i < childrenSize; i++) {
        Node* child = root->children[i];

        ComputeDimensions(child, MAX_WIDTH - root->box->getGlobalBounds().width);
        
        int childTotalWidth = child->box->getGlobalBounds().width + child->padding.left + child->padding.right + child->margin.left + child->margin.right;
        int childTotalHeight = child->box->getGlobalBounds().height + child->padding.top + child->padding.bottom + child->margin.top + child->margin.bottom;

        // if placing the child on the current row exceeds the MAX_WIDTH
        if(rowWidth + childTotalWidth + root->padding.right > MAX_WIDTH) {
            // check if the child can fit on an empty row
            if(childTotalWidth < MAX_WIDTH) {
                // place the child on the new, empty row
                root->box->setSize(sf::Vector2f(rowWidth, root->box->getGlobalBounds().height + rowHeight));
                child->shape->setPosition(0, root->box->getGlobalBounds().height);
                child->box->setPosition(0, root->box->getGlobalBounds().height);
                rowHeight = childTotalHeight;
            }
            else {
                // the child is too big, so make the parent bigger!
                root->box->setSize(sf::Vector2f(childTotalWidth, root->box->getGlobalBounds().height + rowHeight));

                // also place the child on a new, empty row
                child->shape->setPosition(0, root->box->getGlobalBounds().height);
                child->box->setPosition(0, root->box->getGlobalBounds().height);
                
                rowHeight = childTotalHeight;
                rowWidth = childTotalWidth;
            }
        }
        else {
            // place the child next in this row, because we know it doesn't overflow the MAX_WIDTH
            child->shape->setPosition(rowWidth, root->box->getGlobalBounds().height);
            rowWidth += childTotalWidth;
            root->box->setSize(sf::Vector2f(std::max(root->box->getGlobalBounds().width, rowWidth), root->box->getGlobalBounds().height));
            rowHeight = std::max(rowHeight, float(childTotalHeight));
        }
    }

    root->box->setSize(sf::Vector2f(std::max(root->box->getGlobalBounds().width, rowWidth) + root->padding.right, root->box->getGlobalBounds().height + rowHeight + root->padding.bottom + root->padding.top));
}

void ComputePositions(Node* root) {
    if(root == nullptr) return;
    
    int childrenSize = root->children.size();

    if(!childrenSize) return;

    int rowWidth = 0, rowHeight = 0;

    sf::Vector2f parentPosition = root->shape->getPosition(); 

    for(int i = 0; i < childrenSize; i++) {
        Node* child = root->children[i];

        sf::Vector2f childRelativePosition = child->shape->getPosition();

        child->shape->setPosition(
            childRelativePosition.x + parentPosition.x + child->margin.left, 
            childRelativePosition.y + parentPosition.y + child->margin.top
        );

        child->box->setPosition(
            childRelativePosition.x + parentPosition.x + child->margin.left, 
            childRelativePosition.y + parentPosition.y + child->margin.top
        );

        ComputePositions(child);
    }
}

void Render (Node* root, sf::RenderWindow& window) {
    if(root == nullptr) return;

    window.draw(*root->shape);

    root->box->setOutlineThickness(2);
    root->box->setOutlineColor(sf::Color::Black);

    if(root->box->getFillColor() == sf::Color::White)
        root->box->setFillColor(sf::Color::Transparent);
    
    window.draw(*root->box);

    int childrenSize = root->children.size();

    if(!childrenSize) return;

    for(int i = 0; i < childrenSize; i++) {
        Node* child = root->children[i];
        Render(child, window);
    }
}

void ComputeLayout(Node* root, int MAX_WIDTH, sf::RenderWindow& window) {
    ComputeDimensions(root, MAX_WIDTH);
    ComputePositions(root);
    Render(root, window);
}