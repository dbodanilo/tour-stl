#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <set>
#include <vector>

template<class I, class F>
F _for_each(I first, I last, F f) {
    while (first != last) {
        f(*first);
        first++;
    }

    return f;
}

template<class I, class T>
I _find(I first, I last, T x) {
    while (first != last) {
        if (*first == x) return first;
        first++;
    }

    return last;
}

template<class I, class T>
unsigned int _count(I first, I last, T x) {
    unsigned int c = 0;

    while (first != last) {
        if (*first == x) c++;
        first++;
    }

    return c;
}

template<class Ix, class Iy>
bool _equal(Ix first_x, Ix last_x, Iy first_y) {
    while (first_x != last_x) {
        if (*first_x != *first_y) {
            return false;
        }
        first_x++;
        first_y++;
    }

    return true;
}

template<class Ix, class Iy>
Ix _search(Ix first_x, Ix last_x, Iy first_y, Iy last_y) {
    // y is an empty range.
    if (first_y == last_y) return first_x;

    while (first_x != last_x) {
        Ix fx = first_x;
        Iy fy = first_y;

        // possible y starting in first_x.
        while (*fx == *fy) {
            fx++;
            fy++;
            // found y.
            if (fy == last_y) {
                return first_x;
            }
            // remaining x is shorter than y.
            if (fx == last_x) {
                return last_x;
            }
        }

        first_x++;
    }

    return last_x;
}

template<class In, class Out>
Out _copy(In first, In last, Out result) {
    Out res = result;

    while (first != last) {
        *res = *first;
        first++;
        res++;
    }

    return result;
}

template<class In, class Out, class Op>
Out _transform(In first, In last, Out result, Op op) {
    Out res = result;

    while (first != last) {
        *res = op(*first);
        first++;
        res++;
    }

    return result;
}

template<class I, class T>
T _accumulate(I first, I last, T init) {
    while (first != last) {
        init = init + *first;
        first++;
    }

    return init;
}

template<class I, class P, class T>
void _replace_if(I first, I last, P pred, T y) {
    while (first != last) {
        if (pred(*first)) {
            *first = y;
        }
        first++;
    }
}

template<class I>
void print_each(I first, I last) {
    auto f = [](auto x) -> void { std::cout << x << " "; };

    std::cout << "{ ";
    _for_each(first, last, f);
    std::cout << "}";
}

int main() {
    std::deque<int> xs;

    while (true) {
        int x = 0;
        std::cin >> x;
        // x == 0 breaks the loop as well as EOF.
        if (!std::cin.eof() && x != 0) {
            xs.push_back(x);
        }
        else {
            break;
        }
    }

    auto f = [](int x) -> void { std::cout << x << " "; };

    std::cout << std::endl << "for_each():" << std::endl;
    std::cout << "xs = { ";
    _for_each(xs.begin(), xs.end(), f);
    std::cout << "}" << std::endl;

    std::cout << std::endl << "find() and count():" << std::endl;
    for (int i = 0; i < 10; i++) {
        auto iter = _find(xs.begin(), xs.end(), i);
        unsigned c = 0;

        std::cout << i << " is ";
        if (iter == xs.end()) {
            std::cout << "not ";
        }
        else {
            c = _count(xs.begin(), xs.end(), i);
        }
        std::cout << "in xs" << std::endl;

        if (c > 0) {
            std::cout << i << " appears in xs " << c << " times" << std::endl;
        }
    }

    std::vector<int> ys;
    while (true) {
        int y = 0;
        std::cin >> y;
        if (std::cin.eof() || y == 0) {
            break;
        }
        else {
            ys.push_back(y);
        }
    }

    std::cout << std::endl << "equal():" << std::endl;
    if (_equal(xs.begin(), xs.end(), ys.begin())) {
        std::cout << "ys == xs" << std::endl;
    }
    else {
        std::cout << "ys != xs" << std::endl;

        std::cout << "ys = ";
        print_each(ys.begin(), ys.end());
        std::cout << std::endl;
    }

    std::cout << std::endl << "search():" << std::endl;
    // ys[:3] = { 1, 2, 3 }
    auto iter = _search(xs.begin(), xs.end(), ys.begin(), ys.begin() + 3);
    if (iter != xs.end()) {
        std::cout << "xs contains ";
    }
    else {
        std::cout << "xs does not contain ";
    }
    print_each(ys.begin(), ys.begin() + 3);
    std::cout << std::endl;

    std::list<int> zs;
    zs.resize(xs.size(), 0);

    std::cout << std::endl << "copy():" << std::endl;
    auto first_z = _copy(xs.begin(), xs.end(), zs.begin());
    std::cout << "zs = ";
    print_each(first_z, zs.end());
    std::cout << std::endl;

    std::forward_list<int> x2s;
    x2s.resize(xs.size(), 0);

    auto pow2 = [](int x) -> int { return x * x; };

    std::cout << std::endl << "transform():" << std::endl;
    auto first_x2 = _transform(xs.begin(), xs.end(), x2s.begin(), pow2);

    std::cout << "x^2 = ";
    print_each(first_x2, x2s.end());
    std::cout << std::endl;

    auto sum = [](auto first, auto last) { return _accumulate(first, last, 0); };
    std::cout << std::endl << "accumulate()" << std::endl;
    std::cout << "sum(x^2) = " << sum(x2s.begin(), x2s.end());
    std::cout << std::endl;

    auto is_even = [](int x) -> bool { return x % 2 == 0; };

    std::cout << std::endl << "replace_if():" << std::endl;
    _replace_if(xs.begin(), xs.end(), is_even, 1);
    std::cout << "xs = ";
    print_each(xs.begin(), xs.end());
    std::cout << std::endl;

    return 0;
}
