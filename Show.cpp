#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Show {
private:
    int showId;
    Movie* movie;       // Aggregation: Movie exists independently.
    Screen* screen;     // Aggregation: Screen exists independently.
    string startTime;
    vector<ShowSeat> showSeats; // Composition: status belongs to this show.

public:
    Show(int showId, Movie* movie, Screen* screen, string startTime)
        : showId(showId), movie(movie), screen(screen), startTime(startTime) {

        for (const Seat& seat : screen->getSeats())
            showSeats.emplace_back(&seat);
    }

    int getShowId() const { return showId; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }

    void displayInfo() const {
        cout << "Show " << showId
             << " | Screen " << screen->getScreenNumber()
             << " | " << startTime << "\n";
    }

    void displaySeats() const {
        cout << "\nSeat Layout:\n";
        for (const ShowSeat& seat : showSeats) {
            cout << "Seat " << seat.getNumber()
                 << " [" << seatTypeName(seat.getType()) << "] - "
                 << (seat.isAvailable() ? "AVAILABLE" : "BOOKED") << "\n";
        }
    }

    ShowSeat* findSeat(int number) {
        for (ShowSeat& seat : showSeats) {
            if (seat.getNumber() == number)
                return &seat;
        }
        return nullptr;
    }
};
