-- Lab3
-- Michael Quan
-- combine.sql

-- If there isn't already a tuple in Payments that has the same primary key
INSERT INTO Payments(taxpayerID, datePaid, amountPaid)
SELECT taxpayerID, datePaid, amountPaid
FROM NewPayments 
WHERE NOT EXISTS (
SELECT * FROM Payments WHERE Payments.taxpayerID = NewPayments.taxpayerID
	AND Payments.datePaid = NewPayments.datePaid);

UPDATE Payments
SET amountPaid = n.amountPaid + p.amountPaid
FROM NewPayments n, Payments p
WHERE n.taxpayerID = p.taxpayerID
AND n.datePaid = p.datePaid;


