class CashPayment : public Payment {
public:
    bool pay(double amount) override {
        cout << "Cash payment received: Rs. " << amount << "\n";
        return true;
    }

    string getMethod() const override {
        return "CASH";
    }
};
