#include <iostream>
#include <vector>

#include "fn/container_utility.h"
#include "fn/each.h"
#include "fn/filter.h"
#include "fn/fmap.h"

#include "fit/placeholders.h"

using namespace std;

int main() {

    // vector
    cout << "vector" << endl;
    std::vector<int> vectorValues = { 1, 2, 3, 4, 5 };

    vectorValues
        | fn::filter(fit::_1 > 1)
        | fn::fmap(fit::_1 * 10)
        | fn::each([] (auto val) { cout << val << endl; });



    // list
    cout << "list" << endl;
    std::list<int> listValues = { 1, 2, 3, 4, 5 };

    listValues
        | fn::filter(fit::_1 > 1)
        | fn::fmap(fit::_1 * 10)
        | fn::each([] (auto val) { cout << val << endl; });



    // set
    cout << "set" << endl;
    std::set<int> setValues = { 1, 2, 3, 4, 5 };

    setValues
        | fn::filter(fit::_1 > 1)
        | fn::fmap(fit::_1 * 10)
        | fn::each([] (auto val) { cout << val << endl; });



    // map
    cout << "map" << endl;
    std::map<int, int> mapValues =
        { make_pair(1, 1), make_pair(2, 2), make_pair(3, 3),
          make_pair(4, 4), make_pair(5, 5) };

    mapValues
        | fn::filter(fn::on_map_value(fit::_1 > 1))
        | fn::fmap(fn::on_map_value(fit::_1 * 10))
        | fn::each(fn::on_map_value([] (auto val) { cout << val << endl; }));

}
