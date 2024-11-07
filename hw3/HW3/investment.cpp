//class Investment
//{
//public:
//    Investment(string name, int price);
//    string name() const;
//    int purchasePrice() const;
//    virtual bool fungible() const;
//    virtual string description() const = 0;
//    virtual ~Investment();
//private:
//    string m_name;
//    int m_price;
//};
//Investment::Investment(string name, int price) : m_name(name), m_price(price)
//{}
//Investment::~Investment()
//{}
//string Investment::name() const 
//{
//    return(m_name); 
//}
//int Investment::purchasePrice() const
//{
//    return(m_price); 
//}
//bool Investment::fungible() const 
//{
//    return false; 
//}
////Painting
//class Painting : public Investment
//{
//public:
//    Painting(string name, int price);
//    string description() const;
//    ~Painting(); 
//};
//Painting::Painting(string name, int price) :Investment(name, price)
//{}
//string Painting::description() const
//{
//    return("painting");
//}
//Painting::~Painting()
//{
//    cout << "Destroying " + name() + ", a painting" << endl;
//}
////Stock 
//class Stock : public Investment
//{
//public: 
//    Stock(string name, int price, string ticker);
//    string description() const; 
//    bool fungible() const; 
//    ~Stock();
//private: 
//    string m_ticker; 
//};
//Stock::Stock(string name, int price, string ticker) :Investment(name, price), m_ticker(ticker)
//{}
//string Stock::description() const
//{
//    return("stock trading as " + m_ticker); 
//}
//bool Stock::fungible() const
//{
//    return true;
//}
//Stock::~Stock()
//{
//    cout << "Destroying " + name() + ", a stock holding" << endl;
//}
//class House : public Investment
//{
//public: 
//    House(string name, int price); 
//    string description() const; 
//    ~House(); 
//};
//House::House(string name, int price) :Investment(name, price)
//{}
//string House::description() const
//{
//    return("house"); 
//}
//House::~House()
//{
//    cout << "Destroying the house " + name() << endl; ;
//}
//
//
//
//
//void display(const Investment* inv)
//{
//    cout << inv->name();
//    if (inv->fungible())
//        cout << " (fungible)";
//    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
//}
//
