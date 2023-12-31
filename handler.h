#ifndef HANDLER_H_
#define HANDLER_H_

/*
An equation is made of several elements of 'equationlettes',
these are operator based objects, so there can be all kinds.
An equationlette can hold another equationlette in one of its
parameters, where then the parent equationlette waits for the
child equationlette to be evaluated first.
*/

class parseletteStackNode {
  private:
    parselette* owner;
    parseletteStackNode* next;
  
  public:
    // Default Constructor
    parseletteStackNode();
  
    // Next Constructor
    parseletteStackNode(parseletteStackNode* head);
  
    // Create Owner
    void createOwner(int TYPE);
    
    // Set Owner Operator
    void setOwnerOperator(std::string OPERATOR);
  
    
};
  
class parselette {
  /*
    NEEDS AN UPDATE
    
    A parselette is created when an open bracket is detected
    for the first time, eg.

    '(' (a) + (b)) - (c)

    then, another child parselette will be created at the
    second open bracket.

    ( '(' a) + (b)) - (c)

    Now, the second, child, parselette will check if 'a' is
    a special function (eg. sine), a constant, or free variable.

    If it is a constant, it will save the pointer of the 
    specified constant.

    If is is a free variable, it will save the string to one 
    of the 'term' strings. This will be later used to check
    the free variable name, and to replace the free variable
    name with a value at evaluation time.

    ((a ')' + (b)) - (c)

    Upon reaching the first closing bracket, we check the 
    operator of the parselette and store it, in this case,
    '+'.

    ((a) '+' (b)) - (c)
    boolean = true;

    Then we focus on the second,
    child, parselette, as we are now on the second
    term, in this case 'addend' of said parselette. This 
    means we tell the parser to ignore the very next open
    bracket, to not create another parselette by accident.
    (However, if 'b' was a special function, we would create
    another parselette there and continue creating as many
    parselettes as necessary. It is just the initial ')'
    that is ignored) This boolean is instantly flipped once
    we have crossed that next open bracket.

    ((a) + '(' b)) - (c)
    boolean = false;

    Once we have checked 'b', we reach the second closing
    bracket, meaning we have completed the parselette.
    But notice, now we have entered the second part of
    the initial, parent, parselette. 

    We give said parselette the '-' operator, and turn on
    the boolean to ignore the next open bracket.

    ((a) + (b)) '-' (c)
    boolean = true;

    Now we check 'c', and finish the full equation.
  */
  
  private:
    parselette* parent;
    bool lookingForSecondField;             // looking for second field?
    int field;            // Current field
    int type;             // used for integrals, differentials, sums, etc..., type 0: two field operation, type 1: three field operations, type 2: four field operations
    int combination;
    std::string Operator;
    bool complete;
    
    /*
    Type decides which evaluation method to use.
    Say that the operator is '+',
    that means there are two fields, or two addends.
    Now, say both addends are further parselettes,
    then to evaluate this parent parselette, we
    have to evaluate the children first.
    Now, say both addends are constants instead,
    we shouldn't use the childParselette pointers,
    and use the childConstant pointers instead.
    */
    
    // Sub Parselettes
    parselette* childParselettes[4];
    
    /*
    parselette* childParselette1;
    parselette* childParselette2;
    parselette* childParselette3;
    parselette* childParselette4;
    */
    
    // Named variables and constants
    variable* childVariables[4];
  
    /*
    variable* childVariable1;
    variable* childVariable2;
    variable* childVariable3;
    variable* childVariable4;
    */
    
    // Definite Values, eg. numbers
    long double values[4];
  
    /*
    long double value1;
    long double value2;
    long double value3;
    long double value4;
    */
    
    /*
    constant* childConstant1;
    constant* childConstant2;
    constant* childConstant3;
    constant* childConstant4;
  
    freeVariable* childFreeVariable1;
    freeVariable* childFreeVariable2;
    freeVariable* childFreeVariable3;
    freeVariable* childFreeVariable4;
  
    std::string term1;
    std::string term2;
    std::string term3;
    std::string term4;
    */
    
    // Used if this is a constant expression
    long double permanentValue;
  
  public:
    // Recommended Constructor
    parselette(parselette* PARENT, int TYPE);
  
    void setOperator(std::string OPERATOR);
    
    // Returns whether permanent constant expression.
    // This will reduce future computing time,
    // and can be used to simplify the complete expression.
    bool isPermanentConstant();
  
    // Return if the parselette contains a free variable
    bool hasFreeVariable();
  
    // Return free variables
    std::vector<variable*> returnFreeVariables();
    
    // Evaluate the parselette
    long double evaluateParselette(std::vector<std::string>& freeVars, std::vector<long double>& freeVarValues);
};

class handler {
  private:
    std::vector<std::string> inputEquations;
    std::vector<equation> equations;
    std::vector<variable> variables;
  
    // User Loop
    void userLoop();
  
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
  
  public:
    // Default Constructor
    handler();
  
    // Process Input
    void processInput(std::string input);
};

/*
class equationlette {
  private:
    std::string operator;
    std::string term1;
    std::string term2;
    std::string term3;
    std::string term4;
    
    // Possible children
    std::vector<equationlette> equationlettes;
    std::vector<constant> constants;
    
  public:
    // Default Constructor, addition, 1 + 1
    equationlette();
  
    // Regular Constructor, a operator b
    // addition, subtraction, multiplication, etc
    equationlette(std::string operator,
                  std::string term1,
                  std::string term2);
  
    // Container Constructor
    // operations like trigonometric expressions
    equationlette(std::string operator,
                  std::string term1);
  
    // Special Constructor, definite integration,
    // definite differentiation
    equationlette(std::string operator,
                  std::string term1,
                  std::string term2,
                  std::string term3);
  
    // Extra Special Constructor
    // Summation, four terms are required, iterating variable,
    // lower bound, upper bound, and then the internal expression.
    equationlette(std::string operator,
                  std::string term1,
                  std::string term2,
                  std::string term3,
                  std::string term4);
    
    // Evaluate equationette
    long double evaluateEquationette(std::vector<std::string> freeVars, std::vector<long double> freeVarValues);
    
    // Print equationette
    void printEquationette();
};
*/

class curve {
  private:
    plot* owner;
    std::vector<long double> x;
    std::vector<long double> y;
    std::vector<long double> z;
    
    // Using Isometric Projection
    std::vector<SDL_Point> translatedMatrix;
  
  public:
    // Recommended Constructor
    curve(plot* ownerPlot);
    
    // Add Coordinates to the curve
    void addCoordinates(long double x, long double y, long double z);
    
    // Translate Matrix and return the reference to the vector
    std::vector<SDL_Point>& returnTranslatedMatrix();
};

class plot {
  private:
    axis* axis1;
    axis* axis2;
    axis* axis3;
    
    std::vector<equation>& equations;
    std::vector<curve> curves;
  
    bool is3D;
  
  public:
    // Camera Orientation
    long double cameraLocationX;
    long double cameraLocationY;
    long double cameraLocationZ;
  
    long double cameraRotationZ;
    long double cameraPitch;
    
    // Default Constructor
    plot();
  
    // Set 2D or 3D
    void set3D(bool IS3D);
  
    // Update Axes, 2D
    void updateAxes(axis* AXIS1, axis* AXIS2);
  
    // Update Axes, 3D
    void updateAxes(axis* AXIS1, axis* AXIS2, axis* AXIS3);
    
    // Compute Curves
    void computeCurves();
    
    
};

class variableLerp {
  private:
    variable* id;
    long double lowerBound;
    long double upperBound;
    long double step;
    long double lerpSpeed;
  
  public:
    
};

class axis {
  private:
    variable* id;
    long double lowerBound;
    long double upperBound;
    long double step;
  
  public:
    // Recommended Constructor
    axis();
  
    // Set the axis variable
    void setAxisVariable(variable* ID);
  
    
};

class variable {
  private:
    std::string id;
    bool algebraic;
    long double value;
  
  public:
    // Alebraic Constructor
    variable(std::string ID);
  
    // Value Constructor
    variable(std::string ID, long double VALUE);
  
    // Set Algebraic or Valued
    void setAlgebraic(bool ALGEBRAIC);
  
    // Return name
    std::string returnVariableName();
  
    // Return value
    long double returnVariableValue();
};


/*
class freeVariable {
  private:
    std::string id;
    long double value;
    long double lowerBound;
    long double upperBound;
    long double step;
  
  public:
    // Default Constructor, identifier = x, value = lowerBound, lowerBound = -1, upperBound = 1, step = 0.01
    freeVariable();
  
    // Recommended Constructor
    freeVariable(std::string name, long double lowerBound, long double upperBound, long double step);
  
    // Return name
    std::string returnFreeVariableName();
  
    // Return value
    long double returnFreeVariableValue();
    
    // Modify bounds
    bool modifyBounds(long double lowerBound, long double);
  
  
    bool modifyBounds(long double val);
};

class constant {
  private:
    std::string id;
    long double value;
  
  public:
    // Default Constructor, identifier = a, value = 1
    constant();
  
    // Recommended Constructor
    constant(std::string name, long double val);
  
    // Return name
    std::string returnConstantName();
  
    // Return value
    long double returnConstantValue();
    
    // Modify value
    bool modifyConstant(long double val);
};
*/

class equation {
	private:
    std::string inputEquation;
    
    // head of the parselette tree
    parselette* head;
  
	public:
    // Recommended constructor
		equation(std::string INPUTEQUATION, parselette* HEAD);
  
    // Modify Equation
    void modifyEquation(std::string INPUTEQUATION, parselette* HEAD);
  
    // Return Equation
    std::string returnEquation();
  
    // Can evaluate?
    bool evaluable();
		
		// Evaluate, at free variables
    long double evaluateEquation();
};

#endif