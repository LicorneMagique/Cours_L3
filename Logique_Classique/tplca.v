Require Import Arith.
Require Import List.
Export ListNotations.

(* ON RAPPELLE LES DÉFINITIONS VUES EN LANGAGES FORMELS *)

(* Fonction "lgr" qui calcule la longueur d'une liste de nat (et donc de type list nat) *)
Fixpoint lgr (l : list nat) := match l with [] => 0 | _::rl => 1 + (lgr rl) end.

Example ex_lgr : (lgr (1::2::3::4::5::[])) = 5.
Proof. simpl. reflexivity. Qed.

(* Fonction "mir" qui calcule le miroir d'une liste de nat *)
Fixpoint mir (l : list nat) := match l with [] => [] | e::rl => (mir rl) ++ [e] end.
(* dans la vraie vie on ne fera jamais de concaténation de ce type mais ce n'est pas le problème ici *)

Example ex_mir : (mir (1::2::3::4::5::[])) = 5::4::3::2::1::[].
Proof. simpl. reflexivity. Qed.

(* On rappelle le type "btree" des arbres binaires avec valeurs de type nat stockées dans les feuilles *)
Inductive btree : Type :=
| F : nat -> btree
| N : btree -> btree -> btree
.

(* Fonction "bsumval" qui calcule la somme des valeurs contenues dans l'arbre *)
Fixpoint bsumval t :=
  match t with
  | F e => e
  | N t1 t2 => (bsumval t1) + (bsumval t2)
  end.

(* Fonction "bajout" qui ajoute un élément dans un arbre *)
(* plusieurs solutions sont possibles... on travaillera sur celle-là *)
Fixpoint bajout e t : btree :=
  match t with
  | F n => N t (F e)
  | N t1 t2 => N (bajout e t1) t2
  end.

(* exemples *)
(* on peut définir "ab1" :  o
                           / \
                          o   2
                         / \
                        1   o
                           / \
                          o   3
                         / \
                        4   5
*)

Definition ab1 := N (N (F 1) (N (N (F 4) (F 5)) (F 3))) (F 2).

Example ex_bsumval_ab1 : (bsumval ab1) = 15.
Proof. cbv. reflexivity. Qed.

(*************** LOGIQUE CLASSIQUE ***************)

Context (E F2 G : Prop).

(* EXERCICE *)
(* Prouver les lemmes suivants *)
Lemma LC1 : ((F2 \/ E) -> G) -> ((E -> G) /\ (F2 -> G)).
Proof.
intros.
split.

Admitted.

Lemma LC2 : (F2 \/ E) -> ((E -> F2) -> F2).
Proof.
intros.
destruct H.
- apply H0.
Admitted.


(* EXERCICE *)
(* Exprimer et montrer que la longueur de la concaténation de deux listes de nat (donc de type list nat)  est la somme des longueurs des concaténés*)
Lemma concat_compat : forall l1 l2, (lgr l1 + lgr l2) = lgr (l1++l2).
Proof.
intros.
destruct l1, l2.
- simpl.
reflexivity.
- simpl.
reflexivity.
- simpl.
Admitted.

(* EXERCICE *)
(* Montrer que la longueur d'une liste c'est la longueur de son miroir *)
(* On pourra avoir besoin de la commutativité de l'addition, donnée par le lemme Nat.add_comm, et dulemme précédent *)

Check Nat.add_comm.

Lemma lgrmireq : forall l1, lgr l1 = lgr (mir l1).
Proof.
intros.
destruct l1.
- simpl.
reflexivity.
- simpl.
destruct l1.
 + simpl.
   reflexivity.
Admitted.

(* EXERCICE *)
(* Exprimer et montrer que l'addition est associative, c'est-à-dire qu'on a (x + y) + z = x + (y + z) pour x, y et z de type nat. *)
(* rappel : ce qui est noté x + y + z (sans parenthèses) est en fait (x + y) + z *)
Lemma p_assoc : forall x y z, (x + y) + z = x + (y + z).
Proof.
Admitted.


(* EXERCICE *)
(* Exprimer et montrer que la somme des valeurs d'un arbre t à laquelle on additionne un nat e est égale à la somme des valeurs de l'arbre t dans lequel on a ajouté un élément de valeur e. *)

(* On pourra avoir besoin de la commutativité de l'addition, donnée par le lemme Nat.add_comm, et de l'associativité démontrée auparavant. *)

Check Nat.add_comm.

Lemma bsumcons_compat : forall t e, (bsumval t + e) = (bsumval (t bajout e)).
Proof.
Qed.


