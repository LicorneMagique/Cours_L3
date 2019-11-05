# Source

[Cours complets de l'année dernière](https://perso.liris.cnrs.fr/marc.plantevit/doku/doku.php?id=lifbdw2_2018a)

[Cours de cette année](https://perso.liris.cnrs.fr/marc.plantevit/doku/doku.php?id=lifbdw2_2019a)

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

---

## TD4

### EX1

| Partie gauche | Fermeture |
| ------------- | --------- |
| A             | A         |
| B             | BE        |
| C             | CE        |
| D             | BDE       |
| E             | E         |
| AB            | ABCDE = R |
| AC            | R         |
| AD            | R         |
| AE            | R         |
| BC            | R         |
| BD            | BDE       |
| BE            | BDE       |
| CD            | R         |
| CE            | CE        |
| DE            | BDE       |
| BDE           | BDE       |

Liste des DF : {}

## Cours formes normales

<https://openclassrooms.com/fr/courses/4055451-modelisez-et-implementez-une-base-de-donnees-relationnelle-avec-uml/4458402-optimisez-votre-modele-relationnel-avec-les-formes-normales>

L'objectif du cours est d'arriver en 4<sup>ème</sup> forme normale (Forme normale de Boyce-Codd)

- **1<sup>ère</sup> forme normale** : tous les éléments doivent être atomiques → **pas de liste**.  
Exemple de passage à la première forme normale

| (id) | email |
| ---- | ----- |
| 1    | edouard.bracame@joe-bar-team.org, ed@jbt.org |
| 2    | jean.manchzeck@joe-bar-team.org |

↓↓↓↓↓↓↓↓↓↓↓↓

| (id) | email |
| ---- | ----- |
| 1    | edouard.bracame@joe-bar-team.org |
| 1    | ed@jbt.org |
| 2    | jean.manchzeck@joe-bar-team.org |

- **2<sup>ème</sup> forme normale** : tous les éléments d'une table avec une clé primaire **composite** (composée de plusieurs attributs) doivent dépendre de toute la clé primaire, pas d'un sous-ensemble de celle-ci.  
Exemple :

| (coureur | parcours) | difficulté | note |
| -------- | --------- | ---------- | ---- |
| michel   | p1        | 4          | 12/20 |
| bob      | p1        | 4          | 14/20 |
| michel   | p2        | 2          | 18/20 |

La difficulté dépend du parcours et non de la combinaison (parcours, coureur). Il faut donc créer une table associative...

↓↓↓↓↓↓↓↓↓↓↓↓

| (coureur | parcours) | note |
| -------- | --------- | ---- |
| michel   | p1        | 12/20 |
| bob      | p1        | 14/20 |
| michel   | p2        | 18/20 |

| (parcours) | difficulté |
| ---------- | ---------- |
| p1         | 4 |
| p2         | 2 |

- **3<sup>ème</sup> forme normale** : tous les éléments d'une table doivent dépendre de la clé primaire, pas d'un autre élément.  
Exemple :

| (id) | civilité | nom | prenom | sexe |
| -- | ---------- | --- | ------ | ---- |
| 1  | Madame     | Germain | Sophie | F |
| 2  | Monsieur   | Hilbert | David  | M |
| 3  | Madame     | Noether | Emmy   | F |

Le sexe dépend de la civilité, ou l'inverse...

↓↓↓↓↓↓↓↓↓↓↓↓

| (id) | civilité | nom | prenom |
| -- | ---------- | --- | ------ |
| 1  | Madame     | Germain | Sophie |
| 2  | Monsieur   | Hilbert | David  |
| 3  | Madame     | Noether | Emmy   |

| (civilité) | sexe |
| ---------- | ---- |
| Madame     | F |
| Monsieur   | M |

- **Forme normale de Boyce-Codd** : certain(s) élément(s) d'une table avec une clé primaire composite permettent de déterminer une partie de la clé primaire.  
Exemple :

| (num_sécu | pays) | nom | région |
| --------- | ----- | --- | ------ |
| 1..1      | France  | Michel | Rhône |
| 1..1      | Espagne | Paul   | Catalogne |

Certe on peut retrouver le nom et la région à partir de la clé primaire, mais la région permet aussi de déterminer le pays...

↓↓↓↓↓↓↓↓↓↓↓↓

| (num_sécu | région) | nom |
| --------- | ------- | --- |
| 1..1      | Rhône     | Michel |
| 1..1      | Catalogne | Paul |

| (région) | pays |
| -------- | ---- |
| Catalogne | Espagne |
| Rhône     | France |

**Il arrive cependant que des DF ne survivent pas à ce changement de forme normale.

---

### Algorithme de normalisation

En entrée on prend l'ensemble des attributs et l'ensemble des contraintes

En sortie on veut un schéma de BD normalisé en 4<sup>ème</sup> forme normale

---

Soir R l'ensemble de nos relations et F les DF

1. Construire une couverture canonique de F (virer les DF qu'on peut déduire)

2. Pour chaque DF X → Y, créer une relation XY' (Disons qu'on avait projet → chef, budjet. Alors on ajoute deux nouvelles relations : projet → chef et projet → budjet)

3. On supprime les schémas non maximaux par inclusion

4. S'il y a perte de jointure alors on ajoute une relation composée d'une clé de F

---

### Exemple de l'algo

R[ABCDEFGHI]  
F = {
    D → AEI,
    E → CH,
    A → CI,
    I → A,
    H → C,
    C → DI,
    DE → ACI
}

1. D+ → ACDEHI,
    E+ → ACDEHI,
    A+ → ACDEHI,
    I+ → ACDEHI,
    H+ → ACDEHI,
    G+ → GF,
    C+ → ACDEHI,
    DE+ → ACDEHI

    D → E,
    E → A,
    A → I,
    I → H,
    H → C,
    G → F,
    C → D

suite sur papier

## TD5

### EX1

1. ```math
    F1 = {
        A -> C,
        AC -> D,
        E -> AD,
        E -> F
    }
    => {
        A+ -> ACD
        AC+ -> ACD
        E+ -> ACDEF
    }

    F2 = {
        A -> CD,
        E -> AF
    }
    => {
        A+ -> ACD
        E+ -> ACDEF
    }

    Donc F1 <=> F2
    ```

2. ```math
    G = {
        A -> CD
        E -> AF
    }
    ```

3. ```math
    F = {
        A -> BC,
        D -> E,
        C -> D
    } minimum ?
    G = {
        A -> ABCDE,
        D -> DE,
        C -> CDE
    }
    |G| = |F| => F est minimum.
    ```

### EX2 : sur papier

### EX3

1. **Cette question tombe souvent en  DS**

    F optimum => F minimum => F non redondant  
    F non optimum <= F non minimum <= F redondant  
    Donc il suffit de montrer que F redondant pour répondre à la question

    ```math
    F = {
        D -> A,
        D -> C,
        D -> E,
        D -> F,
        CE -> G,
        AG -> F,
        ADG -> B,
        BG -> ADE,
        BF -> DG
    }
    D -> C    D -> E
    ----------------
            D -> CE    CE -> G
            ------------------
                        D -> G    D -> A
                        ----------------
                                D -> GA    AG -> F
                                ------------------
                                        D -> F
    Donc redondance -> CQFD
    ```

2. )

```math
    {
        D+   -> ABCDEFG,
        CE+  -> CEG,
        AG+  -> AFG,
        ADG+ -> ABCDEFG,
        BG+  -> ABCDEFG,
        BF+  -> ABCDEFG
    }
    F = {
        D  -> BF,
        CE -> G,
        AG -> F,
        BG -> F,
        BF -> ACDE
    }
```

## TD6

### EX1

| Question | Relation | 2FN | 3FN | FNBC | 4FN |
| -------- | -------- | --- | --- | ---- | --- |
| 1        | E -> D   | oui | oui | oui  | oui |
| 1        | D -> C   | oui | oui | oui  | oui |
| 2        | E -> S   | oui |
| 2        | E ->> F  | non |
| 3        | RV -> C  | oui | oui | oui |
| 3        | C -> V   | oui | oui | non |

### EX2

Par principe je ne fais pas de démonstrations sur les ensembles en BD

### EX3

1. )

    ```math
    {
        NumR -> NomR, TypeR
        NumI -> NomI
        NumR, NumI -> Qte
    }
    ```

2. )

    Il y a un problème de redondance
