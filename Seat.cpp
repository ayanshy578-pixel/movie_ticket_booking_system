#include <iostream>
#include <string>
using namespace std;

enum class SeatType {
    SILVER,
    GOLD,
    PLATINUM
};

string seatTypeName(SeatType type) {
    switch (type) {
        case SeatType::SILVER: return "SILVER";
        case SeatType::GOLD: return "GOLD";
        case SeatType::PLATINUM: return "PLATINUM";
    }
    return "";
}

class Seat {
private:
    int number;
    SeatType type;

public:
    Seat(int number, SeatType type) : number(number), type(type) {}

    int getNumber() const { return number; }
    SeatType getType() const { return type; }

    void display() const {
        cout << number << "(" << seatTypeName(type) << ")";
    }
};
