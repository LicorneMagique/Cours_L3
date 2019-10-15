(* TP1 Langages formels

   BUT DU TP

   Manipuler Coq / Gallina

   Se familiariser avec 4 mots-clés :
      - Definition
      - Definition avec match ... with
      - Inductive
      - Fixpoint
*)


(* DÉFINIR UN OBJET (entier, fonction, etc.) *)
(* Mot-clef "Definition" 
   suivi du nom de l'objet
   suivi de ":" 
   suivi du type de l'objet
   suivi de ":="
   suivi de la valeur de l'objet. *)
Definition a : nat := 3.
Definition b : nat := 6.

(* En Coq on donne TOUJOURS les types. *)

(* EFFECTUER UN CALCUL... dans l'interpréteur *)
(* Directive "Compute" *)
(* RÉSULTAT ATTENDU : 9 *)
Compute (a+b).

(* AFFICHER LE TYPE... dans l'interpréteur *)
(* Directive "Check" *)
Check (a+b).



(* 1) TYPES ÉNUMÉRÉS et INDUCTIFS *)


(* Mots-clefs "Inductive" et "|" par cas. 
   C'est la définition d'un ensemble inductif, on donne des règles...
   Comme on définit un *type* de données, son propre type est Type. *)
Inductive jour : Type :=
  | lundi : jour
  | mardi : jour
  | mercredi : jour
  | jeudi : jour
  | vendredi: jour
  | samedi : jour
  | dimanche : jour.
(* ici uniquement des cas de base *)


(* On peut définir une FONCTION jour_suivant sur ce type.
   (jour_suivant e) s'évalue en le nom du jour suivant le jour e.
   Elle est réalisée suivant *la forme* du paramètre, c'est du
   "filtrage" ou "PATTERN MATCHING". C'est le mécanisme le plus
   confortable pour manipuler des structures inductives. *)
(* Mots-clef "match" "with" "end" *)
Definition jour_suivant (j : jour) : jour :=
  match j with
  | lundi => mardi
  | mardi => mercredi
  | mercredi => jeudi
  | jeudi => vendredi
  | vendredi => samedi
  | samedi => dimanche
  | dimanche => lundi
  end.

(* On teste. RÉSULTAT ATTENDU : jeudi *)
Compute (jour_suivant mercredi).


(* EXERCICE *)
(* Définir la fonction qui retourne le surlendemain d'un jour donné *)
(* C'est une fonction qui APPLIQUÉE À un jour, RETOURNE un jour *)
Definition jour_suivant_le_jour_suivant (j : jour) : jour :=
  jour_suivant (jour_suivant j).

(* On re-teste et on devrait obtenir vendredi*)
Compute (jour_suivant_le_jour_suivant mercredi).


(* On peut aussi définir les booléens... *)
(* Il n'y a que des cas de base et on va les appeler Vrai et Faux *)
Inductive booleens : Type :=
| Vrai : booleens
| Faux : booleens.

(* Ainsi que les fonctions logiques usuelles. *)
(* Le complémentaire : non. *)
Definition non (a : booleens) : booleens :=
  match a with
  | Vrai => Faux
  | Faux => Vrai
  end.

(* Directive d'affichage de type *)
Check non.

(* Directive d'affichage de valeur *)
Print non.


(* EXERCICE *)
(* Définir la fonction "et" sur les booléens. *)
Definition et (a : booleens) (b : booleens) : booleens :=
  match a with
  | Faux => Faux
  | Vrai => b
  end.

Definition et' : booleens -> booleens -> booleens :=
  fun a =>
    fun b =>
      match a with
      | Faux => Faux
      | Vrai => b
      end.

(* un petit test, RÉPONSE ATTENDUE : Faux *)
Compute (et Vrai (et Faux Vrai)).


(* EXERCICE *)
(* Définir la fonction "ou" sur les booléens. *)
Definition ou : booleens -> booleens -> booleens :=
  fun a => fun b =>
             match a with
             | Vrai => Vrai
             | Faux => b
             end.

(* RÉPONSE ATTENDUE : Vrai *)
Compute (et Vrai (ou Faux Vrai)).


(* Le langage de Coq a bien sûr des booléens (dans le type prédéfini bool),
   ils sont en fait définis de la même façon que nos booleens. Pour l'instant
   nous allons continuer de travailler avec les nôtres. *)

(* On définit maintenant de façon inductive le type des entiers naturels.
   Un entier naturel est :
   - soit un élément particulier noté Z (pour zéro, c'est un cas de base ici),
   - soit le successeur d'un entier naturel.
 
   On a bien DEUX CONSTRUCTEURS pour les entiers : ils sont soit de la
   *forme* "Z" soit de la *forme* "Succ d'un entier".
*)
Inductive entiers : Type :=
| Z : entiers
| Succ : entiers -> entiers.

Definition un  := Succ Z.
Definition deux  := Succ un.
Definition trois  := Succ deux.


(* EXERCICE *)
(* Définir la fonction prédécesseur *)
(* C'est une fonction qui APPLIQUÉE À un entier, RETOURNE un entier *)
(* On considère que le prédécesseur de quelque chose de la forme Z est... Z *)
(* Le prédécesseur de quelque chose de la forme Succ toto est bien sûr toto *)
Definition pred (a : entiers) : entiers :=
  match a with
  | Z => Z
  | Succ n => n
  end.

(* RÉSULTAT ATTENDU :  Succ (Succ Z) *)
Compute (pred (Succ (Succ (Succ Z)))).


(* On veut écrire une FONCTION RÉCURSIVE pour ajouter deux entiers.
   Comme la fonction est récursive, on utilise le mot-clé Fixpoint (et
   non plus Definition).
   Elle se calcule selon la forme du premier paramètre *) 
Fixpoint plus (a : entiers) (b : entiers) : entiers :=
  match a with
  | Z => b
  | Succ n => Succ (plus n b)
  end.


(* EXERCICE *)
(* Multiplication
   Elle se calcule selon la forme du premier paramètre *)
Fixpoint mult (a : entiers) (b : entiers) : entiers :=
  match a with
  | Z => Z
  | Succ n => plus b (mult n b)
  end.

(* RÉSULTAT ATTENDU : 9 *)
Compute (mult trois trois).


(* EXERCICE *)
(* Définir une fonction est_pair, telle que est_pair APPLIQUÉE À un entier a RETOURNE Vrai si a est pair, Faux sinon. *)
Fixpoint est_pair (a : entiers) : booleens :=
  match a with
  | Z => Vrai
  | Succ Z => Faux
  | Succ (Succ n) => est_pair n
  end.
Fixpoint est_pair' (a : entiers) : booleens :=
  match a with
  | Z => Vrai
  | Succ x => non (est_pair' x)
  end.

Fixpoint est_pair'' (a : entiers) : booleens :=
  match a with
  | Z => Vrai
  | Succ x => match x with
              | Z => Faux
              | Succ y => est_pair'' y
   end
end.

(* RÉSULTAT ATTENDU : Vrai *)
Compute (est_pair deux).

(* RÉSULTAT ATTENDU : Faux *)
Compute (est_pair trois).

(* ------------------------------------------------------------ *)


(* Précédemment, on a défini nos booléens et nos entiers naturels,
mais ils sont en fait déjà définis dans la bibliothèque que Coq charge
initialement au démarrage :

Inductive bool : Set :=
  | true : bool
  | false : bool.

avec les fonctions 

negb (le complémentaire)
andb (le et, (le min))
orb  (le ou, (le max))



Inductive nat : Set :=
  | O : nat
  | S : nat -> nat.

avec les fonctions usuelles + , - , * , etc.
et les comparaisons :
Nat.eqb pour le test d'égalité
Nat.ltb pour le test plus petit
Nat.leb pour le test plus petit ou égal.


CE SONT EUX QU'ON UTILISERA DORÉNAVANT.

 *)

(* ------------------------------------------------------------ *)


(* 2) LISTES D'OBJETS DE TYPE NAT *)


(* On considère ici des listes d'objets de type nat. *)

(* On peut définir de façon inductive un type nliste pour les listes d'objets de type nat. 
  Le cas de base est bien sûr la liste vide, l'autre règle de construction applique cons
  à un nat et une liste de l'ensemble inductif pour créer un nouvel élément de cet ensemble
*)
Inductive nliste : Type :=
  | vide : nliste
  | cons : nat -> nliste -> nliste.

Definition liste0 := vide.
Definition liste1 := cons 1 vide.
Definition liste2 := cons 2 (cons 1 vide).
Definition liste3 := cons 3 (cons 2 (cons 1 vide)).
Definition liste4 := cons 4 (cons 3 (cons 2 (cons 1 vide))).
Print liste0.
Print liste1.
Print liste2.


(* EXERCICE *)
(* Écrire une fonction ajoute: nat -> nliste -> nliste telle que ajoute n l
   retourne une liste correspondant à l'ajout de l'élément n à la liste l.
   C'est bien sûr juste la fonction qui applique cons
*)
Definition ajoute (n : nat) (l : nliste) : nliste :=
  cons n l.

(* RÉSULTAT ATTENDU : cons 3 (cons 2 (cons 1 vide)) *)
Compute (ajoute 3 liste2).


(* EXERCICE *)
(* Écrire une fonction longueur telle que longueur APPLIQUÉE À l
   RETOURNE le nombre (nat) d'éléments de la liste l.  On l'a vue en
   cours.
  C'est bien sûr une fonction qui travaille selon la FORME de l : si
  c'est vide, la longueur vaut zéro, et si l est de la forme cons n l'
  à vous de jouer.  *)
Fixpoint longueur (l : nliste) : nat :=
  match l with
  | vide => 0
  | cons n l' => 1 + longueur l'
  end.

(* RÉSULTAT ATTENDU : 2 *)
Compute (longueur liste2).

(* EXERCICE *)
(* Écrire une fonction concat: nliste -> nliste -> nliste telle que concat l l'
   retourne une liste correspondant à l'ajout des éléments de l en tête de la liste l'. *)
Fixpoint concat (l : nliste) (l' : nliste) : nliste :=
  match l with
  | vide => l'
  | cons n l'' => cons n (concat l'' l')
  end.

(* RÉSULTAT ATTENDU : cons 2 (cons 1 (cons 2 (cons 1 vide))) *)
Compute (concat liste2 liste2).

(* EXERCICE *)
(* Écrire une fonction recherche: nat -> nliste -> booleens telle que recherche n l
   retourne Vrai si un élément n appartient à la liste l et Faux sinon. *)
(* Pour l'égalité entre éléments du type nat, soit on la redéfinit, soit on utilise Nat.eqb *)
Require Import Nat.
Check (eqb 3 4).
Compute (eqb 3 4).
Fixpoint eq (n : nat) (n' : nat) : bool :=
  match (n, n') with
  | (O, O) => true
  | (O, S n) => false
  | (S n , O) => false
  | (S m, S m') => eq m m'
  end.

Fixpoint eq' (n : nat) (m : nat) : bool :=
  match n with
  | O => match m with
         | O => true
         | S m' => false
         end
  | S n' => match m with
            | O => false
            | S m' => eq m m'
            end
  end.

(* La fonction recherche APPLIQUÉE À un nat, APPLIQUÉE À une liste, RETOURNE un bool. *)
Fixpoint recherche (n : nat) (l : nliste) : bool :=
  match l with
  | vide => false
  | cons n' l' => match Nat.eqb n n' with
                  | true => true
                  | false => recherche n l'
                  end
  end.

Fixpoint recherche' (n : nat) (l : nliste) : bool :=
  match l with
  | vide => false
  | cons n' l' => orb (Nat.eqb n n') (recherche n l')
  end.

(* RÉSULTAT ATTENDU : true *)
Compute (recherche 1 liste2).

(* RÉSULTAT ATTENDU : false *)
Compute (recherche 3 liste2).


(* FIN DU TP1 *)

(* ------------------------------------------------------------ *)

(* EXERCICES A FAIRE CHEZ VOUS *)

(* EXERICE *)
(* Définir une fonction bcompose : f -> g -> h telle que h est la composition des
deux fonctions booléens f et g *)

(* Tester bcompose en définissant une fonction nonnon : booléens -> booléens qui
définit non o non *)

(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (nonnon Vrai). *)


(* EXERCICE *)
(* Définir la fonction factorielle sur les entiers *)

(* RÉSULTAT ATTENDU : 24 sous forme de Succ( ... (Succ(Z) ...) *)
(* Compute (factorielle (plus trois un)). *)


(* EXERCICE *)
(* Définir la fonction moins, soustraction non négative sur les entiers *)

(* RÉSULTAT ATTENDU : Succ Z *)
(* Compute (moins deux un).*)

(* RÉSULTAT ATTENDU : Z *)
(* Compute (moins deux trois).*)

(* EXERCICE *)
(* Définir une fonction inf, tel que inf a b vaut/retourne Vrai si a est
   inférieur ou égal à b, Faux sinon. *)

(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (inf trois trois). *)


(* EXERCICE *)
(* Définir une fonction egal, tel que egal a b donne Vrai si les entiers
   a et b sont égaux, Faux sinon.*)

(* RÉSULTAT ATTENDU : Vrai *)
(* Compute (egal trois trois). *)

(* RÉSULTAT ATTENDU : Faux *)
(* Compute (egal un trois). *)


(* EXERCICE *)
(* Écrire une fonction miroir: nliste -> nliste, qui
   retourne une liste correspondant à son argument dans l'ordre
   inverse. Dans un premier temps, on pourra utiliser la fonction de
   concaténation vue précédemment. *)

(* RÉSULTAT ATTENDU : cons 1 (cons 2 (cons 3 (cons 4 vide))) *)
(* Compute (miroir liste4).*)

(* RÉSULTAT ATTENDU : cons 1 (cons 2 (cons 3 (cons 4 vide))) *)
(* Compute (miroir' liste4).*)


(* EXERCICE *)
(* Écrire une fonction supprime: nat -> nliste -> nliste telle que
   supprime n l retourne une liste d'objets de type nat correspondant
   à l sans la première occurrence de n (le cas échéant), à l
   sinon. *)

(* RÉSULTAT ATTENDU : cons 4 (cons 2 (cons 1 vide)) *)
(* Compute (supprime 3 liste4). *)


(* EXERCICE *)
(* Écrire une fonction supprime_tout: nat -> nliste -> nliste telle
   que supprime_tout n l retourne une liste correspondant à l sans
   occurrence d'un nat n (le cas échéant), à l sinon. *)


(* EXERCICE *)
(* Écrire une fonction il_existe_pair: nliste -> booleens, telle que
   il_existe_pair l retourne Vrai si un élément de l est pair, Faux
   sinon. *)

(* RÉSULTAT ATTENDU : true *)
(* Compute (il_existe_pair liste4).*)


(* EXERCICE *)
(* Insertion triée *)
(* Écrire dans un premier temps une fonction leq : nat -> nat -> bool qui teste si le
premier entier est inférieur ou égal au second *)

(* RÉSULTAT ATTENDU : true *)
(* Compute (leq 2 2).*)

(* RÉSULTAT ATTENDU : true *)
(* Compute (leq 2 3).*)

(* RÉSULTAT ATTENDU : false *)
(* Compute (leq 3 2).*)

(* Écrire une fonction insertion_triee : nat -> nliste -> nliste qui effectue
une insertion triée dans une liste *)

(* RÉSULTAT ATTENDU : cons 1 (cons 2 (cons 2 (cons 3 (cons 4 vide)))) *)
(* Compute (insertion_triee 2 (miroir liste4)).*)

(* RÉSULTAT ATTENDU : cons 4 (cons 3 (cons 2 (cons 1 (cons 6 vide)))) *)
(* Compute (insertion_triee 6 liste4).*)


(* EXERICE *)
(* Tri par insertion d'une liste *)
(* Écrire une fonction tri_insertion : nliste -> nliste qui effectue
le tri par insertion d'une liste *)

(* RÉSULTAT ATTENDU : cons 1 (cons 1 (cons 2 (cons 2 (cons 3 (cons 3 (cons 4 (cons 4 vide)))))) *)
(* Compute (tri_insertion (concat liste4 liste4)).*)






(* 3) ARBRES BINAIRES *)


(* Arbres binaires *)

(* EXERCICE *)
(* Donner une définition par induction de l'ensemble nBin des arbres
binaires contenant des nat. On souhaite avoir une représentation de
l'arbre vide dans nBin. *)



(* Donner un exemple d'arbre, disons à 5 éléments *)

(*
Definition a1 := nNode
                      (nNode nEmpty 2 nEmpty)
                      1
                      (nNode
                            (nNode nEmpty 4 nEmpty)
                            3
                            (nNode nEmpty 5 nEmpty)
                      ).

Check a1.
Print a1.
*)

(* EXERCICE *)
(* Définir la fonction nelements qui renvoie la liste des éléments
   contenus dans un arbre binaire de nat. Le faire naïvement avec un
   concat pour commencer. *)

(* RÉSULTAT ATTENDU : cons 1 (cons 2 (cons 3 (cons 4 (cons 5 vide)))) *)
(* Compute (nelements a1).*)



(* EXERCICE *)
(* Définir la fonction nnelts qui renvoie le nombre de noeuds internes
   (portant une étiquette de type nat) dans un nBin. *)

(* RÉSULTAT ATTENDU : 5 *)
(* Compute (nnelts a1).*)


(* EXERCICE *)
(* Définir la fonction nfeuilles qui renvoie le nombre de feuilles *)

(* RÉSULTAT ATTENDU : 6 *)
(* Compute nfeuilles a1. *)

