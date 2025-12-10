#include <vector>
#include <string>
#include <iostream>

#include "Voronoi.hpp"
#include "Seeds.hpp"

int main() {
    std::cout << "Enter dimensions of board: ";
    int row, col; std::cin >> row >> col;
    Voronoi v = Voronoi(row, col);
    std::string command;
    
    while (true) {
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == "quit") {
            break;
        }

        if (command == "reset") {
            std::cout << "Enter dimensions of board: ";
            int row, col;
            std::cin >> row >> col;

            v.reset(row, col);
        }
        else if (command == "draw") {
            v.draw();
        }
        else if (command == "count_cells") {
            v.countCells();
        }
        else if (command == "add_symbol") {
            std::cout << "Enter a row, column, and symbol: ";
            int row, col;
            char symbol;
            std::cin >> row >> col >> symbol;

            try {
                v.addSeed(std::make_unique<SymbolSeed>(row, col, symbol));
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << '\n';
            }
        }
        else if (command == "add_color") {
            std::cout << "Enter a row, column, and color: ";
            int row, col;
            std::string color_str;
            std::cin >> row >> col >> color_str;

            try {
                Color color;

                if (color_str == "red") {
                    color = Color::Red;
                } else if (color_str == "yellow") {
                    color = Color::Yellow;
                } else if (color_str == "green") {
                    color = Color::Green;
                } else if (color_str == "blue") {
                    color = Color::Blue;
                } else if (color_str == "magenta") {
                    color = Color::Magenta;
                } else {
                    throw std::invalid_argument("Unknown color.");
                }

                v.addSeed(std::make_unique<ColoredSeed>(row, col, color));
            } catch (const std::exception& e) {
                std::cout << "Error: " << e.what() << '\n';
            }
        } else {
            std::cout << "Unknown command.\n";
        }
    }

    std::cout << "Exiting.";
    return 0;
}