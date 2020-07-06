
<?php
  include './includes/php_functions.inc';

  Init(); 
  DebugAll();
  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn( );
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // Ausgabe eines Formulares mit den Eigenschaften der Bilddaten. Ändern der Daten möglich + Erfolgs- Fehlermeldung
  $output = GetHtmlChangesKunstwerk();
  
  ?>

<!DOCTYPE html>
<html>
  <?php include('template/header.php') ?>


          <div class="container">
            <h1>Bilddaten ändern</h1>
             <div id="Reg-From">
              <form action="./change_pic.php?<?php echo SID ?>&nmbr=<?php echo $_GET['nmbr'] ?>" class="form-container" method="post">
                <!-- Ausgabe Formulardaten von eingestellten Bild -->
                <?php echo $output; ?>
                  
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
