#include <vector>
using namespace std;

class Screen {
private:
    int screenNumber;
    vector<Seat> seats; // Composition: Screen creates and owns its seats.

public:
    Screen(int screenNumber, int seatCount = 12) : screenNumber(screenNumber) {
        for (int i = 1; i <= seatCount; ++i) {
            SeatType type;

            if (i <= 4)
                type = SeatType::SILVER;
            else if (i <= 8)
                type = SeatType::GOLD;
            else
                type = SeatType::PLATINUM;

            seats.emplace_back(i, type);
        }
    }

    int getScreenNumber() const { return screenNumber; }
    const vector<Seat>& getSeats() const { return seats; }
};
