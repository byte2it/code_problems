#include <iostream>
using namespace std;

struct dict
{
    string w;
    int c;
};

// To execute C++, please define "int main()"
bool findwords(string str, dict d[], string& words)
{
    if (str.length() == 0)
        return true;
    else
        for (int wo = 0; wo <  3; wo++)
        {
            int d_length = d[wo].w.length();

            if (str.substr(0, d_length) == d[wo].w)
            {
                if (findwords(str.substr(d_length, str.length()), d, words))
                {

                    d[wo].c--;
                    if (d[wo].c >= 0)
                    {
                        words = d[wo].w + " " + words;
                        return true;
                    }
                }
            }
        }
    return false;
}

int main() {

    dict d[3];

    d[0].w = "abc";
    d[1].w = "ab";
    d[2].w = "abca";

    d[0].c = 3;
    d[1].c = 2;
    d[2].c = 1;
    string words;


    string str2("abcabcabcabca");

    if (findwords(str2, d, words))
        cout << "True" << " " << words << endl;
    else
        cout << "No Words Found" << endl;

    /*if (findwords("abcaababcab", d, words))
        cout << "True" << " " << words << endl;
    else
        cout << "No Words Found" << endl;*/



    //cout<<words<<endl;




    return 0;
}
