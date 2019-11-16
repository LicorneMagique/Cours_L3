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
        adresse varchar(80),
        credit integer
    );

    create table Livre (
        id_ISBN integer primary key,
        id_preteur integer,
        date_pret timestamp,
        titre varchar(50),
        type varchar(50),
        nb_page integer,
        constraint livre_unique unique (id_preteur, date_pret),
        foreign key (id_preteur) references Personne (id_p)
    );

    create table Emprunt (
        id_p integer,
        date_emprunt timestamp,
        id_ISBN integer,
        date_retour timestamp,
        constraint pk_emprunt primary key (id_p, date_emprunt),
        foreign key (id_p) references Personne (id_p),
        foreign key (id_ISBN) references Livre (id_ISBN)
    );

    ```

2. Peuplez la base de donnée avec un jeu petit d’essai comprenant un maximum de cas limites (e.g., livre non-emprunté, personne sans emprunt, emprunteur de son propre livre).

    ```sql
    -- id_p, nom, prenom, adresse
    insert into personne values (1, 'Lambert',  'Michel', '3 rue des Fleurs', 0);
    insert into personne values (2, 'Lasalle',  'Pierre', '4 rue des Cerises', 0);
    insert into personne values (3, 'Casanova', 'Alfred', '5 avenue du Lac', 0);
    insert into personne values (4, 'Gourdin',  'Paul',   '6 boulevard des Sapins', 0);

    -- id_preteur, date_pret, id_ISBN, titre, type, nb_page
    insert into livre values (1, 1, '2019-11-14 16:34:00', 'La Bible', 'Type par défaut', 2547);
    insert into livre values (2, 1, '2019-11-15 12:38:00', 'Le Renard', 'Image', 85);
    insert into livre values (3, 2, '2019-11-09 14:24:00', 'Les chats', 'Roman', 375);
    insert into livre values (4, 2, '2019-11-10 17:52:00', 'Le C++ pour les nuls', 'Documentation', 1421);
    insert into livre values (5, 2, '2019-11-10 17:52:10', 'Le Python pour les nuls', 'Documentation', 1422);
    insert into livre values (6, 2, '2019-11-10 17:52:20', 'Le C# pour les nuls', 'Documentation', 1441);
    insert into livre values (7, 2, '2019-11-10 17:52:30', 'Le C pour les nuls', 'Documentation', 1440);

    -- id_p, date_emprunt, id_ISBN
    insert into emprunt values (1, '2019-12-01 12:31:00', 1);
    insert into emprunt values (1, '2019-12-01 11:22:00', 3);
    insert into emprunt values (1, '2019-12-01 11:22:30', 4);
    insert into emprunt values (1, '2019-12-01 11:22:40', 5);
    insert into emprunt values (1, '2019-12-01 11:22:50', 6);
    insert into emprunt values (1, '2019-12-01 11:23:00', 7);
    insert into emprunt values (2, '2019-12-01 12:31:00', 1);
    insert into emprunt values (2, '2019-12-01 11:22:00', 2);

    ```

3. Implantez la dépendance qui stipule qu’un emprunteur doit nécessairement être un préteur (essayer d’abord de le faire avec une clef étrangère et un CHECK).

    ```sql
    -- Impossible à faire avec un check

    -- Trigger sur l'ajout dans la table emprunt, qui verifie si l'emprunteur est un preteur
    create or replace function check_emprunt() returns trigger as $$
        declare
            id integer;
        begin
            select distinct id_preteur into id from livre where id_preteur = new.id_p;
            if id is null then
                raise exception 'L''emprunteur doit être avoir prété au moins un livre';
            end if;
            return new;
        end;
    $$ LANGUAGE plpgsql;

    drop trigger if exists check_emprunt on emprunt;
    create trigger check_emprunt before insert on emprunt
        for each row execute procedure check_emprunt();

    -- Exemple de tentative d'insertion qui ne fonctionne plus
    insert into emprunt values (3, '2019-12-01 15:42:00', 2);
    ```

4. La règle de gestion est que pour le dépôt d’un livre, on reçoit 4 crédits d’emprunts. Un crédit est retiré à chaque emprunt. Pour aider à la gestion, un attribut calculée Credits est ajouté à la relation PERSONNE . Implantez les déclencheurs en insertion nécessaires pour automatiser la maintenance du nombre de crédits. On assurera en particulier la règle métier suivante : « une personne ne peut pas effectuer d’emprunt si elle ne possède pas les crédits suffisants, sauf si le livre est à elle ».

    ```sql
    -- trigger sur l'insertion dans la table livre qui ajoute 4 au champs credit dans la table personne
    create or replace function add_credit() returns trigger as $$
        begin
            update personne set credit = credit + 4 where id_p = new.id_preteur;
            return new;
        end;
    $$ LANGUAGE plpgsql;

    drop trigger if exists add_credit on livre;
    create trigger add_credit after insert on livre
        for each row execute procedure add_credit();
    ```

    ```sql
    -- trigger sur l'insertion dans la table emprunt qui (retire 1 au credit de la table personne et empeche l'emprunt si plus de credits) sauf si l'emprunteur est le preteur
    create or replace function check_emprunt() returns trigger as $$
        declare
            _id integer; -- id du proprio du livre
            _credit integer; -- credit de celui qui veut emprunter
        begin
            select id_preteur into _id from livre where id_ISBN = new.id_ISBN;
            if _id = new.id_p then
                return new;
            end if;
            select credit into _credit from personne where id_p = new.id_p;
            if _credit > 0 then
                update personne set credit = _credit - 1 where id_p = new.id_p;
                return new;
            end if;
            raise exception 'L''emprunteur doit avoir au moins 1 crédit';
        end;
    $$ LANGUAGE plpgsql;

    drop trigger if exists check_emprunt on emprunt;
    create trigger check_emprunt before insert on emprunt
        for each row execute procedure check_emprunt();

    -- Exemple de tentative d'insertion qui ne fonctionne plus
    insert into emprunt values (3, '2019-12-01 15:42:00', 2);

    ```

5. Des frais de participation à la gestion sont facturés chaque année aux utilisateurs. Ils sont en fonction du nombre d’emprunts, et dégressifs en fonction du rapport (nombre empruntés/nombre prêtés) pour
chaque personne.

    1. Si une personne a emprunté entre 1 et 2 fois le nombre de livres qu’elle a prêté, le tarif annuel est de 1e.
    2. Si le rapport est compris entre 2 (non compris) et 4, le tarif est de 2 e.
    3. Une personne peut emprunter ses propres livres sans frais.

    Implantez une fonction qui, en fonction du numéro d’une personne, retourne le montant en cours de ses frais de participation. Utilisez ensuite cette fonction dans une requête pour faire afficher les frais dûs par chaque personne.

    ```sql
    create or replace function get_frais(
        id integer
    ) returns integer as $$
        declare
            _emprunts integer;
            _prets integer;
        begin
            select distinct count(id_p)
            into _emprunts
            from emprunt e join livre l on e.id_isbn = l.id_isbn
            where id_p = id and id_p <> id_preteur;

            execute format('select count(id_isbn) from livre where id_preteur = $1')
            into _prets
            using id;

            if _prets = 0 then
                return 0;
            end if;

            if _emprunts > 0 and _emprunts < 2*_prets then
                return 1;
            end if;

            return 2;
        end;
    $$ LANGUAGE plpgsql;

    select * from get_frais(1);

    ```
