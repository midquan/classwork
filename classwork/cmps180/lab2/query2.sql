-- Lab2
-- Michael Quan
-- query2.sql

SELECT b.taxPayerID FROM  Businesses b
WHERE b.name LIKE 'TI%' AND b.taxPayerID 
NOT IN (SELECT taxPayerID from TaxReturns); 