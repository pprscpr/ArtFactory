-- Die INSERT der Gruppe: Ernesto Cabrera Garcia, Jonas Wünsch, Stefan Riedl.

-- Kunde 1
START TRANSACTION;

USE artfactory_db;

ALTER TABLE Kunde AUTO_INCREMENT=1001;
ALTER TABLE Kunstwerk AUTO_INCREMENT=1001;

INSERT INTO Kunde	(Anrede, Titel, Vorname, Nachname, Strasse, PLZ, ORT) 
			VALUES	('Herr', NULL, 'Bedolf', 'Kittler', 'Bahnhofstrasse 2', '02826', 'Goerlitz');

SET @Kunden_ID 	= LAST_INSERT_ID();		
INSERT INTO Login 	(Kunden_ID, Login, reg_IP, Passwort)
			VALUES	(@Kunden_ID, 'BediKitti', '77.88.205.245', SHA2('NAMica565', 256));	

INSERT INTO	Kontakt (Kunden_ID, Art_ID, Kontakt, Bemerkung)
			VALUES	(@Kunden_ID, 2, "0151 88888888", "Jeden Tag erreichbar.");

COMMIT;


-- Kunde 2
START TRANSACTION;

USE artfactory_db;

INSERT INTO Kunde	(Anrede, Titel, Vorname, Nachname, Strasse, PLZ, ORT) 
			VALUES	('Herr', NULL, 'Armin', 'Stzynckiszi', 'Keferstrasse 2', '80802', 'Muenchen');

SET @Kunden_ID 	= LAST_INSERT_ID();
INSERT INTO Login 	(Kunden_ID, Login, reg_IP, Passwort)
			VALUES	(@Kunden_ID, 'PowerArmin', '57.58.205.255', SHA2('YokOR1111', 256));

INSERT INTO	Kontakt (Kunden_ID, Art_ID, Kontakt, Bemerkung)
			VALUES	(@Kunden_ID, 2, "0151 88688688", "Ruf mich AN!!");

COMMIT;


-- Kuenstler1
START TRANSACTION;

USE artfactory_db;

INSERT INTO Kunde	(Anrede, Titel, Vorname, Nachname, Strasse, PLZ, ORT) 
			VALUES	('Herr', 'Sir', 'Peter', 'File', 'Königstrasse 2', '50676', 'Koeln');

SET @Kunden_ID 	= LAST_INSERT_ID();
INSERT INTO Login 	(Kunden_ID, Login, reg_IP, Passwort)
			VALUES	(@Kunden_ID, 'PeterFile', '77.12.122.123', SHA2('IIIiii8opepP', 256));

INSERT INTO Kuenstler	(Kunden_ID, Kuenstlername, IBAN, BIC)
			VALUES 		(@Kunden_ID, 'PeterFile', 'DE76790200788326329540', NULL);

INSERT INTO	Kontakt (Kunden_ID, Art_ID, Kontakt, Bemerkung)
			VALUES	(@Kunden_ID, 2, "0174 99877883", "bitte lange klingeln lassen");

INSERT INTO Kunstwerk	(Kunden_ID, Kuenstler_ID, Titel, Image, Hoehe, Breite, Preis, Einstell_IP, Gewicht, Beschreibung, Herstellungsdatum)
			VALUES		(NULL, @Kunden_ID, "peterspeterfilepainting", 'peterspeterfilepainting.jpg', '40', '40', '999,89', '72.23.246.222', '100', "PETERFILE !", "23.11.2010");

SET @Kunstwerk_ID = LAST_INSERT_ID();
INSERT INTO eingeordnet_in VALUES (@Kunstwerk_ID, 115);

INSERT INTO Kunstwerk	(Kunden_ID, Kuenstler_ID, Titel, Image, Hoehe, Breite, Preis, Einstell_IP, Gewicht, Beschreibung, Herstellungsdatum, Kauf_IP, Kauf_Zeitstempel)
			VALUES		(1001, @Kunden_ID, "peterspeterfilepainting2", 'peterspeterfilepainting2.png', '40', '40', '999,89', '72.23.246.222', '100', "PETERFILE 2 !", "23.11.2010", '76.90.999.100', "2020-11-23");

SET @Kunstwerk_ID = LAST_INSERT_ID();
INSERT INTO eingeordnet_in VALUES (@Kunstwerk_ID, 115);
			
COMMIT;


-- Kuenstler2
START TRANSACTION;

USE artfactory_db;

INSERT INTO Kunde	(Anrede, Titel, Vorname, Nachname, Strasse, PLZ, ORT) 
			VALUES	('Frau', 'Queen', 'Shakira', 'Shidshagg', 'Bluecherstrasse 33', '10961', 'Berlin');

SET @Kunden_ID 	= LAST_INSERT_ID();
INSERT INTO Login 	(Kunden_ID, Login, reg_IP, Passwort)
			VALUES	(@Kunden_ID, 'ShackiShitShack', '74.24.242.244', SHA2('IIIii!!!!!hlen', 256));

INSERT INTO Kuenstler	(Kunden_ID, Kuenstlername, IBAN, BIC)
			VALUES 		(@Kunden_ID, 'Simsam', 'DE76790255558326329540', NULL);

INSERT INTO	Kontakt (Kunden_ID, Art_ID, Kontakt, Bemerkung)
			VALUES	(@Kunden_ID, 2, "0157 77888882", NULL);

INSERT INTO Kunstwerk	(Kunden_ID, Kuenstler_ID, Titel, Image, Hoehe, Breite, Preis, Einstell_IP, Gewicht, Beschreibung, Herstellungsdatum)
			VALUES		(NULL, @Kunden_ID, "Quastenpastenmalerei", 'Quastenpastenmalerei.jpg', '222', '222', '7088,99', '72.32.126.211', '555', "Quastig gepampt und rumgeschmiert", "20.08.1945");

SET @Kunstwerk_ID = LAST_INSERT_ID();
INSERT INTO eingeordnet_in VALUES (@Kunstwerk_ID, 119);

INSERT INTO Kunstwerk	(Kunden_ID, Kuenstler_ID, Titel, Image, Hoehe, Breite, Preis, Einstell_IP, Gewicht, Beschreibung, Herstellungsdatum)
			VALUES		(NULL, @Kunden_ID, "Quoddelpoddelmalerei", 'Quoddelpoddelmalerei.jpg', '444', '444', '6077,99', '72.32.126.211', '555', "Gequoddelt und rumgeschmiert", "01.05.1946");

SET @Kunstwerk_ID = LAST_INSERT_ID();
INSERT INTO eingeordnet_in VALUES (@Kunstwerk_ID, 119);
			
COMMIT;
