#include <iostream>
#include <map>
#include <set>
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
        if(p == 0){
            q = 1;
        }
        else{
            q = abs(denominator);
        }
        
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
    if(stream.eof()){
        return stream;
    }

    int p,q;
    stream >> p;
    stream.ignore(1);
    stream >> q;
    rational = Rational(p,q);
    
    return stream;
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return lhs.Numerator() * rhs.Denominator() < rhs.Numerator() * lhs.Denominator();
}

int main() {
    {
        const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
        if (rs.size() != 3) {
            cout << "Wrong amount of items in the set" << endl;
            return 1;
        }

        vector<Rational> v;
        for (auto x : rs) {
            v.push_back(x);
        }
        if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
            cout << "Rationals comparison works incorrectly" << endl;
            return 2;
        }
    }

    {
        map<Rational, int> count;
        ++count[{1, 2}];
        ++count[{1, 2}];

        ++count[{2, 3}];

        if (count.size() != 2) {
            cout << "Wrong amount of items in the map" << endl;
            return 3;
        }
    }

    cout << "OK" << endl;
    return 0;
}