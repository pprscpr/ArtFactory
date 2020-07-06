/*Hier weiß ich nicht genau, wie ich es darstellen soll,
eigentlich müsste beim WHERE nach der Stilrichtung der 
USER einen Suchbegriff eingeben.*/

use artfactory_db;

SELECT 	Titel,
		Stilrichtung
FROM 	Kunstwerk 	INNER JOIN eingeordnet_in 	USING (Kunstwerk_ID)
					INNER JOIN Kategorie		USING (Kategorie_ID)
WHERE	Stilrichtung REGEXP '(Digital)'
ORDER BY Stilrichtung;   
	