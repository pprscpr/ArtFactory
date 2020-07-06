<?php
include './includes/php_functions.inc';

  Init(  );
  DebugAll();
  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn2BuyPic();
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  //Hilfsvar wurde das Bild in der Zwischenzeit schon verkauft ?
  $sold = "";
  // Überprüfen ob das Bild schon gekauft wurde->dann Ausgabe
  // sonst Bild kaufen und Bild ausgeben + "Bild gekauft"
  $output = BuyConfirm();
?>
<!DOCTYPE html>
<html>
 <?php include('template/header.php') ?>
 
<div class="container">
<!-- Ausgabe ob das Bild gekauft wurde -->
<?php echo $output; ?>


</div><!-- /container -->

    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="./js/anim.js"></script>
    
  </body>
</html>
