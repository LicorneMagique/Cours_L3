# TP1

## EX1 : création de la base

```sql
--drop table Movie;
--drop table Reviewer;
--drop table Rating;

create table Movie(mID integer, title varchar(50), year integer, director varchar(30));
create table Reviewer(rID integer, name varchar(30));
create table Rating(rID integer, mID integer, stars integer, ratingDate date);

insert into Movie values(101, 'Gone with the Wind', 1939, 'Victor Fleming');
insert into Movie values(102, 'Star Wars', 1977, 'George Lucas');
insert into Movie values(103, 'The Sound of Music', 1965, 'Robert Wise');
insert into Movie values(104, 'E.T.', 1982, 'Steven Spielberg');
insert into Movie values(105, 'Titanic', 1997, 'James Cameron');
insert into Movie values(106, 'Snow White', 1937, null);
insert into Movie values(107, 'Avatar', 2009, 'James Cameron');
insert into Movie values(108, 'Raiders of the Lost Ark', 1981, 'Steven Spielberg');

insert into Reviewer values(201, 'Sarah Martinez');
insert into Reviewer values(202, 'Daniel Lewis');
insert into Reviewer values(203, 'Brittany Harris');
insert into Reviewer values(204, 'Mike Anderson');
insert into Reviewer values(205, 'Chris Jackson');
insert into Reviewer values(206, 'Elizabeth Thomas');
insert into Reviewer values(207, 'James Cameron');
insert into Reviewer values(208, 'Ashley White');

INSERT INTO Rating VALUES(201, 101, 2, to_date('22-01-2011', 'dd-mm-yyyy'));
insert into Rating values(201, 101, 4, to_date('27-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(202, 106, 4, NULL);
INSERT INTO Rating VALUES(203, 103, 2, to_date('20-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(203, 108, 4, to_date('12-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(203, 108, 2, to_date('30-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(204, 101, 3, to_date('09-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(205, 103, 3, to_date('27-01-2011', 'dd-mm-yyyy'));
insert into Rating values(205, 104, 2, to_date('22-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(205, 108, 4, NULL);
INSERT INTO Rating VALUES(206, 107, 3, to_date('15-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(206, 106, 5, to_date('19-01-2011', 'dd-mm-yyyy'));
INSERT INTO Rating VALUES(207, 107, 5, to_date('20-01-2011', 'dd-mm-yyyy'));
insert into Rating values(208, 104, 3, to_date('02-01-2011', 'dd-mm-yyyy'));
```

## EX2 : requêtes simples

1. Les films réalisés par Steven Spielberg.

    ```sql
    select * from movie where director = 'Steven Spielberg'
    ```

2. Trouver toutes les années, dans l’ordre croisant, qui ont un film qui a reçu une note de 4 ou 5.

    ```sql
    select year
    from rating join movie on rating.mid = movie.mid
    where stars > 3
    order by year
    ```

3. Trouver le nom des personnes qui ont noté le film Gone with the Wind.

    ```sql
    select distinct name
    from movie
    join rating on movie.mid = rating.mid
    join reviewer on rating.rid = reviewer.rid
    where title = 'Gone with the Wind'
    ```

4. Pour chaque évaluation où l’examinateur est identique au réalisateur du film (même nom), retourner le nom de l’examinateur, le titre du film, et le nombre d’étoiles.

    ```sql
    select director, title, stars
    from movie
    join rating on movie.mid = rating.mid
    join reviewer on rating.rid = reviewer.rid
    where director = name
    ```

5. Retourner l’intégralité des évaluations, en remplaçant rID avec les noms des examinateurs et mID par les titres de films. Trier le résultat, d’abord par le nom de relecteur, puis par le titre de film, et enfin
par le nombre d’étoiles.

    ```sql
    select name, title, stars, ratingDate
    from movie
    join rating on movie.mid = rating.mid
    join reviewer on rating.rid = reviewer.rid
    order by name, title, stars
    ```

6. Retourner les titres des films non encore examinés par Chris Jackson.

    ```sql
    select title
    from movie
    where mid not in (
        select mid
        from rating
        where rid = (
            select rid
            from reviewer
            where name = 'Chris Jackson'
        )
    )
    ```

7. Pour tous les cas où la même personne note deux fois le même film et donne une note plus élevée la seconde fois, retourner le nom de l’examinateur et le titre du film.

    ```sql
    select name, title
    from rating r1
    join rating r2 on r1.mid = r2.mid and r1.rid = r2.rid
    join movie on r1.mid = movie.mid
    join reviewer on r1.rid = reviewer.rid
    where r1.ratingdate < r2.ratingdate and r1.stars > r2.stars
    ```

8. Retourner les paires d’évaluateurs qui ont noté le même film, retourner le nom de ces deux examinateurs en éliminant les duplications ((a, b) et (b, a) représentent la même chose).

    ```sql
    select distinct w1.name, w2.name
    from rating r1
    join rating r2 on r1.mid = r2.mid
    join reviewer w1 on r1.rid = w1.rid
    join reviewer w2 on r2.rid = w2.rid
    where r1.rid > r2.rid
    ```

## Exercice 3 : requêtes avançées

1. Trouver les titres des films qui n’ont pas reçu d’évaluations.

    ```sql
    select title
    from movie
    where mid not in (
        select mid
        from rating
    )
    ```

2. Retourner le nom de l’examinateur, le titre du film,et le nombre d’étoiles pour tous les films qui ont actuellement la plus mauvaise note dans la base.

    ```sql
    select name, title, stars
    from movie
    join rating on rating.mid = movie.mid
    join reviewer on rating.rid = reviewer.rid
    where stars = (
        select min(stars)
        from rating
    )
    ```

3. Pour chaque film, trouver la meilleure note reçue. Retourner le titre de film et le nombre d’étoiles. Trier par rapport au titre de film (ordre alphabétique).

    ```sql
    select name, title, stars
    from movie
    join rating r1 on r1.mid = movie.mid
    join reviewer on r1.rid = reviewer.rid
    where stars = (
        select max(stars)
        from rating r2
        where r1.mid = r2.mid
    )
    order by title
    ```

## Exercice 4 : requêtes d’agrégation

1. Lister les titres de films et leur note moyenne.

    ```sql
    ```

2. Trouver le nom de tous les examinateurs qui ont fait au moins 3 évaluations.

    ```sql
    ```

3. Trouver le(s) film(s) ayant la meilleure moyenne de note. Retourner le titre de film, et la note moyenne.

    ```sql
    ```

4. Idem pour la plus mauvaise moyenne.

    ```sql
    ```

5. Trouver la différence entre la moyenne des notes des films (il faut bien calculer la moyenne pour chaque film, puis la moyenne des moyennes : il ne suffit pas de calculer simplement la moyenne des notes avant et après 1980) réalisés avant 1980 et ceux réalisés après.

    ```sql
    ```

6. Pour chaque film, retourner le titre et la différence entre la meilleure et la plus mauvaise note pour un film donné. Trier par rapport à cette amplitude puis en fonction du titre.

    ```sql
    ```

## Exercice 5 : requêtes sur les valeurs nulles

1. Trouver les noms des examinateurs qui n’ont pas daté leurs évaluations.

    ```sql
    ```

2. Pour chaque réalisateur, retourner leur nom, titre de film(s) dirigés et ayant reçu la meilleure note de leur carrière. Retourner également cette note. Ignorer les films dont le réalisateur n’est pas spécifié.

    ```sql
    ```

## Exercice 6 : modification de la base de données

1. Ajouter un nouvel examinateur Roger Ebert dans la base de données avec un rID égal à 209.

    ```sql
    ```

2. Pour vérifier l’insertion précédente, écrire une requête pour retourner le nombre d’évaluateurs.

    ```sql
    ```

3. Insérer des évaluations à 5 étoiles faites par Roger Ebert pour tous les films de la base. Laisser la date à NULL.

    ```sql
    ```

4. Pour vérifier l’insertion précédente, retourner le nom des examinateurs qui ont noté tous les films.

    ```sql
    ```

5. Pour tous les films qui ont une note moyenne supérieure ou égale à 4, ajouter 25 ans à la date de réalisation (mettre à jour les tuples, ne pas en créer).

    ```sql
    ```

6. Pour vérifier la modification précédente, retourner le nombre de films réalisés avant 1990.

    ```sql
    ```

7. Supprimer tous les films de la base à l’exception des films réalisés entre 2000 et 2010.

    ```sql
    ```

8. Maintenant, beaucoup d’évaluations réfèrent à des films qui ne sont plus dans la table Movie. Supprimer toutes les évaluations dont le film correspondant n’apparaît plus dans la table Movie.

    ```sql
    ```

9. Maintenant, des évaluateurs n’ont plus aucune évaluation. Supprimer les examinateurs qui n’ont pas d’évaluation dans la table Rating.

    ```sql
    ```
