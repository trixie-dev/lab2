#include<iostream>
#include <vector>
#include <cmath>

using namespace std;

static const int base = 10;

class Multiplication;

class LongInt
{
private:
    vector<int> digits;
    static Multiplication *multiplication;
public:
    LongInt(){}

    static void SetMult(Multiplication *mult)
    {
        multiplication = mult;
    }
    
    LongInt(int val)
    {
        while(val > 0)
        {
            digits.push_back(val%10);
            val /= 10;
        }
    }
    LongInt(string val)
    {
        for(int i = val.length()-1; i >= 0; --i)
        {
            digits.push_back(val[i]-'0');
        }
    }
    LongInt(vector<int> vec)
    {
        digits = vec;
    }
    LongInt operator*(const int &val);
    LongInt operator*(const LongInt& other);
    
    LongInt operator+(const LongInt& other)
    {
        int len = digits.size();

        if(other.digits.size() > len)
            len = other.digits.size();

        LongInt res;
        res.digits.resize(len+1);

        int t = 0;
        for(int i = 0; i < len; ++i)
        {
            if(i < digits.size())
                t += digits[i];

            if(i < other.digits.size())
                t += other.digits[i];

            res.digits[i] = t%10;
            t /= 10;
        }
        if(t > 0)
            res.digits[res.digits.size()-1] = t;
        
        if(res.digits[res.digits.size()-1] == 0)
            res.digits.pop_back();

        return res;
    }
    
    LongInt operator-(const LongInt& other)
    {
        int len = digits.size();

        if(other.digits.size() > len)
            len = other.digits.size();

        LongInt res;
        res.digits.resize(len);

        int t = 0;
        for(int i = 0; i < len; ++i)
        {
            if(i < digits.size())
                t += digits[i];

            if(i < other.digits.size())
                t -= other.digits[i];

            if(t < 0)
            {
                res.digits[i] = t+10;
                t = -1;
            }
            else
            {
                res.digits[i] = t;
                t = 0;
            }
        }
        while(res.digits[res.digits.size()-1] == 0)
            res.digits.pop_back();

        return res;
    }
    int size()
    {
       return digits.size(); 
    }
    vector<int> slice(int start, int end)
    {
        vector<int> res;
        for(int i = start; i < end; ++i)
        {
            res.push_back(digits[i]);
        }
        return res;
    }

    void print()
    {
        for(auto digit = digits.rbegin(); digit != digits.rend(); ++digit)
        {
            cout << *digit;
        }
        cout << endl;
    }
};



class Multiplication
{
public:
    virtual LongInt multiply(LongInt a, LongInt b) = 0; 
};

class Karatsuba : public Multiplication
{
    /*
    LongInt multiply(LongInt a, LongInt b)
    {
        int a_size = a.size();
        int b_size = b.size();

        int m = min(a_size - 1, b_size - 1);
        int m2 = m/2;
        
        if(a_size < 10 && b_size < 10)
            return a*b;
        LongInt a_left = a.slice(0, m2);
        LongInt a_right = a.slice(m2, a_size);
        
        LongInt b_left = b.slice(0, m2);
        LongInt b_right = b.slice(m/2, b_size);

        LongInt p1 = multiply(a_left, b_left);
        LongInt p2 = multiply(a_left + a_right, b_left + b_right);
        LongInt p3 = multiply(a_right, b_right);
   
        return (p1*(pow(10, (m2 * 2)))) + ((p2-p1-p3 )*(pow(10, m2))) + p3;
        
    }
    */
    LongInt multiply(LongInt a, LongInt b) override
    {
        int an = a.size();
        int bn = b.size();
        int m = min(an-1, bn-1);
        int m2 = m/2;
        return b;
    };
};

Multiplication* LongInt::multiplication = new Karatsuba();

LongInt LongInt::operator*(const LongInt& other)
{
    return multiplication->multiply(*this, other);
}

int main()
{
    LongInt a(1);
    LongInt b("123");
    a.print();
    b.print();
    LongInt::SetMult(new Karatsuba());
    LongInt c = a * b;
    c.print();
    return 0;
};


