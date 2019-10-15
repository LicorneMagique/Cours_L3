# Source

<https://perso.liris.cnrs.fr/sylvain.brandel/wiki/doku.php?id=ens:liflf>  
Ce cours est associé aux cours de logique clasique

## Cours 1

### Notes

Installer coq sur PC  

En rapport avec ce cours : compilation, complexité, recherche en informatique fondamental  

- Notations comme pour les cours de logique classique  
**Ensemble des parties** (P) : ensemble de tous les sous-ensembles d'un ensemble (E)

```math
E = {a, b, c}
P = {0/, {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}}
```

- Produit carthésien

```math
E = {a, b}
F = {x, y}
P = {(a, x), (x, a), (a, y), (y, a), ...}
```

#### Terminologie ensembliste

- *Plus* est une relation **ternaire** sur N<sup>3</sup> : `Plus = {(e1, e2, s), (3,5,8), ...}`
- N'importe quelle fonction type inverse, racine... est une relation **binaire** sur N<sup>2</sup> `Inverse = {(1, -1), (7, -7), ...}`
- **Relation réflexive** : une boucle sur chaque sommet (relation du sommet vers lui-même)
- **Relation réflexive** : R(a, a)
- **Relation symétrique** : R(a, b) => R(b, a)
- **Relation transitive** : R(a, b) & R(b, c) => R(a, c)

---
On pose R ⊂ E<sup>2</sup>  
Si x ∈ E<sub>1</sub>, x R y  
Alors y ∈ E<sub>1</sub>

---
La **clôture** de la relation *Plus* est ℕ, ℕ est donc stable par relation Plus → clôture de la relation par ℕ.

La **fermeture transitive** :

Une fonction f E^(1) → E1 est un cas particulier des relations pour lequel tous les éléments ont au plus une iamge

---
**Fonction injective :** au plus un antécédent

**Fonction surjective :** au moins un antécédent

---

## Cours grammaire

## Notes Coq

Une grosse documentation similaire à nos cours se trouve sur [ce site](https://www.seas.upenn.edu/~cis500/cis500-f13/sf/toc.html)

La correction du TP1 est trouvable sur [cette adresse](https://www.seas.upenn.edu/~cis500/cis500-f13/sf/Basics.html#lab15)

## Cours déterminisation

### Notes déterminisation

#### Élimination du nom déterminisme

On commence par regarder à partir de chaque sommet q<sub>i</sub> où est-ce qu'on peut aller sans consommer autre chose que le caractère vide

| q | E(q)         |
| - | ------------ |
| 0 | {0, 1, 2, 3} |
| 1 | {1}          |
| 2 | {2}          |
| 3 | {3}          |

Puis on regarde à partie de chaque élément de E(q') où est-ce qu'on peut aller en consommant un caractère

| E(q')                       | a                     | b                     | c                     |
| --------------------------- | --------------------- | --------------------- | --------------------- |
| q<sub>0</sub>'={0, 1, 2, 3} | q<sub>1</sub>'={1, 2} | q<sub>2</sub>'={1, 3} | q<sub>3</sub>'={2, 3} |
| q<sub>1</sub>'={1, 2}       | q<sub>1</sub>'={1, 2} | q<sub>4</sub>'={1}    | q<sub>5</sub>'={2}    |
| q<sub>2</sub>'={1, 3}       | q<sub>4</sub>'={1}    | q<sub>2</sub>'={1, 3} | q<sub>6</sub>'={3}    |
| q<sub>3</sub>'={2, 3}       | q<sub>5</sub>'={2}    | q<sub>6</sub>'={3}    | q<sub>3</sub>'={2, 3} |
| q<sub>4</sub>'={1}          | q<sub>4</sub>'={1}    | q<sub>4</sub>'={1}    | q<sub>7</sub>'=∅      |
| q<sub>5</sub>'={2}          | q<sub>5</sub>'={2}    | q<sub>7</sub>'=∅      | q<sub>5</sub>'={2}    |
| q<sub>6</sub>'={3}          | q<sub>7</sub>'=∅      | q<sub>6</sub>'={3}    | q<sub>6</sub>'={3}    |
| q<sub>7</sub>'=∅            | q<sub>7</sub>'=∅      | q<sub>7</sub>'=∅      | q<sub>7</sub>'=∅      |
