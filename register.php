
<?php

  include './includes/php_functions.inc';
  Init(  ); 
  DebugAll();
  // Ein neuer user wird regestriert , sonst Fehlermeldung
  $Errorstring_reg = ArtInsertNewUser(ConnectArtDB( 'Admin' ));
  // erfasse alle Kontaktarten und gebe sie als Dropdown-Menu aus
  $kontakt_art = GetHtmlKontaktArtDropDown( GetKontaktart( ConnectArtDB( 'Kunde' ) ) );

      // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn2BuyPic();
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));

  ?>

<!DOCTYPE html>
<html>
 
 <?php include('template/header.php') ?>


    <div class="container">
      <!--Errorstring ausgabe :Fehlerfall Regestrierung -->
          
      <?php
        if(!empty($Errorstring_reg)) { 
           echo  "<div class=\"alert alert-warning\" role=\"alert\"> <strong>". $Errorstring_reg
                      ."</strong></div>" ;
         } 
      ?>

<div class="row justify-content-center">
  <div class="col-md-12">
    <div class="card">
      <div class="card-header"> Registrierung</div>
      <div class="card-body">
            <div id=demo>
              <!-- Fehlerausgabetext -->
            </div>

  <form action="./register.php"  method="post">
        <div class="form-group row">
            <div class="col-md-6">
              <label for="name" class="col-md-4 col-form-label text-md-left">Anrede</label>
                <select class= "form-control col-md-8" id="Anrede" name="reg[Anrede]">
                <option value="Herr">Herr</option>
                <option value="Frau">Frau</option>
                <option value="Divers">Divers</option>
              <option value="<?php echo ( !empty($_POST['reg']['Anrede']) ? $_POST['reg']['Anrede']:"-"); ?>"
               selected><?php echo ( !empty($_POST['reg']['Anrede']) ? $_POST['reg']['Anrede']:"-"); ?></option>
            </select> 
          </div>

          <div class="col-md-6">
            <label for="Titel" class="col-md-4 col-form-label text-md-left">Titel</label>
            <input type="text" class="form-control col-md-8" id="Titel" name="reg[Titel]" placeholder="Titel"
             oninput="checkField(this,'^[a-zA-Z\.]*$','nicht erlaubtes Zeichen im Titel -- Beispiel : Dr.')" 
             value="<?php echo ( !empty($_POST['reg']['Titel']) ? $_POST['reg']['Titel']:""); ?>" />
          </div>
  
        </div>
          <div class="form-group row">
            <div class="col-md-6">
              <label for="Vorname" class="col-md-4 col-form-label text-md-left">Vorname</label>
              <input type="text" class="form-control col-md-8" name="reg[Vorname]" placeholder="Vorname"
               oninput="checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$','nicht erlaubtes Zeichen im Vornamen -- Beispiel : Achim')"
                value="<?php echo ( !empty($_POST['reg']['Vorname']) ? $_POST['reg']['Vorname']:""); ?>" />
            </div>
          
            <div class="col-md-6">
              <label for="Nachname" class="col-md-4 col-form-label text-md-left">Nachname</label>
              <input type="text" class= "form-control col-md-8" name="reg[Nachname]" placeholder="Nachname"
               oninput="checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð]*$','nicht erlaubtes Zeichen im Nachnamen -- Beispiel : Müller')"
                value="<?php echo ( !empty($_POST['reg']['Nachname']) ? $_POST['reg']['Nachname']:""); ?>"/>
            </div>
        </div>
        
        <div class="form-group row">
          <div class="col-md-4">
            <label for="loginname" class="col-md-6 col-form-label text-md-left">Loginname</label>
            <input type="text" class= "form-control col-md-6" name="reg[loginname]" placeholder="loginname"
             oninput="checkField(this,'^[a-zA-Z0-9]*$','nicht erlaubtes Zeichen im loginnamen -- Beispiel : harry19stx')"
              value="<?php echo ( !empty($_POST['reg']['loginname']) ? $_POST['reg']['loginname']:""); ?>"/>
          </div>
        
          <div class="col-md-4">
            <label for="password" class="col-md-4 col-form-label text-md-left">Passwort</label>
            <input type="password" class= "form-control col-md-8" name="reg[password]" placeholder="password"
            id="password" />
          </div>
      
          <div class="col-md-4">
            <label for="password" class="col-md-4 col-form-label text-md-left">bestätigen</label>
            <input type="password" class="form-control col-md-8" name="reg[password-confirm]"
             placeholder="confirmPassword" oninput="checkPw(this,'password')"/>
          </div>
        </div>

        <div class="form-group row">
          <div class="col-md-4">
            <label for="Strasse" class="col-md-4 col-form-label text-md-left">Strasse</label>
            <input type="text" class="form-control col-md-8" name="reg[Strasse]" placeholder="Strasse"
             oninput="checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s\.]*[0-9]*[a-z]*$','nicht erlaubtes Zeichen im Strassennamen -- Beispiel : Hauptstrasse 13')"
              value="<?php echo ( !empty($_POST['reg']['Strasse']) ? $_POST['reg']['Strasse']:""); ?>"/>
          </div>
        
          <div class="col-md-4">
            <label for="PLZ" class="col-md-4 col-form-label text-md-left">PLZ</label>
            <input type="text" class="form-control col-md-8" name="reg[PLZ]" placeholder="PLZ"
             oninput="checkField(this,'^[0-9]{5,5}$','nicht erlaubtes Zeichen in der Postleitzahl oder ungültige Länge -- Beispiel : 12555')"
              value="<?php echo (!empty($_POST['reg']['PLZ']) ? $_POST['reg']['PLZ']:""); ?>"/>
          </div>
        
          <div class="col-md-4">
            <label for="Ort" class="col-md-4 col-form-label text-md-left">Ort</label>
            <input type="text" class="form-control col-md-8" name="reg[Ort]" placeholder="Ort"
             oninput="checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s]*$','nicht erlaubtes Zeichen im Ortsnamen -- Beispiel : Bremen')"
              value="<?php echo ( !empty($_POST['reg']['Ort']) ? $_POST['reg']['Ort']:""); ?>"/>
          </div>
        </div>
          
        <div class="form-group row">
          <div class="col-md-4">
            <label for="Kontaktart" class="col-md-4 col-form-label text-md-left">Kontaktart</label>
            <!-- erfasse alle Kontaktarten und gebe sie als Dropdown-Menu aus -->
            <?php echo $kontakt_art ?>
          </div>
          
          <div class="col-md-4">
            <label for="Kontakt" class="col-md-4 col-form-label text-md-left">Kontakt</label>
            <input type="text" class="form-control col-md-8" name="reg[Kontakt]" placeholder="Kontakt"
             oninput="checkFieldKontakt(this)"
              value="<?php echo ( !empty($_POST['reg']['Kontakt']) ? $_POST['reg']['Kontakt']:""); ?>" />
          </div>
          
          <div class="col-md-4">
            <label for="Bemerkung" class="col-md-6 col-form-label text-md-left">Bemerkung</label>
            <input type="text" class="form-control col-md-6" name="reg[Bemerkung]" placeholder="Bemerkung"
             oninput="checkField(this,'^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð\\s\.\,]*$','nicht erlaubtes Zeichen im Titel -- Beispiel : das ist eine sehr schöne Seite')"
              value="<?php echo ( !empty($_POST['reg']['Bemerkung']) ? $_POST['reg']['Bemerkung']:""); ?>"/>
          </div>
        </div>
          
        <div class="form-group row">
            <div class="col-sm-12">
              <input type="submit" class="btn btn-dark" name="register" value="Absenden" />
            </div>
        </div>
  </form>
  
 </div>
</div>

    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="./js/anim.js"></script>

    
  </body>
</html>
