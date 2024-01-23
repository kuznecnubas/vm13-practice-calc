#include <iostream>
#include <sstream>
#include <cctype>
#include <math.h>

using namespace std;

int calculate(string mathExpression){
    istringstream iss(mathExpression);
    char currentChar;

    const int maxCountNumbers = 100;
    const int maxCountOperators = 99;

    double peremenie[maxCountNumbers];
    char operators[maxCountOperators];
    char operators_prav[100];

    int count_numbers = 0;
    int count_operators = 0;

    bool correct = true;
    bool pravilo = false;
    bool prav2 = false;

    while (iss >> currentChar) {
        if (isdigit(currentChar) || currentChar == '.') {
            // Числа
            iss.putback(currentChar);
            double number;
            iss >> number;
            peremenie[count_numbers] = number;
            count_numbers++;
        }
        else if (currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '^') {
            // Операторы
            operators[count_operators] = currentChar;
            count_operators++;
            if (currentChar == '*' || currentChar == '/') {
                pravilo = true;
                operators_prav[count_operators] = currentChar;
            }
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
    int j = 0, jj = 0;
    double result = 0;
    double predresult[count_numbers];
    char predoper[maxCountOperators];
    for (int i = 0; i < 100; i++) {
        if (operators[i - 1] == '*' && operators[i + 1] == '/' || operators[i - 1] == '/' && operators[i + 1] == '*' ||
            operators[i - 1] == '*' && operators[i + 1] == '*' || operators[i - 1] == '/' && operators[i + 1] == '/') {
            prav2 = true;
            jj++;
        }
    }

    if(prav2){
        for (int i = 0; i < count_operators; i++) {
            switch (operators[i]) {
                case '/':
                    predresult[i] = peremenie[i] / peremenie[i + 1];
                    break;
                case '*':
                    predresult[i] = peremenie[i] * peremenie[i + 1];
                    break;
                default:
                    predresult[i] = peremenie[i];
                    predoper[j]=operators[i];
                    j++;
            }
        }
        result = predresult[0];
        if(jj<2){
            for (int i = 0; i < j; i++) {
                switch (predoper[i]) {
                    case '+':
                        result = result + predresult[i + 2];
                        break;
                    case '-':
                        result = result - predresult[i + 2];
                        break;
                }
            }
        }else{
            cout<<"Решать такое я не умею, но попытатся решить могу: "<<endl;
        }
    }else if (pravilo) {
        for (int i = 0; i < count_operators; i++) {
            switch (operators[i]) {
                case '/':
                    predresult[i] = peremenie[i] / peremenie[i + 1];
                    jj++;
                    break;
                case '*':
                    predresult[i] = peremenie[i] * peremenie[i + 1];
                    jj++;
                    break;
                default:
                    predresult[i] = peremenie[i];
                    predoper[j]=operators[i];
                    j++;
            }
        }

        result = predresult[0];
        for (int i = 0; i < j; i++) {
            switch (predoper[i]) {
                case '+':
                    result = result + predresult[i + 1];
                    break;
                case '-':
                    result = result - predresult[i + 1];
                    break;
            }
        }
    } else {
        result = peremenie[0];
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
                case '^':
                    result = pow(result,peremenie[i + 1]);
                    break;
            }
        }

    }
    return result;
}

int main() {
    system("chcp 65001");
    string mathExpression;
    while (true) {
        cout << "Введите математическое выражение (exit чтобы выйти): ";
        cin >> mathExpression;
        if(mathExpression == "exit") return 0;
        cout << "Результат: " << calculate(mathExpression) << endl;
    }
}