-- Lab2
-- Michael Quan
-- query3.sql

SELECT b.name,b.address FROM  Businesses b
WHERE b.lastDatePaid >= DATE '2017-3-1' 
UNION
SELECT i.name,i.address FROM  Individuals i
WHERE i.lastDatePaid >= DATE '2017-3-1';
