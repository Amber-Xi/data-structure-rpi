#include <iostream>
#include <fstream>
#include<vector>
#include<cstring>
#include <cassert>
#include <math.h>
#include <map>
#define movieBook_size 100
#define occupancy_level 0.5

//Bulinding a class Node
class Node
{
public:
	//putting in the movie informations
	std::string title;
	std::string year;
	std::string runTime;
	std::vector<std::string> genreList;
	std::vector<std::string> actorlist;
	std::vector<std::string> roleList;
	Node* next;

	Node();
	Node(std::string& t, std::string& y, std::string& r, std::vector<std::string>& genre, std::vector<std::string>& actor, std::vector<std::string>& role);
	bool hash_year(Node* n);
	bool hash_runTime(Node* n);
	bool hash_genreList(Node* n);
	bool hash_actorlist(Node* n);
	bool hash_roleList(Node* n);

};

Node::Node()
{
	/*
	The Node constructor
	*/
	title = "  ";
	year = "  ";
	runTime = "  ";

}
Node::Node(std::string& t, std::string& y, std::string& r, std::vector<std::string>& genre, std::vector<std::string>& actor, std::vector<std::string>& role)
{
	/*
	The Node constructor
	*/
	title = t;
	year = y;
	runTime = r;
	next = NULL;
	for(int i = 0; i < genre.size(); i++)
	{
		genreList.push_back(genre[i]);
	}

	for(int i = 0; i < actor.size(); i++)
	{
		actorlist.push_back(actor[i]);
	}
	for(int i = 0; i < role.size(); i++)
	{
		roleList.push_back(role[i]);
	}

}


int hash_title(std::string key, std::vector<Node*> movieBook)
{
	//according to the movie title to hash
	for(int i =0; i< movieBook.size(); i++)
	{
		//
		if(movieBook[i]->title == key)
		{
			return i;
		}
		
		if(movieBook[i]->title == "  ")
		{
			//empty position
			return i;
		}
	}
	return 0;
}

bool Node::hash_year(Node* n)
{
	// just hash the year
	if(n->year == "?")
	{
		return true;
	}
	return this->year == n->year;
}

bool Node::hash_runTime(Node* n)
{
	//just hash the runTime
	if(n->runTime == "?")
	{
		return true;
	}
	return this->runTime == n->runTime;
}

bool Node::hash_genreList(Node* n)
{
	//just hash the genreList
	if((n->genreList).size() ==0)
	{
		return true;
	}
	std::vector<std::string> genre = this->genreList;
	for(int i = 0; i< genre.size(); i++)
	{
		if(genre[i] != n->genreList[i])
		{
			return false;
		}
	}
	return true;
}

bool Node::hash_actorlist(Node* n)
{
	//just hash the actorlist
	if((n->actorlist).size() ==0)
	{
		return true;
	}
	std::vector<std::string> actor = this->actorlist;
	for(int i = 0; i< actor.size(); i++)
	{
		if(actor[i] != n->actorlist[i])
		{
			return false;
		}
	}
	return true;
}

bool Node::hash_roleList(Node* n)
{
	//just hash the roleList
	if((n->roleList).size() ==0)
	{
		return true;
	}
	std::vector<std::string> role = this->roleList;
	for(int i = 0; i< role.size(); i++)
	{
		if(role[i] != n->roleList[i])
		{
			return false;
		}
	}
	return true;
}

void addNode(Node* n, std::vector<Node*> &movieBook)
{
	// adding the movie node in the moviebook
	int index = hash_title(n->title, movieBook);
	if(movieBook[index]->title == "  ")
	{
		movieBook[index] = n;
	}
	else
	{
		// if meeting the same title, just adding this node's next one
		Node* ptr = movieBook[index];
		while(ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
}

std::vector<std::string> split(std::string& str)
{
	// spliting a string into vector
	std::vector<std::string> v;
	std::string str2 = str;
    while (str2.find(" ") != std::string::npos) {
        int found = str2.find(" ");
        v.push_back(str2.substr(0, found));
        str2 = str2.substr(found + 1);
    }    
    v.push_back(str2);
    return v;
}

std::vector<std::string> slice(std::vector<std::string> const &v, int m, int n)
{
	//indexing a range of vector
    std::vector<std::string> vec(v.cbegin() + m, v.cbegin() + n + 1);
    return vec;
}

int main()
{
	std::vector<Node*> movieBook;

	//first constructing a vector of moviebook with the initial node with the constructor node
	for(int i =0; i< movieBook_size; i++)
	{
		Node* n =new Node();
		movieBook.push_back(n);
	}

	std::string movie_file_open;
	std::string actor_file_open;
	std::string movie;
	std::string actor;
	std::cin >> movie >> movie_file_open;
	std::cin >> actor >> actor_file_open;

	//if the command is "table_size" and "occupancy"
	if(movie == "table_size" && actor == "occupancy")
	{
		std::cin >> movie >> movie_file_open;
		std::cin >> actor >> actor_file_open;	
	}

	std::ifstream actor_file;
	actor_file.open(actor_file_open);
	std::map<std::string, std::string> actors;

	//reading the actor file
	if(actor_file)
	{
		std::string a;
		std::string b;
		while(actor_file >> a >> b)
		{
			actors[a] = b;
		}
	}
	else
	{
		std::cout << "the file cannot open" << std::endl;
	}


	std::ifstream movie_file;
	movie_file.open(movie_file_open);
	int times = 0;

	//reading the movie file
	if(movie_file)
	{
		std::string line;
		std::vector<std::string> lines;
		while(getline(movie_file, line))
		{

			times ++;
			//changing the size of moviebook
			if((times - 6*movieBook.size())%6==0)
			{
				Node* n =new Node();
				movieBook.push_back(n);
			}
			lines.push_back(line);
			if(lines.size() == 6)
			{
				//reading the string into vector
				std::vector<std::string> genre = split(lines[3]);
				std::vector<std::string> actor = split(lines[4]);
				std::vector<std::string> role = split(lines[5]);

				std::vector<std::string> sub_genre = slice(genre, 1, genre.size()-1);
				std::vector<std::string> sub_actor = slice(actor, 1, actor.size()-1);
				std::vector<std::string> sub_role = slice(role, 1, role.size()-1);

				//creating the node
				Node* tmp = new Node(lines[0], lines[1], lines[2], sub_genre,sub_actor, sub_role);
				addNode(tmp, movieBook);
				lines.clear();

			}
		}
	}
	else
	{
		std::cout << "the file cannot open" << std::endl;
	}

	//begining the "query" command
	std::string command = "  ";
	while(command != "exit")
	{
		std::cin >> command;
		
		if(command == "query" )
		{

			std::vector<std::string> sub_genre_1;
			std::vector<std::string> sub_actor_1;
			std::vector<std::string> sub_role_1;
			

			std::string title_input;
			std::cin >> title_input;

			std::string year_input;
			std::cin >> year_input;
		

			std::string runTime_input;
			std::cin >> runTime_input;

			//generating the genreList
			int genre_size;
			std::cin >> genre_size;
			int i = 1;
			std::string genre;
			
			while(i <= genre_size)
			{
				std::cin >> genre;
				sub_genre_1.push_back(genre);
				i++;
			}

			//generating the actorList
			int actor_size;
			std::cin >> actor_size;
			int j = 1;
			std::string actor;
			while(j <= actor_size)
			{
				std::cin >> actor;
				sub_actor_1.push_back(actor);
				j++;
			}

			//generating the roleList
			int role_size;
			std::cin >> role_size;
			int k = 1;
			std::string role;
			while(k <= role_size)
			{
				std::cin >> role;
				sub_role_1.push_back(role);
				k++;
			}
			

			std::vector<Node*> v;
			if(title_input == "?" )
			{
				//go over the movieBook vector
				for(int i = 0; i<movieBook.size(); i++)
				{
					std::string year_in;
					std::string runTime_in;
					std::vector<std::string> genreList_copy;
					std::vector<std::string> actorlist_copy;
					std::vector<std::string> roleList_copy;

					Node* ptr = movieBook[i];
					
					if(ptr->title == "  "){break;}

					//special case of the input and creating a temperary checking node
					title_input = ptr->title;
					if(year_input == "?") {year_in = ptr->year;}else{year_in = year_input;}
					if(runTime_input == "?") {runTime_in = ptr->runTime;}else{runTime_in = runTime_input;}
					if(genre_size == 0){genreList_copy = movieBook[i]->genreList;}else{genreList_copy = sub_genre_1;}
					if(actor_size == 0){actorlist_copy = movieBook[i]->actorlist;}else{actorlist_copy = sub_actor_1;}
					if(role_size == 0){roleList_copy = movieBook[i]->roleList;}else{roleList_copy = sub_role_1;}
					

					Node* n = new Node(title_input,year_in,runTime_in,genreList_copy,actorlist_copy,roleList_copy);
					//if there is just one node on that sopt and check that
					if(ptr->next == NULL)
					{
						if(ptr->hash_year(n) && ptr->hash_runTime(n) && ptr->hash_genreList(n) && ptr->hash_actorlist(n) && ptr->hash_roleList(n))
						{	

							v.push_back(ptr);
						}
					}
					//If there are some nodes after this node, go over the nodes after that one
					while(ptr->next != NULL)
					{
						if(ptr->hash_year(n) && ptr->hash_runTime(n) && ptr->hash_genreList(n) && ptr->hash_actorlist(n) && ptr->hash_roleList(n))
						{
							v.push_back(ptr);
						}
						ptr = ptr->next;
					}
				}
			} 
			else
			{
				// if already cin the specific title
				int index = hash_title(title_input, movieBook);
				Node* ptr = movieBook[index];
				std::string year_in;
				std::string runTime_in;
				std::vector<std::string> genreList_copy;
				std::vector<std::string> actorlist_copy;
				std::vector<std::string> roleList_copy;

				//special case of the input and creating a temperary checking node
				if(year_input == "?") {year_in = ptr->year;}else{year_in = year_input;}
				if(runTime_input == "?") {runTime_in = ptr->runTime;}else{runTime_in = runTime_input;}
				if(genre_size == 0){genreList_copy = movieBook[index]->genreList;}else{genreList_copy = sub_genre_1;}
				if(actor_size == 0){actorlist_copy = movieBook[index]->actorlist;}else{actorlist_copy = sub_actor_1;}
				if(role_size == 0){roleList_copy = movieBook[index]->roleList;}else{roleList_copy = sub_role_1;}

				Node* n = new Node(title_input,year_in,runTime_in,genreList_copy,actorlist_copy,roleList_copy);

				//if there is just one node on that sopt and check that
				if(ptr->next == NULL)
				{
					if(ptr->hash_year(n) && ptr->hash_runTime(n) && ptr->hash_genreList(n) && ptr->hash_actorlist(n) && ptr->hash_roleList(n))
					{

						v.push_back(ptr);
					}
				}
				//If there are some nodes after this node, go over the nodes after that one
				while(ptr->next != NULL)
				{
					if(ptr->hash_year(n) && ptr->hash_runTime(n) && ptr->hash_genreList(n) && ptr->hash_actorlist(n) && ptr->hash_roleList(n))
					{
						v.push_back(ptr);
					}
					ptr = ptr->next;
				}

			}


			if(v.size() == 0)
			{
				std::cout << "No results for query." << std::endl;
			}
			else
			{
				std::cout << "Printing "<< v.size()<<" result(s):"<< std::endl;


			//print the required printing format
			for(int i = 0; i< v.size(); i++)
			{
				std::cout << v[i]->title << std::endl;
				std::cout << v[i]->year << std::endl;
				std::cout << v[i]->runTime << std::endl;
				std::cout << (v[i]->genreList).size() << ' ';

				for(int j = 0; j<(v[i]->genreList).size(); j++)
				{
					if(j == (v[i]->genreList).size()-1)
					{
						std::cout << (v[i]->genreList)[j];
						break;
					}
					std::cout << (v[i]->genreList)[j] << ' ';
		
				} 
				std::cout << std::endl;

				std::cout << (v[i]->actorlist).size() << ' ';
				for(int j = 0; j<(v[i]->actorlist).size(); j++)
				{
					if(j == (v[i]->actorlist).size()-1)
					{
						std::cout << actors[(v[i]->actorlist)[j]] << ' ' <<'('<<(v[i]->roleList)[j]<<')';
						break;
					}
					std::cout << actors[(v[i]->actorlist)[j]] << ' ' <<'('<<(v[i]->roleList)[j]<<')'<< ' ';
				}
				std::cout << std::endl;

			}
		}
		}
	}
}




















