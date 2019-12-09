
(***************************** LIFLF - TPNOTE *********************************)
(************* Evaluation pratique en temps limité : 30' **********************)

(************************ SUJET D'ENTRAINEMENT ********************************)
(* Ce sujet est représentatif de celui qui vous sera donné à réaliser en temps 
limité. Les fonctions demandées ici sont tout à fait classiques, on les
trouve dans les bilbiothèques standards des languages fonctionnels, e.g. :

http://hackage.haskell.org/package/base-4.12.0.0/docs/Data-List.html 
*)
(******************************************************************************)

Require Import List.
Require Import Arith.
Import ListNotations.

(***************************** fonction mystère *******************************)

(* On donne le corps suivant d'une fonction

  match x with
   | Some a => true
   | None   => false
  end.
*)

(* EXERCICE : Définir la fonction "mystere" avec le corps donné ci-dessus. *)
(*            Donner son type *)
(*            Expliquer simplement ce que fait cette fonction. *)
Definition mystere (x : option nat) : bool :=
  match x with
   | Some a => true
   | None   => false
  end.


(***************************** "span" ******************************************)

(* EXERCICE : définir la fonction "span" qui prend en paramètre un prédicat "p",
              une liste "ls" et retourne une paire de liste composée
               - du préfixe le plus long possible de "ls" des éléments qui vérifient "p"
               - le reste de "ls"
   EXEMPLE  : voir les tests unitaires ci-dessous
*)
Fixpoint span (p : nat -> bool) (ls : list nat): (list nat* list nat) :=
  match ls with
   | [] => ([],[])
   | x::ls2 => match p x with
     | true => (x::fst(span p ls2), snd(span p ls2))
     | false => ([], x::ls2)
  end
end.
(* "leb x y" est prédicat booléen qui teste si x est inférieur ou égal à y *)

Goal  span (fun n => leb n 3) [1; 2; 3; 4; 1; 2 ]  = ([1; 2; 3] , [4; 1; 2 ]).
reflexivity.
Qed.

Goal  span (fun n => leb n 5) [1; 2; 3; 4; 1; 2 ]  = ([1; 2; 3; 4; 1; 2 ], []).
reflexivity.
Qed.

Goal  span (fun n => leb n 0) [1; 2; 3; 4; 1; 2 ]  = ([], [1; 2; 3; 4; 1; 2 ]).
reflexivity.
Qed.

(***************************** "break" ******************************************)

(* EXERCICE : définir, sans utiliser "span", la fonction "break"  qui prend en paramètre un prédicat "p",
              une liste "ls" et retourne une paire de liste composée
               - du préfixe le plus long possible de "ls" des éléments qui NE vérifient PAS "p"
               - le reste de "ls"
   EXEMPLE  : voir les tests unitaires ci-dessous
*)

Fixpoint break (p : nat -> bool) (ls : list nat): (list nat* list nat) :=
  match ls with
   | [] => ([],[])
   | x::ls2 => match p x with
     | false => (x::fst(break p ls2), snd(break p ls2))
     | true => ([], x::ls2)
  end
end.

Compute break (fun n => leb 3 n) [1; 2; 3; 4; 1; 2 ].

Goal  break (fun n => leb 3 n) [1; 2; 3; 4; 1; 2 ]  =  ([1; 2] , [3; 4; 1; 2 ]).
reflexivity.
Qed.

Goal  break (fun n => leb n 5) [1; 2; 3; 4; 1; 2 ]  =  ([], [1; 2; 3; 4; 1; 2 ]).
reflexivity.
Qed.

Goal  break (fun n => leb n 0) [1; 2; 3; 4; 1; 2 ]  = ([1; 2; 3; 4; 1; 2 ], []).
reflexivity.
Qed.

(*********************** explication d'énoncé *********************************)

(* EXERCICE : On donne l'énoncé suivant "a_expliquer". 
              Expliquer en français cette propriété
*)
Lemma a_expliquer : forall p ls, fst (span p ls) ++ snd (span p ls) = ls.
Admitted.
Compute span (fun n => leb n 3) [1; 2; 3; 4; 1; 2 ].
Compute fst (span (fun n => leb n 3) [1; 2; 3; 4; 1; 2 ]).
Compute snd (span (fun n => leb n 3) [1; 2; 3; 4; 1; 2 ]).

(* EXERCICE : On donne l'énoncé suivant "a_expliquer_2". 
              Expliquer en français cette propriété
*)
Lemma a_expliquer_2 : forall p ls, span p ls = break (fun x => negb (p x)) ls.
Admitted.

