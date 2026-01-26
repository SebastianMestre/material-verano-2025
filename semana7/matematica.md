<https://cses.fi/problemset/task/1618> - factoriales, factorizacion

Cuando hablamos de numeros estamos hablando de naturales.

# Divisores

Decimos que un numero `a` divide a un numero `n`, si existe un numero `b` tal
que `n = a * b`. En ese caso decimos que `a` es divisor de `n`, y que `n` es
multiplo de `a`. La notación típica es `a | n`.

`D(n)` denota el conjunto de divisores de `n`.

# Números primos

Un numero primo es aquel que tiene exactamente dos divisores. De forma
completamente ingenua, podemos verificar si un número es primo así:

```c++
bool is_prime(int n) {
	int cnt = 0;
	for (int x = 1; x <= n; ++x) {
		if (n % x == 0) {
			cnt += 1;
		}
	}
	return cnt == 2;
}
```

Como todo numero tiene al uno y a si mismo como divisor, alcanza con encontrar
un divisor entre dos y el numero menos uno para asegurar que el numero no es
primo.

```c++
bool is_prime(int n) {
	if (n <= 1) return false;
	for (int x = 2; x < n; ++x) {
		if (n % x == 0) {
			return false;
		}
	}
	return true;
}
```

## Chequeo en O(raíz(N))

Observemos que la existencia de un `a` divisor de `n`, implica que `n = a * b`
y, por lo tanto, que `b` es divisor de `n`.

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
	for (int x = 2; x*x <= n; ++x) {
		if (n % x == 0) {
			return false;
		}
	}
	return true;
}
```

## Criba de Eratóstenes

El método anterior es razonable para verificar si un numero es primo, pero
muchas veces nos interesa saber todos los primos hasta un número `N`. En este
caso, tendríamos costo `O(N^1.5)`, que es demasiado caro para N igual a `10^6`.

Para esto usamos el algoritmo de la criba de Eratóstenes.

Este algoritmo descubre todos los primos juntos, de menor a mayor. Al descubrir
un nuevo primo, marca todos sus múltiplos como números compuestos, lo cual los
descarta de ser primos.

El costo es `O(N/2 + N/3 + N/5 + N/7 + N/11 + ...)` (donde los denominadores son
los numeros primos hasta N), que es igual a `O(N * log(log(N)))`.

```c++
int const maxn = 1000000;
bool is_composite[maxn+1];
void init() {
	for (int p = 2; p <= maxn; ++p) {
		if (is_composite[p]) continue;
		for (int m = 2*p; m <= maxn; m += p) {
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
numeros primos, al que llamamos factorización prima o factorización en primos.

p.ej

- ` 85 = 5^1 * 17^1`
- ` 84 = 2^2 * 3^1 * 7^1`
- `112 = 2^4 * 7^1`

La factorización prima de un numero se puede calcular probando divisores hasta
llegar a la raiz. Podemos dividir n por cada divisor hasta no poder más para
encontrar el exponente. Si al final n no es igual a uno es porque le queda un
divisor primo con exponente uno.

```c++
map<int, int> factor(int n) {
	map<int, int> f;
	for (int x = 2; x*x <= n; ++x) {
		while (n % x != 0) {
			f[x] += 1;
			n /= x;
		}
	}
	if (n != 1) {
		f[n] = 1;
	}
	return f;
}
```

## Criba de Eratóstenes 2.0

La criba de Eratóstenes se puede modificar para calcular la factorización prima
de todos los numeros hasta un N. La idea es simple: al recorrer los múltiplos de
un primo también contamos la cantidad de veces que divide a cada múltiplo.

Esto empeora el costo: ya no es `O(N * log(log(N)))`, si no `O(N * log(N))`.

```c++
map<int, int> factors[maxn+1];
void init() {
	for (int p = 2; p <= maxn; ++p) {
		if (!factors[p].empty()) continue;
		for (int x = p; x <= maxn; ++x) {
			int y = x;
			while (y % p == 0) {
				factors[x][p] += 1;
				y /= p;
			}
		}
	}
}
```

## Coprimalidad

Dos números se dicen coprimos si no tienen divisores primos en común. Por
ejemplo, 9 (3 al cuadrado) y 14 (2 por 7) son coprimos.

Una forma de verificar esta condición es calculando la factorización prima de
ambos y ver que no comparten ningún primo.

## Mayor común divisor

Un concepto que resulta útil es el del mayor común divisor. Como dice el nombre,
dados dos números, el GCD (por las siglas en inglés) es el mayor número que es
divisor de ambos.

```c++
int gcd(int n, int m) {
	int g = 0;
	for (int i = 1; i <= n && i <= m; ++i) {
		if (n % i == 0 && m % i == 0) {
			g = i;
		}
	}
	return g;
}
```

La primera manera 'ingeniosa' de encontrarlo es usando la factorización prima.
Por cada factor primo que comparten los dos números, se toma el mínimo de los
dos exponentes. Esto nos da la factorización prima del GCD, a partir de la cual
es fácil obtener el número en sí.

```c++
map<int,int> gcd(map<int,int>& fn, map<int,int>& fm) {
	map<int,int> fg;
	for (auto [p, e1] : fn) {
		auto it = fm.find(p);
		if (it == end(fm)) continue;
		int r2 = it->second;
		fg[p] = min(e1, e2);
	}
	return fg;
}
```

## El algoritmo de Euclides

En el año 300 AC, Euclides publicó un algoritmo para calcular el GCD.

Supongamos que `n > m`. El algoritmo se basa en la idea de que si `g | n` y
`g | m` entonces `g | n - m`.

```c++
int gcd(int n, int m) {
	while (n != 0) {
		if (n < m) swap(n, m);
		n -= m;
	}
	return m;
}
```

El algoritmo de Euclides original es bastante lento en el caso que un numero es
chico y el otro grande.

Se puede optimizar al observar que no intercambia n y m hasta restarle n a m
tantas veces como para hacerlo menor a m. Esto es equivalente a encontrar el
resto de n en la división por m.

```c++
int gcd(int n, int m) {
	if (n > m) swap(n, m);
	while (n != 0) {
		swap(n, m);
		n %= m;
	}
	return m;
}
```

La implementación típica es mucho más corta.

```c++
int gcd(int n, int m) {
	return n ? gcd(m % n, n) : m;
}
```

## Euclides extendido e inversos modulares


