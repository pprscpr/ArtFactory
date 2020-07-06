-- Die CREATE TABLE von der Gruppe: Ernesto Cabrera Garcia, Jonas Wünsch, Stefan Riedl.
-- Die Website trägt den Namen ArtFactory. 
-- Grundlage für die Erstellung der CREATE TABLE ist das DataDictionary in der Version 3.


DROP DATABASE IF EXISTS artfactory_db;
CREATE DATABASE artfactory_db
  DEFAULT CHARACTER SET "utf8";

USE artfactory_db;

CREATE TABLE Kunde (
	Kunden_ID	SMALLINT	UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
	Anrede		ENUM( "Frau", "Herr", "Divers") NULL,
	Titel		VARCHAR(20)	NULL DEFAULT NULL, 
	Vorname		VARCHAR(40)	NOT NULL,
	Nachname	VARCHAR(60) NOT NULL,
	Strasse		VARCHAR(60)	NOT NULL,
	PLZ			INT(5)	UNSIGNED ZEROFILL NOT NULL,
	ORT			VARCHAR(60)	NOT NULL	
)	Engine = InnoDB;

CREATE TABLE Kuenstler (
	Kunden_ID 		SMALLINT	UNSIGNED PRIMARY KEY NOT NULL, 
	Kuenstlername	VARCHAR(20)	NULL DEFAULT NULL,
	IBAN			VARCHAR(34)	NOT NULL,
	BIC				VARCHAR(11)	DEFAULT NULL, 
	Vita           	TEXT        DEFAULT NULL,
	FOREIGN KEY 	(Kunden_ID)	REFERENCES Kunde (Kunden_ID)
)Engine = InnoDB;

CREATE TABLE Kontaktart (
	Art_ID		TINYINT 	UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
	Bezeichnung	ENUM( "Telefon", "Mobiltelefon", "E-Mail", "Fax")	NOT NULL
)Engine = InnoDB;

CREATE TABLE Kontakt (
	Kontakt_ID	TINYINT 	UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
	Kunden_ID 	SMALLINT 	UNSIGNED NOT NULL,
	Art_ID		TINYINT 	UNSIGNED NOT NULL,
	Kontakt 	TINYTEXT 	NOT NULL,
	Bemerkung	TINYTEXT 	NULL DEFAULT NULL,
	FOREIGN KEY (Kunden_ID) REFERENCES Kunde (Kunden_ID),
	FOREIGN KEY (Art_ID)	REFERENCES Kontaktart (Art_ID)
)Engine = InnoDB;

CREATE TABLE Kunstwerk (
	Kunstwerk_ID			SMALLINT		UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
	Kunden_ID 				SMALLINT 		UNSIGNED DEFAULT NULL, 
	Kuenstler_ID 			SMALLINT 		UNSIGNED NOT NULL,
	Titel 					VARCHAR(120) 	NOT NULL,
	Image					TINYTEXT		NOT NULL,
	Hoehe					SMALLINT(5)		NOT NULL,
	Breite					SMALLINT(5)		NOT NULL,
	Preis					DECIMAL(9,2)	NOT NULL, 
	Kauf_IP 				VARCHAR(39)		NULL DEFAULT NULL, 
	Kauf_Zeitstempel		DATETIME		NULL DEFAULT NULL,
	Einstell_IP				VARCHAR(39)		NOT NULL, 
	Einstell_Zeitstempel	TIMESTAMP 		NOT NULL DEFAULT CURRENT_TIMESTAMP,
	Gewicht					SMALLINT(5)		NOT NULL,
	Beschreibung			TEXT			NULL DEFAULT NULL,
	Herstellungsdatum		VARCHAR(10)		NULL DEFAULT NULL,	
	FOREIGN KEY 			(Kunden_ID)		REFERENCES Kunde (Kunden_ID),
	FOREIGN KEY 			(Kuenstler_ID)	REFERENCES Kuenstler(Kunden_ID)	
)Engine = InnoDB;

CREATE TABLE Kategorie (
	Kategorie_ID	TINYINT 	UNSIGNED AUTO_INCREMENT PRIMARY KEY NOT NULL,
	Beschreibung 	TEXT 		NULL DEFAULT NULL,
	Stilrichtung	VARCHAR(60)	NOT NULL
)Engine = InnoDB;

CREATE TABLE Login (
	Kunden_ID 		SMALLINT	UNSIGNED PRIMARY KEY NOT NULL, 
	Login			TINYTEXT 	NOT NULL,
	reg_Timestamp	TIMESTAMP 	NOT NULL DEFAULT CURRENT_TIMESTAMP,
	reg_IP 			VARCHAR(39)	NOT NULL, 
	Passwort		VARCHAR(64)	NOT NULL,
	FOREIGN KEY 	(Kunden_ID)	REFERENCES Kunde (Kunden_ID)
)Engine = InnoDB;

CREATE TABLE eingeordnet_in (
	Kunstwerk_ID 	SMALLINT 	UNSIGNED NOT NULL,
	Kategorie_ID 	TINYINT 	UNSIGNED NOT NULL,
	PRIMARY KEY 	(Kunstwerk_ID, Kategorie_ID),
	CONSTRAINT		FrKey_eingeordnet_in_Kunstwerk_ID
					FOREIGN KEY (Kunstwerk_ID)	REFERENCES Kunstwerk (Kunstwerk_ID),
	CONSTRAINT 		FrKey_eingeordnet_in_Kategorie_ID
					FOREIGN KEY (Kategorie_ID) 	REFERENCES Kategorie (Kategorie_ID)
)Engine = InnoDB;




