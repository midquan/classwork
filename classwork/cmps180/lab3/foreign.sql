-- Lab3
-- Michael Quan
-- foreign.sql

-- a) The taxpayerID field in IRSagents should reference the taxpayerID primary key in Individuals.

ALTER TABLE IRSagents
ADD CONSTRAINT fk_taxpayerid
FOREIGN KEY (taxpayerID) REFERENCES Individuals(taxPayerID);

-- b) The IRSagentID field in Delinquents should reference the IRSagentID primary key in IRSagents.

ALTER TABLE Delinquents
ADD CONSTRAINT fk_irsagentid
FOREIGN KEY (IRSagentID) REFERENCES IRSagents(IRSagentID);

-- c) The collectionAgencyID field in Delinquents should reference the taxpayerID primary key in Businesses.

ALTER TABLE Delinquents
ADD CONSTRAINT fk_taxpayerid
FOREIGN KEY (collectionAgencyID) REFERENCES Businesses(taxPayerID);