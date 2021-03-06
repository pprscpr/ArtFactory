<?php

  include './includes/php_functions.inc';
  Init();
  DebugAll(); 
  // Logindaten gültig ?->Umlenkung nach welcome , sonst Fehlermeldung
  $ErrString = CheckLogin($_POST, "./welcome.php" ) ;     

      // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn2BuyPic();
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));

?>
<!DOCTYPE html>
<html>
  
  <?php include('template/header.php') ?>

<!-- Ernesto Vorschlag fuer login -->

    <div class="container">
       <!-- Wenn ein Fehler auftritt oder email nicht gueltig oder leer -->
                                  <?php if(!empty($ErrString)) { 
                                    echo  "<div class=\"alert alert-warning\" role=\"alert\"> <strong>". $ErrString
                                       ."</strong></div>" ;
                                       } ?>

                                   
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card" id= "main-card">
                <div class="card-header">Login</div>

                <div class="card-body">
                    <form method="post" action="./login.php">
                        <input type="hidden" name ="<?php echo session_name();?>" 
                                     value="<?php echo session_id();  ?>" />
                        <div class="form-group row">
                            <label for="email" class="col-md-4 col-form-label text-md-right">Login</label>

                            <div class="col-md-6">
                                <input id="login" type="text" class="form-control " name="login"  required autocomplete="login" autofocus>

                               
                               
                            </div>
                        </div>

                        <div class="form-group row">
                            <label for="password" class="col-md-4 col-form-label text-md-right">Passwort</label>

                            <div class="col-md-6">
                                <input id="password" type="password" class="form-control " name="passwd" required autocomplete="current-password">

                            </div>
                        </div>

                        <div class="form-group row mb-0">
                            <div class="col-md-8 offset-md-4">
                                <input type="submit" name="submit" class="btn btn-dark" value="Absenden">
                               
                                
                            </div>
                        </div>
                    </form>
                </div>
            </div>
        </div>
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
