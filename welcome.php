<?php
  
  include './includes/php_functions.inc';
  Init(  );
  
  DebugAll();
  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn( );
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // erstelle ein array mit den Bildern und deren Eigenschaften, die schon gekauft wurden 
  $array = PicturesIBought( ConnectArtDB( 'Gast' ), $_SESSION['login']['uid'] );      
  // gebe die gekauften Bilder als Tabelle aus
  $output = GetHtmlPicturesIBought( $array );


 
  
?>

<!DOCTYPE html>
<html>
 <?php include('template/header.php') ?>

<!-- Section mit Bild links und Text rechts -->
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
                <!-- gebe die gekauften Bilder als Tabelle aus -->
                <?php echo $output; ?>
            </table>
      </div>
    </section>

   <section id="floskel">
      <div class="container floskel-left">
        <p>Wir hoffen, dass Ihnen Ihre Kunstwerke viel Freude bereiten. <br /> 
        Wir laden Sie gerne in unsere Galerie zum Wein und Kunstgenuss ein. <br /> 
      Wir freuen uns auf Sie.</p>
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

