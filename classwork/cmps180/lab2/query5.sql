-- Lab2
-- Michael Quan
-- query5.sql

SELECT p.taxpayerID AS payingTaxpayer, Count(p.taxpayerID) AS howmanyPayments, 
SUM(p.amountPaid) AS sumPayments From Payments p WHERE taxpayerID IN (SELECT q.taxpayerID from Payments q
GROUP BY q.taxpayerID HAVING COUNT(q.datePaid)  >= 1) GROUP BY p.taxpayerID;
