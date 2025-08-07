#include <iostream>
#include <cmath>
using namespace std;

void showMenu() {
    cout << "\n===== Scientific Calculator =====" << endl;
    cout << "1. Addition (+)" << endl;
    cout << "2. Subtraction (-)" << endl;
    cout << "3. Multiplication (*)" << endl;
    cout << "4. Division (/)" << endl;
    cout << "5. Power (x^y)" << endl;
    cout << "6. Square Root (√x)" << endl;
    cout << "7. Modulo (%)" << endl;
    cout << "8. Exit" << endl;
    cout << "Choose an operation: ";
}

int main() {
    int choice;
    double num1, num2;

    do {
        showMenu();
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                cout << "Result: " << num1 + num2 << endl;
                break;
            case 2:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                cout << "Result: " << num1 - num2 << endl;
                break;
            case 3:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                cout << "Result: " << num1 * num2 << endl;
                break;
            case 4:
                cout << "Enter two numbers: ";
                cin >> num1 >> num2;
                if (num2 != 0)
                    cout << "Result: " << num1 / num2 << endl;
                else
                    cout << "Error: Division by zero!" << endl;
                break;
            case 5:
                cout << "Enter base and exponent: ";
                cin >> num1 >> num2;
                cout << "Result: " << pow(num1, num2) << endl;
                break;
            case 6:
                cout << "Enter number: ";
                cin >> num1;
                if (num1 >= 0)
                    cout << "Result: " << sqrt(num1) << endl;
                else
                    cout << "Error: Square root of negative number!" << endl;
                break;
            case 7:
                cout << "Enter two integers: ";
                int a, b;
                cin >> a >> b;
                if (b != 0)
                    cout << "Result: " << a % b << endl;
                else
                    cout << "Error: Division by zero!" << endl;
                break;
            case 8:
                cout << "Exiting Calculator. Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while(choice != 8);

    return 0;
}
