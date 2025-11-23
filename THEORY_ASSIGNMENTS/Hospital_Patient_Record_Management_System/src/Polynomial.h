#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

class Polynomial {
private:
    vector<double> coeffs;

public:
    Polynomial() = default;
    explicit Polynomial(size_t degreePlusOne) : coeffs(degreePlusOne, 0.0) {}
    explicit Polynomial(const vector<double>& c) : coeffs(c) {}

    size_t degree() const { return coeffs.empty() ? 0 : coeffs.size() - 1; }
    const vector<double>& coefficients() const { return coeffs; }
    vector<double>& coefficients() { return coeffs; }

    static Polynomial add(const Polynomial& a, const Polynomial& b) {
        size_t n = max(a.coeffs.size(), b.coeffs.size());
        Polynomial res(n);
        for (size_t i = 0; i < n; ++i) {
            double av = i < a.coeffs.size() ? a.coeffs[i] : 0.0;
            double bv = i < b.coeffs.size() ? b.coeffs[i] : 0.0;
            res.coeffs[i] = av + bv;
        }
        return res;
    }

    static Polynomial multiply(const Polynomial& a, const Polynomial& b) {
        if (a.coeffs.empty() || b.coeffs.empty()) return Polynomial();
        Polynomial res(a.coeffs.size() + b.coeffs.size() - 1);
        for (size_t i = 0; i < a.coeffs.size(); ++i) {
            for (size_t j = 0; j < b.coeffs.size(); ++j) {
                res.coeffs[i + j] += a.coeffs[i] * b.coeffs[j];
            }
        }
        return res;
    }

    double evaluate(double x) const {
        double result = 0.0;
        for (size_t i = coeffs.size(); i-- > 0;) {
            result = result * x + coeffs[i];
        }
        return result;
    }

    void print() const {
        bool first = true;
        for (size_t i = coeffs.size(); i-- > 0;) {
            double c = coeffs[i];
            if (abs(c) < 1e-12) continue;
            if (!first) cout << (c >= 0 ? " + " : " - ");
            else if (c < 0) cout << "-";
            double absC = abs(c);
            if (i == 0) {
                cout << absC;
            } else {
                if (absC != 1.0) cout << absC << "*";
                cout << "x";
                if (i > 1) cout << "^" << i;
            }
            first = false;
        }
        if (first) cout << 0;
        cout << '\n';
    }
};

#endif