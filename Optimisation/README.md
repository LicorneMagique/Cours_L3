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

### Modélisation et résolution du problème - OR-Tools

```python
# Import de la librairie Python de OR-Tools
from ortools.sat.python import cp_model

# Création du model
model = cp_model.CpModel()

# Initialisation des variables sur [0, 201[
a = model.NewIntVar(0, 201, 'a')
b = model.NewIntVar(0, 201, 'b')

# Objectif : formule de Z à maximiser
model.Maximize(350 * a + 300 * b)

# Ajout des contraintes arithmétiques
model.Add(a+b <= 200)
model.Add(9 * a + 6 * b <= 1566)
model.Add(12 * a + 16 * b <= 2880)

# Résolution du problème
solver = cp_model.CpSolver()
solver.Solve(model)

print("Z =", solver.ObjectiveValue())
print("a =", solver.Value(a))
print("b =", solver.Value(b))

```
