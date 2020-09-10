#include <iostream>
#include <set>
#include <string>
#include <map>

#include <tuple>
#include <memory>
#include <cmath>
#include <random>
#include "random.hpp"
//#include <boost/chrono.hpp>

// {
struct S {
    int n;
    std::string s;
    float d;

    bool operator<(const S &rhs) const {
        // compares n to rhs.n,
        // then s to rhs.s,
        // then d to rhs.d
        return std::tie(n, s, d) < std::tie(rhs.n, rhs.s, rhs.d);
    }
};
// }

template<typename T>
auto get_value(T t) {
    if constexpr (std::is_pointer_v<T>)
        return *t;
    else
        return t;
}

auto SumCpp11() {
    return 0;
}

// old way
template<typename T1, typename... T>
auto SumCpp11(T1 s, T... ts) {
    return s + SumCpp11(ts...);
}


template<typename ...Args>
auto sum(Args ...args) {
    return (args + ... + 0);
}

// or even:

template<typename ...Args>
auto sum2(Args ...args) {
    return (args + ...);
}

template<class T>
T get_random_number(T a, T b) {
    std::random_device generator{std::to_string(time(nullptr))};
    std::mt19937_64 engine(generator());
    std::uniform_real_distribution<double> dist{a, b};
    auto random_number = dist(engine);
    return random_number;
    //return (random_number % 2 == 0) ? random_number : -1;
}

class backoff_time_t {
public:
    std::random_device rd;
    std::mt19937_64 mt;
    std::uniform_real_distribution<double> dist;

    backoff_time_t() : rd{std::to_string(time(nullptr))}, mt{rd()}, dist{1.0, 100.0} {}

    double rand() {
        return dist(mt);
    }
};

int main() {

    using namespace std::literals::chrono_literals;
    using namespace std::literals::string_literals;
    auto s = "Testing ...."s;
    //auto dur = 1h + 2min + 3s + 4ms + 5us + 6ns;
    auto dur = 6ns + 5us;
    std::cout << dur.count() << std::endl;

    //=======================================================================================

    auto rand = get_random_number(1.0, 100.0);
    auto rand2 = get_random_number(1.0, 100.0);
    std::cout << "Random number: " << rand <<  " " << rand2 << std::endl;
    std::cout << "Square root: " << std::sqrt(static_cast<float>(rand)) << std::endl;

    auto *r = new backoff_time_t();
    std::cout << "Random number 2: " << r->rand() << " " << r->rand()  << " " << r->rand() << std::endl;

    // get base random alias which is auto seeded and has static API and internal state
    using Random = effolkronium::random_static;
    std::cout << "Random number 3: "
              << Random::get<Random::common>(1, 100) << " "
              << Random::get<Random::common>(1, 100) << std::endl;
    //=======================================================================================

    std::set<S> mySet;

    // pre C++17:
    {
        S value{42, "Test", 3.14};
        std::set<S>::iterator iter;
        bool inserted;

        // unpacks the return val of insert into iter and inserted
        std::tie(iter, inserted) = mySet.insert(value);

        if (inserted)
            std::cout << "Value was inserted\n";
    }

    // with C++17:
    {
        S value{100, "abc", 25.0};
        const auto[iter, inserted] = mySet.insert(value);

        if (inserted)
            std::cout << "Value(" << iter->n << ", " << iter->s << ", " << iter->d << ")" << "  was inserted" << "\n";
    }

    // works with arrays:
    double myArray[4] = {1.0, 2.0, 3.0, 4.0};
    auto[a, b, c, d] = myArray;


    struct S2 {
        int x1: 2;
        volatile double y1;
    };
    S2 myStruct{1, 3.3};
    const auto[x, y] = myStruct;

    std::cout << x << " " << y;

    std::tuple myTuple{1, "casa"};
    auto&[refA, refB] = myTuple;


    const std::map<std::string, std::string> capitals{
            {"Poland",  "Warsaw"},
            {"USA",     "Washington"},
            {"France",  "Paris"},
            {"UK",      "London"},
            {"Germany", "Berlin"}
    };
    for (const auto &[k, v] : capitals) {
        std::cout << "City: " << k << " Country: " << v << std::endl;
    }


    auto pi = std::make_unique<int>(9);
    int i = 9;
    std::cout << get_value(pi.get()) << "\n";
    std::cout << get_value(i) << "\n";

}


template<typename T>
auto get_value2(T t) {
    if constexpr (std::is_pointer_v<T>)
        return *t;
    else
        return t;
}
