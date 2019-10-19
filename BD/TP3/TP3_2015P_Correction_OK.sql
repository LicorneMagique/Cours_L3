-----------------------------------------------------------------
-- Exercice 1 -- atomicité d’une transaction courante
-----------------------------------------------------------------

-- Question 1 ---------------------------------------

DROP TABLE Etudiants;
CREATE TABLE Etudiants(NOM VARCHAR2(16));

INSERT INTO Etudiants VALUES('Louis');
INSERT INTO Etudiants VALUES('Luc');
INSERT INTO Etudiants VALUES('Marc');

SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc}

UPDATE Etudiants SET Nom = 'Lucie' WHERE Nom = 'Luc' ;
DELETE FROM Etudiants WHERE Nom = 'Marc' ;
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Lucie}

ROLLBACK;
SELECT * FROM ETUDIANTS;
-- Etudiants = {}

-- Le ROLLBACK a annulé toutes les modifications, qui ont toutes été effectuées dans la même transaction
-- La structure n'a pas été modifiée, car il y a un commit automatique après un CREATE TABLE

-- Question 2 ---------------------------------------

INSERT INTO Etudiants VALUES('Louis');
INSERT INTO Etudiants VALUES('Luc');
INSERT INTO Etudiants VALUES('Marc');
UPDATE Etudiants SET Nom = 'Lucie' WHERE Nom = 'Luc' ;
DELETE FROM Etudiants WHERE Nom = 'Marc' ;

COMMIT ;
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Lucie}

ROLLBACK;
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Lucie}

-- Le ROLLBACK est sans effet puisque la transaction courante est vide : on a ien fait depuis le dernier COMMIT

DELETE FROM ETUDIANTS;
COMMIT;

-- Question 3 ---------------------------------------

INSERT INTO Etudiants VALUES('Jules');
INSERT INTO Etudiants VALUES('Julie');
Exit;
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Lucie}

-- QUIT et EXIT valident les transactions en cours

-- Question 4 ---------------------------------------
INSERT INTO Etudiants VALUES('EXIT');
SELECT * FROM ETUDIANTS;

-- Après coupure brutale de la connction, un ROLLBACK est implicitement effectué

-- Question 5 ---------------------------------------

INSERT INTO Etudiants VALUES('Louis');
INSERT INTO Etudiants VALUES('Luc');
INSERT INTO Etudiants VALUES('Marc');
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc}

ALTER TABLE Etudiants ADD  Ville VARCHAR2(20); 
ROLLBACK;
SELECT * FROM ETUDIANTS;
-- Etudiants = {(Louis,null), (Luc,null), (Marc,null)}

-- Les commades de modifications de schéma dont ALTER TABLE font un COMMIT implicite
-- Impossible donc d'annuler les deux insertions

ALTER TABLE Etudiants DROP COLUMN Ville;


-- Question 6 ---------------------------------------
INSERT INTO Etudiants VALUES('Jean-Marc');
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc, Jean-Marc}



-- On a une invite qui nous propose :
--   * un COMMIT de la transaction courante
--   * un ROLLBACK de la transaction courante
--   * d'annuler la fermeture

-- Question 7 ---------------------------------------
-- La suite des mises à jour effectuées dans une session (dans sqldeveloper ou la ligne de commande)
-- depuis la dernière validation ou depuis la dernière annulation, constitue la transaction *courante*.
-- Ces mises à jour sont soit 
--    * validées toutes ensemble d'un seul bloc par un COMMIT explicite ou implicite (QUIT/EXIT, ALTER)
--    * annulées toutes ensemble d'un seul bloc par un ROLLBACK explicite ou implicite (fin de session brutale)



-----------------------------------------------------------------
-- Exercice 2 -- transactions concurrentes
-----------------------------------------------------------------

-- Question 1 ---------------------------------------

-- A) sur la première connection
DELETE FROM ETUDIANTS;
COMMIT;
SELECT * FROM ETUDIANTS;
INSERT INTO Etudiants VALUES('Louis');
INSERT INTO Etudiants VALUES('Luc');
INSERT INTO Etudiants VALUES('Marc');
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc}

-- B) sur la deuxième connection
 SELECT * FROM ETUDIANTS;
-- Etudiants = {}
 
-- Si on execute SELECT * FROM ETUDIANTS; depuis une autre connection, on voit
-- le dernier état enregistré, validé par un COMMIT , à savoir Etudiants = {}

-- Question 2 ---------------------------------------

-- A) sur la première connection
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc}

-- B) sur la deuxième connection
INSERT INTO Etudiants VALUES('Jean-Marc');
SELECT * FROM ETUDIANTS;
-- Etudiants = {Jean-Marc}

-- Les modifications des transactions courantes ne sont visibles QUE dans la session
-- où elles ont été effectuées, tant qu'elles n'ont pas été validées.
-- On voit donc des résultats différents selon la connection où l'on se trouve

-- Question 3 ---------------------------------------

-- A) sur la première connection
CREATE TABLE UE
( NomUE VARCHAR2(30),
  NbEtudiants INTEGER
);

INSERT INTO UE VALUES ('SI', NULL);
INSERT INTO UE VALUES ('BD', 50);
SELECT * FROM UE;
-- UE = {(SI,null),(BD,50)}

SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc}

-- B) sur la deuxième connection
SELECT * FROM ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc, Jean-Marc}

INSERT INTO UE VALUES ('SE', 50);
SELECT * FROM UE;
-- UE = {(SE,50)}

-- Comme dans la question précédente, une commande de description de
-- données (ici un CREATE TABLE) valide la transaction courante.
-- Les insertions dans ETUDIANTS sont visibles dans la deuxième session.
-- Pour la table UEs, chacun voit uniquement ses modifications locales


-- Question 4 ---------------------------------------

-- A) sur la première connection

DROP TABLE UE;

-- On obtient le message d'erreur suivant :
-- SQL ERROR: ORA-00054: RESOURCE busy AND acquire WITH NOWAIT specified OR TIMEOUT expired
-- 00054. 00000 -  "resource busy and acquire with NOWAIT specified"

-- B) sur la deuxième connection
SELECT * FROM UE;
-- UE = {(SI,null),(BD,50),(SE,50)}

-- Même si le DROP TABLE echoue, la transaction dans la première session 
-- a été validée et les modifications sont visibles.

-- Pour détruire la table UE, il faut le faire depuis la deuxième fenêtre
-- ou alors COMMIT et supprimer d'où l'on veut : un suppression réussit que si il n'y a
-- pas d'autres sessions qui ont modifié la table à détruire.



-- Question 5 ---------------------------------------

-- A) sur la première connection
ALTER TABLE Etudiants ADD CONSTRAINT pkEtudiants PRIMARY KEY(Nom);
SELECT * FROM ETUDIANTS;
INSERT INTO Etudiants VALUES('Martine');

-- B) sur la deuxième connection
INSERT INTO Etudiants VALUES('Martine');

-- A) sur la première connection
ROLLBACK;

COMMIT;

-- La deuxième session est bloquée tant que la première session n'a pas validé sa transaction
-- En effet, bien que les modifications ne soient pas visible dans la deuxième fenêtre
-- si on accepte la deuxième insertion, on viole la contrainte.
-- Après ROLLBACK, la situation est débloquée et le tuple est inséré dans la deuxième session

-- Question 6 ---------------------------------------

-- A) sur la première connection
INSERT INTO Etudiants VALUES('Martine');

-- B) sur la deuxième connection
INSERT INTO Etudiants VALUES('Martine');

-- A) sur la première connection
COMMIT;

-- Similaire à précédement, à la différence que le tuple n'est PAS inséré dans la deuxième session.


-- Question 7 ---------------------------------------
-- A) sur le premier onglet
INSERT INTO Etudiants VALUES('Martine');

-- B) sur la deuxième onglet
SELECT * FROM ETUDIANTS;
 
-- on utilise en fait la même session et toutes les modifications sont visibles d'un onglet ou de l'autre

-- Question 8 ---------------------------------------
-- Un compte peut disposer de plusieurs sessions en parallèle. Chaque session voit localement ses
-- modifications effectuées dans sa transactions courante. Quand la transaction est validée, les modifications
-- sont visibles depuis toutes les sessions.


-----------------------------------------------------------------
-- Exercice 3 -- privilèges entre deux comptes
-----------------------------------------------------------------
-- on considère que les comptes sont nommés L3IF70 et RTHION

-- Question 1 ---------------------------------------

-- A) sur le premier compte L3IF70
CREATE TABLE Etudiants(NOM VARCHAR2(16));

INSERT INTO Etudiants VALUES('Louis');
INSERT INTO Etudiants VALUES('Luc');
INSERT INTO Etudiants VALUES('Marc');
COMMIT;

GRANT SELECT ON Etudiants TO RTHION ;

SELECT * FROM ALL_TABLES WHERE OWNER = 'L3IF70';
SELECT * FROM USER_TAB_PRIVS;


-- B) sur le deuxième compte RTHION
SELECT * FROM L3IF70.ETUDIANTS;

-- NB : il faut préfixer les noms de tables par l'ID du propriétaire lors des requêtes d'un compte dur l'autre

-- Question 2 ---------------------------------------

-- A) sur le premier compte L3IF70
INSERT INTO Etudiants VALUES('Jean-Marc');

-- B) sur le deuxième compte RTHION
SELECT * FROM L3IF70.ETUDIANTS;
-- Etudiants = {Louis, Luc, Marc}

-- On a bien deux sessions différentes avec leurs propres transactions courantes :
-- RTHION ne voit pas les modifications non validées effectuées par L3IF-70

-- Question 3 ---------------------------------------


-- B) sur le deuxième compte RTHION
INSERT INTO L3IF70.Etudiants VALUES('Jean-Marc');
-- SQL Error: ORA-01031: insufficient privileges
-- 01031. 00000 -  "insufficient privileges"

-- On a une erreur, car seul le droit SELECT a été donné, pas celui d'insertion


-- Question 4 ---------------------------------------
SELECT * FROM L3IF70.ETUDIANTS
UNION
SELECT * FROM RTHION.ETUDIANTS;


-- un exemple parmi d'autres

-----------------------------------------------------------------
-- Exercice 4 -- création et mise à jour de vues
-----------------------------------------------------------------
CREATE TABLE TA
( ID_A NUMBER PRIMARY KEY,
  NAME_A VARCHAR2(32)
);

INSERT INTO TA VALUES(0,'foo');
INSERT INTO TA VALUES(1,'bar');

CREATE TABLE TB
( ID_B NUMBER PRIMARY KEY,
  NAME_B VARCHAR2(32),
  REF_A NUMBER REFERENCES TA(ID_A)
);

INSERT INTO TB VALUES(0,'foofoo',0);
INSERT INTO TB VALUES(1,'foobar',1);

COMMIT;

-- Question 1 ---------------------------------------
CREATE OR REPLACE VIEW TB_REF0 AS
  SELECT * 
  FROM TB
  WHERE TB.REF_A = 0;

SELECT * FROM TB;  
SELECT * FROM TB_REF0;

INSERT INTO TB_REF0 VALUES(2,'foofoo2',0);
INSERT INTO TB_REF0 VALUES(3,'foobar2',1);

-- Les deux insertions ont réussies et ont été ajoutée à TB.
-- Le premier tuple est visible dans TB_REF0 mais pas le second !

  
 -- Question 2 ---------------------------------------
CREATE OR REPLACE VIEW TB_TA AS
  SELECT * 
  FROM TB JOIN TA ON TB.REF_A = TA.ID_A;
  
SELECT * FROM TB_TA; 

INSERT INTO TB_TA VALUES(2,'foofoo2',0, 0, 'foo');
--SQL Error: ORA-01776: cannot modify more than one base table through a join view

-- On ne peut pas modifier deux tables avec un seul insert

 -- Question 3 ---------------------------------------

INSERT INTO TB_TA(ID_B, NAME_B,REF_A) VALUES(2,'foofoo2',0);
SELECT * FROM TB_TA; 
SELECT * FROM TB; 

-- on voit que le tuple a été ajouté à TB et est visible dans TB_TA

INSERT INTO TB_TA(ID_B, NAME_B,REF_A) VALUES(3,'foofoo3',3);
-- violation de clef étrangère : le tuple est refusé

 -- Question 4 ---------------------------------------

INSERT INTO TB_TA(ID_A, NAME_A) VALUES(2,'gaz');
-- SQL ERROR: ORA-01779: cannot MODIFY A COLUMN which maps TO A non KEY-preserved TABLE
-- 01779. 00000 -  "cannot modify a column which maps to a non key-preserved table"

-- il y a une restriction : on ne peut pas ajouter ce tuple car l'attribut REF_A de TB n'est pas clef de la relation.

 -- Question 5 ---------------------------------------

CREATE OR REPLACE VIEW TB_TA_ID AS
  SELECT * 
  FROM TB JOIN TA ON TB.ID_B = TA.ID_A;
  
INSERT INTO TB_TA_ID(ID_A, NAME_A) VALUES(2,'gaz');
-- cette fois si c'est possible.

SELECT * FROM TA;

-- en fait, dans le cas précédent il n'y a pas d'ambiguité et la modification pourrait être
-- effectuée sans risque, c'est donc trop restrictif, mais on peut toujours effectuer la modification
-- sur la table source.

 -- Question 6 ---------------------------------------

CREATE OR REPLACE VIEW TB_TA_2 AS
  SELECT * 
  FROM TB RIGHT JOIN (
    SELECT ID_A, NAME_A, COUNT(ID_B) AS NB_B
    FROM TA LEFT JOIN TB ON TB.REF_A = TA.ID_A
    GROUP BY ID_A, NAME_A
  ) TA2 ON TB.REF_A = TA2.ID_A;
  
  
SELECT * from TB_TA_2;

-- NB : a priori, on ne peut pas le faire sans requete imbriquée dans le FROM
-- à cause du GROUP BY nécessaire pour le comptage
