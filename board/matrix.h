
#ifndef Matrix_h
#define Matrix_h

#include <WString.h>
#include <vector>

class Matrix 
{
    private:
        std::vector<int> _columns;
        std::vector<int> _rows;

        std::vector<int> _states;

    public:
        Matrix(std::vector<int> columns, std::vector<int> rows);
        void Init();
        void Scan();
        int GetState(int index);
        String StatesString();
};

#endif
