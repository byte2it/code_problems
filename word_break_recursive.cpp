
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool dictionary_contains(string word){
    vector<string> dict = { "mobile", "samsung", "sam",
        "sung", "man", "mango", "icecream", "and", 
        "go", "i", "like", "ice", "cream" 
    };
   
    for(auto& x : dict){
        if(x.compare(word) == 0)
            return true;
    }

    return false;
}

bool word_break(string w){
    cout << w << endl;
    int n = w.size();
    
    if(n == 0) return true;
    
    for(int i = 1; i <= n; ++i){
        if(dictionary_contains(w.substr(0, i))){
           if(word_break(w.substr(i, n-i)))
              return true;
        }
    }
    return false;
}

int main() {
     word_break("ilikesamsung")? cout <<"Yesn": cout << "Non";
    return 0;
}
