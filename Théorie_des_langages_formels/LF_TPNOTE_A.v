
(***************************** LIFLF - TPA ************************************)
(************* Evaluation pratique en temps limité : 30' **********************)
(******************************************************************************)

Require Import Arith.
Require Import List.
Export ListNotations.


(* Partie 1. Exercices sur les listes d'entiers *)
(* -------------------------------------------- *)


(* EXERCICE *)
(* Écrire la fonction "lgr" qui calcule la longueur d'une liste de nat (et donc de type list nat) *)
Function lgr (l : list nat) : nat :=
  match l with
    | [] => 0
    | x::l2 => (1 + lgr l2)
  end.

Example ex_lgr : (lgr (1::2::3::4::5::[])) = 5.
Proof. cbv. reflexivity. Qed.


(* EXERCICE *)
(* Écrire la fonction "mir" qui calcule le miroir d'une liste de nat *)
Function mir (l : list nat) : list nat :=
match l with
  | [] => []
  | x::l2 => (mir l2)++[x]
end.
Compute mir (1::2::3::4::5::[]).
Example ex_mir : (mir (1::2::3::4::5::[])) = 5::4::3::2::1::[].
Proof. cbv. reflexivity. Qed.


(* EXERCICE *)
(* Exprimer et prouver que le miroir d'une liste à laquelle on a ajouté un élément en tête
   est le miroir de la liste concaténé à la liste constituée de juste cet élément *)


(* Partie 2. Exercices sur les arbres binaires *)
(* ------------------------------------------- *)


(* On donne le type "btree" des arbres binaires avec valeurs de type nat stockées dans les feuilles *)
Inductive btree : Type :=
| F : nat -> btree
| N : btree -> btree -> btree
.

(* exemples *)
(* L'arbre "ab1" :  o    et "ab2" :    o
                   / \                / \
                  o   2              1   o
                 / \                    / \
                1   o                  o   5
                   / \                / \
                  o   3              2   o
                 / \                    / \
                4   5                  3   4
*)
(* On donne l'arbre "ab1" : *)
Definition ab1 := N (N (F 1) (N (N (F 4) (F 5)) (F 3))) (F 2).

(* EXERCICE *)
(* Définir l'arbre "ab2" correspondant à l'exemple ci-dessus *)
Definition ab2 := N (F 1) (N (N (F 2) (N (F 3) (F 4))) (F 5)).

(* EXERCICE *)
(* Écrire la fonction "bnbf" qui calcule le nombre de feuilles d'un tel arbre *)
Function bnbf : (t : btree) : nat :=
match t with
  | nat => 1
end.

(*
Example ex_bnbf_ab1 : (bnbf ab1) = 5.
Proof. cbv. reflexivity. Qed.
*)


(* EXERCICE *)
(* Écrire la fonction "bnbn" qui calcule le nombre de noeuds d'un tel arbre *)

(*
Example ex_bnbn_ab1 : (bnbn ab1) = 4.
Proof. cbv. reflexivity. Qed.
*)


(* EXERCICE *)
(* Écrire la fonction "bsumval" qui calcule la somme des valeurs contenues dans l'arbre *)

(*
Example ex_bsumval_ab1 : (bsumval ab1) = 15.
Proof. cbv. reflexivity. Qed.
*)


(* EXERCICE *)
(* Écrire la fonction "bajout" qui ajoute un élément dans un arbre *)

(*
Example ex_bajout_ab1 : bnbf (bajout 10 ab1) = 1 + bnbf ab1.
Proof. cbv. reflexivity. Qed.
*)


