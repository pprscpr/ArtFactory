<?php
define( "__MYDEBUG__", false );

/*! \brief Initialisierung - was ist auf allen Seiten gleich
    
    Erledigt folgende Aufgaben für alle Seiten des PMG:
      - Initialisieruntg eines eigenen Debugging-Mechanismuses
      - Ein-/Ausschalten der Fehlermeldungen 
      - Einbinden der benötigten Include-Dateien

    \param keine
    \return keine
*/
function Init(  ){

  if (defined(" __MYDEBUG__ ")&&__MYDEBUG__)
    error_reporting( E_ALL ); // Alle Fehler (auch notices) aktivieren
  else
    error_reporting( 0 );
   
  Art_Session();              // Session sauber initialisieren und aufrufen

  // includes
  include_once("./includes/db_functions.inc");
  if ( !defined("__INC_DBFUNCS__") )
  {
    /* Fehlerbehandlung:
       Unmlenkung auf eine eigene Fehlerseite:
       Netzwerkprobleme! Versuchen Sie es später ...
    */
  }
  include_once("./includes/html_functions.inc");
}



/*! \brief Eine angepasste Session initialisieren
    \param keine
    \return keine
*/
function Art_Session()
{
  ini_set( "session.use_cookies", 0 );      // Schaltet Cookie als Standardmechanismus aus
  ini_set( "session.use_only_cookies", 0 ); // Lässt andere Datenwege zu 
  ini_set( "session.name", "Art" );         // Setzt den Session-Name
  session_start();                           // Benutze den Session-Mechanismus
                         
}

/*! \brief Überprüft, ob ein User bereits angemeldet ist
    
    Überprüft, ob in der Session des Users ein Eintrag für
    ein erfolgreiches Login vorhanden ist.
    Ist dies nicht der Fall wird auf die Anmeldeseite umgelenkt.
    Für die Umlenkung wird ein Fehler in der Session eingetragen und
    das Script, wo diese Umlenkung erfolgt ist.

    \param keine
    \return true - im Erfolgsfall
            sonst eine Umlenkung
*/
function IsLoggedIn( ){
  if ( empty($_SESSION['login']['uid']) ){
    $_SESSION['error']['errno'] = 103;
    $_SESSION['error']['page']  = $_SERVER['PHP_SELF'];
    header("Location: ./index.php?".SID );
  }
  else{
    return true;
  }
}

/*! \brief Überprüft, ob ein User bereits angemeldet ist
    
    Überprüft, ob in der Session des Users ein Eintrag für
    ein erfolgreiches Login vorhanden ist.
    Für die Umlenkung wird ein Fehler in der Session eingetragen und
    das Script, wo diese Umlenkung erfolgt ist.

    \param keine
    \return true - im Erfolgsfall
            sonst false
*/
function IsLoggedIn2BuyPic( ){
  if ( empty($_SESSION['login']['uid']) ){
    $_SESSION['error']['errno'] = 103;
    $_SESSION['error']['page']  = $_SERVER['PHP_SELF'];
    return false;
  }
  else{
    return true;
  }
}


/*! \brief Überprüft, ob ein Fehler in der Session aufgetreten ist
      Überprüft ob ein Fehler in der Session aufgetreten ist und gibt diesen
      Fehler mit genauer Beschreibung zurück
    \param keine
    \return $ErrDiv Titel und Beschreibung eines Session Fehlers
*/
function CheckSessionError( ){
  $ErrDiv = "";

  if ( isset( $_SESSION['error']['errno'] ) ){
    $ErrDiv = ErrorByNo( $_SESSION['error']['errno'] );
    unset( $_SESSION['error'] );
  }
  return $ErrDiv;
}




/*! \brief Erzeugt Fehlermeldungen in Abhängigkeit einer Fehlernummer

  \function Erzeugt ein Div mittels htmlfuncs.inc:ErrDiV()
            Zur Zeit werden folgende Fehlercodes unterstützt
            101: Fehlende Eingabe bei der Anmeldung
            102: Falsche Eingabe bei der Anmeldung
            103: Keine Anmeldung in einer internen Seite
            999: Unbekannter Fehler

  \param $errno Eine Fehlernummer als Ganzzahl

  \return ein String, der das komplette Fehlerdiv für die HTML-Seite beschreibt

******************************************************************* */
function ErrorByNo( $errno ){
  // Welcher Fehler wurde übergeben?
  switch ( $errno ){
    case 101: $title="Fehlende Eingabe";
              $desc= "Sie müssen im Formular".
                  " <span class=\"wichtig\">alle</span> Felder ausfüllen.";
              break;
    case 102: $title="Falsche Eingabe";
              $desc= "Diese Kombination aus Login und Passwort ist ungültig.".
                     " Bitte geben Sie im Formular Ihre korrekten Anmeldedaten ein.";
              break;
    case 103: $title="Fehlende Anmeldung";
              $desc= "Sie haben eine Seite ohne Anmeldung betreten.".
                     "Startseite.";
              break;
     

    default : $title="Sorry - unbekannter Fehler";
              $desc= "Dies sollte nie auftreten.<br />".
                     "Bitte melden Sie diesen Fehler  ...";
              break;
  }

  return ErrorDiv( $title, $desc );
}

/*! \brief Gibt ein Array formatiert zu Debugging-Zwecken aus  
    \param $arr das auszugebende Array
    \return nichts - reine Ausgabe
*/
function DebugArr( $arr ){
  if ( defined( "__MYDEBUG__" ) && __MYDEBUG__ )
  {
    echo "\n<div id=\"debug\">";
    echo "\n  <pre>\n  ";
    print_r( $arr ); 
    echo "\n  </pre>";
    echo "\n</div>";
  }
}


/*! \brief Gibt Session, Cookie, Get, Post -Daten zum Debugging aus
    \param  keine
    \return keine

*/
function DebugAll(){
  if ( defined( "__MYDEBUG__" ) && __MYDEBUG__ ){
    echo "session\n";
    DebugArr( $_SESSION );
    echo "cookie\n"; 
    DebugArr( $_COOKIE );
    echo "get\n"; 
    DebugArr( $_GET );
    echo "post\n"; 
    DebugArr( $_POST );
  }
}

/*! \brief Überprüft, ob beim Login alle Input-Felder belegt sind
  \param Übergabemechanismus - in welchem Array sind die Anmeldedaten enthalten
  \return bool 
*/
function  LoginDataComplete( $arr ){
  if ( !empty($arr['login'])   &&
       !empty($arr['passwd'])   ) 
    return true;
  else
    return false;
}


/*! \brief Überprüft die Anmeldung des Login-Formulares

    Ist die Anmeldung korrekt, so wird auf die Seite "$Destination" umgelenkt
    Ansonsten wird eine Fehlermeldung als HTMl-Div zurückgeliefert
    User ID wird an die Session übergeben

    \param $Destination Seite, auf die im Erfolgsfall umgelenkt wird
    \param $LoginArr    das Array, wo die Anmeldedaten herkommen
    \return $ErrString einen Errorstring mit Fehlerbeschreibung, sonst leer
*/
function CheckLogin( $LoginArr, $Destination ){
  $ErrString ="";
  if ( isset($LoginArr['submit']) ){ 
  // es wurde ein Submit gesendet: Login-Überprüfung findet statt
    if (  LoginDataComplete( $LoginArr ) ){
      // Alle Felder ausgefüllt
      $dbconn  = ConnectArtDB( 'Login' );   //Verbindung zum DB-Server aufbauen
      $uid = GetUIDByLogin( $dbconn, $LoginArr );
      $dbconn->close();
      
      if ( $uid ){ 
        $_SESSION['login']['uid'] = $uid;

        // login Bewegung in Log-Datei speichern
        $log_srtring ="\n".date("l j  F Y h:i:s A ").":".$_SESSION['login']['uid'];
        file_put_contents("./log/log_login.txt", $log_srtring,FILE_APPEND);

        header("Location: ./welcome.php?".session_name()."=".session_id() );
        /*
          wenn cookies deaktiviert sind ( und nur dann ! ) meint PHP, dass Sie
          den String  session_name()."=".session_id() öfter brauchen und 
          bereitet diesen in der Konstanten SID vor.

        header("Location: ./welcome.php?".SID );
        */
      }
      else { // Falsche Anmeldedaten
        $ErrString = ErrorByNo( 102 );
      }
    }
    else {// Fehlende Anmeldedaten
      $ErrString = ErrorByNo( 101 );
    }
  }

  return $ErrString;
}

/*! \brief Überprüft die Anmeldung des Login-Formulares zum Kauf eines Bildes
    
    Ist die Anmeldung korrekt, so wird auf die Seite buy_confirm.php umgelenkt
    und Bild/User -Informationen werdedn an die Session übergeben
    Ansonsten wird eine Fehlermeldung als HTMl-Div zurückgeliefert
    
    \param $Destination Seite, auf die im Erfolgsfall umgelenkt wird
    \param $LoginArr    das Array, wo die Anmeldedaten herkommen
    \return $ErrString einen Errorstring mit Fehlerbeschreibung, sonst leer
*/

function CheckLogin2Buy( $LoginArr, $Destination){
  $ErrString ="";
  
  if ( isset($LoginArr['submit']) ){ 
  // es wurde ein Submit gesendet: Login-Überprüfung findet statt
    if (  LoginDataComplete( $LoginArr ) ){
      // Alle Felder ausgefüllt
      $dbconn  = ConnectArtDB( 'Login' );   //Verbindung zum DB-Server aufbauen
      $uid = GetUIDByLogin( $dbconn, $LoginArr );
      $dbconn->close();
      
      if ( $uid ){ 
        $image = $_POST['img'];
        $image_ID = $_POST['id'];
        $pic = array();
        $pic = explode('.',$image,2);
        $picName = $pic[0];
        $picFormat = $pic[1];
        
        $_SESSION['login']['uid']     = $uid;
        $_SESSION['buy']['id']        = $image_ID;
        $_SESSION['buy']['img']       = $image;
        $_SESSION['buy']['imgname']   = $picName;
        $_SESSION['buy']['imgformat'] = $picFormat;
        $_SESSION['buy']['buy']       = "1";
        
        // login Bewegung in Log-Datei speichern
        $log_srtring ="\n".date("l j  F Y h:i:s A ").":".$_SESSION['login']['uid'];
        file_put_contents("./log/log_login.txt", $log_srtring,FILE_APPEND);

        header("Location: ./buy_confirm.php?".session_name()."=".session_id()."&img=".$image );
        /*
          wenn cookies deaktiviert sind ( und nur dann ! ) meint PHP, dass Sie
          den String  session_name()."=".session_id() öfter brauchen und 
          bereitet diesen in der Konstanten SID vor.

        header("Location: ./welcome.php?".SID );
        */
        echo "<b> Hier kam eine Umlenkung nach welcome.php</b>";
      }
      else{ // Falsche Anmeldedaten
        $ErrString = ErrorByNo( 102 );
      }
    }
    else{// Fehlende Anmeldedaten
      $ErrString = ErrorByNo( 101 );
    }
  }

  return $ErrString;
}

/*! \brief Überprüfung ob das Bild schon gekauft wurde, wenn nicht dann kauft es der User
    
    Es wird überprüft ob das gewünschte Bild schon verkauft wurde, wenn nicht kauft es der User
    und es ernscheind eine entsprechende Meldung

    \param keine
    \return $output Ein Html Code mit Bild-Anzeige und "Bild gekauft" , sonst Meldung "das Bild ist schon verkauft"
*/
// Überprüfen ob das Bild schon gekauft wurde->dann Ausgabe
// sonst Bild kaufen und Bild ausgeben + "Bild gekauft"
function BuyConfirm(){
  global $sold;
  if(isset($_POST['submit'])){
    if($_POST['submit']=="verbindlich kaufen"){
      $sold = PictureAlreadySold(ConnectArtDB( 'Gast' ),$_SESSION['buy']['id']); 
      if($sold=="vorhanden") {
          $kunde = BuyPicture( ConnectArtDB( 'Kuenstler' ), $_SESSION['buy']['id'], $_SESSION['login']['uid']);
          $output  = "\n  <div id=\"buy\">".
                     "\n   <div class=\"alert alert-success\" role=\"alert\">
  Sie haben den Kauf erfolgreich abgeschlossen!
</div>".
                     "\n    <img src=\"pics/big/".$_SESSION['buy']['img']."\" alt=\"pic\">".
                     "\n   </div>".
                     "\n   <a class = \"btn btn-dark\"href=\"show_gallery.php?".SID."&sort=All\">zurück zur Galerie</a>";
      }
      else{
         $output  = "\n  <div id=\"buy\">
         <div class=\"alert alert-warning\" role=\"alert\">Leider war jemand schneller als Sie, das Bild wurde schon verkauft!</div></div>";
          
      }
    }  
  }else{
    $output = GetHtmlBigImage( GetImages( ConnectArtDB( 'Gast' ),"All" ), "confirm" );
  }
  return $output;
}

/*! \brief wenn eingelogged ist dann wird der Name und Daten des Bildes an die Umleiteseite weitergegeben , sonst Login eingeben
    \param $is_logged_in Ein bool ob der User schon eingelogged ist
    \return keine
*/
function BuyPic( $is_logged_in ){
  global $image, $image_ID, $pic, $picName, $picFormat, $ErrString;
  if( $is_logged_in == true ){
    $image = $_POST['img'];
    $image_ID = $_POST['id'];
    $pic = array();
    $pic = explode('.',$image,2);
    $picName = $pic[0];
    $picFormat = $pic[1];
 
    $_SESSION['buy']['id']        = $image_ID;
    $_SESSION['buy']['img']       = $image;
    $_SESSION['buy']['imgname']   = $picName;
    $_SESSION['buy']['imgformat'] = $picFormat;
    $_SESSION['buy']['buy']       = "1";

    header("Location: ./buy_confirm.php?".session_name()."=".session_id()."&img=".$image );
  }
  else {
    $image = $_POST['img'];
    $image_ID =$_POST['id'];
    $ErrString = CheckLogin2Buy( $_POST, "./buy_confirm.php" );

  }
}



/*! \brief Änderungen (UPDATE) an den eingestellten Kunstwerken
     
      wenn Eigenschaften an einen schon eingestellten Kunstwerk geändert werden sollen (UPDATE) dann wird eine DB Update aufgerufen und eine
      Meldung mit den geänderten Daten ausgegeben
    \param keine
    \return $msg eine Meldung mit den geänderten Daten Titel in "..." geändert --
*/
function UpdateChangesKunstwerk(){
      $msg = "";
      if(!empty($_POST['Titel']) ){
          // UPDATE Titel
          // enthält der Bildname Sonderzeichen ?
          if( !preg_match("/[\w ]*/", $_POST['Titel']) ){
            $error = "Der Bildname darf keine Sonderzeichen enthalten!";
            return $error;
            exit();
          }
          $msg .= UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Titel",$_POST['Titel'],$_GET['nmbr']);
      }
      
      if(!empty($_POST['Preis']) ){
          // UPDATE Preis
          if( !preg_match("/[0-9]{1,10}(\.||\,){1,1}[0-9]{2,2}/", $_POST['Preis']) ){
              $error = "Der Preis darf nur Ziffern und oder . ; enthalten!";
              return $error;
              exit();
          }
          $msg .=UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Preis",$_POST['Preis'],$_GET['nmbr']);
      }
       if(!empty($_POST['Hoehe']) ){
          // UPDATE Breite
          // enthält Höhe nur Ziffern ?
          if( !preg_match("/^[0-9]*$/", $_POST['Hoehe']) ){
              $error = "Höhe darf nur Ziffern enthalten!";
              return $error;
              exit();
          }
          $msg .=UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Hoehe",$_POST['Hoehe'],$_GET['nmbr']);
      }
      if(!empty($_POST['Breite']) ){
          // UPDATE Breite
          // enthält Breite nur Ziffern ?
          if( !preg_match("/^[0-9]*$/",$_POST['Breite']) ){
              $error =  "Breite darf nur Ziffern enthalten!";;
              return $error;
              exit();
          }
          $msg .=UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Breite",$_POST['Breite'],$_GET['nmbr']);
      }
      if(!empty($_POST['Gewicht']) ){
          // UPDATE Gewicht
          // enthält das Gewicht nur Ziffern ?
          if( !preg_match("/^[0-9]*$/",$_POST['Gewicht']) ){
              $error = "Das Gewicht darf nur Ziffern enthalten! ";
              return $error;
              exit();
          }
          $msg .=UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Gewicht",$_POST['Gewicht'],$_GET['nmbr']);
      }
      if(!empty($_POST['Herstellungsdatum']) ){
          // UPDATE Herstellungsdatum
          if( !preg_match("/^[0-9]{1,2}\.([0-9]{2,2}||(Jan||Feb||Mar||Apr||Mai||Juni||Juli||Aug||Sep||Nov||Dec))\.[0-9]{2,4}$/", $_POST['Herstellungsdatum']) ){
            $error = "Das Gewicht darf nur Ziffern enthalten! ";
            return $error;
            exit();
          }
          $msg .=UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Herstellungsdatum",$_POST['Herstellungsdatum'],$_GET['nmbr']);
      }
      if(!empty($_POST['Beschreibung']) ){
          // UPDATE Beschreibung
          if( !preg_match("/[\w ]*/",$_POST['Beschreibung']) ){
            $error = "Die Beschreibung darf keine Sonderzeichen wie (; \ {} []) enthalten!";
            return $error;
            exit();
          } 
          
          $msg .=UpdateKunstwerk(ConnectArtDB( 'Kuenstler' ),"Beschreibung",$_POST['Beschreibung'],$_GET['nmbr']);
      }
      return $msg;
}


/*! \brief Änderungen (UPDATE) an den Usereigenschaften
      
      wenn Eigenschaften an einens Users geändert werden sollen (UPDATE) dann wird eine DB Update aufgerufen und eine
      Meldung mit den geänderten Daten ausgegeben.
    \param keine
    \return $msg eine Meldung mit den geänderten Daten Vorname in "..." geändert --
*/
function UpdateChangesUser(){
      $msg = "";
      if(!empty($_POST['Titel']) ){
          // UPDATE Titel
          // befinden sich Sonderziechen oder Ziffern im Titel  ?
          if(!preg_match("/^[a-zA-Z]*$/", $_POST['Titel']) ) {
              $Errorstring = "Keine Sonderzeichen oder Ziffern im Titel benutzen! ";        
              return $Errorstring;
              exit();
          }
          $msg .= UpdateKunde(ConnectArtDB( 'Kunde' ),"Titel",$_POST['Titel'],$_SESSION['login']['uid']);
      }
      
      if(!empty($_POST['Vorname']) ){
          // UPDATE Vorname
          // befinden sich Sonderziechen oder Ziffern im Vorname  ?
          if(!preg_match("/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$/", $_POST['Vorname']) ) {
              $Errorstring = "Keine Sonderzeichen oder Ziffern im Vorname benutzen! ";        
              return $Errorstring;
              exit();
          }
          $msg .=UpdateKunde(ConnectArtDB( 'Kunde' ),"Vorname",$_POST['Vorname'],$_SESSION['login']['uid']);
      }
       if(!empty($_POST['Nachname']) ){
          // UPDATE Nachname
          // befinden sich Sonderziechen oder Ziffern im Nachnamen  ?
          if(!preg_match("/^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$/", $_POST['Nachname']) ) {
              $Errorstring = "Keine Sonderzeichen oder Ziffern im Nachnamen benutzen! ";        
              return $Errorstring;
              exit();
          }
          $msg .=UpdateKunde(ConnectArtDB( 'Kunde' ),"Nachname",$_POST['Nachname'],$_SESSION['login']['uid']);
      }
      if(!empty($_POST['Strasse']) ){
          // UPDATE Strasse
          // Ist die Postleitzahl gültig ?
          if(!preg_match("/^a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s\.]*[0-9]*[a-z]*$/",$_POST['Strasse']) ) {
              $Errorstring = "Kein gültiger Strassenname! ";        
              return $Errorstring;
              exit();
           }
          $msg .=UpdateKunde(ConnectArtDB( 'Kunde' ),"Strasse",$_POST['Strasse'],$_SESSION['login']['uid']);
      }
      if(!empty($_POST['PLZ']) ){
          // UPDATE PLZ
          if(!preg_match("/^[0-9]{5,5}$/", $_POST['PLZ']) ) {
                $Errorstring = "Keine gültige Postleitzahl! ";        
                return $Errorstring;
                exit();
          }
          $msg .=UpdateKunde(ConnectArtDB( 'Kunde' ),"PLZ",$_POST['PLZ'],$_SESSION['login']['uid']);
      }
      if(!empty($_POST['ORT']) ){
          // UPDATE Ort
          // befinden sich Sonderziechen im Ort ?
          if(!preg_match("/^[[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s]*$/", $_POST['ORT']) ) {
              $Errorstring = "Keine Sonderzeichen oder Ziffern im Ort benutzen! ";        
              return $Errorstring;
              exit();
          }

          $msg .=UpdateKunde(ConnectArtDB( 'Kunde' ),"ORT",$_POST['ORT'],$_SESSION['login']['uid']);
      }
    
      return $msg;
}


/*! \brief Änderungen (UPDATE) an den Künstlereigenschaften
      
      wenn Eigenschaften an einens Künstler geändert werden sollen (UPDATE) dann wird eine DB Update aufgerufen und eine
      Meldung mit den geänderten Daten ausgegeben.
    \param keine
    \return $msg eine Meldung mit den geänderten Daten Künstlername in "..." geändert --
*/
function UpdateChangesArtist(){
      $msg = "";
      if(!empty($_POST['IBAN']) ){
          // UPDATE IBAN
          // befinden sich Sonderziechen in der IBAN  ?
          if(!preg_match("/^[a-zA-Z0-9]*$/", $_POST['IBAN']) ) {
              $error = "Die IBAN darf keine Sonderzeichen enthalten! ";        
              return $error;
              exit();
          }
          $msg .= UpdateKuenstler(ConnectArtDB( 'Kuenstler' ),"IBAN",$_POST['IBAN'],$_SESSION['login']['uid']);
      }     
      if(!empty($_POST['Kuenstlername']) ){
          // UPDATE Kuenstlername
          // befinden sich Sonderziechen im Künstlernamen ?
          if(!preg_match("/^[a-zA-Z0-9]*$/", $_POST['Kuenstlername']) ) {
              $error = "Der Kuenstlername darf keine Sonderzeichen enthalten! ";        
              return $error;
              exit();
          }
          $msg .=UpdateKuenstler(ConnectArtDB( 'Kuenstler' ),"Kuenstlername",$_POST['Kuenstlername'],$_SESSION['login']['uid']);
      }
       if(!empty($_POST['BIC']) ){
          // UPDATE BIC
          // befinden sich Sonderziechen in der BIC ?
          if(!preg_match("/^[a-zA-Z0-9]*$/", $_POST['BIC']) ) {
              $error = "Die BIC darf keine Sonderzeichen enthalten! ";        
              return $error;
              exit();
          }
          $msg .=UpdateKuenstler(ConnectArtDB( 'Kuenstler' ),"BIC",$_POST['BIC'],$_SESSION['login']['uid']);
      }
      if(!empty($_POST['Vita']) ){
          // UPDATE Breite
          if(preg_match("/^[;\{}[]]*$/", $_POST['Vita']) ) {
                $error = "Die Vita darf keine Sonderzeichen wie (; \ {} []) enthalten! ";        
                return $error;
                exit();
          }
          $msg .=UpdateKuenstler(ConnectArtDB( 'Kuenstler' ),"Vita",$_POST['Vita'],$_SESSION['login']['uid']);
      } 
      return $msg;
}


/*! \brief zerstört die Session und lenkt auf index.php um

    für einen Logout wird die Session zerstört und auf die index Seite
    umgelenkt.

    \param keine
    \return nichts
*/
function logout(){
    session_destroy();
    header("Location: ./index.php");
}


/*! \brief Überprüft 2 gehashte Passwörter , Umlenkung auf new_pw.php bei Erfolg

    Zum überprüfen ob das eingegebene Passwort mit den aktuellen übereinstimmt
    Umlenkung auf new_pw.php bei Erfolg

    \param $pw - gehashtes Passwort aus der DB
    \param $pw2 - ungehashtes Passwort aus den Form via post
    \return $error Fehlermeldung 
*/
function CheckPw($pw,$pw2){
  $pw2 = hash('sha256', $pw2);
  $error = "";
  if($pw == $pw2){
    header("Location: ./new_pw.php?".SID);
  }
  else {
    $error = "Falsches Passwort";
  }
  return $error;
}

function CheckIfLoginExists($log_arr,$log){
  foreach ($log_arr AS $arr ) {
    $name = $arr['Login'];
    if($name == $log){
      return true;
    }
    
  }
  return false;

}

/*! \brief Speichert eingegbene Nachrichten des User als txt log Datei im Ordner ./log/log_messages
    \param $arr ein Array mit Daten in der Nachricht
    \return kein
*/
function UserMessages($arr){
  if( isset($arr['message']) ){

    $message_string = "\ndate :".date("l j  F Y h:i:s A ")." ".
                      "  name: ".htmlentities($arr['message']['name'])." mail: ".htmlentities($arr['message']['mail']).
                      "  text: ".htmlentities($arr['message']['message']);
    file_put_contents("./log/log_messages.txt", $message_string,FILE_APPEND);
    unset($_POST['message']);
  }
}

?>