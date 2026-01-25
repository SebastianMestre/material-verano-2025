<https://cses.fi/problemset/task/1618> - factoriales, factorizacion

Cuando hablamos de numeros estamos hablando de naturales.

# Divisores

Decimos que un numero `a` divide a un numero `n`, si existe un numero `b` tal
que `n = a * b`. En ese caso decimos que `a` es divisor de `n`, y que `n` es
multiplo de `a`.

`D(n)` denota el conjunto de divisores de `n`.

# Números primos

Un numero primo es aquel que tiene exactamente dos divisores.

Como todo numero tiene al uno y a si mismo como divisor, alcanza con encontrar
un divisor entre dos y el numero menos uno para asegurar que el numero no es
primo.

## Chequeo en O(raíz(N))

Observemos que la existencia de un `a` divisor de `n`, implica que `n = a * b`,
y por lo tanto, que `b` es divisor de `b`.

O sea, la existencia de un divisor implica la existencia de otro divisor,
excepto en el caso que `a` y `b` son iguales, en tal caso `a` es la raiz
cuadrada de `n`, ya que `a*a = n`.

En el caso que `a` y `b` son distintos, uno de los dos debe ser menor a la raiz
cuadrada de `n` y el otro mayor.

Demo:

- si ambos fueran mayores, tendriamos `a*b > n` (absurdo)
- si ambos fueran menores, seria `a*b < n` (absurdo)

Corolario:

Si un numero no tiene divisores entre dos y la raiz cuadrada, tampoco los tiene
entre la raiz y el numero.

De ahi sigue un algoritmo: buscar divisores hasta llegar a la raiz cuadrada. Si
no encontramos ninguno, el numero es primo.

```c++
bool is_prime(int n) {
	if (n <= 1) return false;
	for (int x = 2; x*x <= n; ++x)
		if (n % x == 0)
			return false;
	return true;
}
```

## Criba de Eratóstenes

El método anterior es razonable para verificar si un numero es primo, pero
muchas veces nos interesa saber todos los primos hasta un número `N`. En este
caso, tendríamos costo `O(N^1.5)`, que es demasiado caro para N igual a `10^6`.

Para esto usamos el algoritmo de la criba de Eratóstenes.

Este algoritmo descubre todos los primos juntos, de menor a mayor. Al descubrir
un nuevo primo, marca todos sus multiplos como numeros compuestos, lo cual los
descarta de ser primos.

El costo es `O(N/2 + N/3 + N/5 + N/7 + N/11 + ...)` (donde los denominadores son
los numeros primos hasta N), que es igual a `O(N * log(log(N)))`.

```c++
int const maxn = 1000000;
bool is_composite[maxn+1];
void init() {
	for (int p = 2; p <= maxn; ++p) {
		if (is_composite[p]) continue;
		for (m = 2*p; m <= maxn; m += p) {
			is_composite[m] = true;
		}
	}
}
bool is_prime(int x) {
	if (x <= 1) return false;
	return !is_composite[x];
}
```

# Teorema fundamental de la aritmética

Cualquier numero natural n se puede expresar como un producto de potencias de
numeros primos

p.ej

- ` 85 = 5^1 * 17^1`
- ` 84 = 2^2 * 3^1 * 7^1`
- `112 = 2^4 * 7^1`

## Criba de Eratóstenes 2.0

# Coprimalidad

Dos numeros se dicen coprimos si no tienen divisores primos en comun

## Máximo común divisor y el algoritmo de Euclides

El algoritmo de Euclides:

```c++
int gcd(int a, int b) {
	while (a != b) {
		if (a < b) swap(a, b);
		a -= b;
	}
	return a;
}
```

## Euclides extendido e inversos modulares
