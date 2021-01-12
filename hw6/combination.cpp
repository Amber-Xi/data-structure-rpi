#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

/*
void swap(int &a, int &b) 
{
	int temp = a;
	a = b;
	b = temp;
}


void Permutation(vector<char> str, int index, int m, int size) {
	if (index == m) {  //和本文第一个程序比只是这里打印时不太相同
		for (int i = 0; i < m; i++)
			cout << str[i];
		cout << "\n";
	}
	else {
		for (int i = index; i < size; i++) {
			swap(str[index], str[i]);
			Permutation(str, index + 1, m, size);
			swap(str[index], str[i]);
		}
	}
}




void combinationUtil(vector<char> arr, vector<vector<char> v>& b,  
                    int start, int end, 
                    int index, int r)
{
    b[index].push_back(arr[start]);
    b[index].push_back(arr[start+1]);


    


}  


void printCombination(vector<vector<char> > arr, int n, int r)  
{  
    vector<char> data;  
  
    combinationUtil(arr, data, 0, n-1, 0, r);

    return data;
} 



int main()
{
	vector<char> arr;
    a.push_back('a');
    a.push_back('b');
    a.push_back('c');
    arr.push_back(a);

    vector<vector<vector<char> > > nmsl;
    nmsl = printCombination(arr, arr.size(), 1);
    for (int j = 0; j < nmsl.size(); j++)
    {
        cout << '+' ;
        for(int a = 0; a<nmsl[j].size(); a++)
            {
                cout << nmsl[j][a][0]; 
            }
         cout << '+' << endl;

    }

    int arr[] = {1, 2, 3, 4, 5};  
    int r = 3;  
    int n = sizeof(arr)/sizeof(arr[0]);  
    printCombination(arr, n, r);
*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string>& combination (vector<string>& res, const size_t& choose, string& working, const size_t& pos);

int main () 
{
  vector<string> res;
  const size_t choose = 3;
  string working (5, '0');
  combination (res, choose, working, 0);
  for (size_t i = 0; i != res.size(); ++i) 
  {
    cout << res[i] << '\t';
    cout << endl;
  }
  return 0;
}

vector<string>& combination (vector<string>& res, const size_t& choose, string& working, const size_t& pos) {
  if (choose > working.size() - pos) return res;
  for (size_t i = pos; i != working.size(); ++i) {
    working[i] = '0';
  }
  if (choose == 0 || pos == working.size()) {
    res.push_back (working);
    return res;
  }
  working[pos] = '1';
  combination (res, choose - 1, working, pos + 1);
  working[pos] = '0';
  combination (res, choose, working, pos + 1);
  return res;
}


