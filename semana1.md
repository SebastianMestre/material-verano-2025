# Semana 1

- Introduccion a ICPC
- Sitios para competir en equipo e individualmente
- El notebook de ICPC
- Scripts para compilar y correr tests localmente
- Entrenamiento y estrategia de un equipo

## Introducción a ICPC

    Subregional ----> Regional ----> Superregional (PDA) ----> Mundial
                                ^
                                Usted está aquí

La ICPC consiste en resolver problemas de programación en equipos de tres personas, usando una sola computadora.

Cada problema tiene un límite de tiempo y de memoria, así que necesitamos soluciones eficientes en tiempo de ejecución y uso de memoria. Sin embargo, no obtenemos ninguna ventaja extra por hacer una implementación aún más rápida o que use todavía menos memoria de lo necesario.

De hecho, una solución más eficiente puede ser más compleja, llevarnos más tiempo de implementar y aumentar la probabilidad de envíos incorrectos. Por lo tanto, en la práctica buscamos la solución correcta **más simple posible**.

También nos importa que el código sea relativamente corto y fácil de escribir, para no pasar demasiado tiempo frente a la computadora. En ICPC, muchas veces el cuello de botella es justamente el “tiempo de teclado”: por ejemplo, al final de la prueba podemos tener la idea para dos o tres problemas, pero no el tiempo suficiente para codearlos todos.

Entonces, además de la eficiencia algorítmica, nos preocupa la eficiencia en el tiempo de implementación necesario para llevar la solución desde la idea hasta un envío aceptado. El objetivo debe ser entrar a la computadora, escribir, probar y enviar la solución, y salir lo antes posible para que la puedan usar nuestros compañeros.

### Ejemplo

Escribir un programa que tome una cadena de caracteres representando los puntos de un partido de tenis, y devuelva el ganador del partido.

En el tenis, un partido se estructura en tres niveles: puntos, games y sets.

- El primero en tener al menos cuatro puntos y dos de ventaja sobre el oponente gana un game
- El primero en tener al menos seis games y dos de ventaja sobre el oponente gana un set
- El primero en ganar tres sets gana el partido

De esta manera, para simular el partido en un programa, se deben contar cuántos puntos gana cada jugador, determinar cuándo alguno gana un game, luego sumar games para formar sets, y finalmente ver quién completa la cantidad de sets requerida para ganar el partido.

```cpp
#include <iostream>
#include <string>
using namespace std;
int main() {
    string puntos; cin >> puntos;
    int sa = 0, sb = 0, ga = 0, gb = 0, pa = 0, pb = 0;
    for (char p : puntos) {
        if (p == 'A') {
            pa++;
            if (pa >= 4 && pa - pb >= 2) {
                ga++; pa = pb = 0;
                if (ga >= 6 && ga - gb >= 2) {
                    sa++; ga = gb = 0;
                    if (sa == 2) {
                        cout << 'A' << endl; return 0;
                    }
                }
            }
        } else {
            pb++;
            if (pb >= 4 && pb - pa >= 2) {
                gb++; pb = pa = 0;
                if (gb >= 6 && gb - ga >= 2) {
                    sb++; gb = ga = 0;
                    if (sb == 2) {
                        cout << 'B' << endl; return 0;
                    }
                }
            }
        }
    }
}
```

Sin embargo, también podemos observar que el ganador del partido **siempre es quien gana el último punto**, así que no hace falta implementar toda la simulación y basta con mirar el último punto.

```cpp
#include <iostream>
#include <string>
int main() {
    string puntos; cin >> puntos;
    cout << puntos.back() << "\n";
}
```

## El notebook de ICPC

En la ICPC, cada equipo lleva un documento de referencia (notebook) con implementaciones de algoritmos, teoremas y listas de números útiles. Mi equipo también llevaba algunos scripts.

Notebooks recomendados para empezar:

- [La pandilla](https://github.com/francoderico/la-pandilla/) - Notebook argentino
- [El vasito](https://github.com/mhunicken/icpc-team-notebook-el-vasito) - Notebook argentino
- [El Diego](https://github.com/vmartinv/eldiego) - Notebook argentino
- [KACTL](https://github.com/kth-competitive-programming/kactl) - Notebook de KTH (Suecia)


## Sitios para competir en equipo e individualmente

Algunos sitios útiles para practicar y simular competencias ICPC:

- [Codeforces](https://codeforces.com/) -- Contests individuales frecuentes, formato parecido a ICPC. Aparte en la sección "gyms" hay pruebas de ICPC que se pueden simular en equipo.
- [AtCoder](https://atcoder.jp/) -- Contests individuales con buenos problemas.
- [Matcom Online Grader](https://matcomgrader.com/) -- Tiene regionales ICPC Latinoamérica viejos para simular.
- [Universal Cup](https://ucup.ac/) -- Serie de competencias estilo ICPC (super difíciles).

## Scripts para compilar y correr tests (Linux)

Durante una competencia, lo mejor es abrir una terminal y armar una carpeta donde vayas metiendo todo lo que vas a usar, por ejemplo:

```sh
$ mkdir regional2025
$ cd regional2025
```

Adentro de esta carpeta vamos a guardar los códigos fuente de los problemas, casos de prueba, y un par de cositas más.

Primero, para compilar el código, creamos un `Makefile` con algo así adentro:

```make
CXXFLAGS := -fsanitize=address -g -Wall -Wextra -Wshadow -Wconversion
```

Esto nos permite compilar el código muy rapido:

```sh
$ vim A.cpp # Suponete que implementaste el problema A
$ vim A1.in # Caso de prueba 1
$ vim A2.in # Caso de prueba 2
$ make A
$ ./A < A1.in
A
$ ./A < A2.in
B
```

Igual sigue siendo tedioso, así que creamos un script que se llame `correr.sh`, con permisos de ejecución (`chmod u+x correr.sh`)

```sh
#!/bin/bash
make $1 && for CASO in $1*.in; do echo "==== $CASO ====" ./$1 < $CASO done
```

Ahora podemos correr todos los casos de prueba de un problema con un solo comando:

```sh
$ vim A.cpp
$ vim A1.in
$ vim A2.in
$ ./correr.sh A
==== A1.in ====
A
==== A2.in ====
B
```

## Entrenamiento y estrategia de un equipo

El entrenamiento en ICPC es super simple:

- Hay que hacer muchos problemas para mejorar individualmente.
- Hay que hacer muchos simulacros para mejorar en equipo.

A partir de ahi, hay que analizar los éxitos y fracasos para mejorar.

Algunos posibles fracasos en simulacros:

- No leer algun problema, y después de la prueba ver que lo podríamos haber resuelto.
- Tener dos miembros pensando el mismo problema sin saberlo.
- Que uno esté trabado resolviendo un problema que a otro le sale muy fácil.
- Que uno esté trabado resolviendo un problema que es muy difícil, y no hay chance de que salga.
- Intentar un solo problema en la última hora, cuando hacen falta dos para clasificar.
- Que no salga un problema muy parecido a uno que ya enfrentamos y no nos salió.
- Que consistentemente no nos salen problemas de un mismo tema.

Algunas soluciones directas a estos errores:

- Leer todos los problemas antes de las dos horas de la prueba
- Tener una tablita para ir anotando los problemas que ya estan leidos/alguien lo está pensando/ya están resueltos/etc
- Charlar los problemas durante la prueba para elegir quién va a intentar cual.
- Charlar para decirle al compañero que tiene que abandonar un problema.
- Charlar para decirle al compañero que tiene que pasar el problema que está intentando a otro.
- Tener un objetivo fijado antes de la prueba. Por ejemplo:
  - Clasificar a la proxima ronda
  - Salir top 20
  - Meter 5 problemas
  - Divertirse
- Charlar entre nosotros para tomar decisiones
- Hacer upsolving (resolver los problemas que no nos salieron en la prueba)
- Anotar los temas de los problemas que encaramos y no salieron, para practicarlos en otro momento.

Para entrenar, está bueno ir registrando los simulacros que se hacen, y anotar los problemas que se han resuelto y los que no. Aparte, está bueno anotar los temas de los dos problemas más fáciles que no nos salieron.

Al hacer upsolving, yo recomiendo:

- Para los problemas que nos pueden llegar a salir, pensarlos bastante tiempo.
- Para los problemas que no nos pueden llegar a salir, leer la solución y entenderla.
- Una regla general es que los dos problemas más fáciles que no nos salieron en la prueba, son los que nos pueden llegar a salir.
  
  Por ejemplo, si metieron H y J en el regional 2025, apunten a F y K para el upsolving.

### Estrategia de mi equipo

La estrategia de mi equipo era:

- Al principio de la prueba, escribir el template y leer todos los problemas.
  - Si alguien identifica un problema super fácil, lo codea incluso sin terminar de leer el resto de problemas.
- Una vez leídos todos los problemas, se cuentan los enunciados y se asigna quién va a intentar cada problema.
  - Si uno es experto en un tema, y justo hay un problema que es de ese tema
  - Si uno ya resolvió un problema similar
- Intentamos resolver los más fáciles primero.
- Durante la primera media hora, revisamos la tabla para ver si hay alguno bien fácil que no resolvimos.
- Escribir código en papel antes de ocupar la computadora. (al menos pseudocódigo)
- Si alguien está programando, no lo interrumpimos, para que no ocupe más tiempo la computadora.
- Cuando alguien va a tomar la computadora, predice cuánto tiempo va a tomar. (Si son 40 minutos, es aceptable sacarlo 5 minutos para codear otro problema)
- No debuggear en la computadora, sino mandar a imprimir el código en papel.
- Después de hacer un envío, siempre se envía el código a imprimir, por las dudas.
- Cada hora, hablamos para ver cómo estamos y tomar decisiones.
  - Hay que abandonar alguno de los problemas?
  - Será mejor que alguien le pase el problema que está intentando a otro?
  - Qué problema es el que sigue? (volver a revisar la tabla)
  - Alguno necesita ayuda?
- Cuando queda una hora, hablamos para decidir si intentamos un problema, dos o tres. Elegimos según lo que haga falta para clasificar.

Esta estrategia no es perfecta, y hay que ajustarla a cada equipo y cada prueba.

Y para entrenar, nos enfocabamos mucho en hacer upsolving. Teniamos un google sheet para esto.

| A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | nombre | link | tema 1 | tema 2 |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|--------|------|--------|--------|
| S | S |   |   | S |   |   | S | O | S |   | U | X | X | X | Regional 2025 | codeforces.com/gym/... | DP | Geometria |

- S = resuelto
- O = upsolved
- U = para upsolving
- X = no existe

Tema 1 y tema 2 son los temas de los dos problemas más fáciles que no nos salieron en la prueba.

Un par de veces por semana haciamos upsolving individualmente. Personalmente, yo era de intentar el problema y no leer la solución hasta que no lo habia intentado durante muchas horas.