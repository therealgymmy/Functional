#include <iostream>
#include <vector>

#include "fn/container_utility.h"
#include "fn/each.h"
#include "fn/filter.h"
#include "fn/fmap.h"
#include "fn/reduce.h"
#include "fn/to.h"

#include "fit/placeholders.h"

using namespace fit;
using namespace fn;
using namespace std;

int main() {

    // vector
    cout << "vector" << endl;
    vector<int> vectorValues = { 1, 2, 3, 4, 5 };

    int vectorSum = vectorValues
        | filter(_1 > 1)
        | to(type<set>())
        | to(type<list>())
        | fmap(_1 * 10)
        | each([] (auto val) { cout << val << endl; })
        | reduce(_1 + _2);

    cout << vectorSum << endl;
    cout << endl;

    vector<int*> pointers;
    auto uniqueAddresses = pointers
        | to(type<set>())
        | to(type<list>());



    // list
    cout << "list" << endl;
    list<int> listValues = { 1, 2, 3, 4, 5 };

    int listSum = listValues
        | filter(_1 > 1)
        | fmap(_1 * 10)
        | each([] (auto val) { cout << val << endl; })
        | reduce(_1 + _2, 1000);

    cout << listSum << endl;
    cout << endl;



    // set
    cout << "set" << endl;
    set<int> setValues = { 1, 2, 3, 4, 5 };

    int setSum = setValues
        | filter(_1 > 1)
        | fmap(_1 * 10)
        | each([] (auto val) { cout << val << endl; })
        | reduce(_1 + _2);


    cout << setSum << endl;
    cout << endl;



    // map
    cout << "map" << endl;
    map<int, int> mapValues =
        { make_pair(1, 1), make_pair(2, 2), make_pair(3, 3),
          make_pair(4, 4), make_pair(5, 5) };

    int mapSum = mapValues
        | filter(on_map_value(_1 > 1))
        | fmap(on_map_value(_1 * 10))
        | each(on_map_value([] (auto val) { cout << val << endl; }))
        | reduce(on_map_value(_1 + _2), 1000);

    cout << mapSum << endl;
    cout << endl;

}
