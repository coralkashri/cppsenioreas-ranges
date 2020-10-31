#include <iostream>
#include <vector>
#include <ranges>
#include "custom_iterator.h"

int main() {
    std::vector<int> ints{0,1,2,3,4,5};
    my_item_collection<std::vector, int> custom_ints2;
    custom_ints2.add_item(5, 3);
    custom_ints2.add_item(2, 7);
    custom_ints2.add_item(1, 4);

    auto even = [](auto &elem){ return elem.item() % 2 == 0; };

    for (auto &elem : custom_ints2 | std::views::filter(even)) {
        std::cout << elem.item() << ' ';
    }
    return 0;
}
