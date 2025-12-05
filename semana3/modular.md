
## Aritmetica modular

La aritmética modular es un sistema de numeración construido sobre el resto de la división.

Dos números son *congruentes módulo m* si su diferencia es un múltiplo de m.

```
a ≡ b (mod m)
sii
a - b = k * m (para algún k entero)
```

**Si sumamos m a un número, el resultado es equivalente al número original.**

La relación de congruencia módulo m es una relación de equivalencia:

- Reflexiva: a ≡ a (mod m)
- Simétrica: si a ≡ b (mod m), entonces b ≡ a (mod m)
- Transitiva: si a ≡ b (mod m) y b ≡ c (mod m), entonces a ≡ c (mod m)

Esta relación de equivalencia se comporta bien con las operaciones aritméticas básicas:

```
suponiendo
     a ≡ b (mod m)
     c ≡ d (mod m)
entonces
     a + c ≡ b + d (mod m)
     a - c ≡ b - d (mod m)
     a * c ≡ b * d (mod m)
```

Como caso particular:

```
     a + m ≡ a (mod m)  (por definición ≡(mod m))
pero tambien, podemos pensarlo porque m ≡ 0 (mod m)
     a + m ≡ a + 0 = a
```

Demostracion de la suma:

```
   a ≡ b (mod m)
                           { definición ≡(mod m) }
=> a - b = k1 * m
                           { álgebra }
=> a = b + k1 * m          (1)


   c ≡ d (mod m)
                           { definición ≡(mod m) }
=> c - d = k2 * m
                           { álgebra }
=> c = d + k2 * m          (2)


    a + c
                           { 1 }
  = b + k1 * m + c
                           { 2 }
  = b + k1 * m + d + k2 * m
                           { álgebra }
  = (b + d) + (k1 + k2) * m
                           { definición ≡(mod m) }
  => a + c ≡ b + d (mod m)
```

### representacion canonica

Para todo entero x, existe un unico entero r en el intervalo [0, m-1] tal que x ≡ r (mod m).

A este entero r le podemos llamar representacion canonica de x modulo m.

En particular, si x es positivo, r es el resto de la division de x por m.

Una forma comoda de trabajar con aritmetica modular es siempre mantener los numeros en su representacion canonica.

> Ojo: en C++, cuando x es negativo, `x % m` no es la representacion canonica de x modulo m. (en particular, es negativo)
>
> Podemos hacer lo siguiente:
>
> ```c++
> int const m = 1000000007; // muy importante que sea constante, para mejor performance
> int canonica(int x) { return (x % m + m) % m; }
> ```

### Operaciones en representacion canonica

Si siempre mantenemos los numeros en su representacion canonica, las operaciones se pueden hacer de la siguiente manera:

```c++
// igual que canonica en el intervalo [0, 2m-1], y mas rapido
int nm(int x) { return x - m * (x >= m); }

// obs: si x e y estan en el intervalo [0, m-1], entonces x + y esta en el intervalo [0, 2m-1]
int add(int x, int y) { return nm(x + y); }

// obs: si x e y estan en el intervalo [0, m-1], entonces x + m - y esta en el intervalo [0, 2m-1]
int sub(int x, int y) { return nm(x + m - y); }

// obs: x * y puede desbordar int, por lo que usamos long long
int mul(int x, int y) { return (long long)x * y % m; }
```

# Otras operaciones

```c++
// O(log y)
int pot(int x, int y) {
    if (y == 0) return 1;
    if (y % 2 == 0) return pot(mul(x, x), y / 2);
    return mul(x, pot(x, y-1));
}

// si m es primo, podemos usar el pequeño teorema de Fermat para encontrar el inverso multiplicativo
// x^(m-1) ≡ 1 (mod m)
// x^(m-2) ≡ x^-1 (mod m)
// O(log m)
int inv(int x) { return pot(x, m-2); }

// hay un truco para calcular los inversos multiplicativos de todos los numeros del 1 al n
// en O(n)
int inv[n+1];
inv[1] = 1;
for (int i = 2; i <= n; i++) {
    inv[i] = mul(inv[m % i], m - m / i);
}

// tambien existe este truco mas largo pero mas claro (y de paso calculamos los inversos multiplicativos de los factoriales)
int fac[n+1], ifac[n+1], inv[n+1];
fac[0] = 1;
forn(i, n) fac[i+1] = mul(fac[i], i+1); // factoriales
ifac[n] = inv(fac[n]);
dforn(i, n) ifac[i] = mul(ifac[i+1], i+1); // inversos de los factoriales
forr(i, 1, n) inv[i] = mul(ifac[i], fac[i-1]); // inversos de los numeros del 1 al n
```