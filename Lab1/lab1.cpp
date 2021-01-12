#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function
#include <vector>
using namespace std;

int main()
{
    int count;
    vector<float>numbers;
    cout << "Enter the numbers:";
    cin >> count;
    float sum;
    for(int i =0; i<count; i++)
    {
        float number;
        cin >> number;
        numbers.push_back(number);
    }
    
    for(int i =0; i<numbers.size(); i++)
    {
        sum += numbers[i];
    }
    
    float average;
    average = sum/numbers.size();
    cout << average << endl;
    for(float a: numbers)
    {
        if(a<average)
        {
            cout << a << ",";
        }
    }
}
