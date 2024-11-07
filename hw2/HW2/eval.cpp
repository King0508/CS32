#include <stack> 
#include <string>
#include <iostream>
int evaluate(std::string infix, std::string& postfix, bool& result)
{   
    if(infix.empty()) 
        return 1; 
    postfix = ""; 
    std::stack <char> op;
    int open = 0; 
    int close = 0; 
    int space = 1; 
    int totalSpace = 0; 
    for (int i = 0; i < infix.size(); i++)
    {   
        char c = infix.at(i);
        if (i == infix.size() - 1 && (c == '!' || c == '&' || c == '|' || c == '('))
            return 1; 
        switch (c)
        {
        case 'T': 
            if (i != 0)
            {
                char b = infix.at(i - space); 
                space = 1; 
                if (b == 'T' || b == 'F')
                    return 1;   
            }   
            postfix += 'T';
            break;
        case 'F':
            if (i != 0)
            {
                char b = infix.at(i - space);
                space = 1;
                if (b == 'T' || b == 'F')
                    return 1;
            }
            postfix += 'F'; 
            break; 
        case '(': 
            if (i != 0)
            {
                char b = infix.at(i - space);
                space = 1;
                if (b == ')' || b == 'T' || b == 'F')
                    return 1; 
            }
            op.push(c); 
            open++;
            break;
        case ')':
            if (i == 0)
                return 1; 
            else if (i != 0)
            {
                char b = infix.at(i - space);
                space = 1; 
                if (b == '(' || b == '|' || b == '&')
                    return 1;
            }
            while (!op.empty() && op.top() != '(')
            {
                postfix += op.top(); 
                op.pop(); 
            }
            if(!op.empty())
                op.pop(); 
            close++; 
            break; 
        case '!':
            while (!op.empty() && op.top() != '(' && op.top() != '&' && op.top() != '|' && infix.at(i - space) != '!')
            {        
                postfix += op.top();
                op.pop();
            }
            space = 1; 
            op.push(c); 
            break; 
        case '&':
            if (i == 0)
                return 1;
            else if (i != 0)
            {
                char b = infix.at(i - space);
                space = 1;
                if (b == '(' || b == '|' || b == '&')
                    return 1;
            }
            while (!op.empty() && op.top() != '(' && op.top() != '|')
            {
                postfix += op.top();
                op.pop();
            }
            op.push(c);
            break;
        case '|':
            if (i == 0)
                return 1;
            else if (i != 0)
            {
                char b = infix.at(i - space);
                space = 1; 
                if (b == '(' || b == '|' || b == '&')
                    return 1;
            }
            while (!op.empty() && op.top() != '(')
            {
                postfix += op.top();
                op.pop();
            }
            op.push(c);
            break;
        case ' ':
            if (i != 0 && i != infix.size() - 1)
                space++; 
            totalSpace++; 
            break; 
        default: 
            return 1;
            
        }    
    } 
    if (open != close)
        return 1; 
    if (totalSpace == infix.size())
        return 1;
    while (!op.empty())
    {
        postfix += op.top();
        op.pop();
    }
    for (int i = 0; i < postfix.size(); i++)
    {
        char c = postfix.at(i); 
        if (c == 'T' || c == 'F')
            op.push(c); 
        else if(c == '!' && !op.empty())
        {
            char operand1 = op.top(); 
            op.pop(); 
            if (operand1 == 'T')
                op.push('F');
            else
                op.push('T');
        }
        else if(c == '&' || c == '|')
        {
            char operand2 = op.top();
            op.pop();
            char operand1 = op.top();
            op.pop();
            if (operand1 == operand2 && (c == '&' || c == '|'))
                op.push(operand1); 
            else if (operand1 != operand2 && c == '&')
                op.push('F');
            else if (operand1 != operand2 && c == '|')
                op.push('T');
        }    
    }
    if (op.top() == 'T')
        result = true;
    else
        result = false; 
    return 0; 
}
//Initialize the operand stack to empty
//For each character ch in the postfix string
//if ch is an operand
//push the value that ch represents onto the operand stack
//else // ch is a binary operator
//set operand2 to the top of the operand stack
//pop the stack
//set operand1 to the top of the operand stack
//pop the stack
//apply the operation that ch represents to operand1 and
//operand2, and push the result onto the stack
//When the loop is finished, the operand stack will contain one item,
//the result of evaluating the expression


// Evaluates a boolean expression
       //   If infix is a syntactically valid infix boolean expression,
       //   then set postfix to the postfix form of that expression, set
       //   result to the value of the expression and return zero.  If
       //   infix is not a syntactically valid expression, return 1; in
       //   that case, postfix may or may not be changed, but result must
       //   be unchanged.