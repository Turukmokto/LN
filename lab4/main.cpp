#include <iostream>
#include <fstream>
#include <stack>
#include "LN.h"

using namespace std;

inline LN get_next(std::stack<LN> &st) {
    LN res = st.top();
    st.pop();
    return res;
}

int main(const int argv, const char **args) {
    if (argv != 3) {
        cerr << "Usage: <input file> <output file>";
        return 1;
    }

    ifstream in;
    in.open(args[1], ifstream::in);
    if (!in.is_open()) {
        cerr << "Cannot open input file " << args[1];
        return 1;
    }

    stack<LN> s;
    try {
        string str;
        while (in >> str) {
            if (str == "+") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(x + y);
            } else if (str == "-") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(x - y);
            } else if (str == "*") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(x * y);
            } else if (str == "/") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(x / y);
            } else if (str == "%") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(x % y);
            } else if (str == "~") {
                LN x = get_next(s);
                s.push(~x);
            } else if (str == "_") {
                LN x = get_next(s);
                s.push(-x);
            } else if (str == "<") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(LN(x < y));
            } else if (str == "<=") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(LN(x <= y));
            } else if (str == ">") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(LN(x > y));
            } else if (str == ">=") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(LN(x >= y));
            } else if (str == "==") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(LN(x == y));
            } else if (str == "!=") {
                LN y = get_next(s);
                LN x = get_next(s);
                s.push(LN(x != y));
            } else {
                s.push(LN(str));
            }
        }
    }
    catch (char const *msg) {
        cerr << msg;
        return 1;
    }
    catch (...) {
        cerr << "An unexpected internal error, probably memory overflow\n";
        return 2;
    }
    in.close();

    ofstream out(args[2], ofstream::out);
    if (!out.is_open()) {
        cerr << "Cannot open file " << args[2] << " for writing";
        return 1;
    }

    size_t sz = s.size();
    for (size_t i = 0; i < sz; ++i) {
        out << get_next(s) << '\n';
    }
    out.close();

    return 0;
}