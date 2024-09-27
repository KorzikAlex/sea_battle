#include <iostream>
#include <vector>

class Ship {
public:
    explicit Ship(const size_t size, const size_t x, const size_t y, const size_t orientation): size_(size), x_(x),
        y_(y), orientation_(orientation) {
        for (int i = 0; i < size_; i++)
            ship_status_[i] = 2;
    }

    ~Ship() = default;

private:
    size_t size_;
    size_t x_, y_;
    size_t orientation_;
    std::vector<size_t> ship_status_;
};

class ShipManager {
public:
    explicit ShipManager(const size_t n_of_ships, std::vector<Ship> ships): n_of_ships_(n_of_ships),
                                                                            ships_(std::move(ships)) {
    }

    ~ShipManager() = default;

    static void add_ship(const size_t x, const size_t y, const size_t orientation) {

    }

    static void add_ship(const Ship& ship) {

    }
private:
    size_t n_of_ships_;
    std::vector<Ship> ships_;
};

class Board {
public:
    explicit Board(const size_t x = 10, const size_t y = 10): x_(x), y_(y) {
    }

    ~Board() = default;

private:
    size_t x_, y_;
    std::vector<size_t> ship_status_;
};

int main(int argc, char *argv[]) {
    std::cout << "Hello World!\n";
}
