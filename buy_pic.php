<?php
include 'includes/php_functions.inc';

Init();
DebugAll();
// ist der user eingelogged ?
$is_logged_in = IsLoggedIn2BuyPic();
// wenn eingelogged ist dann wird der Name und Daten des Bildes an die Umleiteseite weitergegeben , sonst Login eingeben
BuyPic( $is_logged_in );
?>
<!DOCTYPE html>
<html>
 
 <?php include('template/header.php') ?> 



<div class="container">
    <div class="row justify-content-center">
        <div class="col-md-8">
            <div class="card" id= "main-card">
                <div class="card-header">Einloggen um das Bild zu kaufen</div>
                <p>Bitte geben Sie Ihre Login Daten ein, um das Bild zu erwerben.</p>
                <div class="card-body">

                    <form method="post" action="./buy_pic.php">
                        <input type="hidden" name ="<?php echo session_name();?>" 
                                     value="<?php echo session_id();  ?>" />
                        <input type="hidden" name="img" value="<?php echo $image ?>">
                        <input type="hidden" name="id" value="<?php echo $image_ID ?>">

                        
                        <div class="form-group row">
                            <label for="email" class="col-md-4 col-form-label text-md-right">Login</label>

                            <div class="col-md-6">
                                <input id="login" type="text" class="form-control " name="login"  required autocomplete="login" autofocus>

                                <!-- Wenn ein Fehler auftritt oder email nicht gueltig oder leer -->
                                    <span class="invalid-feedback" role="alert">
                                        <strong><?php echo $ErrString ?></strong>
                                    </span>
                               
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
