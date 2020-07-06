<?php
include_once 'pic_functions.inc';
/*! \file db_funcs.inc
    \brief Alle Funktionalitäten für DB-Abfragen
    
    Diese Include-Datei enthält all Funktionalitäten für
    DB-Zugriffe und deren Ergebnisse.

    Alle Rückgabewerte dieser Funktionen müssen DB-unabhängig sein.
*/
define ( "__INC_DBFUNCS__", 1 );
define ( "ART_HOST", "localhost" );
define ( "ART_DB",   "artfactory_db" );


/*! \brief stellt eine Verbindung zum DBServer her
    \param $user ein gültiger User muss übergeben werden
    \return eine gültige Datenbankverbindung oder im Fehlerfall: false
*/
function ConnectArtDB( $user )
{
  switch (  $user )
  {
    //case "admin" :    $user   = "artadmin";
      //                $passwd = "artdummy";
        //              break;
    //case "gast"  :    $user   = "artdummy";
      //                $passwd = "artdummy";
        //              break;
    case "Admin"  :   $user   = "artfactory_Admin";
                      $passwd = "B0SSM4N";
                      break;
    case "Gast"  :    $user   = "artfactory_Gast";
                      $passwd = "gast";
                      break;
    case "Kunde"  :   $user   = "artfactory_Kunde";
                      $passwd = "$4zahlenderKunde$4";
                      break;
    case "Kuenstler": $user   = "artfactory_Kuenst";
                      $passwd = "$4zahlender$4Kuenstler$4";
                      break;
    case "Login"  :   $user   = "artfactory_Login";
                      $passwd = "neuer$4zahlender$4Kunde$4";
                      break;                                                                            
    default      :    $user   = "no_user";
                      $passwd = NULL;
  }
  // Verbindung zum DB-Server aufbauen
  //(host, DB-User, DB-User-Pw, Datenbankname)
  $dbconn = new mysqli (ART_HOST, $user, $passwd, ART_DB);
  // Verbindung fehlgeschlagen
  if ( $dbconn->connect_error ) {
    echo "<b>Verbindung fehlgeschlagen:</b>". $dbconn->connect_errno .
              ": ". $dbconn->connect_error;
    $dbconn = false;
  }
  // Debugging-Ausgabe :
  else { 
    if ( defined(__MYDEBUG__) && __MYDEBUG__ )
      echo "<b>Verbindung zum DB-Server hergestellt</b> ".$dbconn->host_info;
  }
  $dbconn->query("SET NAMES utf8");
 
  return $dbconn;
}


/*! \brief Holt eine UserID anhand der Login-Daten aus der DB

    \param $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $LoginArr    das Array, wo die Anmeldedaten herkommen
    \return eine UserID als Ganzzahl im Erfolgsfall
            NULL sonst
*/
function GetUIDByLogin( $dbconn, $LoginArr ) { 
  $pre_stmt = $dbconn->stmt_init();

  $SQL_String = "SELECT Kunden_ID".
                     " FROM Login".
                     " WHERE Login = ? AND Passwort =SHA2(? , 256)";

   if( $pre_stmt->prepare($SQL_String) ){
            $pre_stmt->bind_param("ss", $LoginArr['login'], $LoginArr['passwd']);
            $pre_stmt->execute();
            $pre_stmt->bind_result($uid);
      if( $pre_stmt->fetch() ){
          $dbconn->close();
          return $uid;
      }
      else{
          $dbconn->close();
          return false;
      }

   }
   else {//Fehler!
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";

  }
  $dbconn->close();
}

function GetLoginData($dbconn){

    

}


/*! \brief Gibt den Hashwert eines Users anahand seiner uid wieder
    \param $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $uid eine gültige user ID
    \return $pw ein Hashwert des Passwortes , sonst false
*/
function GetHashedPW( $dbconn, $uid ) { 
  $pre_stmt = $dbconn->stmt_init();

  $SQL_String = "SELECT Passwort".
                     " FROM Login".
                     " WHERE KUNDEN_ID = ? ";

   if( $pre_stmt->prepare($SQL_String) ){
            $pre_stmt->bind_param("i", $uid);
            $pre_stmt->execute();
            $pre_stmt->bind_result($pw);
          
      if( $pre_stmt->fetch() ){
          $dbconn->close();
          return $pw;
      }
      else{
          $dbconn->close();
          return false;
      }

   }
   else {//Fehler!
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";

   }
  ;
}



/*! \brief Fügt bei einer Regestrierung eines neuen Kunden : Kunden , Kontakt, Login Daten ein.
    \detail Diese Funktion ist für die Regestrierung eines neuen Kunden.
            Die erfassten Daten des Kunden werden in die DB-Tab. Kunde, Kontakt, Login 
            geschrieben. Vorher werden die Daten auf Plausibilität überprüft um falsche 
            oder gar bösartigen Input zu vermeiden.
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \return ein Errorstring mit Fehlerbeschreibung, sonst String :"Regestrierung von (loginname) erfolgreich"
*/
function ArtInsertNewUser($dbconn){
     $Errorstring = "";
     $Password = "";
     $PasswordConfirm = "";

     if(isset($_POST['register'])){ 
        unset($_POST['register']);
        $Anrede          = $_POST['reg']['Anrede'];
        $Titel           = $_POST['reg']['Titel'];
        $Vorname         = $_POST['reg']['Vorname'];
        $Nachname        = $_POST['reg']['Nachname'];
        $LoginName       = $_POST['reg']['loginname'];
        $Password        = $_POST['reg']['password'];
        $PasswordConfirm = $_POST['reg']['password-confirm'];
        $Strasse         = $_POST['reg']['Strasse'];
        $PLZ             = $_POST['reg']['PLZ'];
        $Ort             = $_POST['reg']['Ort'];
        $KontaktArt      = $_POST['reg']['KontaktArt'];
        $Kontakt         = $_POST['reg']['Kontakt'];
        $Bemerkung       = $_POST['reg']['Bemerkung'];
        $ip              = $_SERVER['REMOTE_ADDR'];

        // DB Abfrage nach vorhandenen Usernamen
        $SQL_String = "SELECT Login FROM login ";

        $res = $dbconn->query($SQL_String);
        if(!$res){
          if(defined("__MYDEBUG__") && __MYDEBUG__){
            echo "Fehler bei Abfrage".$SQL_String." ".$dbconn->error." ".$dbconn->errno;
          }
          
        }
        while( $ds = $res->fetch_assoc() ){
          $log_array[] = $ds;
        }
        $res->close();

        // Wurden alle Pflichtfelder ausgefüllt ?
        if(empty($Anrede) || empty($Vorname) || empty($Nachname) || empty($Strasse) || empty($PLZ) || empty($Ort)|| empty($LoginName) || empty($Password) || empty($PasswordConfirm) || empty($Kontakt) || empty($KontaktArt) ){
            $Errorstring = "Es wurden nicht alle Felder ausgefüllt.";        
            return $Errorstring;
            exit();
        }
        else{
            // befinden sich Sonderziechen oder Ziffern im Titel  ?
            if(!preg_match("/^[a-zA-Z\.]*$/", $Titel)) {
                $Errorstring = "Keine Sonderzeichen oder Ziffern im Titel benutzen! ";        
                return $Errorstring;
                exit();
            }
            // befinden sich Sonderziechen oder Ziffern im Vorname  ?
            if(!preg_match("/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$/", $Vorname)) {
                $Errorstring = "Keine Sonderzeichen oder Ziffern im Vorname benutzen! ";        
                return $Errorstring;
                exit();
            }
            // befinden sich Sonderziechen oder Ziffern im Nachnamen  ?
            if(!preg_match("/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$/", $Nachname)) {
                $Errorstring = "Keine Sonderzeichen oder Ziffern im Nachnamen benutzen! ";        
                return $Errorstring;
                exit();
            }
            // befinden sich Sonderziechen im Loginnamen ?
            if(!preg_match("/^[a-zA-Z0-9]*$/", $LoginName)) {
                $Errorstring = "Keine Sonderzeichen im Loginnamen benutzen! ";        
                return $Errorstring;
                exit();
            }
            // gibt es den Usernamen schon ?
            if( CheckIfLoginExists($log_array,$LoginName) ){
                $Errorstring = "Ein User mit diesen Login-Namen existiert bereits! ";        
                return $Errorstring;
                exit();
            }
            // Ist die Strassenname gültig ?
            if(!preg_match("/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\s\.]*[0-9]*[a-z]*$/", $Strasse)) {
                $Errorstring = "Kein gültiger Strassenname! ";        
                return $Errorstring;
                exit();
            }
            // befinden sich Sonderziechen im Ort ?
            if(!preg_match("/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\s]*$/", $Ort)) {
                $Errorstring = "Keine Sonderzeichen oder Ziffern im Ort benutzen! ";        
                return $Errorstring;
                exit();
            }
            // ist die PLZ gülig ?
            if(!preg_match("/^[0-9]{5,5}$/", $PLZ)) {
                $Errorstring = "Keine gültige Postleitzahl! ";        
                return $Errorstring;
                exit();
            }
            // Stimmen die Passwörter überein ?
            else if($Password != $PasswordConfirm){
                $Errorstring = "Passwörter stimmen nicht überein! ";        
                return $Errorstring;
                exit();
            }
            // Kontaktangabe überprüfen
            // Telefonnummer nur Ziffern ?
            if($KontaktArt==1){
                if(!preg_match("/^[0-9]{6,18}$/", $Kontakt)) {
                  $Errorstring = "Telefonnummer darf nur aus Zahlen bestehen und mind 6-18 Ziffern beinhalten! ";        
                  return $Errorstring;
                  exit();
                }
            }
            // Mobilnummer nur Ziffern ?
            elseif($KontaktArt==2){
                if(!preg_match("/^[0-9]{6,18}$/", $Kontakt)) {
                    $Errorstring = "Mobiltelefonnummer darf nur aus Zahlen bestehen und mind 6-18 Ziffern beinhalten! ";        
                    return $Errorstring;
                    exit();
                }

            }
            // Emailadresse gültig ?
            elseif($KontaktArt==3){
                if(!filter_var($Kontakt, FILTER_VALIDATE_EMAIL)){
                    $Errorstring = "Email-Adresse ist nicht korrekt!";        
                    return $Errorstring;
                    exit();
                }
            }
            // Faxnummer nur Ziffern ?
            elseif($KontaktArt==4){
                if(!preg_match("/^[0-9]{6,18}$/", $Kontakt)) {
                    $Errorstring = "Faxnummer darf nur aus Zahlen bestehen und mind 6-18 Ziffern beinhalten! ";        
                    return $Errorstring;
                    exit();
                }

            }
        }

        // Kundedaten  in Datenbank einfügen 
        $dbconn->begin_transaction(MYSQLI_TRANS_START_READ_WRITE); 
        $pre_stmt = $dbconn->stmt_init();       
        $SQL_StringKunde = "INSERT INTO Kunde (Anrede, Titel, Vorname, Nachname, Strasse, PLZ, ORT)". 
                       " VALUES  (?, ?, ?, ?, ?, ?, ?);";

        if($pre_stmt->prepare($SQL_StringKunde)){
            $pre_stmt->bind_param('sssssss',$Anrede,$Titel,$Vorname,$Nachname,$Strasse,$PLZ,$Ort);
            $pre_stmt->execute();
            $last_ID = mysqli_insert_id($dbconn);
            $pre_stmt->close();
        }
        else{ // Fehler Kundendaten einfügen!
          $Errorstring = "Fehler beim Registriervorgang Code:1 ";
          if ( defined("__MYDEBUG__") && __MYDEBUG__ ){ 
                echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
                $SQL_StringKunde."<br />".
                $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
          }
        }

        // Kontaktdaten in Datenbank einfügen
        $pre_stmt2 = $dbconn->stmt_init();              
        $SQL_StringKontakt = "INSERT INTO Kontakt (Art_ID, Kunden_ID, Kontakt, Bemerkung)".
                       " VALUES  (?, ?, ?, ?);";

        if($pre_stmt2->prepare($SQL_StringKontakt)){
            $pre_stmt2->bind_param('iiss',$KontaktArt, $last_ID, $Kontakt, $Bemerkung);
            $pre_stmt2->execute(); 
            $pre_stmt2->close();
        }
        else{ // Fehler Kontaktdaten einfügen!
             $Errorstring = "Fehler beim Registriervorgang Code:2 ";
             if ( defined("__MYDEBUG__") && __MYDEBUG__ ){ 
                echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
                $SQL_StringKontakt."<br />".
                $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
             }
        }

        // Logindaten  in Datenbank einfügen
        $pre_stmt3 = $dbconn->stmt_init();
        $SQL_StringLogin = "INSERT INTO Login   (Kunden_ID, Login, reg_IP, Passwort)".
                "VALUES  (?, ?, ?, SHA2(? , 256));";
                      
        if($pre_stmt3->prepare($SQL_StringLogin)){
            $pre_stmt3->bind_param('isss', $last_ID, $LoginName, $ip, $Password);
            $pre_stmt3->execute();  
            $pre_stmt3->close();
        }
        
        else{ // Fehler Logindaten einfügen!
          $Errorstring = "Fehler beim Registriervorgang Code:3 ";
          if ( defined("__MYDEBUG__") && __MYDEBUG__ ){ 
                echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
                $SQL_StringLogin."<br />".
                $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
           }

        }
        $dbconn->commit();
        $dbconn->close();
        // Variablen und Posts zurücksetzen
          $Errorstring .= "Registriervorgang  von ".$LoginName." erfolgreich !";
          
          unset($_POST['reg']);
          unset($_POST['register']);
          unset($LoginName);
          unset($Password);
          unset($PasswordConfirm);
          unset($Strasse);
          unset($KontaktArt);
          unset($Kontakt);
          unset($Bemerkung);
          unset($Anrede);
          unset($Titel);
          unset($Vorname);
          unset($Nachname);
          unset($Strasse);
          unset($PLZ);
          unset($Ort);

    }
    return $Errorstring;
}


/*! \brief Fügt ein neues Kunswerk  inklusive aller notwendigen Daten ein.
    \detail Diese Funktion pflegt ein neues Kunstwerk ein beinhaltet 
    hochladen des Bilder in pic/big/(bildname).png
                            pic/small(bildname).png
    und hinzufügen der Datensätze (Kunden_ID, Kuenstler_ID ,Titel,Image,Hoehe,
    Breite,Preis, Einstell_IP,Gewicht, Beschreibung,Herstellungsdatum)

    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \return ein Errorstring mit Fehlerbeschreibung,
*/
function InsertNewPicture($dbconn){
  $error ="";
  if( isset($_POST['submit_all']) ){  
    $uid = ($_SESSION['login']['uid']); 
    $pic_name=$_POST['picName'];
    $height = $_POST['height'];
    $width = $_POST['width'];
    $price = $_POST['price'];
    $ip = $_SERVER['REMOTE_ADDR'];
    $weight = $_POST['weight'];
    $descr = $_POST['descr'];
    $date = $_POST['date'];
    $style = $_POST['style'];
    $kunde_id = NULL;

    if(empty($uid) || empty($pic_name) || empty($height) || empty($width) || empty($price)|| empty($weight) || 
       empty($descr) || empty($date) ){
          $error = "Nicht alle Felder ausgefüllt";        
          return $error;
          exit();
    } 
    else{// enthält der Bildname Sonderzeichen ?
      if( !preg_match("/[\w ]*/", $pic_name) ){
          $error = "Der Bildname darf keine Sonderzeichen enthalten!";
          return $error;
          exit();
      }
      // enthält Höhe nur Ziffern ?
      if( !preg_match("/^[0-9]*$/", $height) ){
          $error = "Höhe darf nur Ziffern enthalten!";
          return $error;
          exit();
      }
      // enthält Breite nur Ziffern ?
      if( !preg_match("/^[0-9]*$/", $width) ){
          $error =  "Breite darf nur Ziffern enthalten!";;
          return $error;
          exit();
      }
      // enthält Preis nur Ziffern oder .,  ?
      if( !preg_match("/[0-9]{1,10}(\.||\,){1,1}[0-9]{2,2}/", $price) ){
          $error = "Der Preis darf nur Ziffern und oder . ; enthalten!";
          return $error;
          exit();
      }
      // enthält das Gewicht nur Ziffern ?
      if( !preg_match("/^[0-9]*$/", $weight) ){
          $error = "Das Gewicht darf nur Ziffern enthalten! ";
          return $error;
          exit();
      }
      // enthält die Beschreibung nicht zulässige Sonderzeichen ?
      if( !preg_match("/[\w\s ]+/", $descr) ){
          $error = "Die Beschreibung darf keine Sonderzeichen wie (; \ {} []) enthalten!";
          return $error;
          exit();
      }
      // Entspricht das Datum dem richtigen Format ?
      if( !preg_match("/^[0-9]{1,2}\.([0-9]{2,2}||(Jan||Feb||Mar||Apr||Mai||Juni||Juli||Aug||Sep||Nov||Dec))\.[0-9]{2,4}$/", $date) ){
          $error = "Das Gewicht darf nur Ziffern enthalten! ";
          return $error;
          exit();
      }

    }
     // Bild hochladen und Bildname Variable speichern
    $file = UploadPicCreateResizedPics();
      
    // Kunstwerkdaten einfügen
    $SQL_String_Kunstwerk = "INSERT INTO Kunstwerk (Kunden_ID,".
                                                   "Kuenstler_ID,".
                                                   "Titel,".
                                                   "Image,".
                                                   "Hoehe,".
                                                   "Breite,".
                                                   "Preis,".
                                                   "Einstell_IP,".
                                                   "Gewicht,".
                                                   "Beschreibung,".
                                                   "Herstellungsdatum)".

    "VALUES    ( ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);";

    $dbconn->begin_transaction(MYSQLI_TRANS_START_READ_WRITE);
    $pre_stmt = $dbconn->stmt_init();      

    if( $pre_stmt->prepare($SQL_String_Kunstwerk) ){
          $pre_stmt->bind_param('iisssssssss',$kunde_id ,$uid, $pic_name, $file, $height, $width, $price, $ip , $weight, $descr, $date);
          $pre_stmt->execute();
          $last_ID = mysqli_insert_id($dbconn);
          $pre_stmt->close();
      }
      else{ //Fehler Kunsterwerk einfügen!
        $error = "Fehler beim Kunstwerk einfügen";
        if ( defined("__MYDEBUG__") && __MYDEBUG__ ){ 
              echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
              $SQL_StringKunde."<br />".
              $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";         
        }
      }
      // Kunsterwerk in Kategorie einordnen *
      $SQL_String_eingeordnet = "INSERT INTO eingeordnet_in VALUES ( ?, ?)";

      $pre_stmt2 = $dbconn->stmt_init();

      if( $pre_stmt2->prepare($SQL_String_eingeordnet) ){
        $pre_stmt2->bind_param("is", $last_ID, $style);
        $pre_stmt2->execute();
        $pre_stmt2->close();
      }
      else { // Fehler beim einordnen in Kategorie
        $error = "Fehler beim einordnen in Kategorie";
        if ( defined("__MYDEBUG__") && __MYDEBUG__ ){ 
              echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
              $SQL_StringKunde."<br />".
              $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
             
        }
      }
      $dbconn->commit();
      $dbconn->close();   
      return $error;
  }          
}


/*! \brief Fügt ein die notwendigen Datensätze eines Kuenstlers ein.
    \detail Fügt ein die notwendigen Datensätze eines Kuenstlers ein
     : IBAN , BIC, Kuenstlername, Vita

    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \return ein Errorstring mit Fehlerbeschreibung,
*/
function becomeArtist($dbconn){
  $error ="";
  if(isset($_POST['becomeArtist'])){
      $uid = $_SESSION['login']['uid'];
      $IBAN =$_POST['IBAN'];
      $BIC =$_POST['BIC'];
      $Kuenstlername =$_POST['Kuenstlername'];
      $Vita =$_POST['Vita'];

      // Wurden alle Pflichtfelder ausgefüllt ?
        if( empty($uid) || empty($IBAN)  || empty($Kuenstlername) ){
            $error = "Nicht alle Pflichtfelder ausgefüllt! IBAN und Künstlername müssen ausgefüllt sein.";        
            return $error;
            exit();
        }
        else{
          // befinden sich Sonderziechen in der IBAN  ?
            if(!preg_match("/^[a-zA-Z0-9]*$/", $IBAN)) {
                $error = "Die IBAN darf keine Sonderzeichen enthalten! ";        
                return $error;
                exit();
            }// befinden sich Sonderziechen in der BIC ?
            if(!preg_match("/^[a-zA-Z0-9]*$/", $BIC)) {
                $error = "Die BIC darf keine Sonderzeichen enthalten! ";        
                return $error;
                exit();
            }// befinden sich Sonderziechen im Künstlernamen ?
            if(!preg_match("/^[a-zA-Z0-9]*$/", $Kuenstlername)) {
                $error = "Der Kuenstlername darf keine Sonderzeichen enthalten! ";        
                return $error;
                exit();
            }// befinden sich Sonderziechen in der Vita ?
            if(preg_match("/^[;\{}[]]*$/", $Vita)) {
                $error = "Die Vita darf keine Sonderzeichen wie (; \ {} []) enthalten! ";        
                return $error;
                exit();
            }
      }      

      $SQL_String_Kuenstler = "INSERT INTO Kuenstler (Kunden_ID, Kuenstlername, IBAN, BIC, Vita)".
          "VALUES    (?, ?, ?, ?, ?);";

      $pre_stmt = $dbconn->stmt_init();
      if( $pre_stmt->prepare($SQL_String_Kuenstler) ){
        $pre_stmt->bind_param("issss", $uid, $Kuenstlername, $IBAN, $BIC, $Vita);
        $pre_stmt->execute();
        $pre_stmt->close();
        $error = "Registrierung erfolgreich, sie sind jetzt Künstler.";
      }
      else{
        $error = "Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
        if( defined("__MYDEBUG__")&& __MYDEBUG__){
          echo "<div><b>Abfrage fehlgeschlagen</b><br />".
          $SQL_StringKunde."<br />".
          $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
            
        }

      }
   unset($_POST);
  }
  $dbconn->close();
 return $error;
}

/*! \brief Fügt neue Kunden_ID, Kauf_IP, Kauf_Zeitstempel zum Kunswerk hinzu.Kunstwerk ist verkauft
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param  $picture_id eine gültige Kunstwerk_ID, welches Kunstwerk wird verkauft ?
    \param  $user_id eine gültige userID , wer kauft das Kunstwerk ?
    \return ein Errorstring mit Fehlerbeschreibung,
*/
function BuyPicture($dbconn,$picture_id,$user_id){
  $error ="";
  if(isset($_POST['submit'])){
      $uid = $_SESSION['login']['uid'];
      $ip  =$_SERVER['REMOTE_ADDR'];
      $time_stamp =date("Y/m/d H:i:s");
    
      $SQL_String_Kunstwerk = "UPDATE Kunstwerk SET Kunden_ID = ?, Kauf_IP = ?, Kauf_Zeitstempel = ? WHERE Kunstwerk_ID = ?" ;

      $pre_stmt = $dbconn->stmt_init();
      if( $pre_stmt->prepare($SQL_String_Kunstwerk) ){
        $pre_stmt->bind_param("issi", $user_id, $ip, $time_stamp, $picture_id);
        $pre_stmt->execute();
        $pre_stmt->close();
        $error = "Glückwundsch Sie haben das Bild gekauft!";
      }
      else{
        $error = "Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
        if( defined("__MYDEBUG__")&& __MYDEBUG__){
          echo "<div><b>Abfrage fehlgeschlagen</b><br />".
          $SQL_StringKunde."<br />".
          $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
         
        }

      }
  }
  $dbconn->close();
  return $error;
}

/*! \brief DB-Abfrage der User ein Kuenstler ist
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \return $bool true wenn er ein Kuenstler ist, sonst false
*/
function isUserAnArtist($dbconn){
  $bool = false;
  if( isset($_SESSION['login']['uid']) ){
      $uid = $_SESSION['login']['uid'];
      $SQL_String = "SELECT Kunden_ID FROM Kuenstler";
      $res =  $dbconn->query( $SQL_String );

      if(!$res){
        if(defined("__MYDEBUG__")&&__MYDEBUG__){
          echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
            $SQL_String."<br />".
            $dbconn->errno . ": " . $dbconn->error . "</div>";
        }
        $bool = false;
      }
      
      while($ds = $res->fetch_assoc() ){
        if($ds['Kunden_ID']==$uid){
         //echo $ds['Kunden_ID'];
         $bool = true;
        }
      }
    $res->close();   
  }
  $dbconn->close();
  return $bool;
}



/*! \brief DB-Abfrage auf Alle Datensätze in Kategorie.
    \param $dbconn eine gültige msqli Datenbank-Verbindung.
    \return $array gibt ein fertig befülltes Array mit den Inhalt von Kategorie aus.
*/
function GetStyles( $dbconn ){
  
  $SQL_String="SELECT * FROM kategorie ORDER BY Kategorie_ID ASC";

  $erg = $dbconn->query( $SQL_String );

  if ( !$erg ){
    if ( defined("__MYDEBUG__") && __MYDEBUG__ )
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    $dbconn->close();
    return NULL;
  }

  while (  $ds = $erg->fetch_assoc() )
    $array[] = $ds;
  
  $dbconn->close();
  return $array;
}



/*! \brief  DB-Abfrage auf die KontaktartID und die Bezichnung Datensätze in Kontaktart.
    \param $dbconn eine gültige msqli Datenbank-Verbindung.
    \return $array gibt ein fertig befülltes Array mit den Inhalt von Kontaktarten aus.
*/
function GetKontaktart( $dbconn ){
  
  $SQL_String="SELECT Art_ID,Bezeichnung FROM Kontaktart";

  $erg = $dbconn->query( $SQL_String );

  if ( !$erg ){
    if ( defined("__MYDEBUG__") && __MYDEBUG__ )
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    $dbconn->close();
    return NULL;
  }

  while (  $ds = $erg->fetch_assoc() )
    $array[] = $ds;

  $dbconn->close();
  return $array;
}




// Alle unverkauften Bilder inkl Datensätze ausgeben geordnet nach $switch
/*! \brief  DB-Abfrage auf alle unverkauften Bilder sortiert nach $switch "All"= Preis aufst., "New" = neueste zuerst, "Artist"= Kuenstler sortiert  .
      
    Abgefragte Datensätze sind : Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername
    \param $dbconn eine gültige msqli Datenbank-Verbindung.
    \param $switch Bilder sortiert nach : "All"= Preis aufst., "New" = neueste zuerst, "Artist"= Kuenstler sortiert.
    \return $array gibt ein fertig befülltes Array mit den DS von Kunstwerk aus .
*/
function GetImages( $dbconn ,$switch) {
  // ist der Kuenstler eingelogged soll er nicht seine eigenen Kunstwerke sehen/kaufen können
  if( isset($_SESSION['login']['uid']) ){
    $uid = $_SESSION['login']['uid'];
    switch ($switch) {
      case 'All':
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername".
          " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID ".
          " WHERE kunstwerk.KUNDEN_ID IS NULL AND Kuenstler_ID != ".$uid.
          " ORDER BY kunstwerk.Preis ASC";
        break;
      case 'New':
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername ".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        " WHERE kunstwerk.KUNDEN_ID IS NULL AND Kuenstler_ID != ".$uid.
                        " ORDER BY Einstell_Zeitstempel DESC";
        break;
       case 'Artist':
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername ".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        " WHERE kunstwerk.KUNDEN_ID IS NULL AND Kuenstler_ID != ".$uid.
                        " ORDER BY Kuenstlername ASC"; 
                        
        break;
      
      default:
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        "  WHERE kunstwerk.KUNDEN_ID IS NULL AND Kuenstler_ID != ".$uid." ";
        break;
    }
  }
  else { // ist ein user nicht eingelogged sieht er alle verfügbaren Bilder die zum Verkauf stehen
    switch ($switch) {
      case 'All':
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        " WHERE kunstwerk.KUNDEN_ID IS NULL".
                        " ORDER BY kunstwerk.Preis ASC";
        break;
      case 'New':
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername ".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        " WHERE kunstwerk.KUNDEN_ID IS NULL".
                        " ORDER BY Einstell_Zeitstempel DESC";
        break;
       case 'Artist':
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID,Kuenstlername ".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        " WHERE kunstwerk.KUNDEN_ID IS NULL ".
                        " ORDER BY Kuenstlername ASC";
        break;
      
      default:
          $SQL_String = "SELECT Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Kunstwerk_ID".
                        " FROM kunstwerk INNER JOIN kuenstler ON kunstwerk.Kuenstler_ID = kuenstler.Kunden_ID".
                        " WHERE kunstwerk.KUNDEN_ID IS NULL";
        break;
    }
  }
  
  $res = $dbconn->query( $SQL_String );
  if( !$res ){
    if( defined("__MYDEBUG__") && __MYDEBUG__ ){
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    }
    $dbconn->close();
    return false;
  }
  while ( $ds = $res->fetch_assoc() ){
    $array[] = $ds;

  }
  $res->close();
  $dbconn->close();

  if( !empty($array) ){
     return $array;
  }
  else {
     return NULL;
  }

}

/*! \brief DB-Abfrage ob ein Kunstwerk verkauft wurde
    \detail Wenn 2 User sich gleichzeitig um ein Bild bewerben, muss kurz vor dem Bestätigen des Kaufs
            noch einmal abgefragt werden ob das Bild schon währendessen verkauft wurde.
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $picture_id Um welches Kunstwerk handelt es sich (Kunstwerk_ID)
    \return String ob ob das Bild schon verkauft wurde
*/
function PictureAlreadySold($dbconn,$picture_id){
  $SQL_String = "SELECT Image,Kunstwerk_ID FROM kunstwerk WHERE Kunstwerk_ID = \"".$picture_id."\" AND Kunden_ID IS NULL";

  $res = $dbconn->query( $SQL_String );
  if( !$res ){
    if( defined("__MYDEBUG__") && __MYDEBUG__ ){
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    }
    $dbconn->close();
    return"Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
  }
  while ( $ds = $res->fetch_assoc() ){
   if($ds['Kunstwerk_ID']==$picture_id)
      return "vorhanden";

  }

  $dbconn->close();
  return "Leider ist das Bild nicht mehr verfügbar.";
}

/*! \brief DB-Abfrage welche Bilder der User schon gekauft hat
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $user_id eine gültige UserID "Kunden_ID"
    \return ein befülltes Array mit den DS zu den erworbenen Bildern ,bei Fehler false, wenn keine Bilder vorh. dann NULL
*/
function PicturesIBought($dbconn,$user_id){
  $SQL_String =" SELECT   Kuenstlername,Titel,Image,Kauf_Zeitstempel ".
               " FROM  Kuenstler INNER JOIN Kunstwerk ON Kuenstler.Kunden_ID = Kunstwerk.Kuenstler_ID ".
               " WHERE   kunstwerk.Kunden_ID = " .$user_id. ";";
  
  $res = $dbconn->query( $SQL_String );
  if( !$res ){
    if( defined("__MYDEBUG__") && __MYDEBUG__ ){
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    }
    $dbconn->close();
    return false;
  }
   while ( $ds = $res->fetch_assoc() ){
    $array[] = $ds;

  }
  $dbconn->close();
  if( !empty($array) ){
     return $array;
  }
  else {
     return NULL;
  }

}

/*! \brief DB-Abfrage auf die Eigenschaften eines Users die geändert werden können
    \details gibt die Eigenschaften eines User wieder, die im nachhinein wieder geändert werden können (Profildaten bearbeiten)
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $user_id eine gültige UserID "Kunden_ID"
    \return ein befülltes Array mit den DS zu den Eigenschaften eines Users, bei Fehler false, wenn keine vorhanden dann NULL
*/
function UserProperties ($dbconn, $user_id){
  $SQL_String = "SELECT  Anrede, Titel, Vorname, Nachname, Strasse, PLZ, ORT FROM Kunde WHERE Kunden_ID = ".$user_id;
  $res = $dbconn->query( $SQL_String );
  if( !$res ){
    if( defined("__MYDEBUG__") && __MYDEBUG__ ){
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    }
    $dbconn->close();
    return false;
  }
  while ( $ds = $res->fetch_assoc() ){
    $array[] = $ds;
  }
  $dbconn->close();
  if( !empty($array) ){
     return $array;
  }
  else {
     return NULL;
  }
}

/*! \brief DB-Abfrage auf die Eigenschaften eines Künstlers die geändert werden können
    \details gibt die Eigenschaften eines Künstlers wieder, die im nachhinein wieder geändert werden können (Profildaten bearbeiten)
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $user_id eine gültige UserID "Kunden_ID"
    \return ein befülltes Array mit den DS zu den Eigenschaften eines Künstlers, bei Fehler false, wenn keine vorhanden dann NULL
*/
function ArtistProperties ($dbconn, $user_id){
  $SQL_String = "SELECT IBAN,Kuenstlername,BIC,Vita FROM kuenstler WHERE Kunden_ID = ".$user_id;
  $res = $dbconn->query( $SQL_String );
  if( !$res ){
    if( defined("__MYDEBUG__") && __MYDEBUG__ ){
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    }
    $dbconn->close();
    return false;
  }
  while ( $ds = $res->fetch_assoc() ){
    $array[] = $ds;
  }
  $res->close();
  $dbconn->close();
  if( !empty($array) ){
     return $array;
  }
  else {
     return NULL;
  }
}





/*! \brief DB-Abfrage auf die Eigenschaften eines Kunstwerkes das ein Künstler eingestellt hat und welches noch nicht verkauft ist
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $user_id eine gültige UserID "Kunden_ID"
    \return ein befülltes Array mit den DS zu den Eigenschaften des Kunstwerkes, bei Fehler false, wenn keine vorhanden dann NULL
*/
function ArtistPictures($dbconn,$user_id){
  $SQL_String = "SELECT Kunstwerk_ID,Preis,Titel,Image,Hoehe,Breite,Gewicht,Beschreibung,Herstellungsdatum,Einstell_Zeitstempel FROM kunstwerk WHERE KUNDEN_ID IS NULL AND Kuenstler_ID = ".$user_id. ";";

  $res = $dbconn->query( $SQL_String );
  if( !$res ){
    if( defined("__MYDEBUG__") && __MYDEBUG__ ){
      echo "<div><b>Abfrage fehlgeschlagen!</b><br />".
        $SQL_String."<br />".
        $dbconn->errno . ": " . $dbconn->error . "</div>";
    }
    return false;
  }
  while ( $ds = $res->fetch_assoc() ){
    $array[] = $ds;
  }
  $res->close();
  $dbconn->close();
  if( !empty($array) ){
     return $array;
  }
  else {
     return NULL;
  }
}


/*! \brief DB-Abfrage : Ändert die Eigenschaften eines vorhanden Kunstwerkes 
    \details zum ändern der Daten eines Kunstwerkes
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $where welcher Datensatz soll geändert werden
    \param $what was soll in den Datensatz geschrieben werden
    \param $picture_id um welches Bild handelt es sich ?

    \return $error Ein Fehlerstring im Fehlerfall , sonst die Ausgabe "(foo) in (bar) geändert --"
*/
function UpdateKunstwerk($dbconn,$where,$what,$picture_id){
  $error ="";
  if(isset($_POST['submit'])){
      $uid = $_SESSION['login']['uid'];

      $SQL_String = "UPDATE Kunstwerk SET ".$where." = ? WHERE Kunstwerk_ID = ?" ;
        
       $pre_stmt = $dbconn->stmt_init();
      if( $pre_stmt->prepare($SQL_String) ){
        $pre_stmt->bind_param("si", $what, $picture_id);
        $pre_stmt->execute();
        $pre_stmt->close();
        $error = $where." in ".$what." geändert --";
      }
      else{
        $error = "Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
        if( defined("__MYDEBUG__")&& __MYDEBUG__){
          echo "<div><b>Abfrage fehlgeschlagen</b><br />".
          $SQL_StringKunde."<br />".
          $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
        }
        
      }
      $dbconn->close();
      return $error;
  }
  
}       
 /*! \brief DB-Abfrage : Ändert die Eigenschaften eines Kuenstlers 
    \details zum ändern der Daten eines Künstlers
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $where welcher Datensatz soll geändert werden
    \param $what was soll in den Datensatz geschrieben werden
    \param $user_id um welchen user handelt es sich ?

    \return $error Ein Fehlerstring im Fehlerfall , sonst die Ausgabe "(foo) in (bar) geändert --"
*/
function UpdateKuenstler($dbconn,$where,$what,$user_id){ 
  $error ="";
  if(isset($_POST['submit'])){
      $uid = $_SESSION['login']['uid'];
 
      $SQL_String = "UPDATE Kuenstler SET ".$where." = ? WHERE Kunden_ID = ?" ;
        
       $pre_stmt = $dbconn->stmt_init();
      if( $pre_stmt->prepare($SQL_String) ){
        $pre_stmt->bind_param("si", $what, $user_id);
        $pre_stmt->execute();
        $pre_stmt->close();
        $error = $where." in ".$what." geändert --";
      }
      else{
        $error = "Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
        if( defined("__MYDEBUG__")&& __MYDEBUG__){
          echo "<div><b>Abfrage fehlgeschlagen</b><br />".
          $SQL_StringKunde."<br />".
          $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
        }
        
      }
      $dbconn->close();
      return $error;
  }
  
}      
 /*! \brief DB-Abfrage : Ändert die Eigenschaften eines Kunden 
    \details zum ändern der Daten eines Kunden
    \param  $dbconn eine gültige DB-Verbindung vom Typ mysqli
    \param $where welcher Datensatz soll geändert werden
    \param $what was soll in den Datensatz geschrieben werden
    \param $user_id um welchen Kunden handelt es sich ?

    \return $error Ein Fehlerstring im Fehlerfall , sonst die Ausgabe "(foo) in (bar) geändert --"
*/
function UpdateKunde($dbconn,$where,$what,$user_id){ 
  $error ="";
  if(isset($_POST['submit'])){
      $uid = $_SESSION['login']['uid'];
        
      $SQL_String = "UPDATE Kunde SET ".$where." = ? WHERE Kunden_ID = ?" ;
        
       $pre_stmt = $dbconn->stmt_init();
      if( $pre_stmt->prepare($SQL_String) ){
        $pre_stmt->bind_param("si", $what, $user_id);
        $pre_stmt->execute();
        $pre_stmt->close();
        $error = $where." in ".$what." geändert --";
      }
      else{
        $error = "Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
        if( defined("__MYDEBUG__")&& __MYDEBUG__){
          echo "<div><b>Abfrage fehlgeschlagen</b><br />".
          $SQL_StringKunde."<br />".
          $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
        }
        
      }
      $dbconn->close();
      return $error;
  }
 
}         

function UpdatePw($dbconn,$uid,$pw){
  global $pw_error;

  $pw_error = "";
  $SQL_String = "UPDATE login SET Passwort = SHA2(?, 256) WHERE Kunden_ID = ? ";

  $pre_stmt = $dbconn->stmt_init();
  if ( $pre_stmt->prepare($SQL_String) ){
    $pre_stmt->bind_param("ss", $pw, $uid);
    $pre_stmt->execute();
    $pre_stmt->close();
    $pw_error = "Das Passwort wurde erfolgreich geändert.";
    $dbconn->close();
    return true;
  }
  else {
      $pw_error = "Die SQL Abfrage schlug fehl, bitte versuchen sie es noch einmal.";
      if( defined(__MYDEBUG__) && __MYDEBUG__ ){
        echo "<div><b>Abfrage fehlgeschlagen</b><br />".
          $SQL_StringKunde."<br />".
          $pre_stmt->errno . ": " . $pre_stmt->error . "</div>";
      }
      $dbconn->close();
      return false;
  }
 
}

function deleteImage($dbconn, $img_nmbr){
  $SQL_String_eingeordnet = "DELETE  FROM eingeordnet_in WHERE Kunstwerk_ID = ".$img_nmbr;
  $SQL_String_Kunstwerk = "DELETE  FROM kunstwerk WHERE Kunstwerk_ID = ".$img_nmbr ;
  $res = $dbconn->query($SQL_String_eingeordnet);
  if(!$res){
    echo "Fehler beim löschen.".$SQL_String;
    $dbconn->close();
    return false;
  }
  $res = $dbconn->query($SQL_String_Kunstwerk);
  if(!$res){
    echo "Fehler beim löschen.".$SQL_String;
    $dbconn->close();
    return false;
  }
  $dbconn->close();
  return true;


}

?>