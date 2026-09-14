class UpiPayment : public Payment {
private:
    string upiId;

public:
    UpiPayment(string upiId) : upiId(upiId) {}

    bool pay(double amount) override {
        if (upiId.empty())
            return false;

        cout << "Processing UPI payment of Rs. " << amount << "...\n";
        return true;
    }

    string getMethod() const override {
        return "UPI";
    }
};
