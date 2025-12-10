#include "Seeds.hpp"

Seed::Seed(int row, int col) : row(row), col(col) {}

Seed::~Seed() = default;

int Seed::getRow() const {
    return row;
}

int Seed::getCol() const {
    return col;
}

SymbolSeed::SymbolSeed(int row, int col, char symbol) : Seed(row, col), symbol(symbol) {}

std::string SymbolSeed::text() const {
    return std::string(1, symbol);
}


ColoredSeed::ColoredSeed(int row, int col, Color color) : Seed(row, col), colorCode(colorToString(color)) {}

std::string ColoredSeed::text() const {
    return colorCode + "■" + "\033[0m";
}