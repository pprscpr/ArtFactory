<?php
  
  include './includes/php_functions.inc';
  Init(  );
  DebugAll();
  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn( );
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // Wenn Änderungen an den Userdaten vorgenommen werden, werden diese hier geupdatet
  UpdateChangesUser();
  if($is_artist)
    UpdateChangesArtist();


  //löschen eines Bildes 
  if( isset($_GET['del']) ){
     deleteImage( ConnectArtDB('Admin'), $_GET['del']);
     unset($_GET['del']);
  }

  //befülle ein array mit den Eigenschaften der Bilder die gekauft wurden
  $array = PicturesIBought( ConnectArtDB( 'Gast' ), $_SESSION['login']['uid'] );
  //befülle ein array mit den Eigenschaften der eingestellten Kunstwerke eines Kuenstler
  $artist_array = ArtistPictures( ConnectArtDB( 'Gast' ), $_SESSION['login']['uid'] );
  // Gebe vorformatierten HtmlCode zurück : zeige die Kunstwerke eines Kuenstlers
  $artist_pictures = GetHtmlArtistPictures( $artist_array );                 
  // Gebe vorformatierten HtmlCode zurück : zeige die Bilder die gekauft wurden
  $output = GetHtmlPicturesIBought( $array );
  // Gebe vorformatierten HtmlCode zurück : zeige die Eigenschaften eines users
  $properties = GetHtmlUserProperties(UserProperties ( ConnectArtDB( 'Kunde' ) , $_SESSION['login']['uid']) );
  // Gebe vorformatierten HtmlCode zurück : zeige die Eigenschaften eines Kuenstlers
  $properties_art = GetHtmlArtistProperties(  ArtistProperties (ConnectArtDB( 'Kunde' ) , $_SESSION['login']['uid']) );

  
  
?>

<!DOCTYPE html>
<html>
  
   <?php include('template/header.php') ?>

<!-- Section mit Bild links und Text rechts -->
   <?php
      if ($is_artist){
        echo "\n   <section id=\"einstellen\">".
             "\n     <div class=\"container\">".
             "\n      <div class=\"jumbotron\">".
             "\n         <h1>Neue Kunstwerke einstellen</h1>".
             "\n         <a href=\"./pic_upload.php?".SID."\">Kunstwerk einstellen</a>".
             "\n       </div>".
             "\n     </div>".
             "\n   </section>";

        echo "\n   <section id=\"editieren\">".
             "\n     <div class=\"container\">".
             "\n      <div class=\"jumbotron\">".
             "\n         <h1>Kunstwerk editieren</h1>".
             "\n         <p>Kunstwerk ändern</p>".
             "\n       </div>".
             "\n     </div>".
             "\n   </section>";
        
        echo "\n   <section id=\"kunstwerke\">".
             "\n    <div class=\"container\">".
             "\n     <table class=\"table table-condensed\">".
             "\n      <thead>".
             "\n      <tr>".
             "\n       <th>Kunstwerk</th>".
             "\n       <th>Bezeichnung</th>".
             "\n       <th>Eingestellt</th>".
             "\n       <th>Preis</th>".
             "\n       <th>Hoehe</th>".
             "\n       <th>Breite</th>".
             "\n       <th>Gewicht</th>".
             "\n       <th>Herstellungsdatum</th>".
             "\n       <th>Beschreibung </td>".
             "\n       <th>Aktionen</td>".
             "\n      </tr>".
             "\n     </thead>".
             "\n    <tbody>";
        echo  $artist_pictures;
        echo "\n    </table>".
             "\n   </div>".
             "\n  </section>";

      }
   
   ?>
   
   <section id="einstellungen">
        <div class="container">
          <div class="jumbotron">
            <h1> Profildaten ändern </h1> 
            <p>Hier können Sie Ihre Profildaten ändern </p> 
          </div>
        </div>
    </section>

    <section id="Eigenschaften">
      <div class="container">
        <a href="#update"></a>
            <div class="card">
              <div id="demo">
              <!-- Fehlerausgabe -->
              </div>
              <form action="./my_area.php?<?php echo SID."#Eigenschaften" ?>"  method="post">
                <?php 
                   echo $properties;
                   echo $properties_art;
                ?>
                <div class="form-group row">
                  <div class="col-sm-12">
                <input id="subEdit" class="btn btn-dark" type="submit" name="submit">   
                </div>
              </div>
              </form>        
        </div>
      </div>
    </section>
    <section id="einstellen">
      <div class="container">
         <div class="jumbotron">
            <h1>Hier können Sie Ihr Passwort ändern</h1>
            <a href="./change_pw.php?<?php echo SID?>" >Passwort ändern</a>
         </div>
      </div>
    </section>

    <section id="kaeufe">
        <div class="container">
          <div class="jumbotron">
            <h1>Ihre Einkäufe</h1> 
            <p>Hier finden Sie Ihre bereits gekauften Kunstwerke</p> 
          </div>
        </div>
    </section>

    <section id="einkaufsliste">
      <div class="container">
         <table class="table table-condensed">
              <thead>
                <tr>
                  <th>Kunstwerk</th>
                  <th>Bezeichnung</th>
                  <th>Kaufdatum</th>
                  <th>Künstler</th>
                </tr>
              </thead>
              <tbody>
                <?php echo $output; ?>
            </table>
      </div>
    </section>



    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="./js/script"></script>
    <script src="./js/anim.js"></script>
  </body>
</html>

