#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
using namespace std;

//class for the point on the board
class Point 
{ 

private: 
    int x, y; 
  
public:

	//constructor 
    Point(int x1, int y1) 
    { 
        x = x1; 
        y = y1; 
    } 

    //accessor
    int getX() 
    {return x;}

    int getY() 
    {return y;} 
}; 

// class for each word and its corresponding positions
class word_point
{
private:
	string name;
	vector<Point> pos;
public:
	word_point(string name_,vector<Point> pos_)
	{
		name = name_;
		for(int i = 0; i < pos_.size(); i++)
		{
			pos.push_back(pos_[i]);
		}
	}

	string get_name()
	{return name;}

	vector<Point> get_pos()
	{
		return pos;
	}
};

void find_word_across_re(const vector<string> board, string s, vector<word_point>& all_words)
{
	int i=0,j=0,z=0,count = 0;
	int row = board.size();
	int col = board[0].size();

	vector<Point> vec;
	while(i < row)
	{
		while(j < col)
		{
			if(board[i][j] == s[z])
			{
				Point p(i, j);
				vec.push_back(p);
				//cout << vec.size() << endl;
				j++;
				count ++;
				z++;
			}
			
			else
			{
				j++;
				count = 0;
				z=0;
				vec.clear();
			}
			
			if(count == s.size())
			{
				word_point w(s, vec);
				all_words.push_back(w);
				vec.clear();
				z =0;
				count = 0;
			}
		}
		i++;
		j = 0;
	}

}

void find_word_down_re(const vector<string> board, string s, vector<word_point>& all_words)
{
	int i=0,j=0,z=0,count = 0;
	int row = board.size();
	int col = board[0].size();

	vector<Point> vec;
	while(i < col)
	{
		while(j < row)
		{
			if(board[j][i] == s[z])
			{
				Point p(j, i);
				vec.push_back(p);
				//cout << vec.size() << endl;
				j++;
				count ++;
				z++;
			}
			
			else
			{
				j++;
				count = 0;
				z=0;
				vec.clear();
			}
			
			if(count == s.size())
			{
				word_point w(s, vec);
				all_words.push_back(w);
				vec.clear();
				z =0;
				count = 0;
			}
		}
		i++;
		j = 0;
	}

}

bool find_word_across(vector<string> board, string s, vector<Point>& vec)
{
	/*
	finding the words in the dictionary whether in the board in the across way
	*/

	for(int i = 0; i< board.size(); i++)
	{
		if(board[i].find(s) != string::npos)
		{
			int index = board[i].find(s);
			for(int j = index; j < s.size()+index; j++)
			{
				Point p(i, j);
				vec.push_back(p);
			}
			return true;
		}
	}
	return false;
}



bool find_word_down(vector<string> board, string s, vector<Point>& vec)
{
	/*
	finding the words in the dictionary whether in the board in the down way
	*/
	int i=0,j=0,z=0,count = 0;
	int row = board.size();
	int col = board[0].size();

	while(i < col)
	{
		while(j < row)
		{
			if(board[j][i] == s[z])
			{
				Point p(j, i);
				vec.push_back(p);
				//cout << vec.size() << endl;
				j++;
				count ++;
				z++;
			}
			
			else
			{
				j++;
				count = 0;
				z=0;
				vec.clear();
			}
			
			if(count == s.size())
			{
				return true;
			}
		}
		i++;
		j = 0;
	}

	return false;
}

bool check(const vector<string>& dic, string p)
{
	/*
	checking the word whether in the string vector
	*/
	for(int i = 0; i< dic.size(); i++)
	{
		if(dic[i] == p)
		{
			return true;
		}
	}
	return false;

}


vector<string> find_unique(const vector<string>& dic, vector<word_point> possible_solution)
{
	/*
	finding out the words not in the one solution, but in the dictionary word
	*/
	vector<string> unique;
	vector<string> possible_solution_name;
	for(int i =0; i< possible_solution.size(); i++)
	{
		possible_solution_name.push_back(possible_solution[i].get_name());
	}

	// checking each word, and getting the words not in solution words but in the dictionary
	for(int i = 0; i< dic.size(); i++)
	{
		if(check(possible_solution_name, dic[i]) == false)
		{
			//cout << dic[i] <<  "{}"<<endl;
			unique.push_back(dic[i]);
		}
	}
	//cout << "**********" << endl;
	return unique;
}


bool check_ok(const vector<string>& dic, vector<word_point> possible_solution_, vector<string> solution_board)
{
	/*
	checking the board doesn't have the word which is not in the solution vector
	*/
	vector<string> v;
	vector<Point> no_use;

	v = find_unique(dic, possible_solution_);
	for(int i =0; i< v.size(); i++)
	{

		// if the word can be found in the solution board in either the across or down way, this board cann't be the solution
		if(find_word_across(solution_board, v[i], no_use)||find_word_down(solution_board, v[i], no_use))
		{
			return false;
		}
	}
	return true ;
}


bool check_ok_row(vector<string> solution_board, vector<string> dic)
{
	/*
	checking each row doesn't have the word which is not in the solution vector
	*/

	// putting the words of one solution in the vector

	for(int i =0; i< solution_board.size(); i++)
	{
		string a = "";
		int j =0;
		while(j < solution_board[i].size())
		{
			if(solution_board[i][j] != '#')
			{
				a += solution_board[i][j];
			}
			
            else 
            {
            	if(a.size() <= 1) {
            		j++;
            		continue;
			    }
		        if (!check(dic, a)) 
		        {
		        	return false;
		        }
		        a = "";
			}
		
			j++;

		}


		/*
		if(solution_board[i].find('#') != string::npos)
		{
			for(int j = solution_board[i].find('#')+1; j< solution_board[i].size(); j++)
			{	
				if(solution_board[i][j] != '#')
				{
					a += solution_board[i][j];
				}
				else
				{
					// if meeting the '#', there will be one word, and then checking this word
					break;
				}
			}

			// if this word doesn't in the solution, and size is greater or equal to 2, this board is not the solution
			if(!check(dic, a) && a.size() >= 2)
			{
				return  false;
			}
		}
		else
		{
			a = solution_board[i];
			if(!check(dic, a) && a.size() >= 2)
			{
				return false;
			}
		}

		*/
	}
	return true;
}


//vector<string > reverse(vector<string> solution_board)
//{
	/*
	justing reverse the board and checking each column 
	*/
	//int row = solution_board.size();
	//int col = solution_board[0].size();
	//vector<string> reverse;
	//for(int i =0; i< col; i++)
	//{
		//string a = "";
		//for(int j = 0; j< row; j++)
		//{	
			//a += solution_board[j][i];
		//}
		//reverse.push_back(a);
	//}
	//return reverse;
//}

vector<string>& combination(vector<string>& res, const size_t& choose, string& working, const size_t& pos) 
{
	/*
	using the binary to checking the combination of solutinos given by the specific length
	*/
 	if (choose > working.size() - pos) return res;
	for (size_t i = pos; i != working.size(); ++i) 
  	{
    	working[i] = '0';
  	}
  	if (choose == 0 || pos == working.size()) 
  	{
    	res.push_back (working);
    	return res;
  	}
  	working[pos] = '1';
  	combination (res, choose - 1, working, pos + 1);
  	working[pos] = '0';
  	combination (res, choose, working, pos + 1);
  	return res;
}


vector<word_point> find_length(vector<word_point> v, int r)
{
	/*
	finding the length of constains we want to combine
	*/
	vector<word_point> new_v;

	for(int i = 0; i<v.size(); i++)
	{
		if((v[i].get_pos()).size() == r)
		{
			new_v.push_back(v[i]);
		}
	}
	return new_v;
}


vector<vector<word_point> > Combination(vector<vector<vector<word_point> > > superVec)  
{  
	/*
	Doing the combination to get all the possible solutions
	*/
	vector<vector<word_point> > total_solution;
    for (unsigned int i = 0; i < superVec[0].size(); i++)
        total_solution.push_back(superVec[0][i]);
    
    for (unsigned int i = 1; i < superVec.size(); i++)
    {
        int old_size = total_solution.size();
        for (unsigned int j = 0; j + 1 < superVec[i].size(); j++)
        {
 
            for (unsigned int z = 0; z < old_size; z++)
            {
                total_solution.push_back(total_solution[z]);
            }
        }
        
        for (unsigned int j = 0; j < total_solution.size(); j++)
        {
            int index = j % (superVec[i].size());
            for (unsigned int z = 0; z < superVec[i][index].size(); z++)
            {
                total_solution[j].push_back(superVec[i][index][z]);
            }
        }
    }
    
    
    return total_solution;
}

vector<string> fill_board(vector<word_point> vec, vector<string> board)
{
	/*
	filling the original board with one solution which are all the '#'
	*/
	vector<string> b = board;
	for(int i = 0; i< vec.size(); i++)
	{
		vector<Point> position_list = vec[i].get_pos();
		string position_string = vec[i].get_name();

		//by using each word's index and filling the baord with each word's char
		for(int j =0; j < position_list.size(); j++)
		{
			b[position_list[j].getX()][position_list[j].getY()] = position_string[j];
		}
	}
	return b;
}

vector<string> creat_board(vector<string> board)
{
	/*
	creating the board with all the '#'
	*/
	vector<string> b;
	int row = board.size();
	int col = board[0].size();
	for(int i = 0; i< row; i++)
	{
		string a = string(col, ' ');
		b.push_back(a);
		for(int j =0; j < col; j++)
		{
			b[i][j] = '#';
		}
	}
	return b;
}


int main(int argc, char *argv[])
{
	ifstream filein(argv[2]);
	ifstream dicin(argv[1]);

	int num_across = 0;

	vector<string> board;
	vector<string> file;
	vector<int> constaints;
	vector<string> dic;

	//put the value I need in the vector
	if(filein.is_open())
	{
		string line;
		while(getline(filein, line))
		{
			//for all lines
			file.push_back(line);

			//for the board
			if(line[0] != '!'&& line[0] != '+')
			{
				board.push_back(line);
			}
			
			//for the constaints
			if(line[0] == '+')
			{
				constaints.push_back(stoi(line.substr(1,line.size()-1)));
			}
		}
	}

	// Put the dicntionary words in the vector
	if(dicin.is_open())
	{
		string word;
		while(dicin >> word)
		{
			dic.push_back(word);
		}
	}

	//Finding out the number of across solutions
	vector<word_point > all_words; 
	int pos = 0;
	int i =0;
	
	for(int i =0; i< dic.size(); i++)
	{
		find_word_across_re(board, dic[i], all_words);
		find_word_down_re(board, dic[i], all_words);
	}
	
	/*
	vector<word_point > down; 
	for(int i =0; i< dic.size(); i++)
	{
		vector<Point> vec; 
		if(find_word_down(board, dic[i], vec))
		{
			down.push_back(word_point(dic[i],vec));			
		}

	}
	*/

	
	for(int a = 0; a < all_words.size(); a++)
	{
		cout << '{';
		cout << all_words[a].get_name() << "\\";
		vector<Point> v = all_words[a].get_pos();
		for(int i = 0; i < v.size(); i++)
		{
			cout << v[i].getX() << ", " << v[i].getY() << "||";
		}
		cout << '}' << endl;
	}
	

	cout<<"==================="<<endl;



	vector<int> find_repreated (100, 0);
	for(int i = 0; i< constaints.size(); i++)
	{
		find_repreated[constaints[i]]++;
	}
	/*
	for(int i = 0; i< find_repreated.size(); i++)
	{
		cout << find_repreated[i] << endl;

	}
	*/



	vector<vector<vector<word_point> > > all_solution;
	int first = 0;
	for(int i = 1; i< find_repreated.size(); i++)
	{

		if(find_repreated[i] != 0)
		{
			vector<word_point> new_one = find_length(all_words, i);
			//cout << new_one.size() << endl;
			const size_t choose = find_repreated[i];
			string working (new_one.size(), '0');
			vector<string> binary_solution;
			vector<vector<word_point> > solution;
			combination(binary_solution, choose, working, 0);
			//cout << 'b' << endl;
			//for(int g = 0; g < binary_solution.size(); g++)
			//{
				//cout << binary_solution[g] << endl;
			//}
			for(int k = 0; k <binary_solution.size(); k++)
			{
				vector<word_point> mini;
				for(int j = 0; j < binary_solution[k].size(); j++)
				{
					if(binary_solution[k][j] == '1')
					{
						//cout <<  new_one[j].get_name() << xsndl;
				 		mini.push_back(new_one[j]);
	
					}
				}
				//for(int g =0; g< mini.size(); g++)
				//{
					//cout << mini[g].get_name();
				//}
				solution.push_back(mini);
				//cout << mini.size() << endl;

				//cout << "times" << endl;
			}
			all_solution.push_back(solution);
			//cout << 'a' << endl;
		}
	}


	vector<string> copy_board = creat_board(board);
	for(int i =0; i<copy_board.size(); i++)
	{
		for(int j =0; j< copy_board[i].size(); j++)
		{
			cout << copy_board[i][j];
		}
			
	}
		

	//cout << all_solution.size() << endl;



	vector<vector<word_point> > c_solutions = Combination(all_solution);

	
	cout << c_solutions.size() << endl;
	for(int i =0; i< c_solutions.size(); i++)
	{
		cout << "{";
		for(int j =0; j< c_solutions[i].size(); j++)
		{
			cout << c_solutions[i][j].get_name()<< "&";
		}
		cout << "}" << endl;
	}


	cout << "@@@@@@@@@2@@" << endl;
	
	string solution_mode = argv[3];
	string print = argv[4];

	int c_solutions_count = 0;
	int count = 0;
	
	
	while(c_solutions_count < c_solutions.size())
	{
		vector<string> copy_board = creat_board(board);
		copy_board = fill_board(c_solutions[c_solutions_count], copy_board);
		//vector<string> reverse_copy_board = reverse(copy_board);
		if(check_ok(dic, c_solutions[c_solutions_count],copy_board) && check_ok_row(copy_board,dic))
		{
			count++;
		}
		c_solutions_count++;
	
	}
	


	if(solution_mode == "all_solutions" && print == "print_boards")
	{
		cout << "Number of solution(s): "<< count << endl; 
		for(int i = 0; i < c_solutions.size(); i++)
		{
			vector<string> copy_board = creat_board(board);
			copy_board = fill_board(c_solutions[i], copy_board);
			//vector<string> reverse_copy_board = reverse(copy_board);
			if(check_ok(dic, c_solutions[i],copy_board) && check_ok_row(copy_board,dic))
			{
				cout << "Board:" << endl;
				for(int i =0; i<copy_board.size(); i++)
				{
					for(int j =0; j< copy_board[i].size(); j++)
					{
						cout << copy_board[i][j];
						if(j == copy_board[i].size()-1)
						{
							cout << endl;
						}
					}
				}
			}
		}
	}
	
	
	if(solution_mode == "one_solution" && print == "print_boards")
	{
		if(count == 0)
		{
			cout << "Number of solution(s): "<< 0 << endl;
		}
		if(count >0)
		{
			cout << "Number of solution(s): "<< 1 << endl;
			cout << "Board:" << endl;
			vector<string> copy_board = creat_board(board);
			copy_board = fill_board(c_solutions[0], copy_board);

			for(int i =0; i<copy_board.size(); i++)
			{
				for(int j =0; j< copy_board[i].size(); j++)
				{
					cout << copy_board[i][j];
					if(j == copy_board[i].size()-1)
					{
						cout << endl;
					}    
				}
			}
		}
	}
	
}