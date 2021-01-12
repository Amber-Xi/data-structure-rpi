#include <iostream>
#include <fstream>
#include<vector>
#include<cstring>
using namespace std;
vector<int> slice(vector<int> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;

    std::vector<int> vec(first, last);
    return vec;
}



int main()
{

	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	v.push_back(6);
	v.push_back(7);
	v.push_back(8);
	vector<int> vec = slice(v, 1, 4);
	cout << vec[0] << endl;
	string a;
	cin >> a;
	cout << "dlcne" << std::endl;

}