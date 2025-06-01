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
    int ch = getchar();
    if(ch == 27){ // if the first value is ESC (ASCII 27)
        getchar(); // skip the [
        int value = getchar();
        cout << "DEBUG | Entered value is: " << value << endl;
        switch(value) { // compare to ASCII codes
            case 65: // 'A'
                cout << "Up" << endl;
                return 'w';
            case 66: // 'B'
                cout << "Down" << endl;
                return 's';
            case 67: // 'C'
                cout << "Right" << endl;
                return 'd';
            case 68: // 'D'
                cout << "Left" << endl;
                return 'a';
            default:
                cout << "Unknown key" << endl;
                return (char)value;
        }
    }
    if(ch == '\n'){
        return '\n';   
    }
    if(ch == 'y' || ch == 'Y'){
        return 'y';
    }
    else {
        return (char)ch;
    }
}


/*char getArrowKey(){
    cout << "getArrowKey function called | DEBUG" << endl;
    int ch = getchar();
    if(ch == '\033'){ // if the first value is esc
        getchar(); // skip the [
        int value = getchar();
        cout << "DEBUG | Entered value is: " << value << endl;
        switch(value) { // the real value new
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
                return value;
        }
    } else if(ch == '\n'){
        return '\n';   
    }else if(ch == 'y' || ch == 'Y'){
        return 'y';
    
    }
    else {
        return ch;
    }
}
*/
