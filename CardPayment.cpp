class CardPayment : public Payment {
private:
    string cardNumber;

public:
    CardPayment(string cardNumber) : cardNumber(cardNumber) {}

    bool pay(double amount) override {
        if (cardNumber.empty())
            return false;

        cout << "Processing Card payment of Rs. " << amount << "...\n";
        return true;
    }

    string getMethod() const override {
        return "CARD";
    }
};
