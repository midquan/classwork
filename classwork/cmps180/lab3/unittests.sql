-- Lab3
-- Michael Quan
-- unittests.sql


-- For each of the 3 foreign key constraints specified in section 2.3, write one unit test:
-- An INSERT command that violates the foreign key constraint (and elicits an error).

-- -- a) The taxpayerID field in IRSagents should reference the taxpayerID primary key in Individuals

INSERT INTO IRSagents VALUES ( '34DB45', 160, 1, True); 

-- b) The IRSagentID field in Delinquents should reference the IRSagentID primary key in IRSagents.

INSERT INTO Delinquents VALUES ( 160, '34DB45', 108);

-- c) The collectionAgencyID field in Delinquents should reference the taxpayerID primary key in Businesses.

INSERT INTO Delinquents VALUES ( 150, 'A4DV57', 160);

-- Also, for each of the 4 general constraints, write 2 unit tests:
-- An UPDATE command that meets the constraint.

-- 1. amountPaid in Payments must be positive. Please give a name to this positive rent constraint when you
-- create it. We recommend that you use the name positive_payments, but you may use another name. The other
-- constraints don’t need names.

UPDATE Payments
SET amountPaid = 400.00 
WHERE taxpayerID = 119  and datePaid = '09/21/2016';

UPDATE Payments
SET amountPaid = -400.00
WHERE taxpayerID = 119  and datePaid = '09/21/2016' 

-- 2. In Businesses, lastDateFiled must be greater than or equal to lastDatePaid. (Do this just for Businesses, not
-- for Individuals.)

UPDATE Businesses
SET lastDateFiled = '09/21/2016', lastDatePaid =  '09/21/2017'
WHERE taxpayerID = 107;

UPDATE Businesses
SET lastDateFiled = '09/21/2017', lastDatePaid =  '09/21/2016',
WHERE taxpayerID = 107;


-- 3. In IRSagents, if jobLevel is NULL then active must also be NULL.

UPDATE IRSagents
SET jobLevel = NULL, active = NULL
WHERE IRSagentID = A4DV57;

UPDATE IRSagents
SET jobLevel = 2, active = NULL
WHERE IRSagentID = A4DV57;

-- 4. In Individuals, taxpayerID and spouseID must be different.

UPDATE Individuals
SET taxpayerID = 110, spouseID = 160
WHERE name = 'Jin Huff' AND '843 Ante Ave'

UPDATE Individuals
SET taxpayerID = 160, spouseID = 160
WHERE name = 'Jin Huff' AND '843 Ante Ave'