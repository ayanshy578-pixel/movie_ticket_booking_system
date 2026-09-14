class Payment {
public:
    // ABSTRACTION: common payment contract.
    virtual bool pay(double amount) = 0;

    virtual string getMethod() const = 0;

    virtual ~Payment() = default;
};
