CREATE OR REPLACE FUNCTION assignDelinquents (theAgent CHAR(6), theCount INTEGER)
RETURNS INTEGER
LANGUAGE plpgsql
$$

DECLARE
	nullDel INTEGER;
	counter INTEGER := 0; 
	taxID CHAR(6);
	

DECLARE cursor_i CURSOR FOR
  SELECT d.taxPayerID
  FROM Delinquents d
  WHERE d.IRSagentID = NULL;  
 
DECLARE cursor_d CURSOR FOR
  SELECT i.totalTaxOwed
  FROM Individuals i, Delinquents d 
  WHERE i.taxPayerID = d.taxPayerID AND d.IRSagentID = NULL
  ORDER BY i.totalTaxOwed DESC; 

BEGIN
	OPEN cursor_i;
	FETCH FROM cursor_d INTO nullDel;
    WHILE Found 
	LOOP
		OPEN cursor_d;
		FETCH cursos_d INTO taxID; 
		WHILE theCount > counter AND Found
		LOOP
			UPDATE IRSagentID = theCount FROM Delinquents WHERE current of cursor_d = taxPayerID;
			counter := counter + 1;
			FETCH cursor_i into taxID;
		
	FETCH FROM cursor_d INTO nullDel;
	END LOOP;
	
	RETURN counter;
	CLOSE cursor_d;
END;
$$