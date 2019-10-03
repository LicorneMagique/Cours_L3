drop table Movie;
drop table Reviewer;
drop table Rating;

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


