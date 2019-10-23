-- Lab1
-- Michael Quan

-- Drops Lab 1 schema and tables associated with it
DROP SCHEMA Lab1 CASCADE;

-- Creates an empty schema called Lab1
CREATE SCHEMA Lab1;

-- Create the tables TaxReturns, Payments, Individuals, Businesses, IRSagents, Delinquents

CREATE TABLE TaxReturns(
	taxpayerID INTEGER,
	taxYear INTEGER,
	kind CHAR(1),
	dateFiled DATE,
	-- Decimal with 9 digits to left of decimal at most and 2 after decimal
	income DECIMAL(9,2),
	taxOwed DECIMAL(9,2),
	PRIMARY KEY (taxpayerID, taxYear)
);

CREATE TABLE Payments(
	taxpayerID INTEGER,
	datePaid DATE,
	amountPaid DECIMAL(9,2),
	PRIMARY KEY (taxpayerID, datePaid)
);

CREATE TABLE Individuals(
	taxpayerID INTEGER PRIMARY KEY, 
	name VARCHAR(30), 
	address VARCHAR(30), 
	spouseID INTEGER, 
	lastDateFiled DATE, 
	lastDatePaid DATE, 
	totalTaxOwed DECIMAL(9,2)
);

CREATE TABLE Businesses(
	taxpayerID INTEGER PRIMARY KEY, 
	name VARCHAR(30), 
	address VARCHAR(30), 
	businessType CHAR(1), 
	lastDateFiled DATE, 
	lastDatePaid DATE, 
	totalTaxOwed DECIMAL(9,2)
);

CREATE TABLE IRSagents(
	IRSagentID CHAR(6) PRIMARY KEY, 
	taxpayerID INTEGER, 
	jobLevel INTEGER,	
	active BOOLEAN
);

CREATE TABLE Delinquents(
	taxpayerID INTEGER PRIMARY KEY, 
	IRSagentID CHAR(6), 
	collectionAgencyID INTEGER
);