#include <iostream>
#include <deque>
#include <algorithm>
#include <string>
#include <map>

#include "Voronoi.hpp"

Voronoi::Voronoi(int rows, int cols) : rows(rows), cols(cols) {
    grid.resize(rows, std::vector<std::string>(cols, ""));
}

Voronoi::~Voronoi() = default;

void Voronoi::addSeed(std::unique_ptr<Seed> seed) {
    if (out_of_bounds(seed->getRow(), seed->getCol())) {
        throw std::out_of_range("Seed position is out of bounds.");
    }

    for (const auto& other : seeds) {
        if (seed->getRow() == other->getRow() && seed->getCol() == other->getCol()) {
            throw std::runtime_error("Seed already exists at this position.");
        }
    }

    seeds.push_back(std::move(seed));
}

void Voronoi::reset(int newRows, int newCols) {
    seeds.clear();
    rows = newRows;
    cols = newCols;
    grid.assign(rows, std::vector<std::string>(cols, ""));
}

void Voronoi::draw() {
    struct Node {
        int row;
        int col;
        Seed* seed;
    };

    std::deque<Node> queue;
    std::vector<std::vector<bool>> seen(rows, std::vector<bool>(cols, false));

    for (const auto& seed : seeds) {
        Seed* s = seed.get();

        seen[s->getRow()][s->getCol()] = true;
        grid[s->getRow()][s->getCol()] = seed->text();
        queue.push_back({s->getRow(), s->getCol(), s});
    }

    constexpr int dr[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    constexpr int dc[8] = {1, 1, 0, -1, -1, -1, 0, 1};

    while (!queue.empty()) {
        auto [row, col, seed] = queue.front(); queue.pop_front();

        for (int k = 0; k < 8; k++) {
            int nr = row + dr[k], nc = col + dc[k];
            
            if (out_of_bounds(nr, nc) || seen[nr][nc]) {
                continue;
            }

            seen[nr][nc] = true;
            grid[nr][nc] = seed->text();
            queue.push_back({nr, nc, seed});
        }
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void Voronoi::countCells() const {
    if (grid[0][0] == "") {
        throw std::runtime_error("The board hasn't been drawn yet.");
    }

    std::map<std::string, int> counts;

    std::for_each(grid.begin(), grid.end(), [&](const std::vector<std::string>& row) {
        for (const std::string& s : row) {
            counts[s]++;
        } 
    });

    std::cout << "Cell counts:\n";
    for (const auto& [symbol, count] : counts) {
        std::cout << symbol << ": " << count << '\n';
    }
}