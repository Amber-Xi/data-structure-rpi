#include<vector>
#include<iostream>

template <class T> class Table
{
public:
    // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
    Table() {this -> create();}
    Table(const Table<T> &t) {copy(t);}
    Table(unsigned int row, unsigned int col, const T &t = T()) {this -> create(row, col, t);}
    Table& operator=(const Table& t);
    void deconstructor();
    ~Table();
    
    // MEMBER FUNCTIONS AND OTHER OPERATORS
    const T &get(unsigned int row, unsigned int col);
    void set(unsigned int row, unsigned int col, const T& c);
    unsigned int numRows();
    unsigned int numColumns();
    void push_back_column(const std::vector<T>& c);
    void push_back_row(const std::vector<T>& r);
    void pop_back_column();
    void pop_back_row();
    void push_back_rows(const Table<T>& t);
    void push_back_columns(const Table<T>& t);
    void print();
    void copy(const Table<T>& v);

private:
    // PRIVATE MEMBER FUNCTIONS
    void create();
    void create(unsigned int row,unsigned int col, const T& val);
    
    // REPRESENTATION
    T** m_data;
    unsigned int n_row;
    unsigned int n_col;
};

// Create an empty vector (null pointers everywhere).
template <class T> void Table<T>::create()
{
    m_data = NULL;
    n_row = 0;
    n_col = 0;
}

// Create a vector with size n, each location having the given value
template <class T> void Table<T>::create(unsigned int row, unsigned int col, const T& val)
{
    n_row = row;
    n_col = col;
    m_data = new T*[row];
        
    for(unsigned int i = 0; i<row; i++)
    {
        m_data[i] = new T[col];
        for (int j = 0; j<col; j++)
        {
            m_data[i][j] = val;
        }
    }
}

// Assign one vector to another, avoiding duplicate copying.
template <class T> Table<T>& Table<T>::operator=(const Table<T>& t)
{
    if(this != &t)
    {
        for(unsigned int a =0; a< n_row; a++)
        {
            delete [] m_data[a];
        }
        delete []m_data;
        this -> copy(t);
    }
    return *this;
}
// Add a row at the last location and increment the bound
template <class T> void Table<T>::push_back_row(const std::vector<T>& r)
{
        T** new_data = new T*[n_row+1];
        for(unsigned int i=0; i<n_row; i++)
        {
            new_data[i]=new T[n_col];
            for(unsigned int j = 0; j<n_col; j++)
            {
                new_data[i][j] = m_data[i][j];
            }
        }
    
        for(unsigned int a =0; a< n_row; a++)
        {
            delete [] m_data[a];
        }
    
        delete [] m_data;
    
        new_data[n_row]=new T[n_col];
        for(unsigned int b=0; b<r.size();b++)
        {
            new_data[n_row][b] = r[b];
        }
        ++n_row;
        m_data = new_data;
}

// Add a column at the last location and increment the bound
template <class T> void Table<T>::push_back_column(const std::vector<T>& c)
{
    T** new_data = new T*[n_row];
    unsigned int s = 0;
    for(unsigned int i = 0; i<n_row; i++)
    {
        new_data[i] = new T[n_col+1];
        for(unsigned int j=0; j<n_col+1; j++)
        {
            if(j == n_col)
            {
                new_data[i][j] = c[s];
                s++;
                continue;
            }
            new_data[i][j] = m_data[i][j];
        }
    }
    for(unsigned int a =0; a< n_row; a++)
    {
        delete [] m_data[a];
    }
    delete [] m_data;

    m_data = new_data;
    n_col += 1;
}

// access the private data
template <class T> const T &Table<T>::get(unsigned int row, unsigned int col)
{
    if(row >= n_row || col >= n_col)
    {
        std::cerr << "This 'get' function has errors." << std::endl;
        exit(1);
    }
    return m_data[row][col];
}

// change the private data
template <class T> void Table<T>::set(unsigned int row, unsigned int col, const T& c)
{
    if(row >= n_row || col >= n_col)
    {
        std::cerr << "This 'set' function has errors." << std::endl;
        exit(1);
    }
    m_data[row][col] = c;
}

// get the number of rows
template <class T> unsigned int Table<T>::numRows()
{
    return n_row;
}

// get the number of columns
template <class T> unsigned int Table<T>::numColumns()
{
    return n_col;
}

//print the array in the correct format
template <class T> void Table<T>::print()
{
    std::cout << "table: " << n_row << " rows, " << n_col << " cols" << std::endl;
    
    for(unsigned int i=0; i< n_row; i++)
    {
        for(unsigned int j=0; j< n_col; j++)
        {
            std::cout << m_data[i][j] << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

// delete the last column
template <class T> void Table<T>::pop_back_column()
{
    T** new_data = new T*[n_row];
    for(unsigned int i=0; i<n_row; i++)
    {
        new_data[i] = new T[n_col-1];
        for(unsigned int j =0; j< n_col-1; j++)
        {
            new_data[i][j] = m_data[i][j];
        }
    }
    for(unsigned int a =0; a< n_row; a++)
    {
        delete [] m_data[a];
    }
    delete [] m_data;
    m_data = new_data;
    n_col--;
}

// delete the last row
template <class T> void Table<T>::pop_back_row()
{
    T** new_data = new T*[n_row-1];
    for(unsigned int i=0; i<n_row-1; i++)
    {
        new_data[i] = new T[n_col];
        for(unsigned int j =0; j< n_col; j++)
        {
            new_data[i][j] = m_data[i][j];
        }
    }
    for(unsigned int a =0; a< n_row; a++)
    {
        delete [] m_data[a];
    }
    delete [] m_data;
    m_data = new_data;
    n_row--;
}

// copy one array from another
template <class T> void Table<T>::copy(const Table<T>& v)
{
    this->n_row = v.n_row;
    this->n_col = v.n_col;
    this->m_data = new T*[this->n_row];

    for (unsigned int i = 0; i < this->n_row; ++i)
    {
        m_data[i] = new T[this -> n_col];
        for(unsigned int j=0; j< this-> n_col; ++j)
        {
            this -> m_data[ i ][j] = v.m_data[ i ][j];
        }
    }
}

// the destructor to clear the memory
template <class T> Table<T>::~Table()
{
    for(unsigned int i=0; i<n_row; i++)
    {
        delete [] m_data[i];
    }
    delete [] m_data;
}

// Add matrixs of column at the last location and increment the bound
template <class T> void Table<T>::push_back_rows(const Table<T>& t)
{
    T** new_data = new T*[n_row+t.n_row];
    for(unsigned int i=0; i<n_row; i++)
    {
        new_data[i]=new T[t.n_col];
        for(unsigned int j = 0; j<n_col; j++)
        {
            new_data[i][j] = m_data[i][j];
        }
    }
    for(unsigned int a =0; a< n_row; a++)
    {
        delete [] m_data[a];
    }
    
    delete [] m_data;
    
    for(unsigned int b=0; b<t.n_row;b++)
    {
        new_data[b+n_row]=new T[t.n_col];
        for(unsigned int c=0; c<t.n_col;c++)
        {
            new_data[b+n_row][c] = t.m_data[b][c];
        }
    }
    n_row += t.n_row;
    m_data = new_data;
}

// Add matrixs of rows at the last location and increment the bound
template <class T> void Table<T>::push_back_columns(const Table<T>& t)
{
    T** new_data = new T*[n_row];
    for(unsigned int i = 0; i<n_row; i++)
    {
        new_data[i] = new T[n_col+t.n_col];
        for(unsigned int j=0; j<n_col+t.n_col; j++)
        {
            if(j >= n_col)
            {
                new_data[i][j] = t.m_data[i][j-n_col];
                continue;
            }
            new_data[i][j] = m_data[i][j];
        }
    }
    for(unsigned int a =0; a< n_row; a++)
    {
        delete [] m_data[a];
    }
    delete [] m_data;
    
    m_data = new_data;
    n_col += t.n_col;
}

