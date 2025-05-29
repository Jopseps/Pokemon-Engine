#pragma once
#include <iostream>
using namespace std;

int CalculateStringLength(string a){
    return a.length();
}
int CalculateStringLength(int a){
    string stringBuffer = to_string(a);
    return stringBuffer.length();
}
char getArrowKey(){
    cout << "getArrowKey function called | DEBUG" << endl;
    if(getchar() == '\033'){ // if the first value is esc
        getchar(); // skip the [
        int value = getchar();
        fputs("\n",stdin);
        switch(value) { // the real value
            case 'A':
              cout << "Up" << endl;
                return 'w';
            case 'B':
            cout << "Down" << endl;
                return 's';
            case 'C':
            cout << "Right" << endl;
                return 'd';
            case 'D':
            cout << "Left" << endl;
                return 'a';
            default:
                cout << "Unknown key" << endl;
                return 0;
        }
    }
    if(getchar() == '\n') return '\n';
    else return 0;
}
