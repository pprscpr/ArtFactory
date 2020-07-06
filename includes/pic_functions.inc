<?php
/*
=========================================================================================
pic_funtions.inc

Diese Funktionen sind für den Upload von Bildern auf den Server gedacht.

Es werden nur Bilder im Format .jpg, .png, oder .gif akzeptiert.

Die Bilder werden vorher auf Fehler überprüft :
Bildgröße,
vollständiger Upload?,
Datei vorhanden?,
ist die Datei ein Bild?,
richtiges Format,

Die empfangen Bilder werden erst zum Image kovertiert danach neu skaliert
und in 2 größen (small, big) in die gewünschten Pfade gespeichert.


========================================================================================
*/

/*
mfs = maximum file size
Hier wird maximale Größe des Bildes wird festgelegt.
*/
$mfs = 16*1024*1024;
ini_set('upload_max_filesize', $mfs );


/*
Diese Funktion kümmert sich im Fehlerfall um die Fehlerausgabe 
return ist eine ein div der Klasse "error" + vorformatierten Fehlerstring.

AufrufBsp.:
 if ( isset($_GET['err']) ){
        $error = upload_pic_print_error( $_GET['err'] );
  }
*/
function UploadPicPrintError( $errno ){
  $maxsize = ini_get('upload_max_filesize');
  switch ( $errno ){
    case  1: $errtext= "Dieses Bild ist zu groß. Es werden nur Bilder ".
                       "bis zu ".$maxsize." akzeptiert!";
             break;
    case  3: $errtext= "Ihre Date wurde leider nur teilweise geladen.".
                       " Bitte starten Sie den Upload erneut.";
             break;
    case  4: $errtext= "Sie haben keine Datei angegeben!";
             break;
    case 10: $errtext= "Diese Datei ist kein Bild! ";
             break;
    case 11: $errtext= "Dieses Bild hat das falsche Format! ".
                       " Es werden nur Bilder im Format .jpg, .png, oder .gif akzeptiert.";
             break;
    
  }

  return "<div class=\"error\">Fehler beim Bildupload<br />".$errtext.
           "</div>";
}


/*
Eigentliche Upload Funktion für Bilder

Es werden nur Bilder im Format .jpg, .png, oder .gif akzeptiert.

Die Bilder werden vorher auf Fehler überprüft :
Bildgröße,
vollständiger Upload?,
Datei vorhanden?,
ist die Datei ein Bild?,
richtiges Format,

Die empfangen Bilder werden erst zum Image kovertiert danach neu skaliert
und in 2 größen (small, big) in die gewünschten Pfade gespeichert.

param keine
return Bildname des hochgeladenen Bildes
*/
function UploadPicCreateResizedPics(){
	if ( isset($_POST['submit_all']) ){
	    // temporäre Datei merken
	    $orig_file = $_FILES['bild']['tmp_name'];
	    // Vorsicht! Normalerweise beachten: Fehler beim Upload aufgetreten?
	    if ( $_FILES['bild']['error'] != 0  ){
	       // Fehlerbehandlung
	       header("Location: ./pic_upload.php?err=".$_FILES['bild']['error']."&".SID);
	    }
	    $file_info = GetImageSize($orig_file);
	    // Ist die Datei ein Bild?
	    if ( !empty($file_info) ){
	      // Bildinfos anzeigen
		      if(defined(__MYDEBUG__)&&__MYDEBUG__){
		      		DebugArr( $file_info );
		      }   
	    }
	    else {
	   	  // Umlenkung mit Fehlermeldung
	      header("Location: ./pic_upload.php?err=10&".SID);
	      exit();
	    }
	
		// Abhängig vom Dateityp ein image des Originals (Rohdaten) erstellen.
	    // Haben wir ein akzeptables Format? zulässig sind : jpg png gif
	    switch ( $file_info[2] ){
	      case 1 : // gif erkannt
	               $orig_img = ImageCreateFromGIF( $orig_file );
	               break;
	      case 2 : // jpg erkannt
	               $orig_img = ImageCreateFromJPEG( $orig_file );
	               break;
	      case 3 : // png erkannt
	               $orig_img = ImageCreateFromPNG( $orig_file );
	               break;
	      default: // unerwünschtes Bildformat -> Umlenkung mit Fehler
	               header("Location: ./pic_upload.php?err=11&".SID);
	               exit();
	    }

		// Vorbereitung: einige Hilfsvariablen für die Images und Bilddateien
	    // Berechnung des Formates: Landscape oder Portrait
	    $format = ($file_info[0]>$file_info[1])?"l":"p";
	    // Neue images in den Wunschgrößen vorbereiten.
	    define("BIG_SIZE",   600); // max_dimension für das Vollbild
	    define("SMALL_SIZE", 150); // max_dimension für Galerien
	    $bildname = "pic_".time().mt_rand(1000,9999).".png";
	    // Wo werden die Bilder abgespeichert? Ordner müssen vorher existieren.
	    $dest_big   = "./pics/big/";
	    $dest_small = "./pics/small/";
	    // Neue Dimensionen berechnen in Abhängigkeit vom Format:
	    // Dimensionen für Landscape
	    if ( $format == "l" ){ 
	      $new_width_b  = BIG_SIZE;
	      $new_height_b = BIG_SIZE * $file_info[1]/$file_info[0];
	      $new_width_s  = SMALL_SIZE;
	      $new_height_s = SMALL_SIZE * $file_info[1]/$file_info[0];
	    }
	    else { 
	      // Dimensionen für Portrait 
	      $new_width_b  = BIG_SIZE * $file_info[0]/$file_info[1];
	      $new_height_b = BIG_SIZE;
	      $new_width_s  = SMALL_SIZE * $file_info[0]/$file_info[1];;
	      $new_height_s = SMALL_SIZE;
	    }
	    // neue - leere! - images erstellen:
	    $big_img =   ImageCreateTrueColor( $new_width_b, $new_height_b );
	    $small_img = ImageCreateTrueColor( $new_width_s, $new_height_s );

	    // original_image in die passenden ziel_images kopieren
	    /* ImageCopyResized( 
	              zielimage,                  quellimage,
	              ziel_x_start, ziel_y_start, q_x_start, q_y_start,
	              ziel_width  , ziel_height, 
	              q_width,   q_height    )
	    */
	    //Kopie des großen Bildes in guter Qualität erstellen.
	    ImageCopyResampled( $big_img,         $orig_img,
	                      0, 0,             0, 0,
	                      $new_width_b,  $new_height_b, 
	                      $file_info[0], $file_info[1]  );
	    //Kopie des kleinen Bildes in guter Qualität erstellen.
	    ImageCopyResampled( $small_img,         $orig_img,
	                      0, 0,             0, 0,
	                      $new_width_s,  $new_height_s, 
	                      $file_info[0], $file_info[1]  );

	    // großes Bild als PNG abspeichern (Quelle,Ziel)
	    ImagePNG( $big_img,   $dest_big.$bildname  );
	    ImagePNG( $small_img, $dest_small.$bildname  );
	    // kleines Bild als PNG abspeichern (Quelle,Ziel)
	    ImageDestroy( $orig_img );
	    ImageDestroy( $big_img );
	    ImageDestroy( $small_img );

	    return $bildname;
	}
}

?>