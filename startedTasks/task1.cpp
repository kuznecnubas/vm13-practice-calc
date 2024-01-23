#include <iostream>
#include <sstream>
#include <cctype>
#include <cmath>

using namespace std;

const int MAX_SIZE = 100; // Максимальный размер массивов

// Проверка, является ли символ оператором
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

// Вычисление результата для двух чисел с учетом оператора
double applyOperator(double operand1, double operand2, char op) {
    switch (op) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '^':
            return pow(operand1, operand2);
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                cerr << "Ошибка: Деление на ноль." << endl;
                exit(EXIT_FAILURE);
            }
        default:
            cerr << "Ошибка: Неизвестный оператор." << endl;
            exit(EXIT_FAILURE);
    }
}

// Разбивка математического выражения на операторы и операнды
void parseExpression(const string &expression, double operands[], char operators[], int &operandsTop, int &operatorsTop) {
    istringstream iss(expression);
    char token;

    while (iss >> token) {
        if (isdigit(token) || token == '.') {
            double operand;
            iss.putback(token);
            iss >> operand;
            operands[++operandsTop] = operand;
        } else if (isOperator(token)) {
            while (operatorsTop >= 0 && operators[operatorsTop] != '(' &&
                   ((token == '+' || token == '-') || (token == '*' || token == '/') || (token == '^') && (operators[operatorsTop] == '*' || operators[operatorsTop] == '/' || operators[operatorsTop] == '^'))) {
                // Выполняем операции, пока верхний оператор имеет более высокий приоритет
                double operand2 = operands[operandsTop--];
                double operand1 = operands[operandsTop--];
                char op = operators[operatorsTop--];
                operands[++operandsTop] = applyOperator(operand1, operand2, op);
            }
            operators[++operatorsTop] = token; // Добавляем текущий оператор в массив
        } else if (token == '(') {
            operators[++operatorsTop] = token; // Добавляем открывающую скобку в массив
        } else if (token == ')') {
            // Выполняем операции, пока не встретим открывающую скобку
            while (operatorsTop >= 0 && operators[operatorsTop] != '(') {
                double operand2 = operands[operandsTop--];
                double operand1 = operands[operandsTop--];
                char op = operators[operatorsTop--];
                operands[++operandsTop] = applyOperator(operand1, operand2, op);
            }
            --operatorsTop; // Убираем открывающую скобку из массива
        }
    }

    // Выполняем оставшиеся операции
    while (operatorsTop >= 0) {
        double operand2 = operands[operandsTop--];
        double operand1 = operands[operandsTop--];
        char op = operators[operatorsTop--];
        operands[++operandsTop] = applyOperator(operand1, operand2, op);
    }
}

int main() {
    system("chcp 65001");
    string expression;

    while (true) {
        cout << "Введите математическое выражение (для выхода введите 'exit'): ";
        getline(cin, expression);

        if (expression == "exit") {
            return 0; // Завершаем программу при вводе "exit"
        }

        double operands[MAX_SIZE];
        char operators[MAX_SIZE];
        int operandsTop = -1; // Индекс вершины стека операндов
        int operatorsTop = -1; // Индекс вершины стека операторов

        parseExpression(expression, operands, operators, operandsTop, operatorsTop);

        // Выводим результат
        if (operandsTop >= 0) {
            cout << "Результат: " << operands[operandsTop] << endl;
        } else {
            cerr << "Ошибка: Недопустимое выражение." << endl;
        }
    }
}