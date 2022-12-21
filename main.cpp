#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

using longInt = signed long long; // typedef so that I don't have to type signed long long int everywhere :)

// struct to calculate the t and u values in the question n - 1 = pow(2, t) * u
struct TU
{
    longInt t;
    longInt u;

    explicit TU(longInt n)
    {
        longInt count = 0;
        longInt  i = 0;
        longInt  temp = n;

        while(!((temp >> i) & 1))
        {
            count++;
            i++;
        }

        this->t = count;
        this->u = n >> this->t;
    }
};

/* This function is getting the input from the file and storing it in a vector. */
vector<longInt> getInput(const string &fileName)
{
    ifstream fin;
    longInt singleNum = 0;
    vector<longInt> numberList;

    // checks for correct input file
    fin.open(fileName);
    if (!fin.is_open()) {
        cout << "Enter a valid filename" << endl;
        exit(1);
    }

    // reads in the content of the input until -1 is reached
    int i = 0;
    while(singleNum != -1)
    {
        fin >> singleNum;
        if(singleNum != -1)
            numberList.push_back(singleNum);
        i++;
    }

    fin.close();
    return numberList;
}

/* Calculating `pow(a, u) % n` */
longInt power(longInt a, longInt u, longInt n)
{
    longInt ans = 1;
    a = a % n;

    while (u > 0)
    {
        if (u & 1)
            ans = (ans * a) % n;
        u = u >> 1;
        a = (a * a) % n;
    }
    return ans;
}

/* Checks if a random number is witness or not */
bool witness(longInt a, longInt n)
{
    TU tuFunc = TU(n - 1);

    longInt x, y;

    x = power(a, tuFunc.u, n);
//    y = power(a, tuFunc.u, n);

    for (int i = 1; i <= tuFunc.t; i++) {
        y = (x * x) % n;
        if (y == 1 && x != 1 && x != n - 1) {
            return true;
        }
        x = y;
    }
    if(x != 1)
    {
        return true;
    }
    return false;
}

bool isPrime(longInt n)
{
    if (n >= 2147483647)
    {
        return true;
    }

    if (n == 1)
    {
        return false;
    }

    if (n < 0)
    {
        return false;
    }

    longInt i = 2;
    while (i * i <= n)
    {
        if (n % i == 0)
        {
            return false;
        }
        i++;
    }
    return true;
}

/* Prints information into witness.out with the number of witness or if a number is prime */
string printInfo(longInt n, const string &fileName)
{
    longInt count = 0;

    if(isPrime(n))
    {
        return to_string(n).append(" is prime\n");
    }

    // if the witness function returns a false, increase the count by one
    for(longInt i = 2; i <= n - 2; i++)
    {
        if(!witness(i, n))
            count++;
    }

    // in the above loop, we are missing n = 0, 1, and n - 1. If we add those 3 to the count and get n, then n is a
    // prime number
    string strNum = to_string(n);
    if (count + 3 == n || n == 2)
    {
        return strNum.append(" is prime\n");
    }
    else
    {
        string strCount = to_string(count);
        return strNum.append(" ").append(strCount).append("\n");
    }
}

int main()
{
    vector<longInt> numberList;

    numberList = getInput("witness.in");

    ofstream fout;
    string fileName = "witness.out";
    fout.open(fileName);
    if(!fout.is_open())
    {
        cout << "Unable to open file for output." << endl;
        exit(1);
    }

    for (longInt n : numberList)
    {
        fout << printInfo(n, fileName);
    }

    fout.close();

    return 0;
}
