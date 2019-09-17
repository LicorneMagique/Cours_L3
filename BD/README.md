# Source

<https://perso.liris.cnrs.fr/marc.plantevit/doku/doku.php?id=lif10_2016a>

## Cours 1

L'intérêt d'un langage déclaratif est qu'on ne dit pas comment il doit fonctionner → c'est l'optimiseur qui s'occupe de coder notre requête.

Les **contraintes d'intégrité** sont tout ce qu'on défini pour assurer la cohérence des données

### Algèbre relationnel

### SQL

### Définition à savoir

Une Dépendance Fonctionnelle (**DF**) sur un schéma de relation R est une expression formelle de la forme `R : X → Y` (ou simplement `X → Y` lorsque R est implicite), avec X , Y ⊆ R  
**On peut définir une DF de la façon suivante :**  
Soit r une relation sur R. Une DF R : X → Y est satisfaite dans r, noté r |= X → Y , si et seulement si :  
∀ t1, t2 ∈ r.t1[X] = t2[X] ⇒ t1[Y] = t2[Y]

---

## TD1

σ π ⋊ θ × ÷ ∩ ∪ ∧ ∨ ≥ ≤

### Exercice 2

1) Commandes
2) π<sub>Pnom</sub>(Commandes)
3) π<sub>Pnom</sub>(σ<sub>Cnom="Jean"</sub>(Commandes))
4) π<sub>Fnom</sub>(σ<sub>(Pnom="Cornas" ∨ Pnom="Bordeaux") ∧ Prix ≤ 10</sub>(Produits))
5) π<sub>Pnom</sub>(Produits) ∪ *ρ*<sub>Fnom/Pnom</sub>(π<sub>Fnom</sub>(Fournisseurs))
6) π<sub>Pnom,Prix,Fnom</sub>(Produits ⋊ σ<sub>Cnom="Jean"</sub>(Commandes))
7) σ<sub>Fnom<Fnom'</sub>(Fournisseurs ⋊ *ρ*<sub>Fnom/Fnom', Status/Status'</sub>(Fournisseurs))
8) π<sub>Pnom</sub>(σ<sub>Cnom="Jean"</sub>(Commandes)) ∪ π<sub>Pnom</sub>(σ<sub>Prix ≥ 15</sub>(Produits))
9) π<sub>Pnom</sub>(Produits) \ π<sub>Pnom</sub>(Commandes)
10) π<sub>Pnom</sub>(σ<sub>Prix ≤ 15</sub>(Produits)) ∩ π<sub>Pnom</sub>(σ<sub>Qte ≥ 10</sub>(Commande))
11) π<sub>Pnom</sub>(Produits ÷ Fournisseurs)
12) π<sub>Pnom</sub>(Produits) \ π<sub>Pnom</sub>(σ<sub>Prix < Prix'</sub>(Produits × *ρ*<sub>(Pnom/Pnom', Fnom/Fnom', Prix/Prix')</sub>(Produits)))

### Exercice 3

⇒ ⇐ ¬ ⇔ ∃

1) {(c.Nom, c.Pnom, c.Qte) | Commandes(c)}
2) {(c.Pnom) | Commandes(c) }
3) {(c.Pnom) | Commandes(c) ∧ c.Cnom = "Jean"}
4) {p.Fnom | (Produits) ∧ (p.Pnom = "Cornas" ∨ p.Pnom = "Bordeaux") ∧ p.Prix ≤ 10}
5) {(p.Pnom) | ∃f.Produits(p) ∧ Fournisseurs(f) ∧ p.Pnom= f.Fnom}
6) {(p.Pnom, p.Prix, p.Fnom) | Fournisseurs(u) ∧ Fournisseurs(v) ∧ u.ville = v.ville ∧ u.Fnom < v.Fnom}

### Exercice 4

1) max(|r|, |s|) ≤ |R ∪ S| ≤ |r| + |s|
2) 0 ≤ |R ∩ S| ≤ min(|r|, |s|)
3) 0 ≤ |R \ S| ≤ |r|
4) 0 ≤ |π<sub>A</sub>(R)| ≤ |r|
5) |R ⋊ S| = |R ∩ S| car les schémas sont les mêmes
