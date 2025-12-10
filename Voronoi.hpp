#include <vector>
#include <memory>

#include "Seeds.hpp"

class Voronoi {
    private:
        int rows;
        int cols;
        std::vector<std::unique_ptr<Seed>> seeds;
        std::vector<std::vector<std::string>> grid;

        bool out_of_bounds(int r, int c) {
            return r < 0 || r >= rows || c < 0 || c >= cols;
        };

    public:
        Voronoi(int rows, int cols);

        void addSeed(std::unique_ptr<Seed> seed);

        void reset(int newRows, int newCols);

        void draw();

        void countCells() const;
};