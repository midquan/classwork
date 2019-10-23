-- Lab3
-- Michael Quan
-- createviews.sql


CREATE VIEW TaxDebts AS
SELECT t.taxpayerID, SUM(t.taxOwed) AS debt
FROM TaxReturns t
WHERE taxpayerID IN (SELECT tx.taxpayerID 
	FROM TaxReturns tx
	GROUP BY tx.taxpayerID HAVING COUNT(tx.taxpayerID) >= 4);

CREATE VIEW PaymentCredits AS
SELECT p.taxpayerID , MAX(p.datePaid) AS biggestDatePaid, SUM(p.amountPaid) AS credit
FROM Payments p 
WHERE taxpayerID IN (SELECT pa.amountPaid
	FROM Payments pa
	GROUP BY pa.amountPaid HAVING DISTINCT COUNT(pa.amountPaid) >= 2);  	