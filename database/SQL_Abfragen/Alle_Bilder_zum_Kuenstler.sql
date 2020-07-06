use artfactory_db;

SELECT 	Kuenstlername,
		Titel
FROM 	Kuenstler INNER JOIN Kunstwerk ON Kuenstler.Kunden_ID = Kunstwerk.Kuenstler_ID;