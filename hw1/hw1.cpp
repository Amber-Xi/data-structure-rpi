#include <iostream>
#include <fstream>
#include<vector>
#include<cstring>

using namespace std;
std::vector<std::string> replace(std::vector<std::string> string_list,char s,char a);
std::vector<std::string> dilation(std::vector<std::string> string_list,char s);
std::vector<std::string> erosion(std::vector<std::string> string_list,char s,char x);

/*
 This function is for replace all the pointed char
 */
vector<string> replace(vector<string> string_list,char s,char a)
{
    for(int i=0;i<string_list.size(); i++)
    {
        for(int j=0; j<string_list[i].size(); j++)
        {
            if(string_list[i][j] == s)
            {
                string_list[i][j] = a;
            }
        }
    }
    return string_list;
}

/*
 This is for adding pixels along the boundary to expand or grow a cluster.
 */
vector<string> dilation(vector<string> string_list,char s)
{
    vector<string> a = string_list;
    for(int i=0;i<string_list.size(); i++)
    {
        for(int j=0; j<string_list[i].size(); j++)
        {
            if(a[i][j] == s)
            {
                // Checking the boundry
                if(i == 0 && j == 0)
                {
                    string_list[i+1][j] = s; string_list[i][j+1] = s;
                }
                else if(i == 0 && j == string_list[i].size()-1)
                {
                    string_list[i][j-1] = s;string_list[i+1][j] = s;
                }
                else if(i == string_list.size()-1 && j == string_list[i].size()-1)
                {
                    string_list[i-1][j] = s;string_list[i][j-1] = s;
                }
                else if (j == 0 && i == string_list.size()-1)
                {
                    string_list[i-1][j] = s;string_list[i][j+1] = s;
                }
                else if(i == 0)
                {
                    string_list[i+1][j] = s; string_list[i][j-1] = s; string_list[i][j+1] = s;
                }
                else if(j == 0)
                {
                    string_list[i][j+1] = s; string_list[i+1][j] = s; string_list[i-1][j] = s;
                }
                else if(i == string_list.size()-1)
                {
                    string_list[i-1][j] = s;string_list[i][j-1] = s;string_list[i][j+1] = s;
                }
                else if(j == string_list[i].size()-1)
                {
                    string_list[i+1][j] = s; string_list[i-1][j] = s; string_list[i][j-1] = s;
                }
                else
                {
                    string_list[i+1][j] = s;
                    string_list[i-1][j] = s;
                    string_list[i][j-1] = s;
                    string_list[i][j+1] = s;
                }
            }
        }
    }
    return string_list;
}

/*
 This function is for shrinking the boundary of the cluster by reassigning pixels along the boundary to a background color.
 */
vector<string> erosion(vector<string> string_list,char s,char x)
{
    vector<string> a = string_list;
    for(int i=0;i<string_list.size(); i++)
    {
        for(int j=0; j<string_list[i].size(); j++)
        {
            if(a[i][j] == x)
                {
                    // Checking the boundry
                    if(i == 0 && j == 0)
                    {
                        string_list[i+1][j] = x; string_list[i][j+1] = x;
                    }
                    else if(i == 0 && j == string_list[i].size()-1)
                    {
                        string_list[i][j-1] = x;string_list[i+1][j] = x;
                    }
                    else if(i == string_list.size()-1 && j == string_list[i].size()-1)
                    {
                        string_list[i-1][j] = x;string_list[i][j-1] = x;
                    }
                    else if (j == 0 && i == string_list.size()-1)
                    {
                        string_list[i-1][j] = x;string_list[i][j+1] = x;
                    }
                    else if(i == 0)
                    {
                        string_list[i+1][j] = x; string_list[i][j-1] = x; string_list[i][j+1] = x;
                    }
                    else if(j == 0)
                    {
                        string_list[i][j+1] = x; string_list[i+1][j] = x; string_list[i-1][j] = x;
                    }
                    else if(i == string_list.size()-1)
                    {
                        string_list[i-1][j] = x;string_list[i][j-1] = x;string_list[i][j+1] = x;
                    }
                    else if(j == string_list[i].size()-1)
                    {
                        string_list[i+1][j] = x; string_list[i-1][j] = x; string_list[i][j-1] = x;
                    }
                    else
                    {
                        string_list[i+1][j] = x;
                        string_list[i-1][j] = x;
                        string_list[i][j-1] = x;
                        string_list[i][j+1] = x;
                    }
                }
        }
    }
    return string_list;
}


int main(int argc, char *argv[])
{
    //
    ifstream filein(argv[1]);
    ofstream fileout(argv[2]);
    vector<string> all_string;
    
    while(!filein.eof())
    {
        string word;
        filein >> word;
        all_string.push_back(word);
    }
    
    // Do the action if the commend is "replace".
    if(strcmp(argv[3],"replace")==0)
       {
           vector<string> tmp = replace(all_string,argv[4][0], argv[5][0]);
           for (int i = 0; i < tmp.size(); i++)
           {
               if(i == tmp.size()-1)
               {
                   fileout << tmp[i];
               }
               else
               {
                   fileout << tmp[i] << endl;
               }
           }
       }
    // Do the action if the commend is "dilation".
    else if(strcmp(argv[3],"dilation")==0)
       {
           vector<string> tmp = dilation(all_string,argv[4][0]);
           for (int i = 0; i < tmp.size(); i++)
           {
               if(i == tmp.size()-1)
               {
                   fileout << tmp[i];
               }
               else
               {
                   fileout << tmp[i] << endl;
               }
           }
       }
    // Do the action if the commend is "erosion".
    else if(strcmp(argv[3],"erosion")==0)
       {
           vector<string> tmp = erosion(all_string,argv[4][0], argv[5][0]);
           for (int i = 0; i < tmp.size(); i++)
           {
               if(i == tmp.size()-1)
               {
                   fileout << tmp[i];
               }
               else
               {
                   fileout << tmp[i] << endl;
               }
           }
       }
    return 0;
}
