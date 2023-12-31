#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include "window.h"
#include "handler.h"
#include <cstring>

#define PI 3.14159265

// User Loop
void handler::userLoop () {
	// here happens all of the CLI.
	
}

// Add Equation Function
void addEquation(std::string inputEquation);

// Modify Equation Function
void modifyEquation(int id);

// Add Constant Function
void addConstant(std::string name, long double value);

// Add Variable Function
void addVariable(std::string name);

// Change a variable to constant
void varToConst(std::string name, long double value);

// Change a constant to variable
void constToVar(std::string name);

// Modify Constant Function
void modifyConstant(std::string name, long double value);

// Default Constructor
handler();

// Process Input
void handler::processInput (std::string input) {
	std::string buffer;
	int currentChar = 0;
	bool error = false;
	parselette* head = NULL;
	parselette* current = NULL;
	
	// Bracket Check
	int openBrackets = 0;
	int closedBrackets = 0;
	
	for (int i = 0; i < input.size(); i++) {
		if (input[i] = '(') openBrackets++;
		else if (input[i] = ')') closedBrackets++;
	}
	
	if (openBrackets != closedBrackets) printf("Uneven Brackets\n");
	
	
	// Parsing Process
	while (currentChar < input.length() && !error) {
		if (input[currentChar] != ' ') {
			buffer.append(input[currentChar]);
			
			if (buffer.length() > 0) {
				
				switch (buffer[buffer.length() - 1]) {
						
					case '(': {
						
						// Parselette of type 0, trig function or something else.
						if (buffer.length > 1) {
							
						}
						
						// Else, parselette of type 0 with a regular operator
						else {
						
							if (current != NULL) {
								
								if ((current->type == 0 && current->field > 1) || (current->type == 1 && current->field > 2) || (current->type == 2 && current->field > 3)) 

								else if ((current->type == 0 && !current->lookingForSecondField) || current->type > 0) {
									
									if (current->childParselettes[current->field] == NULL) {
										current->childParselettes[current->field] = new parselette(current, 0); // New parselette of type 0.
										current = current->childParselettes[current->field];
										buffer.clear();
									}

									else printf("childParselette already filled\n");
								}
								
								else if (current->type == 0 && current->lookingForSecondField) {
									current->lookingForSecondField = false;
									current->field++;
									buffer.clear();
								}

								else printf("Type error\n");
							}

							else {

								if (head == NULL) {
									head = new parselette(current, 0); // New parselette of type 0.
									current = head;
									buffer.clear();
								}

								else printf("Head non NULL, current NULL");
							}
						}
					}
						
				case ')': {
					
					if (current != NULL) {
						
						if (current->type == 0) {
							
							if (current->field == 0) {
								