#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

// No header files are used as required by the assignment.
// Each class is kept in its own .cpp file and included here.

#include "Movie.cpp"
#include "Seat.cpp"
#include "Screen.cpp"
#include "Cinema.cpp"
#include "ShowSeat.cpp"
#include "Show.cpp"
#include "Customer.cpp"
#include "Payment.cpp"
#include "UpiPayment.cpp"
#include "CardPayment.cpp"
#include "CashPayment.cpp"
#include "PriceCalculator.cpp"
#include "Booking.cpp"
#include "TicketPrinter.cpp"
#include "BookingService.cpp"

int main() {
    Cinema cinema("My Cinema");
    cinema.addScreen(1, 12);
    cinema.addScreen(2, 12);

    vector<Movie> movies = {
        Movie("Avengers: Endgame", "English", 181),
        Movie("3 Idiots", "Hindi", 170),
        Movie("Dangal", "Hindi", 161)
    };

    vector<Show> shows;
    int showId = 1;

    // Shows use existing Movie and Screen objects.
    for (Movie& movie : movies) {
        shows.emplace_back(showId++, &movie,
                           &cinema.getScreens()[0],
                           "10:00 AM");

        shows.emplace_back(showId++, &movie,
                           &cinema.getScreens()[1],
                           "06:00 PM");
    }

    BookingService service;
    TicketPrinter printer;

    cout << "========================================\n";
    cout << "        MOVIE TICKET BOOKING\n";
    cout << "========================================\n";

    string customerName, phone;
    cout << "Enter customer name: ";
    getline(cin, customerName);

    cout << "Enter phone: ";
    getline(cin, phone);

    Customer customer(customerName, phone);

    vector<Booking*> bookings;

    int choice;

    do {
        cout << "\n--------------- MENU ----------------\n";
        cout << "1. List Movies\n";
        cout << "2. List Shows\n";
        cout << "3. Show Seat Layout\n";
        cout << "4. Book Ticket\n";
        cout << "5. Print Ticket\n";
        cout << "6. Cancel Booking\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter a number.\n";
            continue;
        }

        if (choice == 1) {
            cout << "\nMovies Playing:\n";
            for (int i = 0; i < (int)movies.size(); ++i) {
                cout << i + 1 << ". ";
                movies[i].display();
                cout << "\n";
            }
        }

        else if (choice == 2) {
            int movieChoice;
            cout << "Enter movie number: ";
            cin >> movieChoice;

            if (movieChoice < 1 || movieChoice > (int)movies.size()) {
                cout << "Invalid movie choice.\n";
                continue;
            }

            cout << "\nShows for " << movies[movieChoice - 1].getTitle() << ":\n";

            for (const Show& show : shows) {
                if (show.getMovie() == &movies[movieChoice - 1])
                    show.displayInfo();
            }
        }

        else if (choice == 3) {
            int id;
            cout << "Enter show ID: ";
            cin >> id;

            Show* selectedShow = nullptr;

            for (Show& show : shows) {
                if (show.getShowId() == id) {
                    selectedShow = &show;
                    break;
                }
            }

            if (selectedShow == nullptr) {
                cout << "Invalid show ID.\n";
                continue;
            }

            selectedShow->displaySeats();
        }

        else if (choice == 4) {
            int id, count;
            cout << "Enter show ID: ";
            cin >> id;

            Show* selectedShow = nullptr;

            for (Show& show : shows) {
                if (show.getShowId() == id) {
                    selectedShow = &show;
                    break;
                }
            }

            if (selectedShow == nullptr) {
                cout << "Invalid show ID.\n";
                continue;
            }

            selectedShow->displaySeats();

            cout << "How many seats? ";
            cin >> count;

            if (count <= 0 || count > 12) {
                cout << "Invalid seat count.\n";
                continue;
            }

            vector<int> seatNumbers;
            bool duplicate = false;

            for (int i = 0; i < count; ++i) {
                int seatNumber;
                cout << "Enter seat number " << i + 1 << ": ";
                cin >> seatNumber;

                for (int oldSeat : seatNumbers) {
                    if (oldSeat == seatNumber)
                        duplicate = true;
                }

                seatNumbers.push_back(seatNumber);
            }

            if (duplicate) {
                cout << "Same seat selected more than once. Booking rejected.\n";
                continue;
            }

            Booking* booking =
                service.createBooking(&customer, selectedShow, seatNumbers);

            if (booking == nullptr)
                continue;

            cout << "Total Amount: Rs. "
                 << booking->getTotalAmount() << "\n";

            int paymentChoice;
            cout << "\nPayment Method:\n";
            cout << "1. UPI\n";
            cout << "2. Card\n";
            cout << "3. Cash\n";
            cout << "Enter choice: ";
            cin >> paymentChoice;

            shared_ptr<Payment> payment;

            if (paymentChoice == 1) {
                string upi;
                cout << "Enter UPI ID: ";
                cin >> upi;
                payment = make_shared<UpiPayment>(upi);
            }
            else if (paymentChoice == 2) {
                string card;
                cout << "Enter card number: ";
                cin >> card;
                payment = make_shared<CardPayment>(card);
            }
            else if (paymentChoice == 3) {
                payment = make_shared<CashPayment>();
            }
            else {
                cout << "Invalid payment method. Booking cancelled.\n";
                delete booking;
                continue;
            }

            if (service.makePayment(booking, payment)) {
                cout << "Payment successful. Booking confirmed.\n";
                bookings.push_back(booking);
                printer.print(*booking);
            }
            else {
                delete booking;
            }
        }

        else if (choice == 5) {
            int bookingId;
            cout << "Enter booking ID: ";
            cin >> bookingId;

            Booking* found = nullptr;

            for (Booking* booking : bookings) {
                if (booking->getBookingId() == bookingId) {
                    found = booking;
                    break;
                }
            }

            if (found == nullptr) {
                cout << "Booking not found.\n";
            }
            else if (found->getStatus() != BookingStatus::CONFIRMED) {
                cout << "Ticket is not confirmed.\n";
            }
            else {
                printer.print(*found);
            }
        }

        else if (choice == 6) {
            int bookingId;
            cout << "Enter booking ID: ";
            cin >> bookingId;

            Booking* found = nullptr;

            for (Booking* booking : bookings) {
                if (booking->getBookingId() == bookingId) {
                    found = booking;
                    break;
                }
            }

            if (found == nullptr) {
                cout << "Booking not found.\n";
            }
            else if (found->getStatus() == BookingStatus::CANCELLED) {
                cout << "Booking is already cancelled.\n";
            }
            else {
                service.cancelBooking(found);
            }
        }

        else if (choice == 7) {
            cout << "Thank you!\n";
        }

        else {
            cout << "Invalid menu choice.\n";
        }

    } while (choice != 7);

    for (Booking* booking : bookings)
        delete booking;

    return 0;
}
