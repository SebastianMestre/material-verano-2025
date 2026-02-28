## Notas y presentaciones

- Información sobre el curso
- Introduccion a ICPC
- Sitios para competir en equipo e individualmente
- El notebook de ICPC
- Scripts para compilar y correr tests localmente
- Entrenamiento y estrategia de un equipo

## Adjuntos

## Informacion sobre el curso

- Lugar: servidor de Discord (canal "Clases")
- Horario: sábados 11 AM (UTC-4)
- Formato: Teoría + Resolución de problemas + Recomendaciones de problemas y simulacros

### Instructor

Sebastián Mestre

- Argentino, Universidad Nacional de Rosario
- Empecé a hacer programación competitiva en 2017
- International Olympiad in Informatics (IOI) Japón 2018, Azerbaiyán 2019, Singapur 2020
- International Collegiate Programming Contest World Finals (ICPC) Egipto 2023, Kazajistán 2024
- Entrenador del equipo Argentino de IOI 2025
- Coach de equipo de ICPC clasificado a la final de Azerbaiyán 2025 y a la semifinal Chile 2026

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

A partir de ahi, hay que analizar los éxitos y fracasos para mejorar. Mas adelante vamos a entrar más en detalle. Por ahora, les dejo una receta para seguir.

- Simular tan seguido como puedan (una vez por semana es buenísimo)
- Durante las pruebas:
  - Lean todos los problemas al principio de la prueba y charlen quien va a intentar cual.
  - Intenten los más fáciles primero.
  - Anoten en una tablita los problemas que ya estan leidos/alguien está pensando/ya están resueltos/etc
- Justo después de la prueba:
  - Anoten en una planilla los problemas que salieron y el link a la prueba.
- En los dias posteriores a la prueba:
  - Hagan upsolving de los problemas más fáciles que no salieron.
  - Lean la solución de los problemas más dificiles que no salieron, al menos por arriba.
  
