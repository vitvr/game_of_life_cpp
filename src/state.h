// #pragma once

#include <vector>
#include <string>

// This struct may be better suited for a separate render class
// struct Offset {
//     int v;
//     int h;
// };

class State
{
    public:
        State(std::string file_name, char dead, char alive);
        State(std::vector<std::vector<bool>> grid);
        State Get();
        State Step();
    private:
        // Offset o_;
        std::vector<std::vector<bool>> grid_;
        
        int CountNeighbors();
        void AddMargin();
        std::vector<std::vector<bool>> ReadSeedFile(std::string file_name, char dead, char alive);
};
