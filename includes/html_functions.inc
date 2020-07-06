<?php

/*! \brief Erstellt ein Div zur Darstellung von Fehlermeldungen

  \param $title Der Titel der Fehlermeldung als string
  \param $desc  Ein Ausführliche Fehlerbeschreibung als string
  \return ein String, der das Komplette Fehlerdic für die HTML-Seite beschreibt

 */
function ErrorDiv( $title, $desc ){
  return  "\n  <div class=\"error\">".
          "\n    <div class=\"title\">".$title."</div>".
          "\n    <div class=\"desc\">".$desc."</div>".
          "\n  </div>";
}

/*! \brief Erstellt eine Tabelle zur Ausgabe der Stilrichtungen mit Beschreibung

  \param $styles_arr Ein Array mit den Inhalt der Tabelle Kategorie
  \return $table Eine gefüllte Html Tabelle mit den Stilrichtungen und Beschreibungen

 */
function GetHtmlStyles( $styles_arr ){
  $table = "";
  // 1. EINEN table-header erzeugen
  $table .= "\n  <table class = \"table table-condensed table-striped\" id=\"HtmlStyles  \">".
            "\n  <thead><tr><th>Stilrichtungen</th><th>Beschreibung</th></tr></thead>\n  <tbody>";

  // 2. in einer Schleife (foreach!) für jeden DS eine table-row erzeugen
  foreach ( $styles_arr AS $styles )
  {
    $table.= "\n  <tr>".
             "\n   <td>".$styles['Stilrichtung']."</td>".
             "\n   <td>".$styles['Beschreibung']."</td>".
             "\n </tr>";
  }
  // 3. EINEN table-footer erzeugen
  $table .= "\n  </tbody>\n  </table>";
 
  return $table;
}


/*! \brief Erstellt eine Dropdown-Menu zur Ausgabe der Stilrichtungen 

  \param $styles_arr Ein Array mit den Inhalt der Tabelle Kategorie
  \return $select Eine gefüllte Html Select-Anweisung mit den Stilrichtungen 

 */
function GetHtmlStyleDropDown( $styles_arr ){
	
	$select = "";
	$select .="\n   <select class=\"form-control\" id=\"style\" name=\"style\">";
	$select .="\n   <option value=\"0\" selected>-</option>";
  if(!empty($styles_arr)){
  	foreach ($styles_arr AS $styles) {
  		$select .=  "\n       <option value=".$styles['Kategorie_ID'].">".$styles['Stilrichtung'].
  		"</option> ";
  	}
  }
	$select .= "\n  </select> \n";
	return $select;
}

/*! \brief Erstellt eine Dropdown-Menu zur Ausgabe der Kontaktarten

  \param $art_arr Ein Array mit den Inhalt der Tabelle Kategorie
  \return $select Eine gefüllte Html Select-Anweisung mit den Stilrichtungen 

 */
function GetHtmlKontaktArtDropDown( $art_arr ){
  
  $select  = "";
  $select .="\n            <select id=\"KontaktArt\" class=\"form-control col-md-8\" name=\"reg[KontaktArt]\">";
  $select .="\n               <option value=\"0\" selected>-</option>";
  if(!empty($art_arr)){
    foreach ($art_arr AS $art) {
      $select .=  "\n              <option value=".$art['Art_ID'].">".$art['Bezeichnung'].
                                   "</option> ";
    }
  }
  $select .= "\n            </select> \n";
  return $select;
}

/*! \brief Erstellt eine Table-Row zur Ausgabe des Bildes und dessen Eigenschaften(Titel, Kuenstlername, Preis)

  \param $images_arr Ein Array mit den Datensätzen zu den Bildern
  \return $output Eine gefüllte Html Table-Row mit dem Bild und Eigenschaften 
 */
function GetHtmlImages( $images_arr ){
  $output  = "";
             
  if(!empty($images_arr)){
    foreach ($images_arr as $img ) {
      $output .=    "\n<div class=\"box\">".
                    "\n <a href=\"./show_image.php?img=".$img['Image']."&id=".$img['Kunstwerk_ID']."&".SID."\"><img class=\"card-img-top embed-responsive-item\" src=\"./pics/small/".$img['Image']."\" alt=\"pic\" width=160 ></a><br />".
                    "\n <h5>".$img['Titel']."</h5>".
                    "\n <p>Künstler: ".$img['Kuenstlername']."<p>".
                    "\n <p><small class=\"text-muted\">Preis: ".$img['Preis']."</small></p>".
                    "\n</div><!-- /box ends -->";

    }
  }


                    
     
  return $output;
}


/*! \brief Erstellt Html Ausgabe des Bildes(big) und dessen Eigenschaften
    
     Erstellt Html Ausgabe des Bildes(big) und dessen Eigenschaften(Titel, Preis,
     Hoehe, Breite, Gewicht, Beschreibung, Herstellungsdatum )

  \param $images_arr Ein Array mit den Datensätzen zu den Bildern
  \param $where Unterscheidet an welcher Stelle die Funktion aufgerufen werden kann "buy","confirm"
  \return $output Eine Html Ausgabe mit dem Bild und Eigenschaften 
 */
function GetHtmlBigImage( $images_arr , $where ){
  if($where == "buy"){
    $image = $_GET['img'];
    $image_ID = $_GET['id'];
  }
  elseif($where == "confirm"){
     $image = $_SESSION['buy']['img'];
  }

  //So bitte in Zukunft nicht mehr umsetzen. Diese variante macht es fast unmoeglich HTML richtig zu kodieren.
  
  $output = "";
  if(!empty($images_arr)){
    foreach ($images_arr as $img ) {
        if($img['Image']==$image){
            $output .=  "\n   <div class=\"jumbotron\">".
                        "\n    <div class=\"row\">".
                        "\n     <div class=\"col\">".
                        "\n      <img class= \"img-thumbnail\" src=\"./pics/big/".$image."\" alt=\"pic\">".
                        "\n     </div>".
                        "\n     <div class=\"col\">".
                        "\n      <div class=\"imgDscr\">".
                        "\n       <h5>".
                        "\n         ".$img['Titel']." ".
                        "\n       </h5>".
                        "\n       <p>".
                        "\n         Preis in € : ".$img['Preis']." ".
                        "\n       </p>".
                        "\n       <p>".
                        "\n         Höhe in mm: ".$img['Hoehe']." ".
                        "\n       </p>".
                        "\n       <p>".
                        "\n         Breite in mm : ".$img['Breite']." ".
                        "\n       </p>".
                        "\n       <p>".
                        "\n         Gewicht in g : ".$img['Gewicht']." ".
                        "\n       </p>".
                        "\n       <p>".
                        "\n         Beschreibung : ".$img['Beschreibung']." ".
                        "\n       </p>".
                        "\n       <p>".
                        "\n         Herstellungsdatum : ".$img['Herstellungsdatum']." ".
                        "\n       </p>".
                        "\n      </div>".
                        "\n     </div>".
                        "\n    </div>";

           
        }
    }
  }

  if($where == "buy" ){
    $output .= "\n   <div>".
               "\n    <form method=\"post\" action=\"./buy_pic.php?".SID."\">".
               "\n      <input type=\"hidden\" name=\"".session_name()."value=".session_id()."\" />".
               "\n      <input type=\"hidden\" name=\"img\" value=\"".$image."\" />".
               "\n      <input type=\"hidden\" name=\"id\" value=\"".$image_ID."\" />".
               "\n    <div class=\"row\">".
               "\n    <div class=\"col\">".
               "\n      <input class = \"btn btn-dark\" type=\"submit\" name=\"submit\" value=\"kaufen\" />".
               "\n   </div>".
               "\n    </form> ".
               "\n    <div class=\"col\">".
               "\n      <a class = \"btn btn-dark\" href=\"./show_gallery.php?".SID."&sort=All\">zurück zur Galerie</a>".
               "\n   </div>".
               "\n   </div>".
               "\n   </div>".
               "\n   </div>";
  }
  elseif ($where == "confirm") {
    $output .= "\n   <div>".
               "\n    <form method=\"post\" action=\"./buy_confirm.php?".SID."\">".
               "\n      <input type=\"hidden\" name=\"".session_name()."value=".session_id()."\" />".
               "\n    <div class=\"row\">".
               "\n    <div class=\"col\">".
               "\n      <input class = \"btn btn-dark\" type=\"submit\" name=\"submit\" value=\"verbindlich kaufen\" />".
               "\n   </div>".
               "\n    </form> ".
               "\n    <div class=\"col\">".
               "\n      <a class = \"btn btn-dark\" href=\"./show_gallery.php?".SID."&sort=All\">zurück zur Galerie</a>".
               "\n   </div>".
               "\n   </div>".
               "\n   </div>".
               "\n   </div>";
  }


  return $output;
}


/*! \brief Erstellt eine Table-Row zur Ausgabe der gekauften Bilder und deren Eigenschaften(Titel, Kaufzeit,Kuenstlername)

  \param $images_arr Ein Array mit den Datensätzen zu den Bildern
  \return $output Eine gefüllte Html Table-Row mit dem Bild und Eigenschaften 
 */
function GetHtmlPicturesIBought( $images_arr ){
  $output ="";
    if(!empty($images_arr)){
        foreach ( $images_arr as $img ) {
          $output .= "\n          <tr>".
                     "\n            <td><img src=\"./pics/small/".$img['Image']."\" class=\"img-responsive\" alt=\"Kreativität\" width=\"120\" height=\"100\"></td>".
                     "\n            <td>".$img['Titel']."</td>".
                     "\n            <td>".$img['Kauf_Zeitstempel']."</td>".
                     "\n            <td>".$img['Kuenstlername']."</td>".
                     "\n          </tr>";
        }
    }

  return $output;  

 }

//my_area
// Ausabe von Bildern und Eigenschaften eines Kunstwerkes in einer Tabelle
/*! \brief Html-Ausabe von Bildern und Eigenschaften des Kunstwerkes in einer Tabelle mit Button zum ändern der Daten
    
    Html-Ausabe von Bildern und Eigenschaften des Kunstwerkes in einer Tabelle mit Button zum ändern der Daten
    die Funktion kommt in my_area zum Einsatz damit der Künstler seine eingestellten Werke editieren kann

    \param $images_arr Ein Array mit den Datensätzen zu den Bildern
    \return $output Eine gefüllte Html Table-Row mit dem Bild und Eigenschaften + ändern löschen button
*/
 function GetHtmlArtistPictures( $images_arr ){
  $output ="";
   if(!empty($images_arr)){
      foreach ( $images_arr as $img ) {

        $var  = "'";
        $var .= $img['Kunstwerk_ID'];
        $var .= "'";
        
        $_SESSION[$var]['Id'] = $img['Kunstwerk_ID'];
        $_SESSION[$var]['Titel'] = $img['Titel'] ;
        $_SESSION[$var]['Einstell_Zeitstempel'] = $img['Einstell_Zeitstempel'] ;
        $_SESSION[$var]['Preis'] = $img['Preis'] ;
        $_SESSION[$var]['Hoehe'] = $img['Hoehe'] ;
        $_SESSION[$var]['Breite'] = $img['Breite'] ;
        $_SESSION[$var]['Gewicht'] = $img['Gewicht'] ;
        $_SESSION[$var]['Herstellungsdatum'] = $img['Herstellungsdatum'] ;
        $_SESSION[$var]['Beschreibung'] = $img['Beschreibung'] ;

        $output .= "\n          <tr>";
        $output .= "\n            <td><img src=\"./pics/small/".$img['Image']."\" class=\"img-responsive\" alt=\"Kreativität\" width=\"120\" height=\"100\"></td>";
        $output .= "\n            <td>".$img['Titel']."</td>".
                   "\n            <td>".$img['Einstell_Zeitstempel']."</td>".
                   "\n            <td>".$img['Preis']."</td>".
                   "\n            <td>".$img['Hoehe']."</td>".
                   "\n            <td>".$img['Breite']."</td>".
                   "\n            <td>".$img['Gewicht']."</td>".
                   "\n            <td>".$img['Herstellungsdatum']."</td>".
                   "\n            <td>".$img['Beschreibung']."</td>".
                   "\n            <td><div class\"btn-group-vertical\"><a class = \"btn btn-dark\" href=\"./change_pic.php?".SID."&nmbr=".$img['Kunstwerk_ID']."\">Ändern</a> <a class = \"btn btn-danger\" href=\"./my_area.php?".SID."&del=".$img['Kunstwerk_ID']."\">Löschen</a> </div></td>".
                   "\n          </tr>";
        
      }
    }

  return $output;  
 }

/*! \brief Html-Ausabe von Formular Input Feldern(Titel,Vorn,Nachn,Strasse,PLZ,Ort)
    \param $prop_arr Ein Array mit den Datensätzen Eigenschaften eines USers
    \return $output Ein Formular m Input Feldern(Titel,Vorn,Nachn,Strasse,PLZ,Ort)
*/
function GetHtmlUserProperties( $prop_arr ){
  $output ="";
   if(!empty($prop_arr)){
      foreach ( $prop_arr as $arr ) {

        $output ="\n  <div class=\"form-row\">".
                 "\n   <div class=\"form-group col-sm-2\">".
                 "\n     <label class=\"col-form-label\" for=\"inlineFormInput\">Titel</label>".
                 "\n     <input class=\"form-control\" type=\"text\" name=\"Titel\"".
                 "\n      oninput=\"checkField(this,'^[a-zA-Z\.]*$','nicht erlaubtes Zeichen im Titel -- Beispiel : Dr.')\" ".
                 "\n      placeholder=\"".$arr['Titel']."\">".
                 "\n   </div>".
                 "\n   <div class=\"form-group col-sm-10\">".
                 "\n     <label class=\"col-form-label\" for=\"inlineFormInput\">Vorname</label>".
                 "\n     <input class=\"form-control\" type=\"text\" name=\"Vorname\"".
                 "\n       oninput=\"checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$','nicht erlaubtes Zeichen im Vornamen -- Beispiel : Achim')\"".
                 "\n       placeholder=\"".$arr['Vorname']."\">".
                 "\n   </div>".
                 "\n  </div>".
                 "\n  <div class=\"form-row\">".
                 "\n   <div class=\"form-group col-sm-4\">".
                 "\n     <label class=\"col-form-label\"  for=\"inlineFormInput\">Nachname</label>".
                 "\n     <input class=\"form-control\" type=\"text\" name=\"Nachname\"".
                 "\n      oninput=\"checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$','nicht erlaubtes Zeichen im Nachnamen -- Beispiel : Müller')\"".
                 "\n      placeholder=\"".$arr['Nachname']."\">".
                 "\n   </div>".
                 "\n   <div class=\"form-group col-sm-8\">".
                 "\n     <label class=\"col-form-label\"  for=\"inlineFormInput\">Strasse</label>".
                 "\n     <input class=\"form-control\" type=\"text\" name=\"Strasse\"".
                 "\n        oninput=\"checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s\.]*[0-9]*[a-z]*$','nicht erlaubtes Zeichen im Strassennamen -- Beispiel : Hauptstrasse 13')\"".
                 "\n        placeholder=\"".$arr['Strasse']."\">".
                 "\n   </div>".
                 "\n  </div>".
                 "\n  <div class=\"form-row\">".
                 "\n   <div class=\"form-group col-sm-6\">".
                 "\n    <label class=\"col-form-label\"  for=\"inlineFormInput\">PLZ</label>".
                 "\n    <input class=\"form-control\" type=\"text\" name=\"PLZ\"".
                 "\n      oninput=\"checkField(this,'^[0-9]{5,5}$','nicht erlaubtes Zeichen in der Postleitzahl oder ungültige Länge -- Beispiel : 12555')\"".
                 "\n      placeholder=\"".$arr['PLZ']."\">".
                 "\n   </div>".
                 "\n   <div class=\"form-group col-sm-6\">".
                 "\n    <label class=\"col-form-label\" for=\"inlineFormInput\">Ort</label>".
                 "\n    <input class=\"form-control\" type=\"text\" name=\"ORT\"".
                 "\n      oninput=\"checkField(this,''^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s]*$','nicht erlaubtes Zeichen im Ortsnamen -- Beispiel : Bremen')\"".
                 "\n      placeholder=\"".$arr['ORT']."\">".
                 "\n   </div>".
                 "\n  </div>";

      }
    }

  return $output;  

 }




/*! \brief Html-Ausabe von Formular Input Feldern(Iban,Kuenstlername,BIC,Vita)
    \param $prop_arr Ein Array mit den Datensätzen Eigenschaften eines Kuenstlers
    \return $output Ein Formular  mInput Feldern(Iban,Kuenstlername,BIC,Vita)
*/
function GetHtmlArtistProperties( $prop_arr ){
  $output ="";
   if(!empty($prop_arr)){
      foreach ( $prop_arr as $arr ) {
        $output =  "\n  <div class=\"form-row\">".
                   "\n   <div class=\"form-group col-sm-6\">".
                   "\n      <label class=\"col-form-label\"  for=\"inlineFormInput\">IBAN</label>".
                   "\n      <input class=\"form-control\" type=\"text\" name=\"IBAN\"".
                   "\n         oninput=\"checkField(this,'^[A-Z]{2,4}[0-9]{5,10}$','nicht erlaubtes Zeichen in der IBAN oder falsche Länge -- Beispiel : DE8154565487')\"".
                   "\n         placeholder=\"".$arr['IBAN']."\">".
                   "\n    </div>".
                   "\n   <div class=\"form-group col-sm-6\">".
                   "\n      <label class=\"col-form-label\" for=\"inlineFormInput\">Kuenstlername</label>".
                   "\n      <input class=\"form-control\" type=\"text\" name=\"Kuenstlername\"".
                   "\n         oninput=\"checkField(this,'^[a-zA-Z\\w\\s]*$','nicht erlaubtes Zeichen im Künstlernamen -- Beispiel : JackThePainter')\"".
                   "\n         placeholder=\"".$arr['Kuenstlername']."\">".
                   "\n   </div>".
                   "\n  </div>".
                   "\n  <div class=\"form-row\">".
                   "\n   <div class=\"form-group col-sm-6\">".
                   "\n     <label class=\"col-form-label\" for=\"inlineFormInput\">BIC</label>".
                   "\n     <input class=\"form-control\" type=\"text\" name=\"BIC\" ".
                   "\n         oninput=\"checkField(this,'^[A-Z\\w]{2,7}[0-9]{4,10}*$','nicht erlaubtes Zeichen in der BIC oder falsche Länge -- Beispiel : GESODED2378978')\"".
                   "\n         placeholder=\"".$arr['BIC']."\">".
                   "\n   </div>".    
                   "\n   <div class=\"form-group col-sm-6\">".
                   "\n     <label class=\"col-form-label\" for=\"inlineFormInput\">Vita</label>".
                   "\n     <input class=\"form-control\" type=\"text\" name=\"Vita\"".
                   "\n         oninput=\"checkField(this,'^[\\w\\s]*$','nicht erlaubtes Zeichen in der Vita -- Beispiel : künstlerische Ansprüche sprechen mich an')\"".
                   "\n         placeholder=\"".$arr['Vita']."\">\n";
                   "\n   </div>".
                   "\n  </div>".
                   "\n </div>";
          
      }
    }

  return $output;  

}

/*! \brief Html-Ausabe von Formular Input Feldern(titel,Preis,hoehe,breite,gewicht,hrstlDatum,Beschreibung) + submit
    Durch die Datenbankfunktion "UpdateChangesKunstwerk" werden die Daten gleich geupdatet
    \param $prop_arr Ein Array mit den Datensätzen Eigenschaften eines Kunstwerkes
    \return $output Ein Formular  m Input Feldern(titel,Preis,hoehe,breite,gewicht,hrstlDatum,Beschreibung) + submit
*/
function GetHtmlChangesKunstwerk(){
  global $msg;
  $output ="";
  if ( isset($_GET['nmbr']) ){
    $pic_number  = "'";
    $pic_number .= $_GET['nmbr'];
    $pic_number .= "'";

    $titel = $_SESSION[$pic_number]['Titel'];
    $preis = $_SESSION[$pic_number]['Preis'] ;
    $hoehe = $_SESSION[$pic_number]['Hoehe'] ;
    $breite = $_SESSION[$pic_number]['Breite'] ;
    $gewicht = $_SESSION[$pic_number]['Gewicht'] ;
    $herstell = $_SESSION[$pic_number]['Herstellungsdatum'] ;
    $beschreibung = $_SESSION[$pic_number]['Beschreibung'] ;

    $msg = UpdateChangesKunstwerk();

    if(!isset($_POST['submit']) ){
       $output = "\n <input type=\"text\" name=\"Titel\" placeholder=\"".$titel."\">".
                 "\n <input type=\"text\" name=\"Preis\" placeholder=\"".$preis."\">".
                 "\n <input type=\"text\" name=\"Hoehe\" placeholder=\"".$hoehe."\">".
                 "\n <input type=\"text\" name=\"Breite\" placeholder=\"".$breite."\">".
                 "\n <input type=\"text\" name=\"Gewicht\" placeholder=\"".$gewicht."\">".
                 "\n <input type=\"text\" name=\"Herstellungsdatum\" placeholder=\"".$herstell."\">".
                 "\n <input type=\"text\" name=\"Beschreibung\" placeholder=\"".$beschreibung."\">".
                 "\n <input type=\"submit\" name=\"submit\">";
      $msg = "";
    } 
    else {
      $output = $msg ;
    }
  
  }
  return $output;
}

?>