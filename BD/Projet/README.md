# Projet

```postgresql
-- Création de la base
drop table if exists "election-csv";
CREATE TABLE "election-csv" (
    "Code du département" DECIMAL NOT NULL,
    "Département" VARCHAR(15) NOT NULL,
    "Code de la circonscription" DECIMAL NOT NULL,
    "Circonscription" VARCHAR(25) NOT NULL,
    "Code de la commune" DECIMAL NOT NULL,
    "Commune" VARCHAR(133) NOT NULL,
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
    "Sexe" VARCHAR(11) NOT NULL,
    "Nom" VARCHAR(113) NOT NULL,
    "Prénom" VARCHAR(18) NOT NULL,
    "Voix" DECIMAL NOT NULL,
    "% Voix/Ins" DECIMAL NOT NULL,
    "% Voix/Exp" DECIMAL NOT NULL,
    "Code Insee" DECIMAL NOT NULL,
    "Coordonnées" VARCHAR(119),
    "Nom Bureau Vote" VARCHAR(170),
    "Adresse" VARCHAR(148),
    "Code Postal" DECIMAL,
    "Ville" VARCHAR(133),
    uniq_bdv VARCHAR(185)
);

-- #### Fonctions de création des tables ####

create or replace function creation_table_departement() returns void as $$
    declare
        ligne record;
    begin
        -- Création de la table
        drop table if exists departement;
        create table departement (
            code decimal primary key,
            "label" varchar(15) not null
        );
        -- Remplissage de la table
        for ligne in
            select distinct "Code du département", "Département"
            from "election-csv" order by "Code du département"
        loop
            insert into departement values (ligne."Code du département", ligne."Département");
        end loop;
    end;
$$ language plpgsql;

create or replace function creation_table_circonscription() returns void as $$
    declare
        ligne record;
    begin
        -- Création de la table
        drop table if exists circonscription;
        create table circonscription (
            code decimal primary key,
            "label" varchar(25) not null
        );
        -- Remplissage de la table
        for ligne in
            select distinct "Code de la circonscription", "Circonscription"
            from "election-csv" order by "Code de la circonscription"
        loop
            insert into circonscription values (ligne."Code de la circonscription", ligne."Circonscription");
        end loop;
    end;
$$ language plpgsql;

-- #### Programme principale ####

do $$ begin
    perform creation_table_departements();
    perform creation_table_circonscription();
    --drop table "election-csv";
end $$;

-- #### Nettoyage des tables du TP ####

do $$ begin
    drop table departement;
    drop table circonscription;
end $$;

```
