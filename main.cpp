#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include<sstream>

using namespace std;

#define ZERO 48

class LargeInteger
{
private:
    vector<char> digits;
    void cleanup();

public:
    LargeInteger();
    LargeInteger(long long);
    LargeInteger(const LargeInteger& other);
    LargeInteger(string);
    LargeInteger& operator=(LargeInteger other);


    // parse a string to large integer
    void parse(string&);

    // get string representation of your large integer
    string to_str();

    // get number of digit of your number
    int digitNum() { return this->digits.size(); }

    // check if your number is NULL
    bool isNull() { return this->digits.size() == 0; }

    // is Even
    bool isEven() { return (this->digits.at(0) - ZERO) % 2 == 0; }

    // is Negative
    bool isNegative() { return (this->digits.at(this->digits.size() - 1)) == '-'; }

    // multiply your number by 10^n
    LargeInteger multiply_pow_10(unsigned long long n);

    // get abs of the number
    LargeInteger abs();

    // get negative form of the number
    LargeInteger negative();


    friend istream& operator>>(istream&, LargeInteger&);
    friend ostream& operator<<(ostream&, LargeInteger);


    friend bool operator<(LargeInteger first, LargeInteger second);
    friend bool operator>(LargeInteger first, LargeInteger second);
    friend bool operator>=(LargeInteger first, LargeInteger second);
    friend bool operator<=(LargeInteger first, LargeInteger second);
    friend bool operator==(LargeInteger first, LargeInteger second);
    friend bool operator!=(LargeInteger first, LargeInteger second);

    friend bool operator<(LargeInteger first, unsigned long long second);
    friend bool operator>(LargeInteger first, unsigned long long second);
    friend bool operator>=(LargeInteger first, unsigned long long second);
    friend bool operator<=(LargeInteger first, unsigned long long second);
    friend bool operator==(LargeInteger first, unsigned long long second);
    friend bool operator!=(LargeInteger first, unsigned long long second);

    friend bool operator<(unsigned long long first, LargeInteger second);
    friend bool operator>(unsigned long long first, LargeInteger second);
    friend bool operator>=(unsigned long long first, LargeInteger second);
    friend bool operator<=(unsigned long long first, LargeInteger second);
    friend bool operator==(unsigned long long first, LargeInteger second);
    friend bool operator!=(unsigned long long first, LargeInteger second);


    friend LargeInteger operator+(LargeInteger first, LargeInteger second);
    friend LargeInteger operator-(LargeInteger first, LargeInteger second);
    friend LargeInteger operator*(LargeInteger first, LargeInteger second);
    friend LargeInteger operator/(LargeInteger dividend, LargeInteger divisor);
    friend LargeInteger operator%(LargeInteger dividend, LargeInteger divisor);

    friend LargeInteger operator+(LargeInteger first, unsigned long long second);
    friend LargeInteger operator-(LargeInteger first, unsigned long long second);
    friend LargeInteger operator*(LargeInteger first, unsigned long long second);
    friend LargeInteger operator/(LargeInteger dividend, unsigned long long second);
    friend LargeInteger operator%(LargeInteger dividend, unsigned long long second);

    friend LargeInteger operator+(unsigned long long first, LargeInteger second);
    friend LargeInteger operator-(unsigned long long first, LargeInteger second);
    friend LargeInteger operator*(unsigned long long first, LargeInteger second);
    friend LargeInteger operator/(unsigned long long dividend, LargeInteger divisor);
    friend LargeInteger operator%(unsigned long long dividend, LargeInteger divisor);
};

LargeInteger::LargeInteger()
{
    this->digits = {};
}

LargeInteger::LargeInteger(long long value)
{
    if (value == 0)
    {
        this->digits = { ZERO };
    }
    else
    {
        bool sign = false;

        if (value < 0)
        {
            value = -value;
            sign = true;
        }

        while (value > 0)
        {
            this->digits.push_back(value % 10 + ZERO);
            value = value / 10;
        }

        if (sign == true)
        {
            this->digits.push_back('-');
        }
    }
}

LargeInteger::LargeInteger(string digits)
{
    if (digits.at(0) == '-')
    {
        this->digits.push_back(digits.at(0));
        digits.erase(digits.begin());
    }

    for (auto& digit : digits)
    {
        if ((digit >= '0' && digit <= '9'))
            this->digits.push_back(digit);
        else
            throw("Invalid input");
    }

    reverse(this->digits.begin(), this->digits.end());
}

LargeInteger::LargeInteger(const LargeInteger& other)
{
    this->digits = vector<char>(other.digits);
}

LargeInteger& LargeInteger::operator=(LargeInteger other)
{
    this->digits = other.digits;
    return *this;
}

void LargeInteger::cleanup()
{
    while (this->digitNum() > 1 && this->digits[this->digits.size() - 1] == '0')
    {
        this->digits.pop_back();
    }
}

void LargeInteger::parse(string& digits)
{
    if (digits.at(0) == '-')
    {
        this->digits.push_back(digits.at(0));
        digits.erase(digits.begin());
    }

    for (auto& digit : digits)
    {
        if ((digit >= '0' && digit <= '9'))
            this->digits.push_back(digit);
        else
            throw("Invalid input");
    }

    reverse(this->digits.begin(), this->digits.end());
}

string LargeInteger::to_str()
{
    string digits;

    vector<char> int_digits = this->digits;

    for (auto& digit : this->digits)
    {
        digits += digit;
    }

    reverse(digits.begin(), digits.end());

    return digits;
}

LargeInteger LargeInteger::multiply_pow_10(unsigned long long n)
{
    for (unsigned int i = 0; i < n; i++)
    {
        this->digits.insert(this->digits.begin(), '0');
    }

    return *this;
}

LargeInteger LargeInteger::abs()
{
    LargeInteger result = *this;
    if (result.isNegative())
    {
        result.digits.pop_back();
    }

    return result;
}

LargeInteger LargeInteger::negative()
{
    LargeInteger result = *this;
    if (!result.isNegative())
    {
        result.digits.push_back('-');
    }

    return result;
}

ostream& operator<<(ostream& out, LargeInteger big_int)
{
    string digits = big_int.to_str();

    out << digits;

    return out;
}

istream& operator>>(istream& in, LargeInteger& big_int)
{
    string digits;
    in >> digits;

    big_int.parse(digits);

    return in;
}

bool operator<(LargeInteger first, LargeInteger second)
{
    first.cleanup();
    second.cleanup();

    // handle negative case
    if (first.isNegative() && second.isNegative())
    {
        return first.abs() > second.abs();
    }

    if (first.isNegative())
        return true;

    if (second.isNegative())
        return false;

    int n = first.digitNum();
    int m = second.digitNum();

    if (n != m)
    {
        return n < m;
    }

    while (n--)
    {
        if (first.digits[n] > second.digits[n])
        {
            return false;
        }

        if (first.digits[n] < second.digits[n])
        {
            return true;
        }
    }

    return false;
}

bool operator>(LargeInteger first, LargeInteger second)
{
    first.cleanup();
    second.cleanup();

    // handle negative case
    if (first.isNegative() && second.isNegative())
    {
        return first.abs() < second.abs();
    }

    if (first.isNegative())
        return false;

    if (second.isNegative())
        return true;

    int n = first.digitNum();
    int m = second.digitNum();

    if (n != m)
    {
        return n > m;
    }

    while (n--)
    {

        if (first.digits[n] < second.digits[n])
        {
            return false;
        }

        if (first.digits[n] > second.digits[n])
        {
            return true;
        }
    }

    return false;
}

bool operator==(LargeInteger first, LargeInteger second)
{
    return first.digits == second.digits;
}

bool operator!=(LargeInteger first, LargeInteger second)
{
    return !(first == second);
}

bool operator<=(LargeInteger first, LargeInteger second)
{
    return !(first > second);
}

bool operator>=(LargeInteger first, LargeInteger second)
{
    return !(first < second);
}

bool operator<(LargeInteger first, unsigned long long second)
{
    return first < LargeInteger(second);
}

bool operator>(LargeInteger first, unsigned long long second)
{
    return first > LargeInteger(second);
}

bool operator==(LargeInteger first, unsigned long long second)
{
    return first == LargeInteger(second);
}

bool operator!=(LargeInteger first, unsigned long long second)
{
    return first != LargeInteger(second);
}

bool operator<=(LargeInteger first, unsigned long long second)
{
    return first <= LargeInteger(second);
}

bool operator>=(LargeInteger first, unsigned long long second)
{
    return first >= LargeInteger(second);
}

bool operator<(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) < second;
}

bool operator>(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) > second;
}

bool operator<=(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) <= second;
}

bool operator>=(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) >= second;
}

bool operator==(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) == second;
}

bool operator!=(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) != second;
}

LargeInteger operator+(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();

    if (first == 0)
    {
        return second;
    }

    if (second == 0)
    {
        return first;
    }

    LargeInteger result;

    if (first.isNegative() && second.isNegative())
    {
        result = first.abs() + second.abs();
        result = result.negative();
        return result;
    }

    if (first.isNegative())
    {
        return second - first;
    }

    if (second.isNegative())
    {
        return first - second;
    }

    int n = second.digitNum();
    int m = first.digitNum();

    int minNum = min(m, n);
    int maxNum = max(m, n);

    int save = 0;

    for (int i = 0; i < minNum; i++)
    {
        int temp = (first.digits[i] - ZERO) + (second.digits[i] - ZERO) + save;

        result.digits.push_back(temp % 10 + ZERO);
        temp /= 10;
        save = temp % 10;
    }

    vector<char> bigger = (m > n) ? first.digits : second.digits;

    for (int i = minNum; i < maxNum; i++)
    {
        int temp = (bigger[i] - ZERO) + save;

        result.digits.push_back(temp % 10 + ZERO);
        temp /= 10;
        save = temp % 10;
    }

    if (save == 1)
        result.digits.push_back('1');

    return result;
}

LargeInteger operator-(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();

    if (first == 0)
    {
        return second;
    }

    if (second == 0)
    {
        return first;
    }

    LargeInteger result;
    LargeInteger first_abs = first.abs();
    LargeInteger second_abs = second.abs();

    if (first.isNegative() && second.isNegative())
    {
        if (first_abs > second_abs)
        {
            result = first_abs - second_abs;
            result = result.negative();
        }
        else
        {
            result = second_abs - first_abs;
        }

        return result;
    }

    if (first.isNegative())
    {
        result = first_abs + second;
        result = result.negative();
        return result;
    }

    if (second.isNegative())
    {
        return first + second_abs;
    }

    int n = second.digitNum();
    int m = first.digitNum();

    int minNum = min(m, n);
    int maxNum = max(m, n);

    int save = 0;

    for (int i = 0; i < minNum; i++)
    {
        int temp = (first.digits[i]) - (second.digits[i]) - save;

        if (temp < 0)
        {
            temp = temp + 10;
            save = 1;
        }
        else
        {
            save = 0;
        }

        result.digits.push_back(temp + ZERO);
    }

    vector<char> bigger = (m > n) ? first.digits : second.digits;

    for (int i = minNum; i < maxNum; i++)
    {
        int temp = (bigger[i] - ZERO) - save;

        if (temp < 0)
        {
            temp = temp + 10;
            save = 1;
        }
        else
        {
            save = 0;
        }

        result.digits.push_back(temp + ZERO);
    }

    result.cleanup();

    return result;
}

LargeInteger operator*(LargeInteger first, LargeInteger second)
{
    if (first.isNull() || second.isNull())
        return LargeInteger();
    if (first == 0 || second == 0)
    {
        return LargeInteger(0);
    }

    if (first == 1)
    {
        return second;
    }

    if (second == 1)
    {
        return first;
    }

    if (first.isNegative() && second.isNegative())
    {
        return first.abs() * second.abs();
    }

    if (first.isNegative())
    {
        LargeInteger result = first.abs() * second;
        return result.negative();
    }

    if (second.isNegative())
    {
        LargeInteger result = first * second.abs();
        return result.negative();
    }

    int f = first.digitNum();
    int s = second.digitNum();

    if (f == 1 && s == 1)
    {
        int value = (first.digits[0] - ZERO) * (second.digits[0] - ZERO);
        return LargeInteger(value);
    }

    int n = f + s;

    vector<int> pow_sum(n, 0);
    for (unsigned int i = 0; i < f; i++)
    {
        for (unsigned int j = 0; j < s; j++)
        {
            int first_digit = (first.digits[i] - ZERO);
            int second_digit = (second.digits[j] - ZERO);

            pow_sum[i + j] += first_digit * second_digit;
        }
    }

    vector<LargeInteger> pow_sum_large;

    for (int i = 0; i < pow_sum.size(); i++)
    {
        LargeInteger num = LargeInteger(pow_sum[i]);
        num.multiply_pow_10(i);
        pow_sum_large.push_back(num);
    }

    LargeInteger result(0);

    for (auto& sum : pow_sum_large)
    {
        result = result + sum;
    }

    result.cleanup();

    return result;
}

LargeInteger operator/(LargeInteger dividend, LargeInteger divisor)
{
    LargeInteger zero(0);
    LargeInteger one(1);

    if (divisor == zero)
    {
        throw("Division by zero");
    }

    if (divisor > dividend)
    {
        return zero;
    }

    if (dividend == divisor)
    {
        return one;
    }

    if (dividend.isNegative() && divisor.isNegative())
    {
        return dividend.abs() / divisor.abs();
    }

    if (dividend.isNegative())
    {
        LargeInteger result = dividend.abs() / divisor;
        return result.negative();
    }

    if (divisor.isNegative())
    {
        LargeInteger result = dividend / divisor.abs();
        return result.negative();
    }

    int digit_pos = dividend.digitNum() - 1;
    LargeInteger result;

    // temporary/sub dividend
    LargeInteger dv;

    while (digit_pos >= 0)
    {
        // get as much as posible digit for sub-dividsend
        while (digit_pos >= 0 && (dv.isNull() || dv < divisor))
        {
            dv.digits.insert(dv.digits.begin(), dividend.digits[digit_pos--]);

            if (dv < divisor)
            {
                result.digits.insert(result.digits.begin(), '0');
            }
        }

        dv.cleanup();
        if (dv < divisor)
        {
            result.cleanup();
            return result;
        }

        // multiplying and subtracting
        LargeInteger quotient = one;
        LargeInteger save = quotient * divisor;

        while (save <= dv)
        {
            quotient = quotient + one;
            save = quotient * divisor;
        }

        quotient = quotient - one;
        save = quotient * divisor;
        dv = dv - save;

        for (auto& digit : quotient.digits)
        {
            result.digits.insert(result.digits.begin(), digit);
        }

        if (dv == 0)
        {
            dv.digits = {};
        }
    }

    result.cleanup();
    return result;
}

LargeInteger operator%(LargeInteger dividend, LargeInteger divisor)
{
    if (divisor.isNegative())
    {
        return dividend % divisor.abs();
    }

    if (dividend.isNegative())
    {
        LargeInteger result = dividend.abs() % divisor;
        result = divisor - result;
        return result;
    }

    LargeInteger zero(0);
    LargeInteger one(1);

    if (divisor == zero)
    {
        throw("Division by zero");
    }

    if (divisor > dividend)
    {
        return dividend;
    }

    if (dividend == divisor)
    {
        return zero;
    }

    int digit_pos = dividend.digitNum() - 1;

    // temporary/sub dividend
    LargeInteger dv;

    while (digit_pos >= 0)
    {
        // get as much as posible digit for sub-dividsend
        if (dv == 0)
        {
            dv.digits = {};
        }
        while (digit_pos >= 0 && (dv.isNull() || dv < divisor))
        {
            dv.digits.insert(dv.digits.begin(), dividend.digits[digit_pos--]);
        }
        dv.cleanup();

        if (dv < divisor)
        {
            return dv;
        }

        // multiplying and subtracting
        LargeInteger quotient = one;
        LargeInteger save = quotient * divisor;

        while (save <= dv)
        {
            quotient = quotient + one;
            save = quotient * divisor;
        }

        quotient = quotient - one;
        save = quotient * divisor;
        dv = dv - save;
    }

    return dv;
}

LargeInteger operator+(LargeInteger first, unsigned long long second)
{
    return first + LargeInteger(second);
}

LargeInteger operator-(LargeInteger first, unsigned long long second)
{
    return first - LargeInteger(second);
}

LargeInteger operator*(LargeInteger first, unsigned long long second)
{
    return first * LargeInteger(second);
}

LargeInteger operator/(LargeInteger first, unsigned long long second)
{
    return first / LargeInteger(second);
}

LargeInteger operator%(LargeInteger first, unsigned long long second)
{
    return first % LargeInteger(second);
}

LargeInteger operator+(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) + second;
}

LargeInteger operator-(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) - second;
}

LargeInteger operator*(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) * second;
}

LargeInteger operator/(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) / second;
}

LargeInteger operator%(unsigned long long first, LargeInteger second)
{
    return LargeInteger(first) % second;
}

// fast gcd using Stein's algorithm
LargeInteger gcd(LargeInteger a, LargeInteger b)
{
    // MARK: Special cases:
    // if the two are null, just null result
    if (a.isNull() || b.isNull())
        return LargeInteger();

    if (a == 0)
        return b;

    if (b == 0)
        return a;
    // MARK: End Special cases!

    // make sure a >=b in all cases
    if (b > a)
        return gcd(b, a);

    LargeInteger zero(0);
    LargeInteger two(2);
    LargeInteger g(1);

    LargeInteger t;

    while (a.isEven() && b.isEven())
    {
        a = a / two;
        b = b / two;
        g = g * two;
    }

    while (a > 0)
    {

        while (a.isEven())
        {
            a = a / two;
        }

        while (b.isEven())
        {
            b = b / two;
        }

        LargeInteger sub = (a > b) ? (a - b) : (b - a);
        t = sub / two;

        if (a >= b)
        {
            a = t;
        }
        else
        {
            b = t;
        }
    }

    g = g * b;

    return g;
}

LargeInteger pow(LargeInteger base, LargeInteger expo)
{
    LargeInteger result(1);

    while (expo > 0)
    {
        result = result * base;
        expo = expo - 1;
    }

    return result;
}

// calculate base^expo % mod
LargeInteger pow(LargeInteger base, LargeInteger expo, LargeInteger mod)
{
    LargeInteger zero(0);
    LargeInteger result(1);

    if (expo.isEven() == false)
    {
        result = base % mod;
    }

    while (expo != zero)
    {
        expo = expo / 2;
        base = (base * base) % mod;

        if (expo.isEven() == false)
        {
            result = (result * base) % mod;
        }
    }

    return result;
}


LargeInteger hexToDec(string hex) {
    LargeInteger dec = 0;
    int len = hex.length();
    LargeInteger index = 0;

    for (int i = 0; i < len; i++) {
        char hexDigit = hex[i];

        if (hexDigit >= '0' && hexDigit <= '9') {
            dec = dec + (hexDigit - '0') * pow(16, index);
        }
        else if (hexDigit >= 'A' && hexDigit <= 'F') {
            dec = dec + (hexDigit - 'A' + 10) * pow(16, index);
        }
        else if (hexDigit >= 'a' && hexDigit <= 'f') {
            dec = dec + (hexDigit - 'a' + 10) * pow(16, index);
        }
        index = index + 1;
    }

    return dec;
}

string decToHex(LargeInteger dec) {
    string hex = "";
    char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

    while (dec != 0) {
        LargeInteger remainder = dec % 16;
        string temp = remainder.to_str();
        int index = stoi(temp);
        hex = hex + hexDigits[index];
        dec = dec / 16;
    }

    return hex;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    ifstream input(argv[1]);
    ofstream output(argv[2]);

    /*ifstream input("test.inp");
    ofstream output("test.out");*/

    string line;
    getline(input, line);
    LargeInteger p = hexToDec(line);

    getline(input, line);
    LargeInteger n = hexToDec(line);

    getline(input, line);
    istringstream iss(line); // dung iss de phan tich gia tri
    vector<LargeInteger> U;
    while (iss >> line) {
        U.push_back(hexToDec(line));
    }
    LargeInteger u_size("0");
    for (int size = 0; size < (U.size()); size++) {
        u_size = u_size + LargeInteger("1");
    }
    getline(input, line);
    LargeInteger g = hexToDec(line);
    LargeInteger exponent = p - LargeInteger("1"); // exponent = p - 1
    int check = 1;
    for (int i = 0; i < U.size(); i++) {
        LargeInteger u_n = U[i];
        LargeInteger result = pow(g, exponent / u_n, p); // Chia exponent cho u_n
        if (result == LargeInteger("1")) {
            check = 0;
            break;
        }
    }
    if (check == 0) {
        output << "0" << endl; // g la can nguyen thuy
    }
    else {
        output << "1" << endl;
    }

    input.close();
    output.close();

    return 0;
}