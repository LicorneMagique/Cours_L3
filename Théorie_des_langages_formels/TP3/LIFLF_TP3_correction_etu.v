(* TP3 Langages formels *)

(******************************************************************************)
(********** programmation fonctionnelle et automates en Coq (partie 2) ********)
(******************************************************************************)

(*
  L'objectif de LIFLF_TP3 est de définir des automates et de les faire s'exécuter
  dans la partie *programme* de Coq. Pour cela, on va utiliser ce qu'on a défini
  lors du TP2, pour définir les automates :
   1) le codage du quintuplet usuel <K, Sigma, delta : K*Sigma -> K, s, F> en Coq
   2) la représentation finie de la fonction delta : K*Sigma -> K

  Pour aller plus loin, on introduit le polymorphisme en fin de sujet.
*)


(* On commence par rappeler ce qu'on avait défini dans le TP2 *)

(* Notre alphabet d'exemple *)
Inductive Alphabet : Type :=
| a : Alphabet
| b : Alphabet.

(* La fonction "comp_alphabet" de comparaison de deux Alphabet *)
Definition comp_alphabet (x y : Alphabet) : bool :=
  match x with
  | a => match y with
         | a => true
         | b => false
         end
  | b => match y with
         | a => false
         | b => true
         end
end.

Require Export List.
Import ListNotations.

(* La fonction "appartient" qui teste si un entier appartient à une liste d'entiers *)
Fixpoint appartient (x : nat) (l : list nat) : bool :=
  match l with
  | [] => false
  | h::rl => (Nat.eqb x h) || (appartient x rl)
  end.

(* La fonction "trouve" qui prend en paramètres une listes de paires (clef,valeur)
   et une clef k, et renvoie la première valeur associée à k quand elle existe et None sinon
*)
Fixpoint trouve (assoc : list (Alphabet * nat)) (key : Alphabet) : option nat :=
  match assoc with
    | [] => None
    | h::rassoc => if (comp_alphabet key (fst h)) then (Some (snd h))
                   else trouve rassoc key
  end.



(******************************************************************************)
(* Partie 1 : la représentation des Automates en Coq  *)
(******************************************************************************)

(* Formellement, un Automate est un quintuplet <K, Sigma, K, delta : K*Sigma -> K, s, F > avec
   - K l'ensemble des états,
   - Sigma l'alphabet,
   - delta la fonction de transition
   - s l'état initial,
   - F l'ensemble des état finaux

   Ici, on va représenter les ensembles par des listes et la fonction de transition par une fonction (!).
   On va s'appuyer sur le type "Alphabet" défini dans le TP2.
   De même, on va prendre les entiers "nat" pour identifier les états.

   L'automate "M" défini par "automate K Sigma delta s F", correspond au
   quintuplet "M = <K, Sigma, delta, s, F>" du cours.

   On justifie la réprésentation et le choix des types :
    - (K : list nat) : *liste* de TOUS les états. Une liste c'est différent d'un ensemble, plus facilement programmable
    - (Sigma : Alphabet) : liste des symboles utilisés
    - (s : nat) : état initial
    - (F : list nat) une liste de nat des états finals. Là encore ensemble != liste. 

   La principale différence est sur le choix de la fonction de transition delta
    - (delta : nat -> Alphabet -> option nat)

   C'est *presque* le type usuel K * Sigma -> K à la curryfication près ET avec une "option" sur le résultat.
   "option" permet d'exprimer que la fonction de transition delta est *partielle* (et non totale) :
   on va en fait manipuler en Coq des automates aux transitions *partielles*.
*)

(* EXERCICE *)
(* Définir le type Automate représentant ce quintuplet. *)
Inductive Automate : Type :=
    automate : list nat -> list Alphabet -> (nat -> Alphabet -> option nat) -> nat -> list nat -> Automate.

(* Question : pour un automate "M = automate K Sigma delta s F", peut-on dire que
              les élements de F qui ne sont pas dans K sont insignifiants ?
*)


(* EXERCICE *)
(* Définir les 5 fonctions suivantes *)

(* "etats" : prend en paramètre un automate et renvoie la liste des états *)
Definition etats (M : Automate) :  list nat :=
  match M with
    automate ql _ _ _ _ => ql
  end.

(* "symboles" : prend en paramètre un automate et renvoie la liste des symboles de l'alphabet *)
Definition symboles (M : Automate) :  list Alphabet :=
  match M with
    automate _ sigma _ _ _ => sigma
  end.

(* "initial" : prend en paramètre un automate et renvoie l'état initial *)
Definition initial  (M : Automate) :  nat :=
  match M with
    automate _ _ _ q0 _ => q0
  end.

(* "acceptant" : prend en paramètre un automate et un état et renvoie "true" SSI q est un état final *)
Definition acceptant  (M : Automate) (q : nat) : bool  :=
  match M with
    automate _ _ _ _ lF => (appartient q lF)
  end.

(* "transition" : prend en paramètre un automate, un état et un symbole, et renvoie l'état (optionnellement)
   accessible depuis "q" en lisant "c" *)
Definition transition  (M : Automate) (q : nat) (c : Alphabet) : option nat :=
  match M with
    automate _ _ f _ _ => f q c
  end.


(* EXERCICE *)
(* Exemple : définir l'automate "M_nb_b_impair" à deux états qui accepte les mots contenant un nombre impair de 'b',
             et donner des tests unitaires. La fonction delta est donnée ci-dessous. *)

Definition delta_nb_b_impair (q : nat) (c : Alphabet) : option nat :=
match (q,c) with
 | (1,a) => Some 1
 | (1,b) => Some 2
 | (2,a) => Some 2
 | (2,b) => Some 1
 | (_,_) => None
end.

Definition M_nb_b_impair := automate [1;2] [a;b] (delta_nb_b_impair) 1 [2].

Example M_nb_b_impair_etats : etats M_nb_b_impair = [1;2].
Proof.
cbv. reflexivity.
Qed.
Example M_nb_b_impair_symboles : symboles M_nb_b_impair = [a;b].
Proof.
cbv. reflexivity.
Qed.
Example M_nb_b_impair_initial : initial M_nb_b_impair = 1.
Proof.
cbv. reflexivity.
Qed.
Example M_nb_b_impair_acceptant_1 : acceptant M_nb_b_impair 1 = false.
Proof.
cbv. reflexivity.
Qed.
Example M_nb_b_impair_acceptant_2 : acceptant M_nb_b_impair 2 = true.
Proof.
cbv. reflexivity.
Qed.
Example M_nb_b_impair_transition_1 : transition M_nb_b_impair 1 a = Some 1.
Proof.
cbv. reflexivity.
Qed.
Example M_nb_b_impair_transition_2 : transition M_nb_b_impair 2 b = Some 1.
Proof.
cbv. reflexivity.
Qed.


(* EXERCICE *)
(* Définir "execute" qui va calculer l'état d'arrivée en lisant un mot, c'est-à-dire une "list Alphabet" *)

Fixpoint execute (M : Automate)  (q : nat) (w : list Alphabet) : option nat :=
  match w with
  | [] => Some q
  | h::rw => match transition M q h with
             | None => None
             | Some e => execute M e rw end
  end.

Example M_nb_b_impair_execute_1 : execute M_nb_b_impair 1 [] = Some 1.
cbv. reflexivity. Qed.
Example M_nb_b_impair_execute_2 : execute M_nb_b_impair 1 [a;a;b;a;b;b] = Some 2.
cbv. reflexivity. Qed.


(* EXERCICE *)
(* Définir "reconnait" qui va accepter ou refuser un mot *)

Definition reconnait (M : Automate) (w : list Alphabet) : bool :=
  match (execute M (initial M) w) with
  | None => false
  | Some e => acceptant M e
  end.
Example M_nb_b_impair_reconnait_1 : reconnait M_nb_b_impair [] = false.
cbv. reflexivity. Qed.
Example M_nb_b_impair_reconnait_2 : reconnait M_nb_b_impair [a;a;b;a;b;b] = true.
cbv. reflexivity. Qed.


(* EXERCICE *)
(* Exemple : définir l'automate "M_commence_et_finit_par_a" à trois états qui accepte les mots commençant et finissant par 'a',
             et donner des tests unitaires *)

Definition delta_commence_et_finit_par_a (q : nat) (c : Alphabet) : option nat :=
match (q,c) with
 | (1,a) => Some 2
 | (2,a) => Some 2
 | (2,b) => Some 3
 | (3,a) => Some 2
 | (3,b) => Some 3
 | (_,_) => None
end.

Definition M_commence_et_finit_par_a := automate [1;2;3] [a;b] (delta_commence_et_finit_par_a) 1 [2].

Example M_commence_et_finit_par_a_execute_1 : execute M_commence_et_finit_par_a 1 [] = Some 1.
cbv. reflexivity. Qed.
Example M_commence_et_finit_par_a_execute_2 : execute M_commence_et_finit_par_a 1 [a;a;b;a;b;b;a] = Some 2.
cbv. reflexivity. Qed.

Example M_commence_et_finit_par_a_reconnait_1 : reconnait M_commence_et_finit_par_a [] = false.
cbv. reflexivity. Qed.
Example M_commence_et_finit_par_a_reconnait_2 : reconnait M_commence_et_finit_par_a [a;a;b;a;b;b;a] = true.
cbv. reflexivity. Qed.



(******************************************************************************)
(* Partie 2 : la représentation des fonctions de transition en Coq ou
              recherche dans les listes de paires  *)
(******************************************************************************)

(* On souhaite donner une description de la fonction de transition par SON GRAPHE
   plutôt que donner son code.
   Rappel, le graphe d'une fonction f : A -> B est la relation définie par { (x,f(x)) | x dans A}.

   Par exemple la liste [((1,a),1) ; ((1,b),2) ; ((2,a),2) ; ((2,b),1)] indique que
     - ((1,a),1) : état courant 1, symbole courant a --> nouvel état 1
     - ((1,b),2) : état courant 1, symbole courant b --> nouvel état 2
     - ((2,a),2) : état courant 2, symbole courant a --> nouvel état 2
     - ((2,b),1) : état courant 2, symbole courant b --> nouvel état 1
*)

Print delta_nb_b_impair.
(*
Definition delta_nb_b_impair (c : Alphabet) (q : nat) : option nat :=
match (c,q) with
 | (a,1) => Some 1
 | (b,1) => Some 2
 | (a,2) => Some 2
 | (b,2) => Some 1
 | (_,_) => None
end.
*)

(* Comme le domaine de la fonction de transition est fini, on peut faire l'inverse,
   c'est-à-dire construire une fonction à partir d'un graphe FINI.

   On va représenter le graphe de f par *un dictionnaire*, une liste de paires (clé, valeur).

   La principale fonctionalité que l'on attend d'un dictionnaire est de pouvoir retrouver
   la valeur associée à une clé. En le faisant, on reconstruit (à un "option" près) f
*)


(* EXERCICE *)
(* Définir la fonction "trouve_paire" avec pour type "list ((nat * Alphabet) * nat) -> (nat * Alphabet) -> option nat"
   qui prend en paramètres une lite et une clé et retourne la première valeur correspondant à la clé si elle existe,
   None sinon.
   La liste est une liste de "((nat * Alphabet) * Alphabet)" et donc la clé est un "(nat * Alphabet)".
*)
Definition comp_paire (x y : (nat * Alphabet)) : bool :=
  andb (Nat.eqb (fst x) (fst y)) (comp_alphabet (snd x) (snd y)).
Fixpoint trouve_paire (assoc : list ((nat * Alphabet) * nat)) (key : (nat * Alphabet)) : option nat :=
  match assoc with
    | [] => None
    | h::rassoc => if (comp_paire key (fst h)) then (Some (snd h))
                   else trouve_paire rassoc key
  end.


(* EXERCICE *)
(* En utilisant trouve_paire, définir une fonction "graphe_vers_fonction" qui transforme
   une liste "list ((nat * Alphabet) * nat)" en une fonction "Alphabet -> nat -> option nat"
*)
Definition gvf (assoc : list ((nat * Alphabet) * nat)) (q : nat) (c : Alphabet) : option nat :=
  trouve_paire assoc (pair q c).
Definition graphe_vers_fonction (assoc : list ((nat * Alphabet) * nat)) : nat -> Alphabet -> option nat :=
  gvf assoc.


(* EXERCICE *)
(* Exemple : définir l'automate "M_nb_b_impair'"à deux états qui accepte les mots contenant un nombre impair de 'b',
             et donner des tests unitaires. Le graphe de transition est donnée ci-dessous. *)
Definition graphe_nb_b_impair := [((1,a), 1) ; ((1,b),2) ; ((2,a),2) ; ((2,b),1)].

Compute (trouve_paire graphe_nb_b_impair (3,b)).

Definition delta_nb_b_impair_graphe : nat -> Alphabet -> option nat :=
  graphe_vers_fonction graphe_nb_b_impair.

Compute ((graphe_vers_fonction graphe_nb_b_impair) 2 a).

Definition M_nb_b_impair' := automate [1;2] [a;b] (delta_nb_b_impair_graphe) 1 [2].

Example M_nb_b_impair_reconnait_1' : reconnait M_nb_b_impair' [] = false.
cbv. reflexivity. Qed.
Example M_nb_b_impair_reconnait_2' : reconnait M_nb_b_impair' [a;a;b;a;b;b] = true.
cbv. reflexivity. Qed.


(* EXERCICE *)
(* Exemple : définir l'automate à trois états qui accepte les mots commençant et finissant par 'a',
             et donner des tests unitaires. La fonction de transition est donnée ci-dessous. *)
Definition graphe_commence_et_finit_par_a := [((1,a),2) ; ((2,a),2) ; ((2,b),3) ; ((3,a),2) ; ((3,b),3)].
Definition delta_commence_et_finit_par_a_graphe : nat -> Alphabet -> option nat :=
  graphe_vers_fonction graphe_commence_et_finit_par_a.

Compute ((graphe_vers_fonction graphe_commence_et_finit_par_a) 2 a).

Definition M_commence_et_finit_par_a' := automate [1;2;3] [a;b] (delta_commence_et_finit_par_a_graphe) 1 [2].

Example M_commence_et_finit_par_a_reconnait_1' : reconnait M_nb_b_impair' [] = false.
cbv. reflexivity. Qed.
Example M_commence_et_finit_par_a_2' : reconnait M_commence_et_finit_par_a' [a;a;b;a;b;a] = true.
cbv. reflexivity. Qed.


(* Rappel : dans "M_nb_b_impair'" et "M_nb_b_impair" on ne s'intéresse qu'aux états,
            PAS à TOUS les entiers, donc on met une garde sur "q". *)

(* EXERCICE *)
(* Montrer que delta_nb_b_impair et delta_nb_b_impair_graphe sont équivalents sur les états valides *)
Lemma delta_nb_b_impair_trouve : forall q c, (appartient q [1;2] = true) ->  delta_nb_b_impair_graphe q c = delta_nb_b_impair q c.
Proof.
intros q c Happ.
assert (q = 1 \/ q = 2) as Hq.
{ simpl in Happ.
  rewrite Bool.orb_false_r in Happ.
  apply Bool.orb_true_iff in Happ.
  destruct Happ as [Hq1 | Hq2].
  - apply PeanoNat.Nat.eqb_eq in Hq1. left. exact Hq1.
  - apply PeanoNat.Nat.eqb_eq in Hq2. right. exact Hq2.
}
destruct Hq as [Hq1 | Hq2].
- destruct c.
  * rewrite Hq1. cbv. reflexivity.
  * rewrite Hq1. cbv. reflexivity.
- destruct c.
  * rewrite Hq2. cbv. reflexivity.
  * rewrite Hq2. cbv. reflexivity.
Qed.


(* FIN DU TP3 *)

(* ------------------------------------------------------------ *)


(******************************************************************************)
(* Pour aller plus loin : le polymorphisme  *)
(******************************************************************************)

(* Quand on lit et a fortiori quand on écrit la fonction "appartient" on remarque
   son caractère générique sur les listes. *)

Print appartient.

(* Elle est écrite pour le type "list nat" mais si on remplace "Nat.eqb"
   par une fonction "comp_A : A -> A -> bool", "appartient" fonctionnerait
   pour un type donné "A". *)


(* EXERCICE *)
(* Définir la fonction "appartient_poly" qui prend en paramètres
    - un type A
    - une fonction de décision de l'égalité sur A 
    - un élement de x:A
    - une liste d'éléments de A 

(* Tests unitaires avec reflexivity *)
(*
Example appartient_poly_ex1 : appartient_poly nat (Nat.eqb) 0 [1;3;0;5] = true.
Proof.
simpl. reflexivity.
Qed.
Example appartient_poly_ex2 : appartient_poly nat (Nat.eqb) 4 [1;3;0;5] = false.
Proof.
simpl. reflexivity.
Qed.
*)


(* On peut bien sûr montrer par calcul que "appartient" est juste l'instance
   particulière de "appartient_poly nat (Nat.eqb) nat (Nat.eqb)" *)


(* Pour bien représenter *l'appartenance* à la liste, il faut quand même s'assurer
   que "comp_A" respecte la spécification 'décider de l'égalité dans "A"'.
   Les exemples suivants montrent des choix arbitraires de "comp_A". *)

(*
Example appartient_poly_ex3 : appartient_poly nat (fun x y => false) 0 [1;3;0;5] = false.
Proof.
simpl. reflexivity.
Qed.

Example appartient_poly_ex4 : appartient_poly nat (fun x y => true) 4 [1;3;0;5] = true.
Proof.
simpl. reflexivity.
Qed.
*)


(* Si on veut prouver le lemme équivalent pour "appartient_poly", on a besoin
   d'une propriété de type "forall x y:A, comp_A x y = true <-> x = y"
   similaire à "PeanoNat.Nat.eqb_eq", "comp_alphabet_eq", "comp_option_nat_correct", etc. *)

(* EXERCICE *)
(* Montrer que si x = y alors x appartient à une liste constituée que de [y] *)


(* On peut même aller plus loin et montrer que "(comp x y = true <-> x = y)" est 
  non seulement SUFFISANTE mais aussi NECESSAIRE si on veut "appartient_poly A comp x [y] = true <-> x = y" *)

(* EXERCICE *)
(* Montrer que si x appartient à une liste constituée que de [y] alors x = y *)


(* Il en est de même pour "trouve" et "trouve_paire" *)

Print trouve.
Print trouve_paire.

(* EXERCICE *)
(* Définir la fonction "trouve_poly", version polymorphe de "trouve" et "trouve_paire" *)

(* EXERCICE *)
(* Montrer que "trouve" et "trouve_paire" sont bien des instances de "trouve_poly" *)


(* ------------------------------------------------------------ *)
