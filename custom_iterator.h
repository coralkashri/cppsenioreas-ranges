/**
 * Based on iterators customization article on C++ Senioreas:
 * https://cppsenioreas.wordpress.com/2020/10/04/maintain-your-iterations-iterators-customization-part-3/
 * GitHub repository: https://github.com/korelkashri/cppsenioreas-iterators
 */

#ifndef CPPSENIOREAS_RANGES_CUSTOM_ITERATOR_H
#define CPPSENIOREAS_RANGES_CUSTOM_ITERATOR_H

#include <iostream>

/// Concepts

template <template <typename ...> typename Container, typename T>
concept IteratorsFriendlyContainerType = requires (Container<T> container) {
    typename decltype(container)::pointer;
    typename decltype(container)::const_pointer;
    typename decltype(container)::reference;
    typename decltype(container)::const_reference;
    typename decltype(container)::iterator;
    typename decltype(container)::const_iterator;
    typename decltype(container)::reverse_iterator;
    typename decltype(container)::const_reverse_iterator;
    typename decltype(container)::size_type;
};

template <template <typename ...> typename Container, typename T>
requires IteratorsFriendlyContainerType<Container, T>
struct use_collection_iterator {
    typedef typename Container<T>::pointer pointer;
    typedef typename Container<T>::const_pointer const_pointer;
    typedef typename Container<T>::reference reference;
    typedef typename Container<T>::const_reference const_reference;
    typedef typename Container<T>::iterator iterator;
    typedef typename Container<T>::const_iterator const_iterator;
    typedef typename Container<T>::reverse_iterator reverse_iterator;
    typedef typename Container<T>::const_reverse_iterator const_reverse_iterator;
    typedef typename Container<T>::size_type size_type;
};

template <typename T>
concept HasMul = requires() {
    { T() * T() };
};


/// My Item

template <HasMul T>
class my_item {
public:
    my_item(const T &a, const T &b) : value_a(a), value_b (b) {}

    T item() { return value_a * value_b; }
    void set_a(T a) { value_a = a; }
    void set_b(T b) { value_b = b; }

private:
    T value_a, value_b;
};


/// My Collection

template <template <typename ...> typename Container, HasMul ItemT>
using my_collection_iterator = use_collection_iterator<Container, my_item<ItemT>>;

template <template <typename ...> typename Container, HasMul ItemT>
class my_item_collection : public my_collection_iterator<Container, ItemT> {
public:

    // A convenient access to inherited type members
    using base_types = my_collection_iterator<Container, ItemT>;

    /* Custom collection operations */

    void add_item(const ItemT &a, const ItemT &b) {
        items.emplace_back(a, b);
    }

    typename base_types::iterator get_item(size_t idx) {
        auto res = items.begin();
        return std::advance(res, idx);
    }

    /* Required Iterators Access Methods */

    typename base_types::iterator begin() { return items.begin(); }
    typename base_types::iterator end() { return items.end(); }
    [[nodiscard]] typename base_types::const_iterator cbegin() const { return items.cbegin(); }
    [[nodiscard]] typename base_types::const_iterator cend() const { return items.cend(); }
    typename base_types::reverse_iterator rbegin() { return items.rbegin(); }
    typename base_types::reverse_iterator rend() { return items.rend(); }
    [[nodiscard]] typename base_types::const_reverse_iterator crbegin() const { return items.crbegin(); }
    [[nodiscard]] typename base_types::const_reverse_iterator crend() const { return items.crend(); }

    [[nodiscard]] bool empty() const { return items.empty(); }
    [[nodiscard]] typename base_types::size_type size() const { return items.size(); }

private:
    Container<my_item<ItemT>> items;
};

#endif //CPPSENIOREAS_RANGES_CUSTOM_ITERATOR_H
