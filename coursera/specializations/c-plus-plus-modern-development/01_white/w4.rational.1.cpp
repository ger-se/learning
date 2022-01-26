#include <iostream>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
        negative = false;
    }

    Rational(int numerator, int denominator) {
        negative = numerator >= 0 ^ denominator >=0;
        p = abs(numerator);
        q = abs(denominator);
        int nod = GetNod(p, q);
        if(nod > 1){
            p = p/nod;
            q = q/nod;
        }
        
    }

    int Numerator() const {
        return p * (negative? -1: 1);
    }

    int Denominator() const {
        return q;
    }

private:
    int p, q;
    bool negative;

    int GetNod(int numerator, int denomitor){
        int a = numerator, b = denomitor;
        if(a == 0 && b == 0){
            return 1;
        }
        else if(a == 0){
            return b;
        }
        else if(b == 0){
            return a;
        }

        while (a != b)
        {
            if(a > b){
                a = a - b;
            }
            else{
                b = b - a;
            }
        }
        
        return a;
    }
};

int main() {
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    cout << "OK" << endl;
    return 0;
}