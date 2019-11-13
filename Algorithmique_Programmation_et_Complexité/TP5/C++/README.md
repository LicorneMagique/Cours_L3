# Tables de hashage

Réalisé par **Julien GIRAUD** (p1704709)

[README visualisable ici](https://github.com/LicorneMagique/Cours_L3/tree/master/Algorithmique_Programmation_et_Complexit%C3%A9/TP4/C%2B%2B)

## Lancer le programme

```shell
make
make run
gnuplot
gnuplot> plot "performance_lineaire.txt" using 2:1
gnuplot> plot "performance_quadratique.txt" using 2:1
gnuplot> plot "performance_double.txt" using 2:1
gnuplot> exit
make clean
```

## Bilan des performances

D'après mes tests on peut résumer les performances de cette façon :

| Taille         | Pas linéaire  | Pas quadratique | Double hashage |
| -------------- | ------------- | --------------- | -------------- |
| Quelconque     | Bon choix     | Bon choix       | Mauvais choix  |
| Puissance de 2 | Mauvais choix | Bon choix       | Moyen          |
| Nombre premier | Bon choix     | Bon choix       | Très bon choix |
