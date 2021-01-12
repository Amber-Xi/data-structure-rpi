#include <iostream>
#include <fstream>
#include <string>
#include <map>

int main (int argc, char** argv){
    //assert (argc == 2);
    std::ifstream in_file(argv[1]);

    std::map<int, int> modes;

    string s;
    while(in_file >> s)
    {
        ++modes[s];
    }

    /*
    int x;
    while (in_file >> x){
        int new_val = 1;

        if (modes.count(x)){        
            std::map<int, int>::iterator it = modes.find(x);
            new_val = it->second+1;
            modes.erase(it);
        }
   
        modes.insert(std::pair<int, int>(x, new_val));
    }
    */

    int max = 0;
    
    std::cout << "Map contains" << std::endl;
    for (std::map<int, int>::iterator it = modes.begin(); it != modes.end(); it++){
        std::cout << "  " << it->second << " instance(s) of the number " << it->first
                  << std::endl;
        if (it->second > max)
            max = it->second;
    }

    std::cout << "The modes are" << std::endl;
    for (std::map<int, int>::iterator it = modes.begin(); it != modes.end(); it++){
        if (it->second == max){
            std::cout << "  " << it->first << std::endl;
        }
    }
    
    
}