# Movie Ticket Booking System — TCS-504

C++ console project for System Design Assignment 1.

## Features
1. List movies
2. List shows for a movie
3. Display seat layout
4. Book one or more seats
5. Seat pricing: Silver ₹150, Gold ₹250, Platinum ₹400
6. UPI/Card/Cash payment
7. Print ticket
8. Cancel booking and release seats

## OOP concepts
- Encapsulation: private data members + public methods
- Abstraction: abstract Payment class
- Inheritance: UpiPayment, CardPayment, CashPayment
- Runtime polymorphism: Payment pointer calls pay()
- Compile-time polymorphism: overloaded Movie constructors
- Static member: Booking::nextBookingId
- this keyword: Booking::setPayment
- Composition: Cinema→Screen, Screen→Seat, Show→ShowSeat
- Aggregation: Show→Movie and Show→Screen
- Association: Customer interacts with BookingService
- Dependency Inversion: BookingService receives a Payment abstraction instead of constructing a specific payment type

## Compile
The assignment says one class per file and no header files. Therefore main.cpp includes the .cpp class files and is compiled as one translation unit.

```bash
g++ -std=c++17 main.cpp -o movie_booking
./movie_booking
```

On Windows MinGW:
```bash
g++ -std=c++17 main.cpp -o movie_booking.exe
movie_booking.exe
```

## GitHub
Upload all `.cpp` files and this README.md into one repository.
