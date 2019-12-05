# Projet

## Question 1 et 2

Nous avons rassemblé toutes les données dans un seul fichier CSV. Le code permettant de créer la table est le suivant :

```sql
-- Création de la base
drop table if exists "election-csv";
CREATE TABLE "election-csv" (
    "Code du département" DECIMAL NOT NULL,
    "Département" VARCHAR(20) NOT NULL,
    "Code de la circonscription" DECIMAL NOT NULL,
    "Circonscription" VARCHAR(30) NOT NULL,
    "Code de la commune" DECIMAL NOT NULL,
    "Commune" VARCHAR(40) NOT NULL,
    "Bureau de vote" DECIMAL NOT NULL,
    "Inscrits" DECIMAL NOT NULL,
    "Abstentions" DECIMAL NOT NULL,
    "% Abs/Ins" DECIMAL NOT NULL,
    "Votants" DECIMAL NOT NULL,
    "% Vot/Ins" DECIMAL NOT NULL,
    "Blancs" DECIMAL NOT NULL,
    "% Blancs/Ins" DECIMAL NOT NULL,
    "% Blancs/Vot" DECIMAL NOT NULL,
    "Nuls" DECIMAL NOT NULL,
    "% Nuls/Ins" DECIMAL NOT NULL,
    "% Nuls/Vot" DECIMAL NOT NULL,
    "Exprimés" DECIMAL NOT NULL,
    "% Exp/Ins" DECIMAL NOT NULL,
    "% Exp/Vot" DECIMAL NOT NULL,
    "N°Panneau" DECIMAL NOT NULL,
    "Sexe" VARCHAR(1) NOT NULL,
    "Nom" VARCHAR(20) NOT NULL,
    "Prénom" VARCHAR(10) NOT NULL,
    "Voix" DECIMAL NOT NULL,
    "% Voix/Ins" DECIMAL NOT NULL,
    "% Voix/Exp" DECIMAL NOT NULL,
    "Code Insee" DECIMAL NOT NULL,
    "Coordonnées" VARCHAR(20),
    "Nom Bureau Vote" VARCHAR(120),
    "Adresse" VARCHAR(60),
    "Code Postal" DECIMAL,
    "Ville" VARCHAR(40),
    uniq_bdv VARCHAR(130)
);
copy "election-csv" from '/home/julien/Téléchargements/Projet-BD/test/data.csv' delimiter ';' csv header;
```

## Question 3

Nous avons trouvé les DF suivantes :

```sql
{
    "Code du département" -> "Département"
    "Département" -> "Code du département"
    "Code de la circonscription" -> "Circonscription"
    "Code du département", "Code de la commune" -> "Commune", "Code Insee"
    "Code du département", "Code de la commune", "Bureau de vote", "Nom Bureau vote" -> "Coordonnées", "Code Postal", "Ville", "Code de la circonscription", "uniq_bdv", "Inscrits", "Abstentions", "% Abs/Ins", "Votants", "% Vot/Ins", "Blancs", "% Blancs/Ins", "% Blancs/Vot", "Nuls", "% Nuls/Ins", "% Nuls/Vot", "Exprimés", "% Exp/Ins", "% Exp/Vot"
    "N°Panneau" -> "Sexe", "Nom", "Prénom"
    "N°Panneau", "Code du département", "Code de la commune", "Bureau de vote", "Nom Bureau vote" -> "Voix", "% Voix/Ins", "% Voix/Exp"
}
```

## Question 4

Notre schéma entité/association en version relationnel est le suivant :

```math
Candidat(_N°Panneau, Sexe, Nom, Prénom)
Departement(_Code du département, Département)
Circonscription(_Code de la circonscription, Circonscription)
Commune(_#Code du département, _Code de la commune, Commune)
Bureau(_#Code du département, _#Code de la commune, _#Bureau de vote, _Nom Bureau Vote, Ville, Code Postal, #Code de la circonscription, Coordonnées, uniq_bdv, Inscrits, Abstentions, Votants, Blancs, Nuls, Exprimés)
ScoreCandidat(_#Code du département, _#Code de la commune, _#Bureau de vote, _#Nom Bureau Vote, _#N°Panneau, Voix)
```

Ce model passe les formes normales 1, 2, 3 si on enlève les pourcentages qui peuvent être calculés, FNBC

## Question 5 - Création et remplissage des tables

```sql
-- #### Nettoyage du projet ####
do $$ begin
    drop table if exists score;
    drop table if exists bureau;
    drop table if exists complement_commune;
    drop table if exists commune;
    drop table if exists candidat;
    drop table if exists circonscription;
    drop table if exists departement;
end $$;

-- Table "Département"
drop table if exists departement;
create table departement (
    code decimal primary key,
    nom varchar(20) not null
);
insert into departement (
    select distinct "Code du département", "Département"
    from "election-csv" order by "Code du département"
);

-- Table "Circonscription"
drop table if exists circonscription;
create table circonscription (
    code decimal primary key,
    nom varchar(30) not null
);
insert into circonscription (
    select distinct "Code de la circonscription", "Circonscription"
    from "election-csv"
    order by "Code de la circonscription"
);

-- Table "Candidat"
drop table if exists candidat;
create table candidat (
    id decimal primary key,
    sexe varchar(1) not null,
    nom varchar(20) not null,
    prenom varchar(10) not null
);
insert into candidat (
    select distinct "N°Panneau", "Sexe", "Nom", "Prénom"
    from "election-csv"
    order by "N°Panneau"
);

-- Table "Commune"
drop table if exists commune;
create table commune (
    code_departement decimal references departement(code),
    code_commune decimal,
    commune varchar(40) not null,
    primary key (code_departement, code_commune)
);
insert into commune (
    select distinct "Code du département", "Code de la commune", "Commune"
    from "election-csv"
);

-- Table "Bureau"
update "election-csv" set "Nom Bureau Vote" = '' where "Nom Bureau Vote" is null;
drop table if exists bureau;
create table bureau (
    code_departement decimal,
    code_commune decimal,
    code_bureau decimal,
    nom_bureau varchar(120),
    ville varchar(40),
    code_postal decimal,
    code_circonscription decimal references circonscription(code),
    coordonnees varchar(20),
    uniq_bdv varchar(130),
    inscrits decimal not null,
    abstentions decimal not null,
    votants decimal not null,
    blancs decimal not null,
    nuls decimal not null,
    exprimes decimal not null,
    foreign key (code_departement, code_commune) references commune(code_departement, code_commune),
    primary key (code_departement, code_commune, code_bureau, nom_bureau)
);
insert into bureau (
    select distinct "Code du département", "Code de la commune", "Bureau de vote", "Nom Bureau Vote",
    "Ville", "Code Postal", "Code de la circonscription", "Coordonnées", "uniq_bdv",
    "Inscrits", "Abstentions", "Votants", "Blancs", "Nuls", "Exprimés"
    from "election-csv"
);

-- Table "Score Candidat"
drop table if exists score;
create table score (
    code_departement decimal,
    code_commune decimal,
    code_bureau decimal,
    nom_bureau varchar(120),
    id_candidat decimal references candidat(id),
    voix decimal,
    foreign key (code_departement, code_commune, code_bureau, nom_bureau
    ) references bureau(code_departement, code_commune, code_bureau, nom_bureau),
    primary key (code_departement, code_commune, code_bureau, nom_bureau, id_candidat)
);
insert into score (
    select distinct "Code du département", "Code de la commune",
    "Bureau de vote", "Nom Bureau Vote", "N°Panneau", "Voix"
    from "election-csv"
);

```

## Question 6 - Affichage des scores

```sql
drop function if exists get_score(varchar, varchar);
create or replace function get_score(n varchar, p varchar) returns table (
    voix decimal,
    "% voix/inscrits" decimal,
    "% voix/exprimés" decimal,
    "% voix/votants" decimal,
    bureau varchar(140),
    commune varchar(40),
    circonscription varchar(30),
    departement varchar(20)
    ) as $$
    begin
        return query
        select s.voix, s.voix/inscrits, s.voix/nullif(exprimes, 0), s.voix/nullif(votants, 0),
        concat('Bureau ', s.code_bureau, nullif(concat(' - ', s.nom_bureau), ' - '))::varchar(140), co.commune, ci.nom, d.nom
        from score s
        join candidat ca on s.id_candidat = ca.id
        join bureau b on s.code_departement = b.code_departement and s.code_commune = b.code_commune and s.code_bureau = b.code_bureau
        join departement d on s.code_departement = d.code
        join circonscription ci on b.code_circonscription = ci.code
        join commune co on s.code_departement = co.code_departement and s.code_commune = co.code_commune
        where ca.nom = n and ca.prenom = p
        order by d.nom, ci.nom, co.commune, s.code_bureau;
    end;
$$ language plpgsql;

-- Quelques exemples d'utilisation
select * from get_score('LE PEN', 'Marine');
select * from get_score('MACRON', 'Emmanuel');
select * from get_score('MÉLENCHON', 'Jean-Luc');
select avg(voix) from get_score('LE PEN', 'Marine');
select avg(voix) from get_score('MACRON', 'Emmanuel');
select avg(voix) from get_score('MÉLENCHON', 'Jean-Luc');
```
