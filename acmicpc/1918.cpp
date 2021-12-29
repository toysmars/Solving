// acmicpc 1918
// 
// infix to postfix
// 후위표기식

#include <bits/stdc++.h>
using namespace std;

struct InpixToPostfix {

    string Solve(string& f) {
        for (auto token: f) {
            switch (token) {
                case '(':
                    op.push(token);
                    break;
                case ')':
                    while (op.top() != '(') {
                        applyOp();
                    }
                    op.pop();
                    break;
                case '*':
                case '/':
                    while (!op.empty() && (op.top() == '*' || op.top() == '/')) {
                        applyOp();
                    }
                    op.push(token);
                    break;
                case '+':
                case '-':
                    while (!op.empty() && (op.top() == '*' || op.top() == '/' || op.top() == '+' || op.top() == '-')) {
                        applyOp();
                    }
                    op.push(token);
                    break;
                default:
                    val.push(string(1, token));
            }
        }
        while (!op.empty()) {
            applyOp();
        }
        return val.top();
    }

    void applyOp() {
        string a = val.top(); val.pop();
        string b = val.top(); val.pop();
        string v = b + a + op.top(); op.pop();
        val.push(v);
    }

    stack<string> val;
    stack<char> op;
};

int main() {
    string f;
    cin >> f;

    InpixToPostfix solver;
    cout << solver.Solve(f) << endl;

    return 0;
}
