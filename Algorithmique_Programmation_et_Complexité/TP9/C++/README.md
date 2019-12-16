# TP9 - Graphe d'une image et binarisation

Réalisé par **Julien GIRAUD** (p1704709)

[README visualisable ici](https://github.com/LicorneMagique/Cours_L3/tree/master/Algorithmique_Programmation_et_Complexit%C3%A9/TP9/C%2B%2B)

## Lancer le programme

Le programme attend comme paramètres le nom du fichier image source (image4.pgm), le nom du fichier à produire (toto.pgm), alpha (50) et éventuellement sigma (127)

```shell
# Compilation
make

# Sans sigma
./main image4.pgm toto.pgm 50

# Avec sigma
./main image4.pgm toto.pgm 50 127

# Nettoyage
make clean
```
