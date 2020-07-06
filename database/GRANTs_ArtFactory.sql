USE artfactory_db;
CREATE USER artfactory_Admin@'%'            IDENTIFIED BY 'B0SSM4N';
CREATE USER artfactory_Gast@'%'             IDENTIFIED BY 'gast';
CREATE USER artfactory_Kunde@'%'            IDENTIFIED BY '$4zahlenderKunde$4';
CREATE USER artfactory_Kuenst@'%'           IDENTIFIED BY '$4zahlender$4Kuenstler$4';
CREATE USER artfactory_Login@'%'            IDENTIFIED BY 'neuer$4zahlender$4Kunde$4';
CREATE USER artfactory_Admin@'localhost'    IDENTIFIED BY 'B0SSM4N';
CREATE USER artfactory_Gast@'localhost'     IDENTIFIED BY 'gast';
CREATE USER artfactory_Kunde@'localhost'    IDENTIFIED BY '$4zahlenderKunde$4';
CREATE USER artfactory_Kuenst@'localhost'   IDENTIFIED BY '$4zahlender$4Kuenstler$4';
CREATE USER artfactory_Login@'localhost'    IDENTIFIED BY 'neuer$4zahlender$4Kunde$4';


GRANT ALL 		
      ON artfactory_db.*
      TO artfactory_Admin@'%' 				WITH GRANT OPTION;
GRANT ALL 		
      ON artfactory_db.*
      TO artfactory_Admin@'localhost' 		WITH GRANT OPTION;

-- DROP USER artfactory_dbGast;
GRANT USAGE 	
      ON artfactory_db.*
      TO artfactory_Gast@'%';
GRANT USAGE 	
      ON artfactory_db.*
      TO artfactory_Gast@'localhost';
GRANT SELECT 	
      ON artfactory_db.Kategorie
      TO artfactory_Gast@'%';
GRANT SELECT 	
      ON artfactory_db.eingeordnet_in
      TO artfactory_Gast@'%';
GRANT SELECT 	
      ON artfactory_db.Kuenstler
      TO artfactory_Gast@'%';
GRANT SELECT 	
      ON artfactory_db.Kunstwerk
      TO artfactory_Gast@'%';
GRANT SELECT 	
      ON artfactory_db.Kategorie
      TO artfactory_Gast@'localhost';
GRANT SELECT 	
      ON artfactory_db.eingeordnet_in
      TO artfactory_Gast@'localhost';
GRANT SELECT 	
      ON artfactory_db.Kuenstler
      TO artfactory_Gast@'localhost';
GRANT SELECT 	
      ON artfactory_db.Kunstwerk
      TO artfactory_Gast@'localhost';


-- DROP USER artfactory_dbKunde;
GRANT USAGE 	
      ON artfactory_db.*
      TO artfactory_Kunde@'%';
GRANT USAGE 	
      ON artfactory_db.*
      TO artfactory_Kunde@'localhost';
GRANT SELECT    
      ON artfactory_db.Kuenstler
      TO artfactory_Kunde@'%';
GRANT SELECT    
      ON artfactory_db.Kunstwerk
      TO artfactory_Kunde@'%';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kontakt
      TO artfactory_Kunde@'%';
GRANT SELECT          
      ON artfactory_db.Kontaktart
      TO artfactory_Kunde@'%';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kunde
      TO artfactory_Kunde@'%';
GRANT SELECT          
      ON artfactory_db.Kategorie
      TO artfactory_Kunde@'%';
GRANT SELECT          
      ON artfactory_db.eingeordnet_in
      TO artfactory_Kunde@'%';

GRANT SELECT          
      ON artfactory_db.Kuenstler
      TO artfactory_Kunde@'localhost';
GRANT SELECT          
      ON artfactory_db.Kunstwerk
      TO artfactory_Kunde@'localhost';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kontakt
      TO artfactory_Kunde@'localhost';
GRANT SELECT          
      ON artfactory_db.Kontaktart
      TO artfactory_Kunde@'localhost';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kunde
      TO artfactory_Kunde@'localhost';
GRANT SELECT          
      ON artfactory_db.Kategorie
      TO artfactory_Kunde@'localhost';
GRANT SELECT          
      ON artfactory_db.eingeordnet_in
      TO artfactory_Kunde@'localhost';


-- DROP USER KunstKuenster;
GRANT USAGE 		  
      ON artfactory_db.*
      TO artfactory_Kuenst@'%';
GRANT USAGE 		  
      ON artfactory_db.*
      TO artfactory_Kuenst@'localhost';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kuenstler
      TO artfactory_Kuenst@'%';
GRANT ALL             
      ON artfactory_db.Kunstwerk
      TO artfactory_Kuenst@'%';
GRANT ALL             
      ON artfactory_db.Kontakt
      TO artfactory_Kuenst@'%';
GRANT SELECT          
      ON artfactory_db.Kontaktart
      TO artfactory_Kuenst@'%';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kunde
      TO artfactory_Kuenst@'%';
GRANT SELECT          
      ON artfactory_db.Kategorie
      TO artfactory_Kuenst@'%';
GRANT SELECT          
      ON artfactory_db.eingeordnet_in
      TO artfactory_Kuenst@'%';

GRANT SELECT, UPDATE  
      ON artfactory_db.Kuenstler
      TO artfactory_Kuenst@'localhost';
GRANT ALL             
      ON artfactory_db.Kunstwerk
      TO artfactory_Kuenst@'localhost';
GRANT ALL             
      ON artfactory_db.Kontakt
      TO artfactory_Kuenst@'localhost';
GRANT SELECT          
      ON artfactory_db.Kontaktart
      TO artfactory_Kuenst@'localhost';
GRANT SELECT, UPDATE  
      ON artfactory_db.Kunde
      TO artfactory_Kuenst@'localhost';
GRANT SELECT          
      ON artfactory_db.Kategorie
      TO artfactory_Kuenst@'localhost';
GRANT SELECT          
      ON artfactory_db.eingeordnet_in
      TO artfactory_Kuenst@'localhost';

-- DROP USER artfactory_dbLogin;
GRANT USAGE 		  
      ON artfactory_db.*
      TO artfactory_Login@'%';
GRANT USAGE 		  
      ON artfactory_db.*
      TO artfactory_Login@'localhost';
GRANT INSERT          
      ON artfactory_db.Kunde
      TO artfactory_Login@'%';
GRANT SELECT, UPDATE, INSERT  
      ON artfactory_db.Login
      TO artfactory_Login@'%';
GRANT INSERT          
      ON artfactory_db.Kunde
      TO artfactory_Login@'localhost';
GRANT SELECT, UPDATE, INSERT  
      ON artfactory_db.Login
      TO artfactory_Login@'localhost';