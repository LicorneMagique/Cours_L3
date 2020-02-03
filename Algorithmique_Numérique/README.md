# Algorithmie Numérique

Par [BOUAKAZ BRONDEL SAIDA](mailto:saida.bouakaz@univ-lyon1.fr)

## Partie I - Introduction aux concepts de l'algorithmique numérique

[PDF du cours](RappelMatriceSB.pdf)

- Arithmétique en précision finie
- Instabilité numérique et condition d’un problème
- Complexité des algorithmes

| C1 | C2 | C3 | C4 | C5 |
| - | - | - | - | - |
| 0 | 1 | 2 | 5 | 18 | 86 | 1 |
| 0 | 3 | 4 | 9 | 31 | 53 | 12 |
| 3 | 2 | 0 | 0 | 3 | 6 | 4 |
| 2 | V2 | 0 | 3 | 1 | 1/2 | 1 |
| 1 | 1 | 0 0  1 3/4  6)
| 1/2 | 1 | 1 2  1   3  9)

On ne doit pas avoir de 0 en haut à gauche donc on inverse L1 avec la première ligne qui marche

L1 <=> L3
(3    2 0 0  3   6  4)
(0    3 4 9 31  53 12)
(0    1 2 5 18  86  1)
(2   V2 0 3  1 1/2  1)
(1    1 0 0  1 3/4  6)
(1/2  1 1 2  1   3  9)

Puis on fait L4 - 2*L1 => L4 pour enlever le 2 au début de L4  
Puis L5 - L1 => L1  
Puis L6 - 1/2 * L1 => L6

## Partie II - Résolution numérique de systèmes linéaires

- Méthode de Gauss
- Factorisation LU
- Matrices particulières
- Méthodes itératives (Jacobi, Gauss-Seidel) - (étude de la complexité, stabilité, convergence)

## Partie III - Zéro d’une fonction

- Méthode de dichotomie
- Bissection
- Newton (étude de la complexité, stabilité, précision)

## Partie IV - Approximation polynomiale, méthodes des moindres carrés

- Moindres carrés
- Chebychev (méthodes, complexité, comparaison de méthodes)

## Partie V - Intégration numérique

- Trapèzes
- Simpson

## Partie VI - Approximation polynomiale

- Formule de Lagrange
- Polynôme de Newton
