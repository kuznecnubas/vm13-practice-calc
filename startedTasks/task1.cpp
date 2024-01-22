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

    const int MAX_COUNT_NUMBERS = 100;
    const int MAX_COUNT_OPERATORS = 99;

    double peremenie[MAX_COUNT_NUMBERS];
    char operators[MAX_COUNT_OPERATORS];

    int count_numbers = 0;
    int count_operators = 0;

    bool correct = true;

    while (iss >> currentChar) {
        if (isdigit(currentChar) || currentChar == '.') {
            // Числа
            iss.putback(currentChar);
            double number;
            iss >> number;
            peremenie[count_numbers] = number;
            count_numbers++;
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/') {
            // Операторы
            operators[count_operators] = currentChar;
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
    double result = peremenie[0];
    for (int i = 0; i < count_operators; i++) {
        switch (operators[i]) {
            case '/':
                result /= peremenie[i + 1];
                break;
            case '*':
                result *= peremenie[i + 1];
                break;
            case '+':
                result += peremenie[i + 1];
                break;
            case '-':
                result -= peremenie[i + 1];
                break;
        }
    }
    cout << "Результат: " << result;
    return 0;
}