#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
#include "handler.h"

#define PI 3.14159265

// Recommended constructor
equation::equation (std::string INPUTEQUATION, parselette* HEAD) {
  inputEquation = INPUTEQUATION;
  head = HEAD;
}

// Modify Equation
void equation::modifyEquation (std::string INPUTEQUATION, parselette* HEAD) {
  inputEquation = INPUTEQUATION;
  head = HEAD;
}

// Return Equation
std::string equation::returnEquation () {
  return inputEquation;
}

bool equation::evaluable () {
  return head->evaluable();
}

// Evaluate, at free variables
long double equation::evaluateEquation () {
  return head->evaluate();
}