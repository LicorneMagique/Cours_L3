# TP4

Le principe d’une bibliothèque coopérative est de permettre de collectiviser les livres possédés par de nombreuses personnes. Un livre a un identifiant ISBN unique, un titre, un type et un nombre de pages. Chaque livre peut aussi être identifié par un couple composé de la personne qui l’a prêté à la bibliothèque et la date (et l’heure) du prêt. Un emprunt de livre est identifié par la personne qui emprunte et la date de l’emprunt. Une personne est identifié par un numéro et a un nom, un prénom et une adresse.

1. Proposer un schéma de base de données comportant les relations PERSONNE , LIVRE et EMPRUNT pour modéliser cet énoncé et implémentez cette base de données en SQL avec les clés, les clés primaires et les clés étrangères.

    ```sql
    drop table emprunt;
    drop table livre;
    drop table personne;

    create table Personne (
        id_p integer primary key,
        nom varchar(30),
        prenom varchar(30),
        adresse varchar(80)
    );

    create table Livre (
        id_ISBN integer primary key,
        id_preteur integer,
        date_pret date,
        titre varchar(50),
        type varchar(50),
        nb_page integer,
        constraint livre_unique unique (id_preteur, date_pret),
        foreign key (id_preteur) references Personne (id_p)
    );

    create table Emprunt (
        id_p integer,
        date_emprunt date,
        id_ISBN integer,
        date_retour date,
        constraint pk_emprunt primary key (id_p, date_emprunt),
        foreign key (id_p) references Personne (id_p),
        foreign key (id_ISBN) references Livre (id_ISBN)
    );

    ```

2. Peuplez la base de donnée avec un jeu petit d’essai comprenant un maximum de cas limites (e.g., livre non-emprunté, personne sans emprunt, emprunteur de son propre livre).

    ```sql
    -- id_p, nom, prenom, adresse
    insert into personne values (1, 'Lambert',  'Michel', '3 rue des Fleurs');
    insert into personne values (2, 'Lasalle',  'Pierre', '4 rue des Cerises');
    insert into personne values (3, 'Casanova', 'Alfred', '5 avenue du Lac');
    insert into personne values (4, 'Gourdin',  'Paul',   '6 boulevard des Sapins');

    -- id_preteur, date_pret, id_ISBN, titre, type, nb_page
    insert into livre values (1, 1, '2019-11-14', 'La Bible', 'Type par défaut', 2547);
    insert into livre values (2, 1, '2019-11-15', 'Le Renard', 'Image', 85);
    insert into livre values (3, 2, '2019-11-09', 'Les chats', 'Roman', 375);
    insert into livre values (4, 2, '2019-11-10', 'Le C++ pour les nuls', 'Documentation', 1421);

    -- id_p, date_emprunt, id_ISBN, date_retour
    insert into emprunt values (1, '2019-12-01', 1, '2019-12-03');
    insert into emprunt values (1, '2019-12-02', 2, '2019-12-04');
    insert into emprunt values (3, '2019-12-01', 2);

    ```

3. Implantez la dépendance qui stipule qu’un emprunteur doit nécessairement être un préteur (essayer d’abord de le faire avec une clef étrangère et un CHECK).

    ```sql
    --trigger sur l'ajout dans la table emprunt, qui verifie si l'emprunteur est un preteur
    ```

4. La règle de gestion est que pour le dépôt d’un livre, on reçoit 4 crédits d’emprunts. Un crédit est retiré à chaque emprunt. Pour aider à la gestion, un attribut calculée Credits est ajouté à la relation PERSONNE . Implantez les déclencheurs en insertion nécessaires pour automatiser la maintenance du nombre de crédits. On assurera en particulier la règle métier suivante : « une personne ne peut pas effectuer d’emprunt si elle ne possède pas les crédits suffisants, sauf si le livre est à elle ».

    ```sql
    ```

5. Des frais de participation à la gestion sont facturés chaque année aux utilisateurs. Ils sont en fonction du nombre d’emprunts, et dégressifs en fonction du rapport (nombre empruntés/nombre prêtés) pour
chaque personne.

    1. Si une personne a emprunté entre 1 et 2 fois le nombre de livres qu’elle a prêté, le tarif annuel est de 1e.
    2. Si le rapport est compris entre 2 (non compris) et 4, le tarif est de 2 e.
    3. Une personne peut emprunter ses propres livres sans frais.

    Implantez une fonction qui, en fonction du numéro d’une personne, retourne le montant en cours de ses frais de participation. Utilisez ensuite cette fonction dans une requête pour faire afficher les frais dûs par chaque personne.

    ```sql
    ```
