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
