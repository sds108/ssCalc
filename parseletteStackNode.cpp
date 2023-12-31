#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "window.h"
#include "handler.h"
#include <cstring>

#define PI 3.14159265

// Default Constructor
parseletteStackNode::parseletteStackNode () {
  owner = NULL;
  next = NULL;
}
  
// Next Constructor
parseletteStackNode::parseletteStackNode (parseletteStackNode* head) {
  owner = NULL;
  next = head;
}

// Create Owner
void parseletteStackNode::createOwner (int TYPE) {
  owner = new parslette (TYPE);
}
  
void parseletteStackNode::setOwnerOperator (std::string OPERATOR) {
  if (owner != NULL) owner->Operator = OPERATOR;
}