#include <iostream>
#include <vector>

#include "fn/container_utility.h"
#include "fn/each.h"
#include "fn/filter.h"
#include "fn/fmap.h"
#include "fn/reduce.h"

#include "fit/placeholders.h"

using namespace std;

int main() {

    // vector
    cout << "vector" << endl;
    std::vector<int> vectorValues = { 1, 2, 3, 4, 5 };

    int vectorSum = vectorValues
        | fn::filter(fit::_1 > 1)
        | fn::fmap(fit::_1 * 10)
        | fn::each([] (auto val) { cout << val << endl; })
        | fn::reduce(fit::_1 + fit::_2);

    cout << vectorSum << endl;
    cout << endl;



    // list
    cout << "list" << endl;
    std::list<int> listValues = { 1, 2, 3, 4, 5 };

    int listSum = listValues
        | fn::filter(fit::_1 > 1)
        | fn::fmap(fit::_1 * 10)
        | fn::each([] (auto val) { cout << val << endl; })
        | fn::reduce(fit::_1 + fit::_2, 1000);

    cout << listSum << endl;
    cout << endl;



    // set
    cout << "set" << endl;
    std::set<int> setValues = { 1, 2, 3, 4, 5 };

    int setSum = setValues
        | fn::filter(fit::_1 > 1)
        | fn::fmap(fit::_1 * 10)
        | fn::each([] (auto val) { cout << val << endl; })
        | fn::reduce(fit::_1 + fit::_2);


    cout << setSum << endl;
    cout << endl;



    // map
    cout << "map" << endl;
    std::map<int, int> mapValues =
        { make_pair(1, 1), make_pair(2, 2), make_pair(3, 3),
          make_pair(4, 4), make_pair(5, 5) };

    int mapSum = mapValues
        | fn::filter(fn::on_map_value(fit::_1 > 1))
        | fn::fmap(fn::on_map_value(fit::_1 * 10))
        | fn::each(fn::on_map_value([] (auto val) { cout << val << endl; }))
        | fn::reduce(fn::on_map_value(fit::_1 + fit::_2), 1000);

    cout << mapSum << endl;
    cout << endl;

}
