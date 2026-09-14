#include <iostream>
#include <vector>
using namespace std;

class BookingService {
private:
    PriceCalculator priceCalculator;

public:
    Booking* createBooking(Customer* customer, Show* show,
                           const vector<int>& seatNumbers) {

        vector<ShowSeat*> selectedSeats;

        // Validate every seat before changing any seat status.
        for (int number : seatNumbers) {
            ShowSeat* seat = show->findSeat(number);

            if (seat == nullptr) {
                cout << "Invalid seat number: " << number << "\n";
                return nullptr;
            }

            if (!seat->isAvailable()) {
                cout << "Seat " << number << " is already BOOKED.\n";
                return nullptr;
            }

            selectedSeats.push_back(seat);
        }

        double total = priceCalculator.calculate(selectedSeats);

        // Booking does not print tickets or process payment.
        // It only stores booking data.
        return new Booking(customer, show, selectedSeats, total);
    }

    bool makePayment(Booking* booking, shared_ptr<Payment> payment) {
        booking->setPayment(payment);

        // Runtime polymorphism: correct pay() runs based on object type.
        bool paid = payment->pay(booking->getTotalAmount());

        if (!paid) {
            cout << "Payment FAILED. Booking not confirmed.\n";
            return false;
        }

        for (ShowSeat* seat : booking->getSeats())
            seat->book();

        booking->confirm();
        return true;
    }

    void cancelBooking(Booking* booking) {
        if (booking == nullptr)
            return;

        booking->cancel();
        cout << "Booking cancelled. Seats are AVAILABLE again.\n";
    }
};
