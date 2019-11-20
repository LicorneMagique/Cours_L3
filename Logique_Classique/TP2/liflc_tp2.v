Require Import Arith.

(* AVOIR SON COURS SOUS LES YEUX *)
(* AVOIR SON COURS SOUS LES YEUX *)
(* AVOIR SON COURS SOUS LES YEUX *)
(* AVOIR SON COURS SOUS LES YEUX *)
(* AVOIR SON COURS SOUS LES YEUX *)




(**********************************************************************)
(* STRUCTURE DE BASE DES LISTES (FINIES) D'ENTIERS                    *)
(**********************************************************************)


(*On rappelle que les objets de type nat sont définis inductivement de façon similaire à *)
Inductive entiers : Set :=
  | O : entiers
  | S : entiers -> entiers.
Print nat.

(* On dispose donc d'un principe d'induction nat_ind, construit à peu près comme vu en cours *)
Check nat_ind.


(* On définit les listes de nat *)
Inductive nlist : Set :=
| nnil : nlist                  
| ncons : nat -> nlist -> nlist. 

(* ... avec des notations confortables *)
Infix "::" := ncons.
Notation "[]" := nnil.

(* Vous avez vu la génération des principes d'induction ? *)
Check nlist_ind.
(* Comparez avec le cours *)



(* Rappel Coq : 
des CONSTRUCTEURS DIFFÉRENTS donnent des TERMES DIFFÉRENTS 
(discriminate) *)
(* Prouver que pour tout nat x et toute liste de nat l,
la liste vide n'est pas obtenue par l'ajout de x en tête de l. *)
Lemma nil_neq_cons : forall (x:nat) (l:nlist), [] = x :: l -> False.
Proof.
intro x.
intro l.
intro xl.
discriminate.
Qed.


(******************************************************************************)
(* FONCTIONS NON-RECRUSIVES SUR LES TYPES INDUCTIFS                           *)
(******************************************************************************)

(* Si on n'a pas besoin d'hypothèse d'induction, il est en général suffisant de faire une étude par cas, 
   c'est-à-dire un destruct de l'objet étudié *)

Inductive Alphabet : Type :=
| a : Alphabet
| b : Alphabet.

(* Prouvez la correction complète de la fonction comp_alphabet de votre TP de LIFLF, c'est-à-dire qu'elle retourne true si et seulement si ses paramètres sont égaux. 
  - on procède par cas sur les deux paramètres
  - on peut être amené à faire des calculs (avec simpl dans le but ou simpl in toto dans l'hypothèse toto. *)
Definition comp_alphabet (x : Alphabet) (y : Alphabet) : bool :=
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

(* Le ssi veut dire "si A alors B" ET "si B alors A" *)
(* D'où le prédicat :
"(comp_alphabet x y = true -> x = y)" si A alors B
" /\ " et
"(x = y -> comp_alphabet x y = true)" si B alors A *)
Theorem comp_alphabet_ssi : forall (x:Alphabet) (y:Alphabet), (comp_alphabet x y = true -> x = y) /\ (x = y -> comp_alphabet x y = true).
Proof.
intro x.
intro y.
split. (*On veut montrer deux formules donc on les sépare*)
- intro x2. (*On précise qu'on gère le premier cas*)
  destruct x, y. (*On remplace les variables par toutes leurs valeurs possibles*)
  + reflexivity.
  + simpl in x2. (*On remplace "comp_alphabet a b" par sa valeur*)
    exfalso.
    discriminate.
  + simpl in x2.
    discriminate.
  + reflexivity.
- intro x2.
  rewrite x2.
  destruct y.
  + simpl.
    reflexivity.
  + simpl.
    reflexivity.
Qed.

(* on rappelle la fonction de comparaison sur les option nat codée en LIFLF *)
Definition comp_option_nat (x y: option nat) : bool :=
(* START CUT *)
match x with
  | None => match y with | None => true | Some toto => false end
  | Some n => match y with | Some m => Nat.eqb n m | None => false end
end.

(* Montrer que (comp_option_nat x y) retourne true SEULEMENT SI x=y. 
   on utilisera le théorème 
   beq_nat_true: forall n m : nat, Nat.eqb n  m = true -> n = m 
   qu'on spécialisera aux bons paramètres n_fixe, m_fixe avec 
   pose (beq_nat_true n_fixe m_fixe) as nom_de_la_nouvelle_hypothèse.
   
   ATTENTION : Nat.eqb e1 e2 s'écrit aussi e1 =? e2

*)

Theorem comp_option_nat_seulement_si : forall (x:option nat) (y:option nat), (comp_option_nat x y = true -> x = y).
Proof.
intros.
destruct x, y.
- pose (beq_nat_true n n0).
  apply e in H.
  rewrite H.
  reflexivity.
- simpl in H.
  discriminate.
- simpl in H.
  discriminate.
- reflexivity.
Admitted.


(******************************************************************************)
(* FONCTIONS RECURSIVES ET INDUCTION SUR LES ENTIER                           *)
(******************************************************************************)

(* Exercice : montrer que la fonction plus appliquée à 0 et un x
   quelconque retourne x. *)
(* La définition de plus est récursive sur le paramètre de gauche,
   donc pas de problème ici, c'est juste un calcul (simpl) *)
Lemma plus_Z_l : forall (x : nat), plus 0 x = x.
Proof.
Admitted.

(* Exercice : montrer que la fonction plus appliquée un x quelconque
   et 0 retourne x. *)
(* Mmmh là il faut travailler par induction sur x... *)
(* on utilise "induction x" qui invoque la règle nat_ind. *)
Lemma plus_Z_r : forall x, plus x 0 = x.
Proof.
Admitted.


(******************************************************************************)
(* FONCTIONS RECURSIVES ET INDUCTION SUR LES LISTES                           *)
(******************************************************************************)


(* Exercice : définir "concat" la fonction de concaténation de deux
   listes l1 et l2 (par récursion sur l1) *)
Fixpoint concat (l1 l2 : nlist) : nlist := 
  []. (* Remplacez [] *)


(* On note ++ en notation infix pour la concatenation *)
Infix "++" := concat.

(* VU EN COURS : fonction de longueur des listes      *)
Fixpoint length (l : nlist) : nat :=
  match l with
  | []     => 0 
  | x :: l => S(length l) 
  end.

(* Exercice : montrer que la fonction retourne 0 SEULEMENT SI la liste
   est vide *)
Lemma length_zero_seulement_si_vide : False. (* remplacer False *)
Proof.
Admitted.                                  



(* Exercice : montrer que la fonction appliquée à la concaténation de
deux listes quelconques l1 l2 retourne la somme des applications de
cette fonction à chacune des deux listes.*)
Lemma length_of_concat : False. (* remplacer False *)
Proof.
Admitted.



(* Exprimer et montrer qu'ajouter un élément x en tête de la
concaténation de deux listes l1 et l2 est la même chose que concaténer
l1 avec x en tête et l2. *)
(* pas de difficulté, c'est juste un pas de calcul (simpl). *)

Lemma concat_cons : False. (* remplacer False *)
Proof.
Admitted.
  
(* Montrer maintenant que concaténer à l1 la liste vide renvoie exactement la liste l1. *)
(* Comme on a défini concat par récursion sur le premier paramètre, il va falloir une induction... *)
Lemma concat_nil_r : False. (* remplacer False *)
Proof.
Admitted.


(* On reprend la fonction appartient du TP de LIFLF *)
Fixpoint appartient (x : nat) (l : nlist) : bool :=
  match l with
  | [] => false
  | h::rl => (Nat.eqb x h) || (appartient x rl)
  end.

(* Exprimer (cf. TD de LIFLC) et montrer que cette fonction retourne
true sur la donnée de paramètres x de type nat et l de type nlist
seulement si on peut écrire l comme une nlist l1 concaténée à une
nlist l2 commençant par x *)

(* on aura besoin du théorème 
   - Bool.orb_prop 
*)
Check Bool.orb_prop.

(* on aura besoin du théorème 
   - beq_nat_true (déjà vu)
*)
Check beq_nat_true.

(* En hypothèse l'existentiel est éliminé/spécialisé avec destruct de
l'hypothèse *)
(* Rappel : la règle d'introduction de l'existentiel dans le but est exists objet_specialisé *)
  
Theorem appartient_seulement : False. (* remplacer False *)
Proof.
Admitted.

    
(**********************************************************************)(**********************************************************************)
(**********************************************************************)(**********************************************************************)
(**********************************************************************)(**********************************************************************)
(* À FAIRE CHEZ VOUS                                                  *)(**********************************************************************)
(**********************************************************************)(**********************************************************************)

Lemma plus_Succ_r : forall a b, S (plus a b) = plus a (S b). 
Proof.
Admitted.

(* Montrer que l'addition est commutative, on pourra avoir besoin du
lemme plus_Z_r démontré au début du TP. *)
Lemma plus_commute : forall x y, plus x y  = plus y x.
Proof.
Admitted.

(******************************************************************************)
(* Les arbres binaires de nat *)
(******************************************************************************)

(* On définit un type inductif pour les arbres binaires d'entiers *)
Inductive BinTree : Set :=
  | leaf : BinTree 
  | node : BinTree -> nat -> BinTree -> BinTree.

(**********************************************************************)
(* Montrer (par induction bien sûr) qu'un arbre binaire comportant
   n occurrences de l’arbre vide contient n - 1 éléments              *)
(**********************************************************************)
(* On pourra avoir besoin du théorème plus_n_Sm *)
Check plus_n_Sm.

(* Les deux fonctions qui comptent *)
Fixpoint count_leaves (t:BinTree) : nat :=
  0 (* remplacer 0 *).

Fixpoint count_nodes (t:BinTree) : nat :=
  666 (* remplacer 666 *).

(* la propriété *)
Lemma count_leaves_nodes : forall (t:BinTree), 1 + (count_nodes t) =  (count_leaves  t).
Proof.
Admitted.


