# DP: Problemas de optimizacion

Ya vimos como usar la DP para calcular la cantidad de cosas en conjuntos con forma recursiva.

Ahora vamos a hacer DP para maximizar o minimizar valores.

En general, la idea es la misma.

Definimos conjuntos de estados y relaciones de recurrencia que nos permiten calcular el valor de cada estado.

La diferencia es que ahora tenemos que maximizar o minimizar una función objetivo.

## Problema: Caminos minimos en grillas

Imaginate una grilla de NxM, y queremos encontrar el camino minimo de la **casilla** de la esquina superior izquierda a la **casilla** inferior derecha, moviendose solo hacia abajo o hacia la derecha.