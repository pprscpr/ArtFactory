use artfactory_db;

SELECT 	Vorname,
		Nachname
FROM 	Kunde INNER JOIN Kuenstler USING (Kunden_ID)
WHERE 	Kunde.Kunden_ID = Kuenstler.Kunden_ID;
	