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
    bool pravilo = false;
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
            if(currentChar == '*' || currentChar == '/') pravilo = true;
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
    int result;
    int predresult;
    if(pravilo){
        for (int i = 0; i < count_operators; i++) {
            switch (operators[i]) {
                case '/':
                    predresult = peremenie[i] / peremenie[i + 1];
                    break;
                case '*':
                    predresult = peremenie[i] * peremenie[i + 1];
                    break;
                default:
                    break;
            }
        }
        for (int i = 0; i < count_operators; i++) {
            switch (operators[i]) {
                case '+':
                    result = predresult + peremenie[i + 1];
                    break;
                case '-':
                    result = predresult - peremenie[i + 1];
                    break;
            }
        }
    }else{
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
    }


    cout << "Результат: " << result;
    return 0;
}