#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Point {
public:
    Point() {x = y = 0;}
    Point(int x_,int y_) {x = x_; y = y_;}
    
    // representation
    int x,y;
};

class Word {
public:
    Word() {
        length = 0;
    }
    Word(Point position, int len, std::string config, std::string cont) {
        fisrt_letter_position.x = position.x;
        fisrt_letter_position.y = position.y;
        length = len;
        configuration = config;
        content = cont;
    }
    
    bool operator==(const Word& w) const {
        return (fisrt_letter_position.x == w.fisrt_letter_position.x) && (fisrt_letter_position.y == w.fisrt_letter_position.y) && configuration == w.configuration && content == w.content;
        
    }
    
    // representation
    Point fisrt_letter_position;
    int length;      // length of this word
    std::string configuration;    // the way this word aligns: "across" for across, "down" for down
    std::string content;   // content of this word
};

void read_dictionary(std::ifstream& dic_file, std::vector<std::string>& dictionary) {
    std::string x;
    while (dic_file >> x) {
        dictionary.push_back(x);
    }
}

int max_length_of_dic(std::vector<std::string>& dictionary) {     // find the maximum length of words in the dictionary
    int temp = 0;
    for(unsigned int i = 0; i < dictionary.size(); i++) {
        if(temp < dictionary[i].size()) {
            temp = dictionary[i].size();
        }
    }
    return temp;
}

// modify the dictionary so the the length of the words equals the index this word is at in the vector
std::vector<std::vector<std::string> >  modify_dictionary(std::vector<std::string>& dictionary, int max_length_of_dic) {
    std::vector<std::vector<std::string> > temp;
    for(unsigned int i = 0; i <= max_length_of_dic; i++) {
        std::vector<std::string> temp_;
        for(unsigned int j = 0; j < dictionary.size(); j++) {
            if(dictionary[j].size() == i) {
                temp_.push_back(dictionary[j]);
            }
        }
        temp.push_back(temp_);
    }
    return temp;
}

void read_grid_file(std::ifstream& grid_file,  std::vector<std::vector<char> >& grid, std::vector<int>& constraint) {
    std::string x;
    while (grid_file >> x) {
        int temp;
        if(x[0] == '+') {   // just store the constraint in both vectors
            temp = std::stoi(x.substr(1, x.size() - 1));    // the number after the plus sign;
            constraint[temp] += 1;
            continue;
        }
        
        if(x[0] != '!' && x[0] != '+') {      // store the grid info
            std::vector<char> temp_;
            for(unsigned int i = 0; i < x.size(); i++) {
            temp_.push_back(x[i]);
            }
            grid.push_back(temp_);
        }
    }
}

// a recursion function that checks the words that both appear in the dic and the grid
void checkword(Point start_position, const std::vector<std::vector<char> >& grid, const std::vector<std::vector<std::string> >& modified_dictionary, const std::vector<int>& lengths, std::vector<Word>& word_found) {
    
    // base case -- position is at the end
    if(start_position.x == grid.size() - 1 && start_position.y == grid[0].size() - 1) {
        return;
    }
    
    // check across at this position
    if(start_position.y + 3 <= grid[0].size()) {
        for(unsigned int i = 0; i < lengths.size(); i++) {   // for all the lengths in across constraints
            int len = lengths[i];
            if(start_position.y + len <= grid[0].size()) {    //  if there is enough space of len left in the gird after the position
                std::vector<char> line = grid[start_position.x];   // the line the position at
                std::string word = "";     // the word of a certain len starting at this position
                for(unsigned int m = start_position.y; m < start_position.y + len; m++) {     // record this word
                    word += line[m];
                }
                for(unsigned int j = 0; j < modified_dictionary[len].size(); j++) {
                    if(word == modified_dictionary[len][j]) {    // the word is found in the dic
                        Word temp = Word(start_position, len, "across", word);    // record the info of this word
                        word_found.push_back(temp);
                        break;
                    }
                }
            }
        }
    }
    
    // check down at this position
    if(start_position.x + 3 <= grid.size()) {
        for(unsigned int i = 0; i < lengths.size(); i++) {   // for all the lengths in down constraints
            int len = lengths[i];
            if(start_position.x + len <= grid.size()) {    //  if there is enough space of len left in the gird after the position
                std::string word = "";     // the word of a certain len starting at this position
                for(unsigned int m = start_position.x; m < start_position.x + len; m++) {     // record this word
                    word += grid[m][start_position.y];
                }
                for(unsigned int j = 0; j < modified_dictionary[len].size(); j++) {
                    if(word == modified_dictionary[len][j]) {    // the word is found in the dic
                        Word temp = Word(start_position, len, "down", word);    // record the info of this word
                        word_found.push_back(temp);
                        break;
                    }
                }
            }
        }
    }

    // recursive case
    if(start_position.y < grid[0].size() - 1) {      //   not reach the end of the line
        Point p = Point(start_position.x, start_position.y+1);
        checkword(p, grid, modified_dictionary, lengths, word_found);
    }
    else {
        Point p = Point(start_position.x+1, 0);
        checkword(p, grid, modified_dictionary, lengths, word_found);
    }
}

// modify the words found so that the index of the vector this funtion returns is the length of the word stored inside
std::vector<std::vector<Word> > modify_word_found(const std::vector<Word>& word_found, int max_length) {
    std::vector<std::vector<Word> > out;
    for(unsigned int i = 0; i <= max_length; i++) {
        std::vector<Word> temp;
        for(unsigned int j = 0; j < word_found.size(); j++) {     // append the word if its length equals the index
            if(word_found[j].length == i) {
                temp.push_back(word_found[j]);
            }
        }
        out.push_back(temp);
    }
    return out;
}

// a recursion function that find all possible combinations for a given length of word constraint
void find_solution_by_length(int order, const std::vector<Word>& word_found_at_this_length, std::vector<std::vector<Word> >& all_solution_at_this_length, std::vector<int>& record) {
    if(order == 0) {    // base case
        std::vector<Word> temp;   // used to store a particular solution at this length
        for(unsigned int i = 1; i < record.size(); i++) {       // store each solution
            temp.push_back(word_found_at_this_length[record[i]]);
        }
        all_solution_at_this_length.push_back(temp);
        return;
    }
    
    // recursive case    use combinations to find the solutions
    // the current index will be record[order]]
    int prev_index;
    if(order < record.size() - 1) {
        prev_index = record[order + 1];
    }
    else {
        prev_index = record[order] + 1;     // make sure that this does not affect the recursive below when there is no previous index
    }
    
    int new_order = order - 1;
    while (record[order] <= (word_found_at_this_length.size() - order)) {
        if(order != record.size() - 1 && record[order] <= prev_index) {  // the recursion goes on only when the index is greater than the previous index
            record[order]++;
            continue;
        }
        std::vector<int> temp = record;
        find_solution_by_length(new_order, word_found_at_this_length, all_solution_at_this_length, temp);
        record[order]++;
    }
}


// combine the sub-solutions to make a comprehensive one
void combine(std::vector<std::vector<Word> >& solutions_of_all_length, const std::vector<std::vector<Word> >& all_solution_at_this_length) {
    if(solutions_of_all_length.size() == 0) {
        solutions_of_all_length = all_solution_at_this_length;
    }
    else {
        int multiple = all_solution_at_this_length.size();     // this multiple indicates how many solutions there are at a given length
        std::vector<std::vector<Word> > temp = solutions_of_all_length;
        for(unsigned int i = 1; i < multiple; i++) {
            for(unsigned int j = 0; j < temp.size(); j++) {
                solutions_of_all_length.push_back(temp[j]);     // copy the vector multiple times
            }
        }
        
        for(unsigned int j = 0; j < solutions_of_all_length.size(); j++) {    // to combine each solution
            int count;
            count = j / temp.size();
            for(unsigned int m = 0; m < all_solution_at_this_length[count].size(); m++) {
                solutions_of_all_length[j].push_back(all_solution_at_this_length[count][m]);
            }
        }
    }
}

// returns true if it is a valid solution, false other wise
bool check_overlap(const std::vector<Word>& one_solution) {
    for(unsigned int i = 0; i < one_solution.size(); i++) {    // two index
        for(unsigned int j = 0; j < one_solution.size(); j++) {
            if(j > i) {
                Word word1 = one_solution[i];
                Word word2 = one_solution[j];
                if(word1.content == word2.content) {   // duplicate words not allowed
                    return false;
                }
                int minimum_len = word1.length + word2.length +1;   // the minimum total length if these two words are valid
                int actual_len;
                if(word1.fisrt_letter_position.x == word2.fisrt_letter_position.x && word1.configuration == word2.configuration && word1.configuration == "across") {    // on the same line
                    if(word1.fisrt_letter_position.y <= word2.fisrt_letter_position.y) {  // word 1 is at the front
                        actual_len = word2.fisrt_letter_position.y - word1.fisrt_letter_position.y + word2.length;
                    }
                    else {   // word 2 is at the front
                        actual_len = word1.fisrt_letter_position.y - word2.fisrt_letter_position.y + word1.length;
                    }
                    if(actual_len < minimum_len) {    // the two words overlapped
                        return false;
                    }
                }
                if(word1.fisrt_letter_position.y == word2.fisrt_letter_position.y && word1.configuration == word2.configuration && word1.configuration == "down") {  // on the same column
                    if(word1.fisrt_letter_position.x <= word2.fisrt_letter_position.x) {  // word 1 is at the front
                        actual_len = word2.fisrt_letter_position.x - word1.fisrt_letter_position.x + word2.length;
                    }
                    else {   // word 2 is at the front
                        actual_len = word1.fisrt_letter_position.x - word2.fisrt_letter_position.x + word1.length;
                    }
                    if(actual_len < minimum_len) {    // the two words overlapped
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// initialize the grid so that they are all #
void initialize_grid(std::vector<std::vector<char> >&grid) {
    for(unsigned int i = 0; i < grid.size(); i++) {
        for(unsigned j = 0 ; j < grid[i].size(); j++) {
            grid[i][j] = '#';
        }
    }
}

// form a board
std::vector<std::vector<char> > formgrid(const std::vector<std::vector<char> >&grid, const std::vector<Word> & solutions) {
    std::vector<std::vector<char> > temp = grid;
    initialize_grid(temp);
    for(unsigned int j = 0; j < solutions.size(); j++) {     // for each solution
        Word word = solutions[j];    // this is one word
        int x0 = word.fisrt_letter_position.x;    // initial x coordinate of this word
        int y0 = word.fisrt_letter_position.y;     // initial y coordinate
        if(word.configuration == "across") {
            for(unsigned int index = 0; index < word.length; index++) {
                temp[x0][y0 + index] = word.content[index];
            }
        }
        else if(word.configuration == "down") {
            for(unsigned int index = 0; index < word.length; index++) {
                temp[x0 + index][y0] = word.content[index];
            }
        }
    }
    return temp;
}

// check if there are any words in the solutions not in the dictionary
bool check_in_dic(const std::vector<Word>& solution, const std::vector<std::vector<std::string> >& modified_dictionary, const std::vector<std::vector<char> >&grid) {
    
    int word_count = 0;
    bool valid = true;
    // check across
    Point start(0,0);
    
    while(start.x < grid.size() && start.y < grid[0].size()) {    // not reach the end
        while(grid[start.x][start.y] == '#') {
            if(start.x == grid.size() - 1 && start.y == grid[0].size() - 1)  {    // reach the end
                break;
            }
            if(start.y == grid[0].size() - 1) {   // go to the next line
                start.x ++;
                start.y = 0;
            }
            else{
                start.y++;
            }
        }
        if(start.x == grid.size() - 1 && start.y == grid[0].size() - 1)  {    // reach the end
            break;
        }
            std::string word = "";
            while(grid[start.x][start.y] != '#') {   // to read a word
                word += grid[start.x][start.y];
                if(start.y == grid[0].size() - 1) {   // go to the next line
                    start.x ++;
                    start.y = 0;
                    break;
                }
                else{
                    start.y++;
                }
            }
        
            if(word.size() <= 1) continue;
            else word_count += 1;
            
            // check if this has already been counted as word
            bool found = false;
            for(unsigned int i = 0; word.size() < modified_dictionary.size() && i < modified_dictionary[word.size()].size(); i++) {
                if(word == modified_dictionary[word.size()][i]) {
                    found = true;
                    break;
                }
            }
            if(found == false) valid = false;
    }
   
    // check down
    Point startd(0,0);

    while(startd.x < grid.size() && startd.y < grid[0].size()) {    // not reach the end
        while(grid[startd.x][startd.y] == '#' ) {
            if(startd.x == grid.size() - 1 && startd.y == grid[0].size() - 1)  {    // reach the end
                break;
            }
            if(startd.x == grid.size() - 1) {   // go to the next line
                startd.y ++;
                startd.x = 0;
            }
            else{
                startd.x++;
            }
        }
        if(startd.x == grid.size() - 1 && startd.y == grid[0].size() - 1)  {    // reach the end
            break;
        }
            std::string word = "";
            while(grid[startd.x][startd.y] != '#') {   // to read a word
                word += grid[startd.x][startd.y];
                if(startd.x == grid.size() - 1) {   // go to the next line
                    startd.y ++;
                    startd.x = 0;
                    break;
                }
                else{
                    startd.x++;
                }
            }
        
            if(word.size() <= 1) continue;
            else word_count += 1;
            
            bool found = false;
            for(unsigned int i = 0; word.size() < modified_dictionary.size() && i < modified_dictionary[word.size()].size(); i++) {
                if(word == modified_dictionary[word.size()][i]) {
                    found = true;
                    break;
                }
            }
            if(found == false) valid = false;
        }

    return valid && word_count == solution.size();
}

// check if there are invalid solutions, return a vector that excludes those overlapping solutions
std::vector<std::vector<Word> > filter(const std::vector<std::vector<Word> >& solutions_of_all_length, const std::vector<std::vector<char> >& grid, std::vector<std::vector<std::string> >& modified_dictionary, std::vector<int>& lengths){
    std::vector<std::vector<Word> > out;
    for(unsigned int i = 0; i < solutions_of_all_length.size(); i++) {    // for each individual solution
        bool can_be_preserved;
        can_be_preserved = check_overlap(solutions_of_all_length[i]);   // invalid words
        if(can_be_preserved == false ) {
            continue;
        }
        
        std::vector<std::vector<char> > newgrid;
        newgrid = formgrid(grid, solutions_of_all_length[i]);
        
 
        // if all the words formed are in the dictionary
        bool all_words_in_dic = check_in_dic(solutions_of_all_length[i], modified_dictionary, newgrid);
        if(all_words_in_dic == false) continue;
        
        out.push_back(solutions_of_all_length[i]);
    }
    return out;
}

// print a board
void printgrid(const std::vector<std::vector<char> >&grid) {
    std::cout<<"Board:\n";
    for(unsigned int i = 0; i < grid.size(); i++) {
        for(unsigned j = 0 ; j < grid[i].size(); j++) {
            std::cout << grid[i][j];
        }
        std::cout<<"\n";
    }
}



// print all the solutions
void print_board(const std::vector<std::vector<char> >&grid, const std::vector<std::vector<Word> >& solutions_of_all_length) {
    for(unsigned int i = 0; i < solutions_of_all_length.size(); i++) {
        std::vector<std::vector<char> > temp = grid;
        initialize_grid(temp);
        for(unsigned int j = 0; j < solutions_of_all_length[i].size(); j++) {     // for each solution
            Word word = solutions_of_all_length[i][j];    // this is one word
            int x0 = word.fisrt_letter_position.x;    // initial x coordinate of this word
            int y0 = word.fisrt_letter_position.y;     // initial y coordinate
            if(word.configuration == "across") {
                for(unsigned int index = 0; index < word.length; index++) {
                    temp[x0][y0 + index] = word.content[index];
                }
            }
            else if(word.configuration == "down") {
                for(unsigned int index = 0; index < word.length; index++) {
                    temp[x0 + index][y0] = word.content[index];
                }
            }
        }
        printgrid(temp);
    }
}


int main(int argc, char* argv[]) {
    std::ifstream dic_file(argv[1]);     // dictionary file
    std::ifstream grid_file(argv[2]);      // initail gird file
    
    if(argc < 5 || argc > 6) {
        std::cerr << "Not enough comman line arguments.\n";
        exit(1);
    }
    
    // error reading
    if (!dic_file.good() || !grid_file.good()){
        std::cerr << "Can't open" << argv[1] << " or " << argv[2] << " to read.\n";
        exit(1);
    }
    
    // file reading
    std::vector<std::string> dictionary;
    read_dictionary(dic_file, dictionary);
    
    int max_length = max_length_of_dic(dictionary);
    std::vector<int> constraint;       // vector to store the length constraint, number of index indicates the number of words need to find
    for(unsigned int i = 0; i < max_length + 1; i++) {    // initialize the value as 0
        constraint.push_back(0);
    }
    
    std::vector<std::vector<std::string> > modified_dictionary;
    modified_dictionary = modify_dictionary(dictionary, max_length);  // modify the dic
    
    std::vector<std::vector<char> > grid;     // vector to store the grid
    std::vector<int> lengths;    // all different value of lengths that need to be checked
    read_grid_file(grid_file, grid, constraint);
    
    for(unsigned int i = 0; i < max_length + 1; i++) {    // store all value of lengths in this vector
        if(constraint[i] != 0) {
            lengths.push_back(i);
        }
    }
    
    // find the words
    std::vector<Word> word_found;   // vector to store the word that both appears in the dic and grid and required by the constraint
    Point start = Point(0,0);
    checkword(start, grid, modified_dictionary, lengths, word_found);
    
    std::vector<std::vector<Word> > modified_word_found;   // modify it for easier later calculation;
    modified_word_found = modify_word_found(word_found, max_length);
   
    // combination of solutions
    std::vector<std::vector<Word> >solutions_of_all_length;   // each element in the vector is a comprehensive combinations of solutions
    
    // find the solutions
    for(unsigned int i = 0; i < modified_word_found.size(); i++) {
        if(modified_word_found[i].size() == 0) {
            continue;
        }
        int required_number = constraint[i];
          if(required_number == 0) {
              continue;
          }
        std::vector<Word> word_found_at_this_length = modified_word_found[i];
        std::vector<std::vector<Word> > all_solution_at_this_length;
        std::vector<int> record;    // a vector that records the index
        for(unsigned int index = 0; index <= required_number; index++) {
            record.push_back(0);     // intialize it
        }
        
        if(required_number > word_found_at_this_length.size()) break; // NOT ENOUGH WORD FOUND
        
        find_solution_by_length(required_number, word_found_at_this_length, all_solution_at_this_length, record);
        combine(solutions_of_all_length, all_solution_at_this_length);   //  combine to seek final solutions
    }
    
    std::vector<std::vector<Word> > filtered_solutions;   // solutions that excludes invalid ones
    filtered_solutions = filter(solutions_of_all_length, grid, modified_dictionary, lengths);
    
    int total_num = 0;
    for(unsigned int a = 0; a < constraint.size(); a++) {
        total_num += constraint[a];
    }
    std::vector<std::vector<Word> > temp;
    for(unsigned int a = 0; a < filtered_solutions.size(); a++) {    // not enough words found
        if(filtered_solutions[a].size() < total_num)  {
            continue;
        }
        else temp.push_back(filtered_solutions[a]);
    }
    filtered_solutions = temp;
    
    
    // output
    std::string solution_mode(argv[3]);
    std::string output_mode(argv[4]);
    
    if(solution_mode == "one_solution") {
        int size = 1;
        if(filtered_solutions.size() == 0)  {
            size = 0;
        }
        std::cout<<"Number of solution(s): " << size <<"\n";
    }
    else if(solution_mode == "all_solutions") {
        std::cout<<"Number of solution(s): " << filtered_solutions.size() <<"\n";
    }
    
    if(output_mode == "print_boards") {         // print out all the solutions
        if(solution_mode == "one_solution" && filtered_solutions.size() > 0) {
            std::vector<std::vector<Word> >temp;
            temp.push_back(filtered_solutions[0]);
            print_board(grid, temp);
        }
        else if(solution_mode == "all_solutions") {
            print_board(grid, filtered_solutions);
        }
    }

}
