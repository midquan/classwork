-- Lab2
-- Michael Quan
-- create.sql

-- Drops Lab 2 schema and tables associated with it
DROP SCHEMA Lab2 CASCADE;

-- Creates an empty schema called Lab2
CREATE SCHEMA Lab2;

-- Create the tables TaxReturns, Payments, Individuals, Businesses, IRSagents, Delinquents

CREATE TABLE TaxReturns(
	taxpayerID INTEGER,
	taxYear INTEGER,
	kind CHAR(1),
	dateFiled DATE NOT NULL,
	-- Decimal with 9 digits to left of decimal at most and 2 after decimal
	income DECIMAL(11,2),
	taxOwed DECIMAL(11,2),
	PRIMARY KEY (taxpayerID, taxYear),
	UNIQUE(taxpayerID, dateFiled)
);

CREATE TABLE Payments(
	taxpayerID INTEGER,
	datePaid DATE,
	amountPaid DECIMAL(11,2) NOT NULL,
	PRIMARY KEY (taxpayerID, datePaid)
);

CREATE TABLE Individuals(
	taxpayerID INTEGER PRIMARY KEY, 
	name VARCHAR(30), 
	address VARCHAR(30), 
	spouseID INTEGER UNIQUE, 
	lastDateFiled DATE, 
	lastDatePaid DATE, 
	totalTaxOwed DECIMAL(11,2)
);

CREATE TABLE Businesses(
	taxpayerID INTEGER PRIMARY KEY, 
	name VARCHAR(30), 
	address VARCHAR(30), 
	businessType CHAR(1), 
	lastDateFiled DATE, 
	lastDatePaid DATE, 
	totalTaxOwed DECIMAL(11,2),
	UNIQUE(name, address)
);

CREATE TABLE IRSagents(
	IRSagentID CHAR(6) PRIMARY KEY, 
	taxpayerID INTEGER NOT NULL, 
	jobLevel INTEGER,	
	active BOOLEAN
);

CREATE TABLE Delinquents(
	taxpayerID INTEGER PRIMARY KEY, 
	IRSagentID CHAR(6), 
	collectionAgencyID INTEGER
);