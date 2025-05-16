#include <vector>

// struct Offset {
//     int v;
//     int h;
// };

class State
{
    public:
        State(std::vector<std::vector<bool>> grid);
        State Get();
        State Step();
    private:
        // Offset o_;
        std::vector<std::vector<bool>> grid_;
        
        int CountNeighbors();
        void AddMargin();
};
