#include <iostream>
#include <unordered_map>

using namespace std;

using ll = long long;

unordered_map<ll, ll> len_cache;

// Calcula la longitud de la secuencia final para un número x
ll get_len(ll x) {
    if (x <= 1) return 1;
    if (len_cache.count(x)) return len_cache[x];
    return len_cache[x] = 2 * get_len(x / 2) + 1;
}

// Cuenta cuántos 1s hay en la secuencia generada por x entre [l, r]
ll count_ones(ll x, ll left_pos, ll l, ll r) {
    if (x <= 1) {
        if (left_pos >= l && left_pos <= r) return x;
        else return 0;
    }

    ll left_child = x / 2;
    ll mid = left_pos + get_len(left_child);
    ll right_child_pos = mid + 1;

    ll total = 0;

    // Parte izquierda
    if (l <= mid - 1)
        total += count_ones(left_child, left_pos, l, r);

    // Nodo actual
    if (mid >= l && mid <= r)
        total += x % 2;

    // Parte derecha
    if (r >= right_child_pos)
        total += count_ones(left_child, right_child_pos, l, r);

    return total;
}

int main() {
    ll n, l, r;
    cin >> n >> l >> r;

    cout << count_ones(n, 1, l, r) << endl;

    return 0;
}
