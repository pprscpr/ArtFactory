<?php

include './includes/php_functions.inc';
include './includes/pic_functions.inc';

  Init(  );
  DebugAll();
  //ist der User wirklich eingelogged ?
  $is_logged_in = IsLoggedIn( );
  // ist der User ein Kuenstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  
  // ist der User eingelogged und ist er ein kuenstler ?
  if($is_artist && $is_logged_in ){
      // Fehlermeldung_init
      $error ="";
      // Kunststile und Beschreibung erfassen und in Tabelle ausgeben
      $show_styles = GetHtmlStyles( GetStyles( ConnectArtDB( 'Gast' ) ) );
      // Kunststile mit Kennziffer erfassen und als DropdownMenu ausgeben
      $get_style_dropdown = GetHtmlStyleDropDown( GetStyles( ConnectArtDB( 'Gast' ) ) );
      // Fehlermeldung auswerten 
      $db_error = InsertNewPicture( ConnectArtDB( 'Admin' ) );

      // ist ein Fehler aufgetreten ?
      if ( isset($_GET['err']) ){
        // Fehlermeldungcode erfassen und auswerten
            $error = UploadPicPrintError( $_GET['err'] );
      } // Bild hochladen geklickt ?
      elseif ( isset($_POST['submit_all']) && empty($db_error) ) {
        // Ausgabe dass das Bild erfolgreich hochgeladen wurde
            $error = "Upload war erfolgreich";
      }
  } // Der User ist kein Kuenstler oder nicht eingelogged -> Umlenkung
  else {
    header("Location: ./welcome.php?".SID."&nein=nein");
  }

?>


<!DOCTYPE html>
<html>
 
 <?php include('template/header.php') ?>
    

<!-- Form für den Upload eines Bildes , nur Backend, noch unbehandelt-->
    <div id = "maincontainer" class="container">
      
        <!-- Fehlermeldung ausgeben -->
        <div id="Fehler_Upload">
          <?php echo $error." ".$db_error ; ?>
        </div>
        
        <!-- Formular inkl alle notwendiger Daten um ein Bild hochzuladen -->
        <div class="row justify-content-center">
        <div class="col-md-12">
            <div class="card">
                <div class="card-header">Upload eines Bildes</div>
                <div class="card-body">
                <div id="demo">
                </div>
            <form method="post" action="pic_upload.php?<?php echo SID?>" enctype="multipart/form-data" >
              <div class="form-group row">
                <div class="col-md-12">
                <label class="col-md-4 col-form-label text-md-left" >Bild:</label>
                <input class= "form-control-file col-md-8 " type="file" name="bild" />
              </div>
            </div>
              <div class="form-group row">
                <div class="col-md-4">
                <label class="col-md-4 col-form-label text-md-left" >Bildname</label>
                <input type="text" class= "form-control-file col-md-6 " name="picName" 
                        oninput="checkField(this,'^[a-zA-Z0-9\\s]*$','nicht erlaubtes Zeichen im Bildnamen -- Beispiel : Die vier Fragezeichen')"
                        value="<?php echo (!empty($_POST['picName']) ? $_POST['picName']:""); ?>"
                        placeholder="Name des Bildes" />
              </div>
               <div class="col-md-4">
                <label class="col-md-6 col-form-label text-md-left" >Bildhöhe</label>
                <input type="text" class= "form-control-file col-md-6 " name="height" 
                        oninput="checkField(this,'^[0-9]*$','nicht erlaubtes Zeichen in der Höhe -- Beispiel : 22')"
                        value="<?php echo (!empty($_POST['height']) ? $_POST['height']:""); ?>"
                        placeholder="Höhe des in mm" />
              </div>
              <div class="col-md-4">
                <label class="col-md-6 col-form-label text-md-left" >Bildbreite</label>
                <input type="text" class= "form-control-file col-md-6 " name="width" 
                        oninput="checkField(this,'^[0-9]*$','nicht erlaubtes Zeichen im Breite -- Beispiel : 33')"
                        value="<?php echo (!empty($_POST['width']) ? $_POST['width']:""); ?>"
                        placeholder="Breite des in mm" />
              </div>
            </div>
            <div class="form-group row">
                <div class="col-md-6">
                <label class="col-md-4 col-form-label text-md-left" >Preis</label>
                <input type="text" class= "form-control-file col-md-8 " name="price" 
                        oninput="checkField(this,'^[0-9]{1,10},[0-9]{2,2}$','nicht erlaubtes Zeichen im Preis oder ungültige Länge -- Beispiel : 12,00')"
                        value="<?php echo (!empty($_POST['price']) ? $_POST['price']:""); ?>"
                        placeholder="Bitte mit Nachkommastelle angeben! 20,30" />
              </div>
               <div class="col-md-6">
                <label class="col-md-4 col-form-label text-md-left" >Gewicht in g</label>
                 <input type="text" class= "form-control-file col-md-8 " name="weight" 
                          oninput="checkField(this,'^[0-9]{1,10}$','nicht erlaubtes Zeichen in der Gewichtsngabe oder ungültige Länge -- Beispiel : 300')"
                          value="<?php echo (!empty($_POST['weight']) ? $_POST['weight']:""); ?>"
                          placeholder="Gewicht in g" />
              </div>
             </div>

            <div class="form-group row">
            <div class="col-md-12">
                <label class="col-md-4 col-form-label text-md-left" >Beschreibung</label>
                <input type="text" class="col-md-8 col-form-label text-md-left" name="descr" 
                        oninput="checkField(this,'^[a-zA-Z\\w\\s]*$','nicht erlaubtes Zeichen in der Beschreibung -- Beispiel : Auquarellmalerei')"
                        value="<?php echo (!empty($_POST['descr']) ? $_POST['descr']:""); ?>"
                        placeholder="Beschreibung" />
              </div>
            </div>
            <div class="form-group row">
                <div class="col-md-12">
                <label class="col-md-4 col-form-label text-md-left" >Erstellungsdatum</label>
                <input type="text" class= "form-control-file col-md-8 " name="date" 
                        oninput="checkField(this,'^[0-9]{1,2}\.([0-9]{2,2}||(Jan||Feb||Mar||Apr||Mai||Juni||Juli||Aug||Sep||Nov||Dec))\.[0-9]{2,4}$',
                        'nicht erlaubtes Zeichen im Datum oder falsches Format -- Beispiel : 20.01.2020 oder 20.Jan.2020')"
                        value="<?php echo (!empty($_POST['date']) ? $_POST['date']:""); ?>"
                        placeholder="Bitte im Format : 20.01.2019 oder 20.Jan.2019 eingeben" />
              </div>
            </div>

              <div class="form-group row">
                <div class="col-md-12">
                <label class="col-md-4 col-form-label text-md-left" >Stilrichtungen</label>
                <!-- DropdownMenu für Stile erzeugen -->
              <?php echo $get_style_dropdown; ?> <!-- name="style"-->
              </div>
             </div>
          
              <div class="btn-group">
              <input type="reset" class="btn btn-warning" value="Reset" />
              <input type="submit" class="btn btn-dark" name="submit_all" value="Bild einstellen" />
              </div>
            </form>
        </div>
      </div>
      </div>
    </div>
  </div>

      <!-- Alle Stile nocheinmal aufgelistet und erklärt -->
      <div class ="container" id="Stile erklärt">
        <?php echo $show_styles; ?>
      </div>
    </div><!-- /container --> 



    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

   <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
   <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
   <script src="./js/script.js"></script>
   <script src="./js/anim.js"></script>
  </body>
</html>

