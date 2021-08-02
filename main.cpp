/*

Disclaimer - this file was never intended as a seriour project so it violates some programming design principles due to dev time restriction.
feel free to modify it.

Note - definition of "oddity" in complex numbers is a bit of a problematic topic. 
in this code i have chosen to define "even" as (even,even) and only it gets to the "/2 step". (odd,odd) , (odd,even) and (even_odd) are all getting "3n+1".

This code will receive 2 numbers and output the log to both cout and CSV. have fun and modify as you please!

*/

#include <iostream>
#include <string>
#include <fstream>




using namespace std;



enum class Oddity {even, odd_even, even_odd, odd_odd};

struct Pair{
    unsigned long long r;
    unsigned long long i;
    Pair(unsigned long long r=0, unsigned long long i=0) : r(r), i(i) {}
    
    Oddity getOddity()
    {
        return 
        r%2==1 ?  //odd real?
            (i%2==1 ? Oddity::odd_odd : Oddity::odd_even) //odd imaginary?
            :
            (i%2==1 ? Oddity::even_odd : Oddity::even) //odd imaginary?
            ;
    }

    static string oddityToString(Oddity o)
    {
        switch(o)
        {
            case Oddity::even:
                return "even    ";
            case Oddity::odd_even:
                return "odd_even";
            case Oddity::even_odd:
                return "even_odd";
            case Oddity::odd_odd:
                return "odd_odd ";
        }
        return "even"; //shouldnt happen
    }

    string getString(){
        Oddity o = getOddity();
        return "[" + oddityToString(o) + "] (" + to_string(r) + "," + to_string(i) + ")" ;
    }
};

Pair operator+(const Pair& a, const Pair& b)
{
    return Pair(a.r + b.r, a.i + b.i);
}

Pair operator+(const Pair& p, unsigned long long x)
{
    return Pair(p.r + x, p.i);
}
Pair operator*(const Pair& p, unsigned long long x)
{
    return Pair(p.r * x, p.i * x);
}

Pair operator/(const Pair& p, unsigned long long x)
{
    return Pair(p.r / x, p.i / x);
}
bool operator==(const Pair& a, const Pair& b)
{
    return a.r==b.r && a.i==b.i;
}


struct OddityCounter
{
    int even_c = 0;
    int odd_odd_c = 0;
    int even_odd_c = 0;
    int odd_even_c = 0;
    void reg(Oddity o){
        switch(o)
        {
            case Oddity::even:
                even_c++ ; return;
            case Oddity::odd_even:
                odd_even_c++ ; return;
            case Oddity::even_odd:
                even_odd_c++ ; return;
            case Oddity::odd_odd:
                odd_odd_c++ ; return;
        }
    }
    string getString(){
        return 
        "Even -> " + to_string(even_c) + "\n"
        +
        "Odd Even -> " + to_string(odd_even_c) + "\n"
        +
        "Even Odd -> " + to_string(even_odd_c) + "\n"
        +
        "Odd Odd -> " + to_string(odd_odd_c) + "\n\n";
    }
};



int main(int argc, char* argv[])
{
    if(argc!=3){
        cout << "supply 2 numbers" << endl;
        return -1;
    }

    Pair p;
   

    string arg1 = argv[1];
    string arg2 = argv[2];
    size_t pos;
    p.r = stoll(arg1, &pos);
    p.i = stoll(arg2, &pos);

    std::ofstream file(to_string(p.r) + "_" + to_string(p.i) + ".csv");
    file << "Real, Imaginary \n";

    cout << "original pair  = " << p.getString() << endl;

    constexpr int MAX_ATTEMPTS=5000;
    int i=1;
    OddityCounter counter;

    file << to_string(p.r) << "," << to_string(p.i) << endl;

    for(i; i<=MAX_ATTEMPTS; i++){
        auto o = p.getOddity();
        counter.reg(o);

        cout << "step" << i << "\t{";
        if(o==Oddity::even){
            p = p/2;
            cout << "down";
        }else{
            p = p*3 + 1;
            cout << " up ";
        }
        file << to_string(p.r) << "," << to_string(p.i) << endl;
        cout << "}" << " = " << p.getString() << endl;

        if(p==Pair{1,0}){break;}
    }

    if (i-1==MAX_ATTEMPTS){
        cout << "\nDIVERGENT after "<<i-1 <<" steps" << endl;
    }else{
        cout << "\nFINITE after "<<i-1 <<" steps" << endl;
    }
    cout << counter.getString();
    
    cout << endl;

    
    file.close();
    return 0;
}
