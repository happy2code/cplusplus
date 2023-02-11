// Lambdas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

struct FoodItem {
    std::string name;
    float cost_in_rupees;
};

std::ostream& operator << (std::ostream& os, const FoodItem& item)
{
    os << item.name << " : Rs " << item.cost_in_rupees << std::endl;
    return os;
}

std::vector Menu = {
    FoodItem { "Idly", 65 },
    FoodItem { "Onion Rava Dosai", 131},
    FoodItem { "Masala Dosai", 126},
    FoodItem { "Podi Utappam", 126},
    FoodItem { "Poori", 115},
    FoodItem { "Special Meals", 319},
    FoodItem { "Quick Lunch", 189},
    FoodItem { "Sambar Rice", 94},
    FoodItem { "Coffee", 50},
    FoodItem { "Horlicks", 89},
};

void PrintCostlierThan100(const FoodItem& item)
{
    if (item.cost_in_rupees > 100) std::cout << item;
}

void PrintCostlierThan(const FoodItem& item, float price)
{
    if (item.cost_in_rupees > price) std::cout << item;
}
struct PrintCostlierThan
{
    float _cost;
    PrintCostlierThan(float cost) : _cost(cost) {};
    void operator()(const FoodItem& item) {
        if (item.cost_in_rupees > _cost) {
            std::cout << item;
        }
    }
};

int main()
{
    for (auto item : Menu)
    {
        if (item.cost_in_rupees > 100) {
            std::cout << item;
        }
    }

    std::for_each(Menu.begin(), Menu.end(), PrintCostlierThan100);
    std::for_each(Menu.begin(), Menu.end(), std::bind(PrintCostlierThan, std::placeholders::_1, 200));
    std::for_each(Menu.begin(), Menu.end(), PrintCostlierThan{ 110 });

    int cost = 90;
    std::for_each(Menu.begin(), Menu.end(), [=](FoodItem& item) {  if (item.cost_in_rupees < cost) {
        std::cout << item;
    }});


}

