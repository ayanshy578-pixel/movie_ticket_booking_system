#include <vector>
#include <string>
#include <memory>
using namespace std;

enum class BookingStatus {
    PENDING,
    CONFIRMED,
    CANCELLED
};

class Booking {
private:
    // Static member generates unique booking IDs.
    inline static int nextBookingId = 1001;

    int bookingId;
    Customer* customer;
    Show* show;
    vector<ShowSeat*> seats;
    double totalAmount;
    BookingStatus status;
    shared_ptr<Payment> payment;

public:
    Booking(Customer* customer, Show* show,
            const vector<ShowSeat*>& seats, double totalAmount)
        : bookingId(nextBookingId++),
          customer(customer),
          show(show),
          seats(seats),
          totalAmount(totalAmount),
          status(BookingStatus::PENDING),
          payment(nullptr) {}

    int getBookingId() const { return bookingId; }
    Customer* getCustomer() const { return customer; }
    Show* getShow() const { return show; }
    const vector<ShowSeat*>& getSeats() const { return seats; }
    double getTotalAmount() const { return totalAmount; }
    BookingStatus getStatus() const { return status; }

    void setPayment(shared_ptr<Payment> payment) {
        this->payment = payment; // this keyword
    }

    shared_ptr<Payment> getPayment() const { return payment; }

    void confirm() { status = BookingStatus::CONFIRMED; }

    void cancel() {
        status = BookingStatus::CANCELLED;
        for (ShowSeat* seat : seats)
            seat->cancel();
    }
};
