#include <iostream>
#include <fstream>
using namespace std;
class CreditCard{
private:
    struct cc{
        string CardOwnerName;
        int CardNumber;
        int Pincode;
        float Wallet;
    };
    cc Card[1000];
    int i=0;
public:
    CreditCard()
    {
        ifstream r("Credit Card.txt");
        while(!r.eof())
        {
            r >>  Card[i].CardOwnerName >> Card[i].CardNumber >> Card[i].Pincode >> Card[i].Wallet;
            i++;
        }
        r.close();
    }
    int GetPin(int userindex){
        return Card[userindex].Pincode;
    }
    bool AccessCard(int userindex,int Pin)
    {
        if(Card[userindex].CardNumber>-1)
        {
            if (Pin==Card[userindex].Pincode)
            {
                cout<<"Correct Pincode"<<endl;
                return true;
            }
            else
            {
                cout<<"Wrong pincode please try again"<<endl;
                return false;
            }
        }
        else
        {
            cout<<"Card does not exist"<<endl;
            return false;
        }
    }
    void ChargeCard(int userindex,float price){
        float amount=Card[userindex].Wallet;
        Card[userindex].Wallet=price+amount;
        update();
    }
    void AddCard(string CardOwnrName,int CardNum,int Pin )
    {
        Card[i].CardOwnerName=CardOwnrName;
        Card[i].CardNumber=CardNum;
        Card[i].Pincode=Pin;
        Card[i].Wallet=0;
        i++;
        update();
    }
    void EditCard(int userindex,string NewCardOwnrName,int NewCardNum,int NewPin)
    {
        Card[userindex].CardOwnerName=NewCardOwnrName;
        Card[userindex].CardNumber=NewCardNum;
        Card[userindex].Pincode=NewPin;
        update();
    }
    void RemoveCard(int userindex)
    {
        Card[userindex].CardNumber=-1;
        update();
    }
    void SetWallet(int userindex,float w)
    {
        Card[userindex].Wallet=w;
        update();
    }
    float GetWallet(int userindex)
    {
        float user=Card[userindex].Wallet;
        return (user);
    }
    void update()
    {
        ofstream w;
        w.open("Credit Card.txt");
        for(int j=0;j<i;j++)
        {
                w << Card[j].CardOwnerName <<"    "<< Card[j].CardNumber <<"    "<< Card[j].Pincode <<"    "<< Card[j].Wallet<<endl;
        }
    }
};
class User{
private:
    int i=0;
    struct user{
        int id=1;
        string username;
        string password;
        float MoneySpent;
    };
    int userindex=0;
    CreditCard c;
    user F[1000];
public:
    User()
    {
        ifstream myfile("User.txt");
        while(!myfile.eof())
        {
            myfile >>F[i].id >> F[i].username >> F[i].password >> F[i].MoneySpent ;
            i++;
        }
        myfile.close();
    }
    int login(string Username, string Password)
    {
        bool found=false;
        while(userindex<i)
        {
            if(Username==F[userindex].username)
            {
                 if(Password==F[userindex].password)
                {
                    cout<<"Access Granted"<<endl;
                    found=true;
                    return userindex;
                }
                else
                {
                    cout<<"Wrong password"<<endl;
                    userindex=0;
                    return -1;
                }
            }
            userindex++;
        }
        if(found==false)
        {
            cout<<"Username not found"<<endl;
            userindex=0;
            return -1;
        }
        return false;
    }
    
    bool DiscountOrNo(int index)
    {
        if (F[index].MoneySpent>=10000)
        {
            cout<<"You have 20% discount"<<endl;
            F[index].MoneySpent=0;
            return true;
        }
        else
            return false;
    }
    void EditCredentials(string Newname,string Newpass)
    {
        F[userindex].password=Newpass;
        F[userindex].username=Newname;
        update();
    }
    void signup(string Username,string Pass,string CardName,int CardNum,int Pin)
    {
        F[i].id=i+1;
        F[i].username=Username;
        F[i].password=Pass;
        F[i].MoneySpent=0;
        c.AddCard(CardName, CardNum, Pin);
        i++;
        update();
    }
    void SetMoneySpent(int index,float amount)
    {
        float a;
        float money=F[index].MoneySpent;
        a=amount+money;
        F[index].MoneySpent=a;
        update();
    }
    float GetMoneySpent()
    {
        return F[userindex].MoneySpent;
    }
    
    void update()
    {
        ofstream w;
        w.open("User.txt");
        for(int j=0;j<i;j++)
            w<<F[j].id<<"    "<<F[j].username<<"    "<<F[j].password<<"    "<<F[j].MoneySpent<<endl;
        w.close();
    }
};
class Product{
public:
    int id=0;
    string Name;
    float Price;
    int quantity;
    string category;
    string marketname;
    void DisplayProduct()
    {
        cout<<id<<"   "<<Name<<"   "<<Price<<"   "<<quantity<<"   "<<category<<"    "<<marketname<<endl;
    }
    
    void EditProduct(string n,float pr,int q, string c, string market)
    {
        Name=n;
        Price=pr;
        quantity=q;
        category=c;
        marketname=market;
    }
    void AddProduct(int s,string n,float pr,int q, string c,string market)
    {
        id=s+1;
        Name=n;
        Price=pr;
        quantity=q;
        category=c;
        marketname=market;
    }
    
    void RemoveProduct()
    {
        id=-1;
    }
};
class SuperMarket{
private:
    int index=0;
    Product market[500];
public:
    SuperMarket()
    {
        ifstream myfile("p.txt");
        while(!myfile.eof())
        {
            myfile >>market[index].id >> market[index].Name >> market[index].Price >> market[index].quantity >>market[index].category>>market[index].marketname;
            index++;
        }
        myfile.close();
    }
    void ReduceQuantity(int id,int q){
        market[id].quantity=market[id].quantity-q;
        if(market[id].quantity==0)
            market[id].RemoveProduct();
        update();
    }
    void AddQuantity(string n,int q)
    {
        int i=0;
        while(market[i].Name!=n)
        {
            i++;
        }
        market[i].quantity=market[i].quantity+q;
        update();
    }
    float GetPrice(int id)
    {
        return (market[id].Price);
    }
    string GetName(int id){
        return market[id].Name;
    }
    int GetQuantity(int id){
        return market[id].quantity;
    }
    int GetId(int id){
        return market[id].id;
    }
    void DisplayMarketProducts(){
        for(int i=0;i<index;i++)
        {
            if(market[i].id!=-1){
                market[i].DisplayProduct();
            }
        }
    }
    void DisplayMarketCategories()
    {
            ifstream r("Categories.txt");
            string category;
            while(!r.eof())
            {
                r >> category;
                cout<<category<<endl;
            }
            r.close();
    }
    void AddMarketProducts(string na,float pr,int q,string category,string markt)
    {
        market[index].AddProduct(index,na,pr,q,category,markt);
        index++;
        update();
    }
    bool RemoveMarketProducts(int ids)
    {
        int j=0;
        while (j<index)
        {
            if(market[j].id==ids)
            {
                market[j].id=-1;
                update();
                return true;
            }
            j++;
        }
        return  false;
    }
    bool EditMarketProducts(int ids,string na,float pr,int q,string category,string markt){
        int j=0;
        while (j<index)
        {
            if(market[j].id==ids)
            {
                market[j].EditProduct(na, pr, q, category, markt);
                update();
                return true;
            }
            j++;
        }
        return  false;
    }
    void update()
    {
        ofstream w("p.txt");
        for(int i=0;i<index;i++)
        {
            if(market[i].id!=-1)
                w << market[i].id <<"    "<< market[i].Name <<"    "<< market[i].Price <<"    "<< market[i].quantity <<"    "<<market[i].category<<"    "<<market[i].marketname<<endl;
        }
    }
};
class cart{
private:
    Product Cart[500];
    SuperMarket s;
    float Minimum=30;
    User u;
    CreditCard c;
    int index=0;
public:
    bool Add(int id,int q){
        id--;
        if(s.GetQuantity(id)-q>=0)
        {
            Cart[index].Name=s.GetName(id);
            Cart[index].id=s.GetId(id);
            Cart[index].quantity=q;
            Cart[index].Price=s.GetPrice(id);
            s.ReduceQuantity(id,q);
            index++;
            return true;
        }
        else
        {
            cout<<"Not enough of this product is available"<<endl;
            return false;
        }
            
    }
    void Remove(int id){
        if(Cart[id].Name!="")
        {
            s.AddQuantity(Cart[id].Name, Cart[id].quantity);
            Cart[id].quantity=0;
        }
    }
    void Reset(){
        for(int i=0;i<index;i++)
        {
            s.AddQuantity(Cart[i].Name, Cart[i].quantity);
            Cart[i].id=0;
            Cart[i].Name="";
            Cart[i].Price=0;
            Cart[i].marketname="";
            Cart[i].category="";
            Cart[i].quantity=0;
        }
        index=0;
    }
    void ChangeQuantity(int id,int q)
    {
        s.AddQuantity(Cart[id].Name, Cart[id].quantity-q);
        Cart[id].quantity=q;
    }
    float CartTotalPrice(){
        float TotalPrice=0;
        for (int i=0;i<index;i++){
            if(Cart[i].id!=-1)
                TotalPrice=TotalPrice+(Cart[i].Price*Cart[i].quantity);
        }
        return TotalPrice;
    }
    void DisplayCart(){
        for(int i=0;i<index;i++)
        {
            if(Cart[i].quantity!=0)
                cout<<i<<"    "<<Cart[i].Name<<"    "<<Cart[i].Price<<"    "<<Cart[i].quantity<<endl;
        }
        cout<<endl;
        
    }
    float AllowCheckout(int index){
        float Checkout=0;
        if(CartTotalPrice()>=Minimum)
        {
            if(u.DiscountOrNo(index)==true)
            {
                Checkout=CartTotalPrice()*0.8;
            }
            else
            {
                Checkout=CartTotalPrice();
            }
            return Checkout;
        }
        else
        {
            cout<<"You need to get items of atleast 30 pounds total"<<endl;
            return 0;
        }
           
    }
    bool pay(int index,int pin,bool rush){
        float wallet;
        wallet=c.GetWallet(index);
        float amount;
        amount=AllowCheckout(index);
        if(wallet>=amount && amount>0 && c.AccessCard(index, pin)==1)
        {
            if(pin==c.GetPin(index))
            {
                if(rush==true)
                {
                    c.SetWallet(index, (wallet-amount-20));
                    u.SetMoneySpent(index,(amount+20));
                    cout<<"Payment successful"<<endl;
                    cout<<"Current balance is: ";
                    wallet=c.GetWallet(index);
                    cout<<wallet<<endl;
                    cout<<"Amount paid is: ";
                    cout<<(amount+20)<<endl;
                    return true;
                }
                else
                {
                    c.SetWallet(index, (wallet-amount));
                    u.SetMoneySpent(index,amount);
                    cout<<"Payment successful"<<endl;
                    cout<<"Current balance is: ";
                    wallet=c.GetWallet(index);
                    cout<<wallet<<endl;
                    cout<<"Amount paid is: ";
                    cout<<amount<<endl;
                    return true;
                }
            }
            else
            {
                Reset();
                cout<<"Wrong pin"<<endl;
                return false;
            }
        }
        else
        {
            Reset();
            cout<<"Not enough in balance or not enough of this product is available"<<endl;
            return false;
        }
    }
};
int main()
{
    SuperMarket s;
    User u;
    CreditCard c;
    cart cart;
    int attempts=3;
    string username;
    string password;
    char option,rush;
    int option2;
    int loginSucceeded=-1;
    string CardName;
    int CardNum;
    int pin;
    string ProductName;
    float price;
    int quantity;
    string category;
    string marketname;
    int productid;
    int NumToAdd;
    float Amount;
    string username1,password1;
    cout<< "--------------------------------------------- Welcome to instashop ---------------------------------------------"<<endl;
    cout<<endl;
    cout<<"Are you a User(U) or an Admin(A): ";
    cin>>option;
    if(option=='u' || option=='U')
    {
        cout<<"1: Login"<<endl;
        cout<<"2: signup"<<endl;
        cin>>option2;
        if(option2==1)
        {
            cout<<"Attempts: ";cout<<attempts<<endl;
            cout<<"Enter username: "<<endl;
            cin>>username;
            cout<<"Enter password: "<<endl;
            cin>>password;
            loginSucceeded=u.login(username, password);
            while(attempts>1)
            {
                if(loginSucceeded==-1)
                {
                    attempts--;
                    cout<<"Attempts: ";cout<<attempts<<endl;
                    cout<<"Enter username: "<<endl;
                    cin>>username1;
                    cout<<"Enter password: "<<endl;
                    cin>>password1;
                    loginSucceeded=u.login(username1, password1);
                }
                else
                {
                    break;
                }
            }
            if(loginSucceeded==-1)
            {
                cout<<"No more attempts"<<endl;
            }
            else
            {
                cout<<"1: Edit credintials "<<endl;
                cout<<"2: Start shopping "<<endl;
                cout<<"3: Remove card"<<endl;
                cin>>option2;
                if(option2==2)
                {
                    option='y';
                    while(option=='y' || option=='Y')
                    {
                        cout<<"1: Add to cart"<<endl;
                        cout<<"2: Remove from cart"<<endl;
                        cout<<"3: Reset cart"<<endl;
                        cout<<"4: Edit product quantity"<<endl;
                        cin>>option2;
                        switch (option2) {
                            case 1:
                                s.DisplayMarketProducts();
                                option='y';
                                while(option=='y' || option=='Y')
                                {
                                    cout<<"Enter the id of the item you want to add: ";
                                    cin>>option2;
                                    cout<<"Enter the quantity you want from this item: ";
                                    cin>>quantity;
                                    cart.Add(option2, quantity);
                                    cout<<"Do you want to continue adding products to cart?";
                                    cin>>option;
                                    cart.DisplayCart();
                                    cout<<"Total price is: ";
                                    cout<<cart.CartTotalPrice()<<endl;
                                }
                                break;
                            case 2:
                                cart.DisplayCart();
                                option='y';
                                while(option=='y' || option=='Y')
                                {
                                    cout<<"Enter the id of the item you want to remove: ";
                                    cin>>option2;
                                    cart.Remove(option2);
                                    cart.DisplayCart();
                                    cout<<"Total price is: ";
                                    cout<<cart.CartTotalPrice()<<endl;
                                    cout<<"Do you want to continue removing items from cart?";
                                    cin>>option;
                                }
                                break;
                            case 3:
                                cart.Reset();
                                cout<<"Reset successful"<<endl;
                                break;
                            case 4:
                                cart.DisplayCart();
                                option='y';
                                while(option=='y' || option=='Y')
                                {
                                    cout<<"Enter the id of the item you want change its quantity: ";
                                    cin>>option2;
                                    cout<<"Enter the new quantity you want: ";
                                    cin>>quantity;
                                    cart.ChangeQuantity(option2,quantity);
                                    cout<<"Total price is: ";
                                    cout<<cart.CartTotalPrice()<<endl;
                                    cart.DisplayCart();
                                    cout<<"Do you want to edit another product quantity? (Y/N)";
                                    cin>>option;
                                }
                                break;
                            
                            default:
                                break;
                        }
                        cout<<"Do you want to continue shopping?"<<endl;
                        cin>>option;
                    }
                    cart.DisplayCart();
                    cout<<"Total price is: ";
                    cout<<cart.CartTotalPrice()<<endl;
                    cout<<"Do you want payment by cash(C) or card(D)"<<endl;
                    cin>>option;
                    cout<<"Do you want rush order which will add 20 extra dollars to the total amount?(Y/N)"<<endl;
                    cin>>rush;
                    if(option=='d' || option=='D')
                    {
                        cout<<"Enter pin: ";
                        cin>>pin;
                        if(cart.pay(loginSucceeded,pin,rush)==true)
                        {
                            cout<<"Bye!!!"<<endl;
                        }
                    }
                    else
                        cout<<"Pay by cash when delivery man arrives"<<endl;
                    option2=0;
                }
                if(option2==3)
                {
                    c.RemoveCard(loginSucceeded);
                }
                if(option2==1)
                {
                    cout<<"1: Edit username or password"<<endl;
                    cout<<"2: Edit Credit card details"<<endl;
                    cout<<"3: Charge card"<<endl;
                    cin>>option2;
                    switch(option2)
                    {
                        case 1:
                            cout<<"Enter new username: ";
                            cin>>username;
                            cout<<"Enter new password: ";
                            cin>>password;
                            u.EditCredentials(username, password);
                            break;
                        case 2:
                            cout<<"Enter new card name: ";
                            cin>>CardName;
                            cout<<"Enter new card number: ";
                            cin>>CardNum;
                            cout<<"Enter new pin: ";
                            cin>>pin;
                            c.EditCard(loginSucceeded, CardName, CardNum, pin);
                            break;
                        case 3:
                            cout<<"Enter the amount you want to charge your card with: ";
                            cin>>Amount;
                            c.ChargeCard(loginSucceeded, Amount);
                            break;
                        default:
                            break;
                    }
                }
                
            }
        }
        else
        {
            cout<<"Please enter username you want: ";
            cin>>username;
            cout<<"Please enter password you want: ";
            cin>>password;
            cout<<"Please enter credit card name: ";
            cin>>CardName;
            cout<<"Please enter credit card num: ";
            cin>>CardNum;
            cout<<"Please enter pincode: ";
            cin>>pin;
            u.signup(username, password, CardName, CardNum, pin);
        }
    }
    else
    {
        cout<<"Attempts: ";cout<<attempts<<endl;
        cout<<"Admin username: "<<endl;
        cin>>username;
        cout<<"Admin password: "<<endl;
        cin>>password;
        loginSucceeded=u.login(username, password);
        while(attempts>1)
        {
            if(loginSucceeded==-1)
            {
                attempts--;
                cout<<"Attempts: ";cout<<attempts<<endl;
                cout<<"Admin username: "<<endl;
                cin>>username;
                cout<<"Admin password: "<<endl;
                cin>>password;
                loginSucceeded=u.login(username, password);
            }
            else
            {
                break;
            }
        }
        if(loginSucceeded==-1)
        {
            cout<<"No more attempts"<<endl;
        }
        else
        {
            option='y';
            while(option=='y' || option=='Y')
            {
                cout<<"1: Display products: "<<endl;
                cout<<"2: Add products"<<endl;
                cout<<"3: Edit products"<<endl;
                cout<<"4: Remove products"<<endl;
                cout<<"5: Display market categories"<<endl;
                cin>>option2;
                switch (option2) {
                    case 1:
                        s.DisplayMarketProducts();
                        break;
                    case 2:
                        cout<<"Please enter number of products to add: ";
                        cin>>NumToAdd;
                        for(int i=0;i<NumToAdd;i++)
                        {
                            cout<<"Please enter product name: ";
                            cin>>ProductName;
                            cout<<"Please enter product price: ";
                            cin>>price;
                            cout<<"Please enter product quantity";
                            cin>>quantity;
                            cout<<"Please enter product category";
                            cin>>category;
                            cout<<"Please enter product market name";
                            cin>>marketname;
                            s.AddMarketProducts(ProductName, price, quantity, category, marketname);
                        }
                        break;
                    case 3:
                        s.DisplayMarketProducts();
                        cout<<endl;
                        cout<<"Please enter number of products to edit: ";
                        cin>>NumToAdd;
                        for(int i=0;i<NumToAdd;i++)
                        {
                            cout<<"Please enter id of product you want to edit";
                            cin>>productid;
                            cout<<"Please enter new product name: ";
                            cin>>ProductName;
                            cout<<"Please enter new product price: ";
                            cin>>price;
                            cout<<"Please enter new product quantity";
                            cin>>quantity;
                            cout<<"Please enter new product category";
                            cin>>category;
                            cout<<"Please enter new product market name";
                            cin>>marketname;
                            s.EditMarketProducts(productid, ProductName, price, quantity, category, marketname);
                        }
                        break;
                    case 4:
                        s.DisplayMarketProducts();
                        cout<<"Please enter number of products to remove: ";
                        cin>>NumToAdd;
                        for(int i=0;i<NumToAdd;i++)
                        {
                            cout<<"Please enter id of product you want to remove";
                            cin>>productid;
                            s.RemoveMarketProducts(productid);
                        }
                        break;
                    case 5:
                        s.DisplayMarketCategories();
                        break;
                    default:
                        break;
            }
                cout<<"Do you want to continue (Y/N): ";
                cin>>option;
            }
        }
    }
}
