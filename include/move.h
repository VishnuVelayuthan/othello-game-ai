#ifndef MOVE_H
#define MOVE_H

#include "./openai/nlohmann/json.hpp"

#include <cstddef>
#include <vector>
#include <functional>
#include <string>

enum class FlipType : short {
    UP = 0, 
    DOWN = 1,
    LEFT = 2, 
    RIGHT = 3, 
    LUD = 4, 
    RUD = 5,
    LDD = 6,
    RDD = 7
};

class Move {
public:
    Move(int row, int col, char m_player, FlipType iniType) :
        row(row), col(col), m_player(m_player), flipTypes()
    {
        flipTypes.push_back(iniType);
    };

    Move(Move* move) : row(move->row), col(move->col), m_player(move->m_player){
        for (int i = 0; i < move->flipTypes.size(); i++)
            this->flipTypes.push_back(move->flipTypes[i]);
    };
    
    friend bool operator==(const Move& lhs, const Move& rhs) {
        return lhs.row == rhs.row && lhs.col == rhs.col && lhs.m_player == rhs.m_player;
    }

    friend bool operator<(const Move& lhs, const Move& rhs) {
        return lhs.row < rhs.row || lhs.col < rhs.col;
    }

    inline bool isNull() {
        return col == -1 || row == -1 ;
    }

    inline size_t hash() const {
        return 
            std::hash<int>()(row) ^ std::hash<int>()(col) * std::hash<char>()(m_player) << 1
        ;
    }

    inline void addType(FlipType flipT) {flipTypes.push_back(flipT);};

    inline int getIrow() {return this->row;};
    inline int getIcol() {return this->col;};
    inline char getPlayer() {return this->m_player;};
    inline const std::vector<FlipType>& getFlipTypes() {return this->flipTypes;};

    inline const std::string toString() {
        return "(" + std::to_string(row) + "," + std::to_string(col) + ")";
    }

    inline nlohmann::json toJson() {
        nlohmann::json j;
        j.emplace("row", row);
        j.emplace("col", col);
        j.emplace("m_player", m_player);
        return j; 
    };

    inline const bool isMove(int r, int c) {return r == row && c == col;};

private:
    int row;
    int col;
    char m_player;

    std::vector<FlipType> flipTypes;

};

namespace std {
template<>
struct hash<Move> {
    size_t operator()(const Move& move) const {
        return move.hash();
    }
};

template<>
struct hash<Move*> {
    size_t operator()(const Move* move) const {
        return move->hash();
    }
};
}


#endif
