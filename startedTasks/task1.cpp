#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;
int main() {
    system("chcp 65001");
    string mathExpression;
    cout << "Введите математическое выражение: ";
    cin >> mathExpression;

    istringstream iss(mathExpression);
    char currentChar;

    const int maxCountNumbers = 100;
    const int maxCountOperators = 99;

    double per[maxCountNumbers];
    char op[maxCountOperators];

    int count_numbers = 0;
    int count_operators = 0;

    bool correct = true;

    while (iss >> currentChar) {
        if (isdigit(currentChar) || currentChar == '.') {
            // Числа
            iss.putback(currentChar);
            double number;
            iss >> number;
            per[count_numbers] = number;
            count_numbers++;
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // Операторы
            op[count_operators] = currentChar;
            count_operators++;
        }
        else{
            correct = false;
            break;
        }
    }
    if (!correct){
        cout << "Неверный ввод";
        return 0;
    }
    double result = per[0];
    for (int i = 0; i < count_operators; i++) {
        switch (op[i]) {
            case '/':
                result /= per[i + 1];
                break;
            case '*':
                result *= per[i + 1];
                break;
            case '+':
                result += per[i + 1];
                break;
            case '-':
                result -= per[i + 1];
                break;
        }
    }
    cout << "Результат: " << result;
    return 0;
}