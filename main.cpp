#include <iostream>
#include <vector>
#include <ranges>
#include <map>
#include "custom_iterator.h" // https://cppsenioreas.wordpress.com/2020/10/04/maintain-your-iterations-iterators-customization-part-3/

#define EXAMPLE 6

int main() {
    std::vector<int> ints = {1, 2, 3, 4, 5, 6};

    auto even = [](auto elem) { return elem % 2 == 0; };
    auto square = [](auto elem) { return elem * elem; };

#if EXAMPLE == 1
    for (int i : ints | std::views::filter(even) | std::views::transform(square)) {
    // Equivalent to:
    // for (int i : std::views::transform(std::views::filter(ints, even), square)) {
    // for (int i : std::ranges::transform_view{std::ranges::filter_view{ints, even}, square}) {
        std::cout << i << ' ';
    }
#elif EXAMPLE == 2
    ints = {1, 3, 5, 7, 9, 11};
    auto odd = [](auto elem) { return elem % 2; };
    auto inc = [](auto elem) { return ++elem; };
    auto notf = [](auto &func) {
        return [&](auto elem) {
            return !func(elem);
        };
    };
    auto range = ints | std::views::filter(notf(odd)) | std::views::transform(inc);
    for (int i : range) { std::cout << i << ' '; }
#elif EXAMPLE == 3
    auto inc = [](auto elem) { return ++elem; };
    auto mul = [](auto elem) { return elem * 2; };
    auto div = [](auto elem) { return elem / 2; };
    auto range = (ints | std::views::transform(inc)) | (std::views::transform(square) | std::views::transform(div));
    for (int i : range) { std::cout << i << ' '; }
#elif EXAMPLE == 4
//    auto range = ints | std::views::take(3);
//    ints = {1, 3, 5, 7, 2, 4, 9, 11};
//    auto range = ints | std::views::take_while([](auto elem) { return elem < 7; });

/*  Split - Join Example
 * ----------------------
    std::string str = "Hello,World,of,C++,ranges";
    auto ranges = str | std::views::split(',');
    for (auto range : ranges) {
        for (auto elem : range) {
            std::cout << elem;
        }
        std::cout << '\n';
    }
    auto join_ranges = ranges | std::views::join;
    for (auto elem : join_ranges) {
        std::cout << elem << " ";
    }
*/
    std::map<std::string, int> my_map;
    my_map.insert({"key1", 2});
    my_map.insert({"key2", 4});
    my_map.insert({"key3", 5});
    my_map.insert({"key4", 6});
    my_map.insert({"key5", 8});
    std::cout << "Keys: ";
    for (auto key : my_map | std::views::keys) {
        std::cout << key << " ";
    }

    std::cout << "\nValues: ";
    for (auto value : my_map | std::views::values) {
        std::cout << value << " ";
    }

#elif EXAMPLE >= 5
    my_item_collection<std::vector, int> custom_ints2;
    custom_ints2.add_item(5, 3);
    custom_ints2.add_item(2, 7);
    custom_ints2.add_item(1, 4);
#endif

#if EXAMPLE == 5
    auto my_item_even = [] <typename T> (my_item<T> &elem){ return elem.item() % 2 == 0; };
    auto my_item_square = [] <typename T> (my_item<T> &elem) {return elem.item() * elem.item(); };

    for (auto elem : custom_ints2 | std::views::filter(my_item_even) | std::views::transform(my_item_square)) {
        std::cout << elem << ' ';
    }
#elif EXAMPLE >= 6
    auto my_item_to_int = [] <typename T> (my_item<T> &elem){ return elem.item(); };

    for (auto elem : custom_ints2 | std::views::transform(my_item_to_int) | std::views::filter(even) | std::views::transform(square)) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
#endif

#if EXAMPLE == 7
    auto new_range = custom_ints2 | std::views::transform(my_item_to_int) | std::views::filter(even) | std::views::transform(square);

    for (auto elem : new_range | std::views::reverse) {
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
#endif


    return EXIT_SUCCESS;
}