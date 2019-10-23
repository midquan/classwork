-- Lab3
-- Michael Quan
-- general.sql


-- 1. amountPaid in Payments must be positive. Please give a name to this positive rent constraint when you
-- create it. We recommend that you use the name positive_payments, but you may use another name. The other
-- constraints don’t need names.

ALTER TABLE Payments ADD CONSTRAINT positive_payments CHECK(amountPaid > 0);

-- 2. In Businesses, lastDateFiled must be greater than or equal to lastDatePaid. (Do this just for Businesses, not
-- for Individuals.)

ALTER TABLE Businesses ADD CHECK(lastDateFiled >= lastDatePaid);

-- 3. In IRSagents, if jobLevel is NULL then active must also be NULL.

ALTER TABLE IRSagents ADD CHECK(jobLevel = NULL OR active <> NULL);

-- 4. In Individuals, taxpayerID and spouseID must be different.

ALTER TABLE Individuals ADD CHECK(taxpayerID <> spouseID);
