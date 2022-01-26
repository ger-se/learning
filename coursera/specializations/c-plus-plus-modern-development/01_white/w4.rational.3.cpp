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

bool operator==(const Rational& lhs, const Rational& rhs){
    return lhs.Denominator() == rhs.Denominator() && lhs.Numerator() == rhs.Numerator();
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator()*rhs.Denominator()+rhs.Numerator()*lhs.Denominator(),lhs.Denominator()*rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational&rhs){
    return Rational(lhs.Numerator()*rhs.Denominator()-rhs.Numerator()*lhs.Denominator(),lhs.Denominator()*rhs.Denominator());
}

Rational operator*(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator()*rhs.Numerator(), lhs.Denominator()*rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs){
    return Rational(lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator());
}

int main() {
    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a * b;
        bool equal = c == Rational(8, 9);
        if (!equal) {
            cout << "2/3 * 4/3 != 8/9" << endl;
            return 1;
        }
    }

    {
        Rational a(5, 4);
        Rational b(15, 8);
        Rational c = a / b;
        bool equal = c == Rational(2, 3);
        if (!equal) {
            cout << "5/4 / 15/8 != 2/3" << endl;
            return 2;
        }
    }

    cout << "OK" << endl;
    return 0;
}