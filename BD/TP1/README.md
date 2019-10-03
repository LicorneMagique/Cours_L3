# TP1

## EX1

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

## EX2

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
    from movie, rating, reviewer
    where title = 'Gone with the Wind' and movie.mid = rating.mid and rating.rid = reviewer.rid
    ```

4. Pour chaque évaluation où l’examinateur est identique au réalisateur du film (même nom), retourner le nom de l’examinateur, le titre du film, et le nombre d’étoiles.

    ```sql
    select director, title, stars
    from movie, rating, reviewer
    where movie.mid = rating.mid and rating.rid = reviewer.rid and director = name
    ```

5. Retourner l’intégralité des évaluations, en remplaçant rID avec les noms des examinateurs et mID par les titres de films. Trier le résultat, d’abord par le nom de relecteur, puis par le titre de film, et enfin
par le nombre d’étoiles.

    ```sql
    select name, title, stars, ratingDate
    from movie, rating, reviewer
    where movie.mid = rating.mid and rating.rid = reviewer.rid
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
    SELECT name, title
    FROM rating r, rating r2, movie, reviewer
    WHERE movie.mid = r.mid AND reviewer.rid = r.rid AND r.rid = r2.rid AND r.mid = r2.mid
    AND r2.ratingDate > r.ratingDate AND r2.stars > r.stars
    ```

8. Retourner les paires d’évaluateurs qui ont noté le même film, retourner le nom de ces deux examinateurs en éliminant les duplications ((a, b) et (b, a) représentent la même chose).

    ```sql
    SELECT DISTINCT w.name n1, w2.name n2
    FROM Rating r, Rating r2, Reviewer w2, Reviewer w
    WHERE w2.rID = r2.rID AND w.rID = r.rID
    AND r.rID > r2.rID AND r.mID = r2.mID
    ```

## EX3
