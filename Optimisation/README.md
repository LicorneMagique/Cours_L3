# Optimisation / Programmation Linéaire

Par [BOUAKAZ BRONDEL SAIDA](mailto:saida.bouakaz@univ-lyon1.fr)

[Site de l'UE](http://odf.univ-lyon1.fr/ue-8166-12/optimisation.html)

## Programmation Linéaire

Un programme linéaire est un problème d'optimisation : maximisation ou minimisation

Ce type de problème est défini par

- des variables de décision (valeurs à calculer)
- une fonction objectif linéaire (à optimiser : AX <= B)
- diapo

---

Exemple 2

Fonction objectif :  
`350 * nbA + 300 * nbB`

Contraintes :  
`nbA + nbB <= 200`
`9 * nbA + 6 * nbB <= 1566`
`12 * nbA + 16 * nbB <= 2880`
`nbA >= 0`
`nbB >= 0`


### Modélisation et résolution du problème

```python
from constraint import *

problem = Problem()
problem.addVariable("a", range(0, 201))
problem.addVariable("b", range(0, 201))
problem.addConstraint(lambda a, b: a+b <= 200, ("a", "b"))
problem.addConstraint(lambda a, b: 9 * a + 6 * b <= 1566, ("a", "b"))
problem.addConstraint(lambda a, b: 12 * a + 16 * b <= 2880, ("a", "b"))

solutions = problem.getSolutions()

bestVal = -1
for solution in solutions:
    val = 350 * solution['a'] + 300 * solution['b']
    bestVal = val if val > bestVal else bestVal
print("val = ", bestVal)

for solution in solutions:
    if 350 * solution['a'] + 300 * solution['b'] == bestVal:
        print(solution)

```
