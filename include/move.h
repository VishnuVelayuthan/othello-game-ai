#ifndef MOVE_H
#define MOVE_H

#include <cstddef>
#include <functional>

class Move {
public:
    Move(int row, int col, char m_player);
    
    friend bool operator==(const Move& lhs, const Move& rhs) {
        return lhs.row == rhs.row && lhs.col == rhs.col && lhs.m_player == rhs.m_player;
    }

    size_t hash() const {
        return 
        std::hash<int>()(row) ^ std::hash<int>()(col) * std::hash<char>()(m_player) << 1
        ;
    }


private:
    int row;
    int col;
    char m_player;

};

namespace std {
template<>
struct hash<Move> {
    size_t operator()(const Move& move) const {
        return move.hash();
    }
};
}


#endif
