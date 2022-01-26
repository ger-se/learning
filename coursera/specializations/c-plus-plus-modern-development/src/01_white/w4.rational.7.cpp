#include <iostream>
#include <exception>
using namespace std;

class Rational {
public:
    Rational() {
        p = 0;
        q = 1;
        negative = false;
    }

    Rational(int numerator, int denominator) {
        if(denominator == 0){
            throw invalid_argument("Denominator can not be zero.");
        }

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

    bool IsZero() const{
        return p == 0;
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
    if(rhs.Numerator() == 0){
        throw domain_error("Denominator can not be zero.");
    }
    
    return Rational(lhs.Numerator()*rhs.Denominator(), lhs.Denominator()*rhs.Numerator());
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
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
    Rational lhs, rhs;
    string operation;
    try
    {
        cin >> lhs >> operation >> rhs;
    }
    catch(const invalid_argument& exception){
        cout << "Invalid argument"<< endl;
        return 0;
    }

    if(rhs.IsZero() && operation == "/"){
        cout << "Division by zero" << endl;
        return 0;
    }

    Rational result;
    if(operation == "+"){
        result = lhs + rhs;
    } else if(operation == "-"){
        result = lhs - rhs;
    } else if(operation == "*"){
        result = lhs * rhs;
    } else if(operation == "/"){
        result = lhs / rhs;
    }
    else{
        cout << "Invalid argument" << endl;
        return 0;
    }

    cout << result << endl;
    return 0;
}