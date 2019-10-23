-- Lab2
-- Michael Quan
-- query4.sql

SELECT i.name AS taxpayerName, (SELECT name FROM Individuals WHERE i.spouseID = taxpayerID) AS spouseName 
FROM Individuals i WHERE i.spouseID IS NOT NULL;
