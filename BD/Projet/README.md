# Projet

## Question 1 et 2

Nous avons rassemblé toutes les données dans un seul fichier CSV. Le code permettant de créer la table est le suivant :

```sql
-- Création de la base
drop table if exists "election-csv";
CREATE TABLE "election-csv" (
    "Code du département" DECIMAL NOT NULL,
    "Département" VARCHAR(12) NOT NULL,
    "Code de la circonscription" DECIMAL NOT NULL,
    "Circonscription" VARCHAR(25) NOT NULL,
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
    "Nom" VARCHAR(16) NOT NULL,
    "Prénom" VARCHAR(8) NOT NULL,
    "Voix" DECIMAL NOT NULL,
    "% Voix/Ins" DECIMAL NOT NULL,
    "% Voix/Exp" DECIMAL NOT NULL,
    "Code Insee" DECIMAL NOT NULL,
    "Coordonnées" VARCHAR(119),
    "Nom Bureau Vote" VARCHAR(170),
    "Adresse" VARCHAR(148),
    "Code Postal" DECIMAL,
    "Ville" VARCHAR(40),
    uniq_bdv VARCHAR(185)
);
copy "election-csv2" from '/home/julien/Téléchargements/Projet-BD/test/data.csv' delimiter ';' csv header;
```

## Question 3

Nous avons trouvé les DF suivantes :

```php
{
    "Code du département" -> "Département"
    "Département" -> "Code du département"
    "Code de la circonscription" -> "Circonscription"
    "Circonscription" -> "Code de la circonscription"
    "Code du département", "Code de la commune" -> "Commune", "Code Insee"
    "Code du département", "Code de la commune", "Bureau de vote" -> "Code Postal", "Ville"
    "Code du département", "Code de la commune", "Bureau de vote", "Nom Bureau Vote" -> "Code du département", "Code de la circonscription", "Coordonnées", "Adresse", "uniq_bdv", "Inscrits", "Abstentions", "% Abs/Ins", "Votants", "% Vot/Ins", "Blancs", "% Blancs/Ins", "% Blancs/Vot", "Nuls", "% Nuls/Ins", "% Nuls/Vot", "Exprimés", "% Exp/Ins", "% Exp/Vot"
    "N°Panneau" -> "Sexe", "Nom", "Prénom"
    "N°Panneau", "Code Insee", "Bureau de vote", "Nom Bureau Vote" -> "Voix", "% Voix/Ins", "% Voix/Exp"
}
```

## Question 4

Notre schéma entité/association en version relationnel est le suivant :

```math
Candidat(_N°Panneau, Sexe, Nom, Prénom)
Departement(_Code du département, Département)
Circonscription(_Code de la circonscription, Circonscription)
Commune(_#Code du département, _Code de la commune, Code Insee, Commune)
Complement_Commune(_#Code du département, _#Code de la commune, Code Postal, Ville)
Bureau(_#Code du département, _#Code de la commune, _Bureau de vote, _Nom Bureau Vote, _Adresse, #Code du département, #Code de la circonscription, Coordonnées, uniq_bdv, Inscrits, Abstentions, % Abs/Ins, Votants, % Vot/Ins, Blancs, % Blancs/Ins, % Blancs/Vot, Nuls, % Nuls/Ins, % Nuls/Vot, Exprimés, % Exp/Ins, % Exp/Vot)
ScoreCandidat(_#Code du département, _#Code de la commune, _#Bureau de vote, _#Nom Bureau Vote, _#N°Panneau, Voix, % Voix/Ins, % Voix/Exp)
```

Ce model passe les formes normales 1, 2, 3 si on considère que les pourcentages doivent être stockés en base plutôt que d'être calculés lors des requettes (en l'absence de plus d'information on va supposer qu'il faut garder les résultats en base), FNBC

## Question 5 - Création et remplissage des tables

```sql
-- Table "Département"
drop table if exists departement;
create table departement (
    code decimal primary key,
    "label" varchar(12) not null
);
insert into departement (
    select distinct "Code du département", "Département"
    from "election-csv" order by "Code du département"
);

-- Table "Circonscription"
drop table if exists circonscription;
create table circonscription (
    code decimal primary key,
    "label" varchar(25) not null
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
    nom varchar(16) not null,
    prenom varchar(8) not null
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
    code_insee decimal,
    commune varchar(40) not null,
    constraint pk_commune primary key (code_departement, code_commune)
);
insert into commune (
    select distinct "Code du département", "Code de la commune", "Code Insee", "Commune"
    from "election-csv"
);

-- Table "Complément Commune"
drop table if exists complement_commune;
create table complement_commune (
    code_departement decimal,
    code_commune decimal,
    code_bureau decimal,
    code_postal decimal,
    ville varchar(40),
    foreign key (code_departement, code_commune) references commune(code_departement, code_commune),
    primary key (code_departement, code_commune, code_bureau)
);
insert into complement_commune (
    select distinct "Code du département", "Code de la commune", "Bureau de vote", "Code Postal", "Ville"
    from "election-csv" where "Ville" <> ''
);

-- Table "Bureau"
drop table if exists bureau;
create table bureau (
    code_departement decimal,
    code_commune decimal,
    code_bureau decimal,
    nom_bureau varchar(170),
    adresse varchar(150),
    code_circonscription decimal references circonscription(code),
    coordonnees varchar(120),
    uniq_bdv varchar(185),
    inscrits decimal not null,
    abstentions decimal not null,
    "% abs/ins" decimal not null,
    votants decimal not null,
    "% vot/ins" decimal not null,
    blancs decimal not null,
    "% clancs/ins" decimal not null,
    "% clancs/vot" decimal not null,
    nuls decimal not null,
    "% nuls/ins" decimal not null,
    "% nuls/vot" decimal not null,
    exprimes decimal not null,
    "% exp/ins" decimal not null,
    "% exp/vot" decimal not null,
    foreign key (code_departement, code_commune) references commune(code_departement, code_commune),
    primary key (code_departement, code_commune, code_bureau, nom_bureau, adresse)
);
insert into bureau (
    select distinct "Code du département", "Code de la commune", "Bureau de vote", "Nom Bureau Vote", "Adresse", "Code de la circonscription", "Coordonnées", "uniq_bdv", "Inscrits", "Abstentions", "% Abs/Ins", "Votants", "% Vot/Ins", "Blancs", "% Blancs/Ins", "% Blancs/Vot", "Nuls", "% Nuls/Ins", "% Nuls/Vot", "Exprimés", "% Exp/Ins", "% Exp/Vot"
    from "election-csv"
);

-- Table "Score Candidat"
drop table if exists score;
create table score (
    code_departement decimal,
    code_commune decimal,
    code_bureau decimal,
    nom_bureau varchar(170),
    adresse varchar(150),
    id_candidat decimal references candidat(id),
    voix decimal,
    "% voix/ins" decimal,
    "% voix/exp" decimal,
    foreign key (code_departement, code_commune, code_bureau, nom_bureau, adresse
        ) references bureau(code_departement, code_commune, code_bureau, nom_bureau, adresse),
    primary key (code_departement, code_commune, code_bureau, nom_bureau, adresse, id_candidat)
);
insert into score (
    select distinct "Code du département", "Code de la commune", "Bureau de vote", "Nom Bureau Vote", "Adresse", "N°Panneau", "Voix", "% Voix/Ins", "% Voix/Exp"
    from "election-csv"
);
ScoreCandidat(_#Code du département, _#Code de la commune, _#Bureau de vote, _#Nom Bureau Vote, _#N°Panneau, Voix, % Voix/Ins, % Voix/Exp)

```
