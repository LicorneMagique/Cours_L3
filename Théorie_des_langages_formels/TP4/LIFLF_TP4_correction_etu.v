(* TP4 Langages formels *)

(******************************************************************************)
(************************ grammaires et automates en Coq **********************)
(******************************************************************************)

(* L'objectif de ce TP est de reprendre la définition des automates vue au TP précédent,
   d'ajouter la définition d'une grammaire équivalente et de prouver que l'automate
   et la grammaire sont effectivment équivalents.
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


(* Le type Automate représentant ce quintuplet. *)
Inductive Automate : Type :=
    automate : list nat -> list Alphabet -> (nat -> Alphabet -> option nat) -> nat -> list nat -> Automate.

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

(* La fonction "execute" qui va calculer l'état d'arrivée en lisant un mot, c'est-à-dire une "list Alphabet" *)
Fixpoint execute (M : Automate)  (q : nat) (w : list Alphabet) : option nat :=
  match w with
  | [] => Some q
  | h::rw => match transition M q h with
             | None => None
             | Some e => execute M e rw end
  end.

(* La fonction "reconnait" qui va accepter ou refuser un mot *)
Definition reconnait (M : Automate) (w : list Alphabet) : bool :=
  match (execute M (initial M) w) with
  | None => false
  | Some e => acceptant M e
  end.


(* L'automate "M_nb_b_impair" à deux états qui accepte les mots contenant un nombre impair de 'b' *)
Definition delta_nb_b_impair (q : nat) (c : Alphabet) : option nat :=
match (q,c) with
 | (1,a) => Some 1
 | (1,b) => Some 2
 | (2,a) => Some 2
 | (2,b) => Some 1
 | (_,_) => None
end.
Definition M_nb_b_impair := automate [1;2] [a;b] (delta_nb_b_impair) 1 [2].


(* L'automate "M_commence_et_finit_par_a" à trois états qui accepte les mots commençant et finissant par 'a' *)
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


(* ------------------------------------------------------------ *)


(* Fin des rappels. Ici commence le TP4. *)

(* L'automate M_nb_b_impair implémente la grammaire G1 suivante :
   S1 -> a S1
   S1 -> b S2
   S2 -> a S2
   S2 -> b S1
   S2 -> epsilon
*)

(* Expliquer que "G1 m i" c'est le <blink>PRÉDICAT</blink> "mot généré par G1 à partir du non-terminal i" *)
(* Expliquer en langue naturelle comment construire ce prédicat *)
Inductive G1 : (list Alphabet) -> nat -> Prop :=
| G1_0 : G1 [] 2
| G1_1a : forall m, G1 m 1 -> G1 (a::m) 1 
| G1_1b : forall m, G1 m 2 -> G1 (b::m) 1 
| G1_2a : forall m, G1 m 2 -> G1 (a::m) 2
| G1_2b : forall m, G1 m 1 -> G1 (b::m) 2
.

(* G1 génère le mot abaabab à partir du non-terminal S1 *)
Example ex_G1_1 : G1 [a;b;a;a;b;a;b] 1.
Proof.
  apply G1_1a. (* état courant 1, symbole courant a -> état 1, reste baabab *)
  apply G1_1b. (* état courant 1, symbole courant b -> état 2, reste aabab *)
  apply G1_2a. (* état courant 2, symbole courant a -> état 2, reste abab *)
  apply G1_2a. (* état courant 2, symbole courant a -> état 2, reste bab *)
  apply G1_2b. (* état courant 2, symbole courant b -> état 1, reste ab *)
  apply G1_1a. (* état courant 1, symbole courant a -> état 1, reste b *)
  apply G1_1b. (* état courant 1, symbole courant b -> état 2, reste epsilon *)
  apply G1_0.
Qed.
Print ex_G1_1.

(* G1 génère le mot baab à partir du non-terminal S2 *)
Example ex_G1_2 : G1 [b;a;a;b] 2.
Proof.
  apply G1_2b.
  apply G1_1a.
  apply G1_1a.
  apply G1_1b.
  apply G1_0.
Qed.

(* Evidemment, G1 ne peut pas générer, par exemple, le mot bbb à partir du non-terminal S1. *)


(* EXERCICE *)
(* Définir la grammaire G2 implémentée par l'automate M_commence_et_finit_par_a,
   et donner des exemples de mots générés par cette grammaire. *)

(* L'automate M_commence_et_finit_par_a implémente la grammaire G2 suivante :
   S1 -> a S2
   S2 -> a S2
   S2 -> b S3
   S2 -> b S1
   S2 -> epsilon
*)

Inductive G2 : (list Alphabet) -> nat -> Prop :=
| G2_0 : G2 [] 2
| G2_1a : forall m, G2 m 2 -> G2 (a::m) 1
| G2_2a : forall m, G2 m 2 -> G2 (a::m) 2
| G2_2b : forall m, G2 m 3 -> G2 (b::m) 2
| G2_3a : forall m, G2 m 2 -> G2 (a::m) 3
| G2_3b : forall m, G2 m 3 -> G2 (b::m) 3
.

(* G2 génère le mot a à partir du non-terminal S1 *)
Example ex_G2_1 : G2 [a;a;b;a] 1.
Proof.
apply G2_1a.
apply G2_2a.
apply G2_2b.
apply G2_3a.
apply G2_0.
Qed.
Print ex_G2_1.

(* ------------------------------------------------------------ *)

(* Equivalence grammaire et automate *)

(* On veut prouver :
   "Soit un automate M qui implémente une grammaire G.
    G génère un mot m à partir de S1 ssi M accepte m."

   EN PARTICULIER :
   "G1 génère un mot m à partir de S1 ssi M_nb_b_impair accepte m."

   ET :
   "G2 génère un mot m à partir de S1 ssi M_commence_et_finit_par_a accepte m."
*)


(* 1. Sens Automate => Grammaire *)

(* On sait trouver une exécution par dérivation : *)
(* Si G permet de générer un mot m à partir du non-terminal Sq,
      alors M accepte m à partir de l'état q *)

(* EXERCICE *)
(* Montrer que si G1 génère un mot, alors M_nb_b_impair accepte ce mot. *)
Lemma G1_mime_M1 :
  forall m q, G1 m q
  -> exists e, execute M_nb_b_impair q m = Some e /\ acceptant M_nb_b_impair e = true.
Proof.
  intros m q Hregu. (* ici expliquer qu'on a un prédicat inductif donc
                       on peut faire une induction dessus *)
  induction Hregu  as [| m Hregu IHa1 | m Hregu IHb1 | m Hregu IHa2 | m Hregu IHb2].
  + exists 2. simpl. split.
    * reflexivity.
    * reflexivity.
  + simpl. simpl in IHa1. assumption.
  + simpl. simpl in IHb1. assumption.
  + simpl. simpl in IHa2. assumption.
  + simpl. simpl in IHb2. assumption.
Qed.


(* Tout mot m généré par G à partir de la source est reconnu par M. *)
(* Si G génère un mot m à partir du non-terminal S1, alors A accepte m *)

(* EXERCICE *)
(* Montrer que si G1 génère un mot, alors M_nb_b_impair accemte ce mot. *)
(* HINT. C'est un cas particulier du théorème précédent *)
Lemma G1_reco_M1 : forall m, G1 m 1 -> reconnait M_nb_b_impair m = true.
Proof.
  intros m Hregu.
  unfold reconnait. simpl.
  destruct (G1_mime_M1 m 1 Hregu) as [Hqfin Haccept].
  destruct Haccept as [Hsome Haccepttrue].
  rewrite Hsome. simpl in Haccepttrue. assumption.
Qed.


(* 2. Sens grammaire => automate *)

(* On sait trouver une dérivation par exécution. *)
(* Si q est un état valide de M
   alors si M accepte m à partir de l'état q, alors G génère m à partir de son non-terminal Sq *)
Require Import Arith.
Check EqNat.beq_nat_true.

(* EXERCICE *)
(* Montrer que si M_nb_b_impair accepte un mot à partir d'un état valide, alors G1 génère ce mot. *)
Lemma M1_mime_G1 :
  forall m q, (appartient q (etats M_nb_b_impair)) = true
  -> (forall e, execute M_nb_b_impair q m = Some e /\ acceptant M_nb_b_impair e = true -> G1 m q).
Proof.
  induction m as [| c rm IHrm].
  - intros q Hqvalid e Hreco.
    unfold acceptant in Hreco. simpl in Hreco.
    destruct Hreco as [HeqSome Heqbool].
    injection HeqSome. intro Hq. rewrite Hq.
    rewrite Bool.orb_false_r in Heqbool. apply EqNat.beq_nat_true in Heqbool.
    rewrite Heqbool.
    apply G1_0.
  - intros q Hqvalid e Hreco.
    unfold M_nb_b_impair in Hqvalid. unfold etats in Hqvalid.
    unfold appartient in Hqvalid.
    rewrite Bool.orb_false_r in Hqvalid.
    apply Bool.orb_prop in Hqvalid.
    assert (Happ : appartient 1 (etats M_nb_b_impair) = true). (* un fois pour toutes ici mais *)
    { simpl. reflexivity. } (* ça pourrait changer dans les deux cas suivant A.     *)
    destruct Hqvalid as [Hq1 | Hq2].
    + apply PeanoNat.Nat.eqb_eq in Hq1.
      rewrite Hq1. rewrite Hq1 in Hreco.
      destruct c.
      * simpl in Hreco.
        apply G1_1a.
        exact ((IHrm 1) Happ e Hreco).
      * simpl in Hreco.
        apply G1_1b.
        exact ((IHrm 2) Happ e Hreco).
    + apply PeanoNat.Nat.eqb_eq in Hq2.
      rewrite Hq2. rewrite Hq2 in Hreco.
      destruct c.
      * simpl in Hreco.
        apply G1_2a.
        exact ((IHrm 2) Happ e Hreco).
      * simpl in Hreco.
        apply G1_2b.
        exact ((IHrm 1) Happ e Hreco).
Qed.


(* Remarque : le théorème précédent pourrait être formulé de la manière suivante : voici le corollaire *)
Lemma M1_mime_G1' :
  forall m q, (appartient q (etats M_nb_b_impair)) = true /\ (forall e, execute M_nb_b_impair q m = Some e /\ acceptant M_nb_b_impair e = true)
   -> G1 m q.
intros m q H.
destruct H.
apply M1_mime_G1 with (e := 2).
- exact H.
- apply H0.
Qed.


(* Tout mot m reconnu par M est généré par G à partir de la source. *)
(* Si M accepte m, alors G génère m à partir du non-terminal S1. *)

(* EXERICE *)
(* Montrer que si M_nb_b_impair accepte un mot, alors G1 génère ce mot à partir de S1. *)
Lemma M1_regu_G1 : forall m, reconnait M_nb_b_impair m = true -> G1 m 1.
Proof.
  intros m Hreco.
  unfold reconnait in Hreco.
  apply (M1_mime_G1 m 1 eq_refl 2).
  simpl in Hreco.
  destruct (execute M_nb_b_impair 1 m) as [e |].
  - rewrite Bool.orb_false_r in Hreco.
    apply EqNat.beq_nat_true in Hreco.
    rewrite Hreco. simpl.
    split.
    + reflexivity.
    + reflexivity.
  - discriminate Hreco.
Qed.


(* FIN DU TP4 *)


