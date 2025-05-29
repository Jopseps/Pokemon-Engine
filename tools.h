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
