class ShowSeat {
private:
    const Seat* seat;
    bool booked;

public:
    ShowSeat(const Seat* seat) : seat(seat), booked(false) {}

    int getNumber() const { return seat->getNumber(); }
    SeatType getType() const { return seat->getType(); }
    bool isAvailable() const { return !booked; }

    bool book() {
        if (booked)
            return false;

        booked = true;
        return true;
    }

    void cancel() {
        booked = false;
    }
};
