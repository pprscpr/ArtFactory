use artfactory_db;

SELECT 	Titel,
		Stilrichtung
FROM 	Kunstwerk 	INNER JOIN eingeordnet_in 	USING (Kunstwerk_ID)
					INNER JOIN Kategorie		USING (Kategorie_ID)
ORDER BY Stilrichtung; 
	