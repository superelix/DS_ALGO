#include <bits/stdc++.h>
using namespace std;
#define int long long int
#define fast                 \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
#define F first
#define S second
#define PB push_back
#define MP make_pair
const ll mod = 1e9 + 7, N = 2e6 + 7, M = 2e6 + 7, INF = INT_MAX / 10;

ll fact[142858];

ll prime[2 * 100000 + 1];

vector<array<ll, 2>> prime_collection;

ll _exponent(ll x, ll b)
{
    if (b == 0)
        return 1LL;
    ll ans = _exponent(x, b / 2);
    ans *= ans;
    if (b & 1)
    {
        ans *= x;
    }
    return ans;
}

ll calculate_exponent(ll x, ll b, ll MOD)
{
    if (b == 0)
        return 1LL;
    ll ans = calculate_exponent(x, b / 2, MOD);
    ans *= ans;
    ans %= MOD;
    if (b & 1)
    {
        ans *= x;
    }
    return ans % MOD;
}

ll spf(ll x, ll p, ll co_mod)
{
    ll res = calculate_exponent(fact[co_mod - 1], x / co_mod, co_mod);
    if (x >= p)
        res = (res * spf(x / p, p, co_mod)) % co_mod;
    return (fact[x % co_mod] * res) % co_mod;
}

// n is  pi^qi where pi is a prime and qi is max power in 142858.
void precalculate(ll p, ll q, ll divisor)
{
    ll n = divisor;
    fact[0] = 1;
    fact[1] = 1;
    for (int idx = 2; idx <= n - 1; idx++)
        fact[idx] = (fact[idx - 1] * ((idx % p) ? idx : 1)) % n;
}

ll max_power(ll n, ll p)
{
    ll exp = 0;
    while (n)
    {
        exp += (n / p);
        n /= p;
    }
    return exp;
}

ll inverse(ll a, ll m, ll &x, ll &y)
{
    if (m == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll x1 = 0, y1 = 0;
    ll _gcd = inverse(m, a % m, x1, y1);
    x = y1;
    y = x1 - (a / m) * y1;
    return _gcd;
}

void sieve()
{
    for (int i = 0; i < 2 * 100000 + 1; i++)
        prime[i] = 1;

    prime[0] = 0;
    prime[1] = 0;

    for (int i = 2; i < 2 * 100000 + 1; i++)
    {
        if (prime[i])
        {
            for (int j = i + i; j < 2 * 100000 + 1; j += i)
            {
                prime[j] = 0;
            }
        }
    }
}

void solve()
{

    ll n, r;
    cin >> n >> r;
    ll MOD = 142857;

    vector<array<ll, 2>> crt_collection;
    ll prod = 1;

    for (array<ll, 2> x : prime_collection)
    {
        ll divisor = _exponent(x[1], x[0]);
        prod *= divisor;

        precalculate(x[1], x[0], divisor);
        ll up = spf(n, x[1], divisor);
        ll down = (spf(r, x[1], divisor) * spf(n - r, x[1], divisor)) % divisor;

        ll inv_divisor = 0, inv_down = 0;
        ll _gcd = inverse(down, divisor, inv_down, inv_divisor);

        up = (up * inv_down) % divisor;

        ll left_power = max_power(n, x[1]) - max_power(r, x[1]) - max_power(n - r, x[1]);
        ll _up = calculate_exponent(x[1], left_power, divisor);

        up *= _up;
        up %= divisor;

        // up is the remainder of nCr when divided by p^q where divisor is p^q.
        crt_collection.PB({up, divisor});
    }

    ll ans = 0;

    // Ony use the crt.
    for (array<ll, 2> x : crt_collection)
    {
        ll pi = prod / x[1];
        ll inv_pi, inv_x1;
        ll _gcd = inverse(pi, x[1], inv_pi, inv_x1);
        ll current = (x[0] * inv_pi) % MOD;
        current *= pi;
        current %= MOD;
        ans += current;
        ans %= MOD;
    }
    cout << (ans + MOD) % MOD << endl;
}

signed main()
{
    fast;
    int t;

    sieve();

    ll modulo = 142857;

    // Storing all the prime p and its maximum power  q such that modulo%(p^q)==0.

    for (int i = 2; i < 2 * 100000 + 1; i++)
    {
        ll cnt = 0;
        while (prime[i] && (modulo % i == 0))
        {
            modulo /= i;
            cnt++;
        }

        if (cnt)
        {
            prime_collection.PB({cnt, i});
        }
    }

    cin >> t;

    while (t--)
    {
        solve();
    }
    return 0;
}

