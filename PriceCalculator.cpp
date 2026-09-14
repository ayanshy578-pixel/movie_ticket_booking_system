#include <vector>
using namespace std;

class PriceCalculator {
private:
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

public:
    double calculate(const vector<ShowSeat*>& seats) const {
        double total = 0;

        for (const ShowSeat* seat : seats) {
            switch (seat->getType()) {
                case SeatType::SILVER:
                    total += SILVER_PRICE;
                    break;
                case SeatType::GOLD:
                    total += GOLD_PRICE;
                    break;
                case SeatType::PLATINUM:
                    total += PLATINUM_PRICE;
                    break;
            }
        }

        return total;
    }
};
