#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
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

ostream& operator<<(ostream& stream, const Rational& rational){
    int p = rational.Numerator(), q = rational.Denominator();
    stream << p <<'/'<< q;
    return stream;
}

istream& operator>>(istream& stream, Rational& rational){
    int p,q;
    stream >> p;

    char c;
    while ((stream && !stream.eof()) && (c=stream.peek()) && (c == ' ' || c == '/') && (stream >> c));
    if(!stream || stream.eof()){
        return stream;
    }

    stream >> q;
    if(!stream){
        return stream;
    }
    
    rational = Rational(p,q);
    
    return stream;
}

int main() {
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 3;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 4;
        }
    }

    cout << "OK" << endl;
    return 0;
}