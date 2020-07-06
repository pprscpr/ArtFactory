<?php
include './includes/php_functions.inc';
  Init(  );
  DebugAll();
  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn2BuyPic();
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // sortierungs anweisung erfassen
  $image_sort = $_GET['sort'];
  // Bild feed nach sortierungsalgorithmus ausgeben
  $image_feed = GetHtmlImages( GetImages( ConnectArtDB( 'Gast' ), $image_sort ) );

?>

<!DOCTYPE html>
<html>
  
  <?php include('template/header.php') ?>

<section id="Galerie">
  <div id = "sortOpt" class="container">
      <div class="btn-group" role="group" aria-label="Sortieren nach">
        <div class="btn btn-dark"><a href="./show_gallery.php?<?php echo SID."&sort=All"; ?>">Preis</a></div>
        <div class="btn btn-dark"><a href="./show_gallery.php?<?php echo SID."&sort=New"; ?>">neuste zuerst</a></div>
        <div class="btn btn-dark"><a href="./show_gallery.php?<?php echo SID."&sort=Artist"; ?>">nach Künstler</a></div>
      </div>
  </div><!-- /container -->


      <div class="container">
        <div class="boxes">
            
            <?php echo $image_feed; ?>

        </div><!-- end boxes -->
    </div>

</section>

    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="./js/anim.js"></script>
  </body>
</html>
