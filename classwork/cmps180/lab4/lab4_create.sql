

DROP SCHEMA Lab4 CASCADE;
CREATE SCHEMA Lab4;

--Remember to execute:  ALTER ROLE your_user_id SET SEARCH_PATH TO Lab4;
--Logout and login again for this to take effect


--TaxReturns(taxpayerID, taxYear, kind, dateFiled, income, taxOwed)

CREATE TABLE TaxReturns (
	taxpayerID INT,
	taxYear INT,
	kind CHAR(1),
	dateFiled DATE NOT NULL,
	income DECIMAL(11, 2),
	taxOwed DECIMAL(11, 2),
	PRIMARY KEY (taxpayerID, taxYear),
	UNIQUE (taxpayerID, dateFiled)
);

--Payments(taxpayerID, datePaid, amountPaid)

CREATE TABLE Payments (
	taxpayerID INT,
	datePaid DATE,
	amountPaid DECIMAL(11, 2) NOT NULL,
	PRIMARY KEY (taxpayerID, datePaid)
);

--Individuals(taxpayerID, name, address, spouseID, lastDateFiled, lastDatePaid, totalTaxOwed)

CREATE TABLE Individuals (
	taxpayerID INT PRIMARY KEY,
	name VARCHAR(30),
	address VARCHAR(30),
	spouseID INT UNIQUE,
	lastDateFiled DATE,
	lastDatePaid DATE,
	totalTaxOwed DECIMAL(11, 2)
);

--Businesses(taxpayerID, name, address, businessType, lastDateFiled, lastDatePaid, totalTaxOwed)

CREATE TABLE Businesses ( 
	taxpayerID INT PRIMARY KEY,
	name VARCHAR(30),
	address VARCHAR(30),
	businessType CHAR(1),
	lastDateFiled DATE,
	lastDatePaid DATE,
	totalTaxOwed DECIMAL(11, 2),
	UNIQUE (name, address)
);

--IRSagents(IRSagentID, taxpayerID, jobLevel, active)

CREATE TABLE IRSagents (
	IRSagentID CHAR(6) PRIMARY KEY,
	taxpayerID INT NOT NULL, 
	jobLevel INT, 
	active BOOLEAN
);

--Delinquents(taxpayerID, IRSagentID, collectionAgencyID)

CREATE TABLE Delinquents (
	taxpayerID INT PRIMARY KEY, 
	IRSagentID CHAR(6), 
	collectionAgencyID INT
);
