#include <iostream>
#include "hash_chain.h"
#include "hash_map.h"
#include <iterator>

using namespace std;

struct HashInt
{
    size_t operator()(int key, int capacity) const
    {
        return key % capacity;
    }
};

int main()
{
    HashTable<int, int, HashInt> hash_table_int(10);
    cout << "Created empty hash table" << endl;
    cout << hash_table_int << endl;

    cout << "Key type: int, value type: int" << endl;
    cout << "Adding one element" << endl;
    hash_table_int.insert_node(10, 10);

    cout << "Adding more elements" << endl;
    hash_table_int.insert_node(1, 1);
    hash_table_int.insert_node(2, 2);
    hash_table_int.insert_node(5, 5);
    hash_table_int.insert_node(8, 8);
    cout << hash_table_int << endl;

    cout << "Adding element that will cause collision" << endl;
    hash_table_int.insert_node(11, 11);
    hash_table_int.insert_node(12, 12);
    hash_table_int.insert_node(15, 15);
    cout << hash_table_int << endl;

    cout << "Current load factor: " << hash_table_int.calc_load_factor() << endl;

    cout << "Deleting element by key (key = 11)" << endl;
    auto hash_start_old = hash_table_int.begin();
    hash_table_int.delete_node(11);
    cout << endl;

    cout << "Let's take a look at all the elements" << endl;
    for (auto hash_start = hash_table_int.begin(); hash_start != hash_table_int.end(); hash_start++)
    {
        cout << *hash_start << endl;
    }

    cout << endl;
    cout << hash_table_int << endl;

    cout << "Getting a whole pair" << endl;
    cout << hash_table_int.get_pair(15) << endl;

    cout << "Adding new elements and triggering a rehash..." << endl;
    hash_table_int.insert_node(16, 16);
    hash_table_int.insert_node(17, 17);
    hash_table_int.insert_node(18, 18);
    hash_table_int.insert_node(19, 19);
    hash_table_int.insert_node(20, 20);
    hash_table_int.insert_node(21, 21);
    cout << hash_table_int << endl;

    cout << "Clearing whole table" << endl;

    hash_table_int.clear();
    cout << hash_table_int << endl;
    cout << "Current load factor: " << hash_table_int.calc_load_factor() << endl;
    static_assert(
        std::bidirectional_iterator<HashIterator<int, int, HashInt>>,
        "error, dont pass checking");
    return 0;
}
