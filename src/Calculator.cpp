#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <iomanip>
#include <algorithm> // For std::transform

using namespace std;

// This constant is needed for trigonometric and logarithmic functions.
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// A global vector to hold the history of calculations.
vector<string> history;

/**
 * @brief Saves the calculation history to a file named 'history.txt'.
 */
void saveHistoryToFile() {
    ofstream file("history.txt");
    if (!file.is_open()) {
        cout << "Error: Could not save history file.\n";
        return;
    }
    for (const auto& h : history) {
        file << h << endl;
    }
    file.close();
}

/**
 * @brief Loads the calculation history from 'history.txt' into the history vector.
 */
void loadHistoryFromFile() {
    ifstream file("history.txt");
    if (!file.is_open()) {
        return;
    }
    string line;
    while (getline(file, line)) {
        history.push_back(line);
    }
    file.close();
}

/**
 * @brief Prints the stored calculation history to the console.
 */
void viewHistory() {
    if (history.empty()) {
        cout << "No history available.\n";
        return;
    }
    cout << "\n=== Calculation History ===\n";
    for (const auto& h : history) {
        cout << h << endl;
    }
}

/**
 * @brief Formats a number for display, showing an integer if the number
 * is a whole number, or two decimal places otherwise.
 * @param num The number to format.
 * @return A string with the formatted number.
 */
string formatNumber(double num) {
    ostringstream out;
    out << fixed;
    if (floor(num) == num) {
        out << setprecision(0) << num;
    } else {
        out << setprecision(2) << num;
    }
    return out.str();
}

/**
 * @brief Determines if a string is a recognized function name.
 * @param str The string to check.
 * @return True if it is a function, false otherwise.
 */
bool isFunction(const string& str) {
    return str == "sin" || str == "cos" || str == "tan" || str == "sqrt" || str == "log" || str == "log10";
}

/**
 * @brief Applies an operator to two numbers.
 * @param a The first operand.
 * @param b The second operand.
 * @param op The operator character.
 * @return The result of the operation.
 */
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw runtime_error("Division by zero!");
            return a / b;
        case '^': return pow(a, b);
    }
    return 0;
}

/**
 * @brief Applies a scientific function to a single number.
 * @param val The operand.
 * @param func The function name as a string.
 * @return The result of the function.
 */
double applyFunction(double val, const string& func) {
    if (func == "sin") return sin(val * M_PI / 180.0);
    if (func == "cos") return cos(val * M_PI / 180.0);
    if (func == "tan") {
        if (fmod(val, 90.0) == 0.0 && fmod(val / 90.0, 2.0) != 0.0) {
            throw runtime_error("Tangent of this angle is undefined!");
        }
        return tan(val * M_PI / 180.0);
    }
    if (func == "sqrt") {
        if (val < 0) throw runtime_error("Square root of a negative number!");
        return sqrt(val);
    }
    if (func == "log") {
        if (val <= 0) throw runtime_error("Natural logarithm of a non-positive number!");
        return log(val);
    }
    if (func == "log10") {
        if (val <= 0) throw runtime_error("Logarithm of a non-positive number!");
        return log10(val);
    }
    return 0;
}

/**
 * @brief Determines the precedence of an operator or function.
 * @param token The operator or function as a string.
 * @return An integer representing the token's precedence.
 */
int precedence(const string& token) {
    if (token == "+" || token == "-") return 1;
    if (token == "*" || token == "/") return 2;
    if (token == "^") return 3;
    if (isFunction(token)) return 4;
    return 0;
}

/**
 * @brief Evaluates a mathematical expression using two stacks (one for numbers, one for operators/functions).
 * @param expression The mathematical expression as a string.
 * @return The result of the expression.
 */
double evaluateExpression(string expression) {
    // Standardize input string by adding spaces around operators for easier tokenization
    string standard_expr;
    for (char c : expression) {
        if (string("+-*/^()").find(c) != string::npos) {
            standard_expr += ' ';
            standard_expr += c;
            standard_expr += ' ';
        } else {
            standard_expr += c;
        }
    }
    
    stringstream ss(standard_expr);
    string token;
    stack<double> values;
    stack<string> ops;

    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1]))) {
            values.push(stod(token));
        } else if (isFunction(token)) {
            ops.push(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                string op = ops.top(); ops.pop();
                if (isFunction(op)) {
                    double val = values.top(); values.pop();
                    values.push(applyFunction(val, op));
                } else {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op[0]));
                }
            }
            if (!ops.empty()) ops.pop(); // Pop '('
        } else {
            while (!ops.empty() && precedence(ops.top()) >= precedence(token)) {
                string op = ops.top(); ops.pop();
                if (isFunction(op)) {
                    double val = values.top(); values.pop();
                    values.push(applyFunction(val, op));
                } else {
                    double val2 = values.top(); values.pop();
                    double val1 = values.top(); values.pop();
                    values.push(applyOp(val1, val2, op[0]));
                }
            }
            ops.push(token);
        }
    }

    while (!ops.empty()) {
        string op = ops.top(); ops.pop();
        if (isFunction(op)) {
            double val = values.top(); values.pop();
            values.push(applyFunction(val, op));
        } else {
            double val2 = values.top(); values.pop();
            double val1 = values.top(); values.pop();
            values.push(applyOp(val1, val2, op[0]));
        }
    }
    
    if (values.empty()) {
        throw runtime_error("Invalid expression");
    }

    return values.top();
}

int main() {
    loadHistoryFromFile();
    string input;

    cout << "Welcome to the Advanced Scientific Calculator!\n";
    cout << "Enter an expression (e.g., 2+sin(90)*5), 'history' to view, or 'exit' to quit.\n";
    cout << "Supported operators: +, -, *, /, ^, and parentheses ().\n";
    cout << "Supported functions: sin, cos, tan, sqrt, log, log10.\n\n";

    while (true) {
        cout << "> ";
        getline(cin, input);

        if (input == "exit") {
            cout << "Exiting calculator. Goodbye!\n";
            break;
        }
        if (input == "history") {
            viewHistory();
            continue;
        }

        try {
            double result = evaluateExpression(input);
            string record = input + " = " + formatNumber(result);
            history.push_back(record);
            cout << "Result: " << formatNumber(result) << endl;
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    saveHistoryToFile();
    return 0;
}
