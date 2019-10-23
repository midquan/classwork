-- Lab3
-- Michael Quan
-- queryviews.sql


SELECT d.taxpayerID, t.debt, p.credit
FROM Delinquents d, TaxDebts t, PaymentCredits p
WHERE d.taxpayerID = t.taxpayerID = p.taxpayerID;

DELETE FROM TaxReturns 
WHERE taxpayerID = 112 AND taxYear = 2016;

DELETE FROM TaxReturns 
WHERE taxpayerID = 116 AND taxYear = 2017;

SELECT d.taxpayerID, t.debt, p.credit
FROM Delinquents d, TaxDebts t, PaymentCredits p
WHERE d.taxpayerID = t.taxpayerID = p.taxpayerID;