<?php


  include './includes/php_functions.inc';


  Init( );
  DebugAll();
  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn( );
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // Trage Daten des Kuenstlers in DB ein im Fehlerfall errorstring
  $Errorstring_reg = becomeArtist(ConnectArtDB( 'Admin' ));
  
  ?>

<!DOCTYPE html>
<html>
 <?php include('template/header.php') ?> 


          <div class="container">
            <h1>Als Künstler registrieren</h1>
            <p>Wenn Sie selbst Ihre Werke einstellen möchten, müssen Sie nur noch Ihre Daten hier lassen, dann kann es losgehen.</p>
             <?php if(!empty($Errorstring_reg)) { 
                      echo  "<div class=\"alert alert-warning\" role=\"alert\"> <strong>". $Errorstring_reg.
                         "</strong></div>";
                    } 
             ?>
            <div class="row justify-content-center">
              
            <div class="col-md-8">
            <div class="card" id= "main-card">
              <div class="card-header">Login</div>
               <div class="card-body">
               <div id="demo">
               </div>
                <form action=" <?php $_SERVER['PHP_SELF'] ?> " class="form-container" method="post">
                    <div class="form-group row">
                        <label for="text" class="col-md-4 col-form-label text-md-right">IBAN</label>
                      <div class="col-md-6">
                        <input class="form-control " type="text" name="IBAN" placeholder="IBAN" 
                               oninput="checkField(this,'^[A-Z]{2,4}[0-9]{5,10}$'
                               ,'nicht erlaubtes Zeichen in der IBAN oder falsche Länge -- Beispiel : DE8154565487')" />
                      </div>
                    </div>
                    <div class="form-group row">
                        <label for="text" class="col-md-4 col-form-label text-md-right">BIC</label>
                      <div class="col-md-6">
                        <input type="text" name="BIC" placeholder="BIC"
                                oninput="checkField(this,'^[A-Z\\w]{2,7}[0-9]{4,10}*$'
                                ,'nicht erlaubtes Zeichen in der BIC oder falsche Länge -- Beispiel : GESODED2378978')" /> 
                               
                    </div>
                   </div>
                   <div class="form-group row">
                        <label for="text" class="col-md-4 col-form-label text-md-right">Künstlername</label>
                      <div class="col-md-6">
                        <input class="form-control " type="text" name="Kuenstlername" placeholder="Kuenstlername" 
                               oninput="checkField(this,'^[a-zA-Z\\w\\s]*$'
                               ,'nicht erlaubtes Zeichen im Künstlernamen -- Beispiel : JackThePainter')" />
                      </div>  
                   </div>
                   <div class="form-group row">
                        <label for="password" class="col-md-4 col-form-label text-md-right">Vita</label>
                      <div class="col-md-6">
                        <input class="form-control " type="text" name="Vita" placeholder="Vita" 
                                oninput="checkField(this,'^[\\w\\s\,\.]*$'
                                ,'nicht erlaubtes Zeichen in der Vita -- Beispiel : künstlerische Ansprüche sprechen mich an')" >
                   </div>
                        <input class="btn btn-dark" type="submit"name="becomeArtist" value="Absenden" />
                   </div>
                  </div>
                </form>
             </div>
            </div>
          </div>
        </div>

    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>

    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="./js/script.js"></script>
    <script src="./js/anim.js"></script>
  
  </body>
</html>
