#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <unordered_map>
#include <stdexcept>
using namespace std;

const unordered_map<char, int> precedence =
{
    {'>',5},
    {'<',5},
    {'+', 10},
    {'-', 10},
    {'*', 20},
    {'/', 20}
};

struct Token
{
    enum class Kind { Number, Char , Variable } kind;
    union { int number; char ch;  };
    string name;
};

Token makeNumber(int n) { Token t; t.kind = Token::Kind::Number;   t.number = n; return t; };
Token makeChar(char c)  { Token t; t.kind = Token::Kind::Char;     t.ch = c;     return t; };
Token makeVar(string s) { Token t; t.kind = Token::Kind::Variable; t.name = s;   return t; };

enum class NodeType { Number, Binary, Variable };

struct TreeNode
{
    NodeType type;
    union { int number; char op; };
    string name;
    TreeNode* left  = nullptr;
    TreeNode* right = nullptr;
};

bool isOperator(char ch)
{
    return precedence.find(ch) != precedence.end();
};

inline bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
};

TreeNode* makeVariableNode(string name)
{
    TreeNode* node = new TreeNode;
    node->type=NodeType::Variable;
    node->name=name;
    return node;
};

TreeNode* makeNumberNode(int value)
{
    TreeNode* node = new TreeNode;
    node->type = NodeType::Number;
    node->number = value;
    return node;
};

TreeNode* makeBinaryNode(char op, TreeNode* lhs, TreeNode* rhs)
{
    TreeNode* node = new TreeNode;
    node->type = NodeType::Binary;
    node->op   = op;
    node->left  = lhs;
    node->right = rhs;
    return node;
};

void collapse(stack<TreeNode*>& operands, stack<char>& operators)
{
    char op       = operators.top(); operators.pop();
    TreeNode* rhs = operands.top();  operands.pop();
    TreeNode* lhs = operands.top();  operands.pop();
    operands.push(makeBinaryNode(op, lhs, rhs));
};

void printAST(TreeNode* node, int depth = 0)
{
    if (!node) return;
    for (int i = 0; i < depth; i++) cout << "  ";
    if (node->type == NodeType::Number)       cout << node->number<< '\n';
    else if(node->type == NodeType::Variable) cout << node->name  << '\n';
    else                                      cout << node->op    << '\n';
    printAST(node->left,  depth + 1);
    printAST(node->right, depth + 1);
};

int evaluate(TreeNode* node, unordered_map<string, int>& symbols) {
    
    if (node->type == NodeType::Number) 
        return node->number;
    
    if (node->type == NodeType::Variable) {
        if (symbols.find(node->name) == symbols.end())
            throw runtime_error("Undefined variable: " + node->name);
        return symbols[node->name];
    }
    
    int lhs = evaluate(node->left,  symbols);
    int rhs = evaluate(node->right, symbols);
    
    switch (node->op) {
        case '<': return lhs < rhs;
        case '>': return lhs > rhs;
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/':
            if (rhs == 0) throw runtime_error("Division by zero");
            return lhs / rhs;
        default: throw runtime_error("Unknown operator");
    }
};

void destroy(TreeNode* node)
{
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
};

vector<Token> tokenize(const string& expr)
{
    vector<Token> tokens;

    for (size_t i = 0; i < expr.size(); )
    {
        char ch = expr[i];
        if (ch == ' ') { i++; continue; }

        if (isdigit(ch))
        {
            int value = 0;
            while (i < expr.size() && isdigit(expr[i]))
                value = value * 10 + (expr[i++] - '0');
            tokens.push_back(makeNumber(value));
        }
        else if (is_alpha(ch))
        {
            string name;
            while (i < expr.size() && is_alpha(expr[i])) name.push_back(expr[i++]);
            tokens.push_back(makeVar(name));
        }
        else
        {
            tokens.push_back(makeChar(ch));
            i++;
        }
    }

    vector<Token> result;
    for (size_t i = 0; i < tokens.size(); i++)
    {
        result.push_back(tokens[i]);
        if (i + 1 < tokens.size())
        {
            bool curIsNum   = tokens[i].kind   == Token::Kind::Number;
            bool curIsVar   = tokens[i].kind   == Token::Kind::Variable;
            bool curIsClose = tokens[i].kind   == Token::Kind::Char && tokens[i].ch   == ')';
            bool nextIsOpen = tokens[i+1].kind == Token::Kind::Char && tokens[i+1].ch == '(';
            bool nextIsNum  = tokens[i+1].kind == Token::Kind::Number;
            bool nextIsVar  = tokens[i+1].kind == Token::Kind::Variable;

            if ( (curIsNum || curIsVar || curIsClose) && (nextIsOpen || nextIsVar || nextIsNum) )
                result.push_back(makeChar('*'));
        }
    }
    return result;
};

TreeNode* buildAST(const string& expression)
{
    vector<Token> tokens = tokenize(expression);

    stack<TreeNode*> operands;
    stack<char>      operators;

    for (const Token& tok : tokens)
    {
        if (tok.kind == Token::Kind::Number)
        {
            operands.push(makeNumberNode(tok.number));
        }
        else if (tok.kind == Token::Kind::Variable)
        {
            operands.push(makeVariableNode(tok.name));
        }
        else
        {
            char ch = tok.ch;

            if (ch == '(')
            {
                operators.push('(');
            }
            else if (ch == ')')
            {
                while (!operators.empty() && operators.top() != '(')
                    collapse(operands, operators);
                if (operators.empty())
                    throw runtime_error("Mismatched parentheses");
                operators.pop();
            }
            else if (isOperator(ch))
            {
                while (!operators.empty() &&
                       operators.top() != '(' &&
                       precedence.at(operators.top()) >= precedence.at(ch))
                {
                    collapse(operands, operators);
                }
                operators.push(ch);
            }
            else
            {
                throw runtime_error(string("Unknown token: ") + ch);
            }
        }
    }

    while (!operators.empty())
    {
        if (operators.top() == '(')
            throw runtime_error("Mismatched parentheses");
        collapse(operands, operators);
    }

    return operands.top();
};

int main() {
    cout << "Expression Parser 1.0\n";
    cout << "Type an expression or assignment. 'exit' to quit.\n\n";

    unordered_map<string, int> symbols;
    string line;

    while (true) {
        cout << ">>> ";
        if (!getline(cin, line)) break;
        if (line.empty()) continue;
        if (line == "exit" || line == "quit") break;

        try {
            size_t eq = line.find('=');
            if (eq != string::npos) {
                string varName = line.substr(0, eq);
                while (!varName.empty() && varName.back() == ' ')
                    varName.pop_back();
                string expr = line.substr(eq + 1);

                TreeNode* root = buildAST(expr);
                symbols[varName] = evaluate(root, symbols);
                cout << varName << " = " << symbols[varName] << "\n";
                destroy(root);
            } else {
                TreeNode* root = buildAST(line);
                printAST(root);
                cout << evaluate(root, symbols) << "\n";
                destroy(root);
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }

    cout << "\nBye.\n";
    return 0;
};
