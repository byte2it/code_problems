/* 
 * File:   main.cpp
 * Author: dolphinden
 *
 * Created on August 25, 2017, 12:24 PM
 */

#include <cstdlib>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
/*
 
 "Chennai" -> "Banglore"
"Bombay" -> "Delhi"
"Goa"    -> "Chennai"
"Delhi"  -> "Goa"
 
 */
using namespace std;

int main(int argc, char** argv) {
    
    string response;
    unordered_map<string, string> order;
    unordered_set<string> reverse;

    while(true) {
        if(response == "get")
            break;
    
        getline(cin, response);
        int pos = string::npos;
        pos = response.find("->");
        if(pos != string::npos){
            string sL = response.substr(0, pos-1);
            string sR = response.substr(pos+3);
            order.emplace(sL, sR);
            reverse.emplace(sR);
        }
    }

    auto it = order.begin();
    string start = "";
    for(; it != order.end(); ++it){
        if(reverse.find(it->first) == reverse.end()){
            start = it->first;
            cout << " start point is : " << it->first << endl;
            break;
        }
    }
    
    cout << it->first << " -> " << it->second << endl;
    
    while(true){
        it = order.find(it->second);
        if(it == order.end())
            break;
        
        cout << it->first << " -> " << it->second << endl;            
    }

    return 0;
}

