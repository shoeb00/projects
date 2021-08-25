#include<bits/stdc++.h>
using namespace std;

class SalesTask{

    private:
    string reciept; 
    

    public:
    //calculate() calculates the tax, print and returns the total tax and total cost
    pair<float, float> calculate(){
        int quantity = getQuatity();
        string item = getItem();
        float price = getPrice();
        float goodsTax = getGoodsTax(price);
        float importTax = getImportTax(price);
        price = (price + goodsTax + importTax) * quantity;

        cout << quantity << " " << item << ":  " << fixed << setprecision(2) << price << endl;
        pair<float, float> p;
        p.first = price;
        p.second = goodsTax + importTax;
        return p;
    }

    SalesTask(string reciept) {
        this->reciept = reciept;
    }

    private:

    //getQuantity() extract the quatity of each item from the input
    int getQuatity(){
        int i = 0;
        string quantity;
        while(reciept[i] != ' ') quantity.push_back(reciept[i++]); 
        return stoi(quantity);
    }

    //getItem() extracts the item from the input string
    string getItem(){
        int i = 0;
        string item;
        while(reciept[i] != ' ') i++;
        i++;
        size_t found = reciept.find(" at ");
        if(found!=string::npos) item = reciept.substr(i, found-i);
        return item;
    }


    //getPrice() extract the price from the input string and returns it as float
    float getPrice() {
        string price;
        int i = reciept.size()-1;
        while(reciept[i] != ' ') price.push_back(reciept[i--]);
        reverse(price.begin(), price.end());
        return stof(price);
    }

    //getGoodTax() checks whether goods tax is applicable or not
    float getGoodsTax(float price){
        vector<string> no_tax_goods = {
            "chocolate", "book", "pill", 
        };
        bool tax_check; 
        for(auto goods : no_tax_goods){
            size_t check = reciept.find(goods);
            if(check!=string::npos) return 0;
        }
        float tax = 0;
        tax = (price*10)/100;
        return tax;
    }


    //getImportTax() calculates the import tax and round up the value to nearest 0.05
    float getImportTax(float price){
        size_t check_imported = reciept.find(" imported ");
        bool check = string::npos==check_imported ? false : true; 
        float import_tax = 0;
        if(check){
            import_tax = (price*5)/100;
            import_tax = ceil(import_tax * 20) / 20;
        } 
        return import_tax;
    }
};

int main() {
    int inputs;
    cout << "Enter the number of inputs: ";
    cin >> inputs;
    cin.ignore();
    float sales_tax = 0, total = 0;
    for(int i = 0; i < inputs; i++){
        string reciept;
        getline(cin, reciept);
        SalesTask s(reciept);
        pair<float, float> p = s.calculate();
        total += p.first;
        sales_tax += p.second;
    }
    cout << "Sales Taxes: " << fixed << setprecision(2) << sales_tax << endl;
    cout << "Total: " << fixed << setprecision(2) << total << endl;
}