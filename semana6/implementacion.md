
Como los números que tratamos en combinatoria son muy grandes, típicamente nos piden el resultado en módulo.

Esto presenta algunas dificultades prácticas. En particular, muchas cuentas que nos interesan involucran divisiones.

Lo que sigue es un resumen de las operaciones básicas en módulo, y después profundizamos un poco en cómo calcular coeficientes binomiales.

## Operaciones basicas

Ya vimos las operaciones básicas en módulo, pero las repito acá a forma de recordatorio.

```c++
int const m = 1000000007;
int nm(int x) { return x - m * (x >= m); }
int add(int x, int y) { return nm(x + y); }
int sub(int x, int y) { return nm(x + m - y); }
int mul(int x, int y) { return (long long)x * y % m; }
```

## Potencias

Como resultado de aplicaciones sucesivas del principio del producto, podemos necesitar calcular potencias en módulo.

```c++
int pot(int x, int y) {
    if (y == 0) return 1;
    if (y % 2 == 0) return pot(mul(x, x), y / 2);
    return mul(x, pot(x, y-1));
}
```

## Coeficientes binomiales

Recordemos que la cantidad de formas de elegir k elementos de un conjunto de n elementos es n! / (k! * (n-k)!).

Una 'división' en módulo es una multiplicación por el inverso multiplicativo, lo cual no siempre es trivial.

```c++
int div(int x, int y) { return mul(x, inv(y)); }
```

### El caso feliz: m primo, n < m, n < 10^7


Tipicamente, en los problemas de combinatoria se cumplen estas condiciones. Acá pasan varias cosas buenas:

- Como `m` es primo, todos los numeros del 1 al m-1 tienen inverso multiplicativo.
- `n` es menor a `m`, por lo que `m` no aparece en la factorización de `n!`. Si esto no fuera cierto, `fac[n]` seria igual `a` 0 en módulo `m`.
- `n` es suficientemente chico como para que podamos precomputar los factoriales y sus inversos.

```c++
int fac[maxn+1], ifac[maxn+1]; // factoriales y sus inversos
int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return mul(fac[n], mul(ifac[k], ifac[n-k]));
}
```

Para precomputar los factoriales y sus inversos en O(N), podemos usar el siguiente codigo:

```c++
int in[maxn+1];
void init() {
    // factoriales
    fac[0] = 1;
    forn(i, maxn) fac[i+1] = mul(fac[i], i+1);

    // inversos de los factoriales
    ifac[maxn] = inv(fac[maxn]);
    dforn(i, maxn) ifac[i] = mul(ifac[i+1], i+1);

    // Extra: inversos de los numeros del 1 al n
    forr(i, 1, maxn+1) in[i] = mul(ifac[i], fac[i-1]);
}
```

### n < 10^3

Si n es muy chico, podemos calcular todos los coeficientes binomiales en O(N^2) mediante la construccion del triangulo de Pascal.

No importa que `m` sea primo o no.

```c++
int pascal[maxn+1][maxn+1];
void init() {
    forn(i, maxn+1) pascal[i][0] = 1;
    forn(i, maxn+1) pascal[i][i] = 1;
    forr(i, 1, maxn+1) forr(j, 1, i) pascal[i][j] = add(pascal[i-1][j-1], pascal[i-1][j]);
}
int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    return pascal[n][k];
}
```

### m primo, k < m, k "chico"

Trabajando un poco, podemos cancelar (n-k) factores en el numerador y el denominador, terminando con un total de k factores para calcular.

```
  (n choose k)
=
  1 * 2  * ... * (n-k-1) * (n-k) * (n-k+1) * ... * (n-1) * n
  / (1 * 2 * ... * (k-1) * k)
  / (1 * 2 * ... * (n-k))
=
  (n-k+1) * (n-k+2) * ... * (n-1) * n
  / (1 * 2 * ... * (k-1) * k)
```

No nos queda otra que calcular el numerador en O(K), pero el denominador (`k!`) podemos tenerlo precalculado.

```c++
int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    int res = 1;
    forr(i, n-k+1, n+1) res = mul(res, i);
    return mul(res, ifac[k]);
}
```

Notar que esto tambien funciona para el caso que `n-k` es chico, simplemente porque `comb(n, k) = comb(n, n-k)`.

### n < 10^5

La idea es trabajar con la factorizacion en primos de los factoriales.

Comenzamos factorizando cada numero con una criba.

```c++
vector<pair<int, int>> sieve[maxn+1];
void init() {
    for (int i = 2; i <= maxn; ++i) {
        if (!sieve[i].empty()) continue;
        for (int j = i; j <= maxn; j += i) {
            int x = j;
            int e = 0;
            while (x % i == 0) {
                x /= i;
                e++;
            }
            sieve[j].pb({i, e});
        }
    }
}
```

Despues, para calcular `(n choose k)`, podemos operar sobre la factorizacion en primos de los factoriales (multiplicar -> sumar exponentes, dividir -> restar exponentes).

```c++
int comb(int n, int k) {
    if (k < 0 || k > n) return 0;
    static unordered_map<int, int> cnt;
    cnt.clear();
    forr(i, 1, n+1)   for (auto &[p, e] : sieve[i]) cnt[p] += e;
    forr(i, 1, k+1)   for (auto &[p, e] : sieve[i]) cnt[p] -= e;
    forr(i, 1, n-k+1) for (auto &[p, e] : sieve[i]) cnt[p] -= e;
    int res = 1;
    for (auto &[p, e] : cnt) res = mul(res, pot(p, e));
    return res;
}
```

Es bastante lento, pero funciona si solo necesitamos calcular un numero limitado de coeficientes binomiales.

------------

Hay muchisimos casos que podriamos analizar, pero quiero dejar la idea que el calculo de coeficientes binomiales se puede hacer de muchas formas, y que algunas se pueden inventar en el momento.

Por ejemplo, en una competencia virtual tuvimos que usar una idea como la que sigue:

### m primo, m <= n < 2\*m, k > m, n < 10^7

La dificultad acá es que `n` es mayor a `m`, por lo que `m` aparece en la factorización de `n!` y entonces, `fac[n]` es igual a 0 en módulo `m`.

Lo que nos salva es que `k >= m` entonces `m` tambien aparece en la factorización de `k!`. Por lo tanto, en `(n choose k) = n! / (k! * (n-k)!)`, podemos cancelar el factor de `m` en el numerador y el denominador.

Aparte, como `n` es menor a `2*m`, `m` no aparece en la factorización de `(n-k)!`.

Como de todas formas se cancela el factor de `m`, la idea es calcular unos factoriales pero ignorando los factores de `m`.

```c++
int fac[maxn+1], ifac[maxn+1]; // factoriales y sus inversos
void init() {
    fac[0] = 1;
    forn(i, maxn) fac[i+1] = i+1 == m ? fac[i] : mul(fac[i], nm(i+1));
    ifac[maxn] = inv(fac[maxn]);
    dforn(i, maxn) ifac[i] = i+1 == m ? ifac[i+1] : mul(ifac[i+1], nm(i+1));
}
```

Despues el cálculo es el mismo que en el caso feliz.
