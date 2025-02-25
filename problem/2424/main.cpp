#include <iostream>
#include "src.hpp"
using std::cin;
using std::cout;
using std::endl;
const int MAX_SIZE = 100;
int identity[MAX_SIZE];
int elements[MAX_SIZE];

int main(){
    int n;
    cin >> n;
    Permutation p(n);
    for(int i = 0; i < n; i++) {
        identity[i] = i;
    }
    p.apply(identity);
    for(int i = 0; i < n; i++) {
        cout << identity[i] << " ";
    }
    cout << endl;
    for(int i = 0; i < n; i++) {
        cin >> p.mapping[i];
    }
    p.apply(identity);
    for(int i = 0; i < n; i++) {
        cout << identity[i] << " ";
    }
    cout << endl;
    Permutation q(identity, n);
    cout << p * q << endl;
    cout << q.inverse() << endl;
    int m = n / 2;
    for(int i = 0; i < m; i++) {
      elements[i] = i;
    }
    Cycle c(elements, m);
    cout << c << endl;
    c.apply(identity, n);
    for(int i = 0; i < n; i++) {
        cout << identity[i] << " ";
    }
    cout << endl;
    cout << c.toPermutation(n) << endl;
    Transposition t{};
    t.apply(identity, n);
    for(int i = 0; i < n; i++) {
        cout << identity[i] << " ";
    }
    cout << endl;
    t = Transposition(1, 2);
    t.apply(identity, n);
    for(int i = 0; i < n; i++) {
        cout << identity[i] << " ";
    }
    cout << endl;
    cout << t.toPermutation(n) << endl;
}