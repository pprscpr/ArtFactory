<?php

  include './includes/php_functions.inc';
  Init();
  DebugAll();
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  $is_logged_in = IsLoggedIn( );
  $pw_error = "";
  $pw_bool = false;
  $uid = $_SESSION['login']['uid'];
  $pw = GetHashedPW( ConnectArtDB('Login'), $uid );
  if (isset( $_POST['passwd'] ) && isset( $_POST['passwd-conf'] ) ){
      if( $_POST['passwd'] == $_POST['passwd-conf'] ){
        $pw_bool = UpdatePw( ConnectArtDB('Login'), $_SESSION['login']['uid'],$_POST['passwd'] );
      }
      elseif($_POST['passwd'] != $_POST['passwd-conf']){
        $pw_error = "Passwörter stimmen nicht überein.";
      }

  }
?>
<!DOCTYPE html>

<?php include('template/header.php') ?>

<!-- Ernesto Vorschlag fuer login -->
 <div class="container">
   <?php if(!empty($pw_error)) { 
                                    echo  "<div class=\"alert alert-warning\" role=\"alert\"> <strong>". $pw_error
                                       ."</strong></div>" ;
                                       } ?>
    <div class="row justify-content-center">
        <div class="col-md-12">
            <div class="card" id= "main-card">
              <div class="card-header">Bitte geben Sie Ihr neues Passwort ein!</div>
              <div class="card-body">
            <?php
              if( !$pw_bool ){
                echo "\n<form method=\"post\" action=\"./new_pw.php?\".SID>".
                     "\n <input type=\"hidden\" class\"form-control col-md-8\" name =\"".session_name()."\" 
                                           value=\"".session_id()."\" />".
                  "\n<div class=\"form-group row\">".
                        "\n<label for=\"password\" class=\" col-md-4 col-form-label text-md-right\">Passwort</label>".
                         "\n <div class=\"col-sm-6\">".
                           "\n<input id=\"password\" type=\"password\" class=\"form-control\" name=\"passwd\" required autocomplete=\"current-password\">".
                    "\n</div>".
                    "\n</div>".

                        "\n<div class=\"form-group row \">".
                            "\n<label for=\"password\" class=\"col-md-4 col-form-label text-md-right\">Passwort wiederholen</label>".
                               "\n <div class=\"col-sm-6\">".
                              "\n<input id=\"password\" type=\"password\" class=\"form-control \" name=\"passwd-conf\" required autocomplete=\"current-password\">".

                                  "\n</div>".
                              "\n</div>".

                              "\n<div class=\"form-group row \">
                                  <div class=\"col-md-8 offset-md-4\">
                                      <input type=\"submit\" name=\"Neues Passwort bestätigen\" class=\"btn btn-dark\" value=\"Absenden\">
                                 
                                 </div>
                              </div>
                              </div>
                              </div>
                          </form>
                        </div>

                    </div>";
                    }
                    else {
                      echo $pw_error;
                    }
                  ?>
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
