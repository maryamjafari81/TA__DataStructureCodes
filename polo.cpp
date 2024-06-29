
#include <iostream>

using namespace std;

class Polynomial {
private:
    double* coefficients;
    int degree;

public:
    Polynomial() {
        coefficients = nullptr;
        degree = -1;
    }

    void addCoefficient(double coeff) {
        double* newCoefficients = new double[degree + 2];
        for (int i = 0; i <= degree; i++) {
            newCoefficients[i] = coefficients[i];
        }
        newCoefficients[degree + 1] = coeff;

        delete[] coefficients;
        coefficients = newCoefficients;
        degree++;
    }

    void removeCoefficient(int index) {
        if (index >= 0 && index <= degree) {
            for (int i = index; i < degree; i++) {
                coefficients[i] = coefficients[i + 1];
            }
            degree--;
        } else {
            cout << "Invalid index." << endl;
        }
    }

    Polynomial addPolynomial(Polynomial other) {
        Polynomial result;
        int maxSize = max(degree, other.degree);

        for (int i = 0; i <= maxSize; i++) {
            double coeff1 = (i <= degree) ? coefficients[i] : 0;
            double coeff2 = (i <= other.degree) ? other.coefficients[i] : 0;
            result.addCoefficient(coeff1 + coeff2);
        }

        return result;
    }

    Polynomial subtractPolynomial(Polynomial other) {
        Polynomial result;
        int maxSize = max(degree, other.degree);

        for (int i = 0; i <= maxSize; i++) {
            double coeff1 = (i <= degree) ? coefficients[i] : 0;
            double coeff2 = (i <= other.degree) ? other.coefficients[i] : 0;
            result.addCoefficient(coeff1 - coeff2);
        }

        return result;
    }

    void displayPolynomial() {
        for (int i = 0; i <= degree; i++) {
            cout << coefficients[i] << "x^" << i << " ";
            if (i != degree) {
                cout << "+ ";
            }
        }
        cout << endl;
    }

    ~Polynomial() {
        delete[] coefficients;
    }
};

int main() {
    Polynomial poly1, poly2, result;
    int choice, index;
    double coeff;

    cout << "Enter the coefficients of the first polynomial (enter -1 to stop): ";
    while (true) {
        cin >> coeff;
        if (coeff == -1) break;
        poly1.addCoefficient(coeff);
    }

    cout << "Enter the coefficients of the second polynomial (enter -1 to stop): ";
    while (true) {
        cin >> coeff;
        if (coeff == -1) break;
        poly2.addCoefficient(coeff);
    }

    cout << "Choose an operation:" << endl;
    cout << "1. Add polynomials" << endl;
    cout << "2. Subtract polynomials" << endl;
    cin >> choice;

    if (choice == 1) {
        result = poly1.addPolynomial(poly2);
    } else if (choice == 2) {
        result = poly1.subtractPolynomial(poly2);
    } else {
        cout << "Invalid choice." << endl;
        return 1;
    }

    cout << "Result: ";
    result.displayPolynomial();

    return 0;
}
