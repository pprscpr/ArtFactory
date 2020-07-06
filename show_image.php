<?php
include './includes/php_functions.inc';

  Init(  );
  DebugAll();
  // ist der user eingelogged ? 
  $is_logged_in = IsLoggedIn2BuyPic();
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // Bild mit jeweiligen Eigenschaften ausgeben
  $image =  GetHtmlBigImage( GetImages( ConnectArtDB( 'Gast' ), "All" ),"buy" );

?>
<!DOCTYPE html>
<html>
  <?php include('template/header.php') ?>

<div class="container">
<!-- Hier sollen Karten angezeigt werden anhand eines grids... CSS oder Bootstrap grid, beides geht. Ich werde dazu Cards verwenden kommt noch.. es muss nur eine in eine foreach eingebunden werden, da die Daten aus der Datenbank kommen. -->
<?php echo $image; ?>


</div><!-- /container -->



    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

    <script src="https://code.jquery.com/jquery-3.2.1.js" integrity="sha256-DZAnKJ/6XZ9si04Hgrsxu/8s717jcIzLy3oi35EouyE=" crossorigin="anonymous"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <script src="./js/anim.js"></script>
  </body>
</html>
