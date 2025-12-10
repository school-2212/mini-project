#pragma once

#include <string>

class Seed {
    protected:
        int row;
        int col;

    public:
        Seed(int row, int col);

        virtual ~Seed();

        int getRow() const;

        int getCol() const;

        virtual std::string text() const = 0;
};

class SymbolSeed : public Seed {
    private:
        char symbol;

    public:
        SymbolSeed(int row, int col, char symbol);

        std::string text() const override;
};

enum class Color {
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
};

class ColoredSeed : public Seed {
    private:
        std::string colorCode;

        std::string colorToString(Color color) {
            switch (color) {
                case Color::Red:     return "\033[31m";
                case Color::Green:   return "\033[32m";
                case Color::Yellow:  return "\033[33m";
                case Color::Blue:    return "\033[34m";
                case Color::Magenta: return "\033[35m";
            }

            return "\033[30m"; 
        }

    public:
        ColoredSeed(int row, int col, Color color);

        std::string text() const override;
};