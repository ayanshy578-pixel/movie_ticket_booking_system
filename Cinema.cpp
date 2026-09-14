#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Cinema {
private:
    string name;
    vector<Screen> screens; // Composition: Cinema owns its screens.

public:
    Cinema(string name) : name(name) {}

    void addScreen(int screenNumber, int seatCount = 12) {
        screens.emplace_back(screenNumber, seatCount);
    }

    vector<Screen>& getScreens() { return screens; }
    const vector<Screen>& getScreens() const { return screens; }

    void displayScreens() const {
        for (const Screen& screen : screens)
            cout << "Screen " << screen.getScreenNumber() << "\n";
    }
};
