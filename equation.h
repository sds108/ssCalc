#ifndef EQUATION_H_
#define EQUATION_H_

/*
An equation is made of several elements of 'equationlettes',
these are operator based objects, so there can be all kinds.
An equationlette can hold another equationlette in one of its
parameters, where then the parent equationlette waits for the
child equationlette to be evaluated first.
*/

class parenthesesStackNode {
  private:
    parselette* owner;
    parenthesesStackNode* next;
  
  public:
};



  
class parselette {
  /*
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
    int mode;
    int parameter;        // used for integrals, differentials, sums, etc...
    int type;             // used for integrals, differentials, sums, etc...
    std::string operator;
    
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
  
    parselette* childParselette1;
    parselette* childParselette2;
    parselette* childParselette3;
    parselette* childParselette4;
    
    constant* childConstant1;
    constant* childConstant2;
    constant* childConstant3;
    constant* childConstant4;
  
    std::string term1;
    std::string term2;
    std::string term3;
    std::string term4;
    
    // Used if this is a constant expression
    long double permanentValue;
  
  public:
    // Recommended Constructor
    parselette(std::string operator);
    
    // Returns whether permanent constant expression.
    // This will reduce future computing time,
    // and can be used to simplify the complete expression.
    bool isPermanentConstant();
    
    // Evaluate the parselette
    long double evaluateParselette(std::vector<std::string>& freeVars, std::vector<long double>& freeVarValues);
};

class handler {
  private:
    std::vector<std::string> inputEquations;
    std::vector<equation> equations;
    std::vector<constant> constants;
  
    // Add Equation Function
    void addEquation(std::string inputEquation);
    
    // Modify Equation Function
    void modifyEquation(int index);
  
    // Add Constant Function
    void addConstant(std::string name, long double value);
  
    // Modify Constant Function
    void modifyConstant(std::string name, long double value);
  
  public:
    // Default Constructor
    handler();
  
    // Process Input
    void processInput(std::string input);
};

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

class equation {
	private:
    std::vector<std::string>& freeVars;
    std::vector<long double>& lowerBoundVars;
    std::vector<long double>& upperBoundVars;
    std::vector<long double>& stepVars;
    
    // head of the parselette tree
    parselette* head;
  
    
    
	public:
		// Default Constructor
		equation();
		
		// Free Variable Constructor, usually x, as in y = f(x)
    // Using string so that it's possible to have free variables
    // with a subscript, eg. x_1.
		equation(std::string freeVar);
		
		// Multiple Free Variables Constructor
		equation(std::vector<std::string> freeVars);
		
		// Evaluate, at free variables
    long double evaluateEquation(std::vector<std::string> freeVars, std::vector<long double> freeVarValues);
};

#endif