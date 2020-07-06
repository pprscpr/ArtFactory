
<?php

  include './includes/php_functions.inc';
  Init(  );
  DebugAll();               

  $error = CheckSessionError( );
  


  // ist der user eingelogged ?
  $is_logged_in = IsLoggedIn2BuyPic();
  // ist der user ein Künstler ?
  $is_artist = isUserAnArtist(ConnectArtDB( 'Gast' ));
  // Nachrichten der User in txt-Datei abspeichern
  UserMessages($_POST);
  


?>

<!DOCTYPE html>
<html>
  
  <?php include('template/header.php') ?>

<!-- alt. CookieBanner-->
<!--<div id="cookie">
    <h1>Cookies</h1>
     <p>Wir möchten Ihnen mitteilen, dass wir KEINE! Cookies verwenden</p>
     <button onclick="btnClick()">Schade</button>
</div>-->

    <section id="showcase">
      <div class="container"> <!-- moves content away from left towards center-->
        <div class="row">
          <div class="col-md-6 col-sm-6">
            <div class="showcase-left">
              <img src="img/colors.jpg">
            </div>
          </div>
         
          <div class="col-md-6 col-sm-6">
            <div class="showcase-right">
              <h1>Wilkommen auf der ArtFactory Homepage</h1>
              <p>ArtFactory ist einer der führenden Online-Händler, wenn es um Kunst geht. Wir bieten Ihnen ein Online-Galerie in der Sie ohne Zeitdruck unser vielfältiges Sortiment an exklusiven Kunstwerken bestaunen können.</p>
            </div>
            <br />
            <!-- Link zur Gallery sort:Preis-->
            <a class="btn btn-dark" href="./show_gallery.php?<?php echo SID."&sort=All"; ?>" class="btn btn-default btn-lg showcase-btn">Unser Angebot</a>
          </div>
        </div>
      </div>
    </section>

    <section id="cite">
      <div class="container">
        <p>"Wenn es eine Freude ist, das Gute zu genießen, ist es eine größere, das Bessere zu empfinden, und in der Kunst ist das Beste gut genug."</p>
        <p class="origin">- Johann Wolfgang von Goethe</p>
      </div>
    </section>

    <section id="info1">
      <div class="container">
        <div class="row">
          <div class="col-md-6 col-sm-6">
            <div class="info-left">
              <img src="img/brushpaint.jpg">
            </div>
          </div>
          <div class="col-md-6 col-sm-6">
            <div class="info-right">
              <h2>Unser Sortiment</h2>
              <p>Unsere Galerie bietet von Abstrakter Malerei bis Vortizismus alle Stilrichtungen von verschiedensten Künstlern an.  </p>
              <br />
              <!-- Link zur Gallery sort:neueste zuerst-->
              <a class="btn btn-dark" href="./show_gallery.php?<?php echo SID."&sort=New"; ?>"class="btn btn-default btn-lg">Neue Kunstwerke</a>
            </div>
          </div>
        </div>
      </div>
    </section>
    <hr />
    <section id="info2">
      <div class="container">
        <div class="row">
          <div class="col-md-6 col-sm-6">
            <div class="info-left">
              <h2>Unsere Künstler</h2>
              <p>Sind professionelle Künstler in der Entwicklung bis hin zu hochklassigen, professionellen Künstlern mit bemerksenswerten Organisationstalent, die populär und gefragt sind.</p>
              <br />
              <!-- Link zur Gallery sort: nach Kuenstler sortiert-->
              <a class="btn btn-dark" href="./show_gallery.php?<?php echo SID."&sort=Artist"; ?>"class="btn btn-default btn-lg">Unsere Künstler</a>
              
            </div>
          </div>
          <div class="col-md-6 col-sm-6">
            <div class="info-right">
              <h2>Preise</h2>
              <p>Die Preise der Kunstwerke werden durch ein Team von Experten in Absprache mit den Künstlern festgelegt. Diese können abhängig von der Entwicklung des Künstlers über die Zeit stark variieren.</p>
            </div>
          </div>
        </div>
      </div>
    </section>

<div class="container">
    <section id="contact">
      <div class="container">
        <div class="row">
          <div class="col-md-5 col-sm-5">
            <form action="./index.php?<?php echo SID ; ?>" method="post">
              <div class="form-group">
                <label>Name: </label>
                <input class="form-control" type="text" name="message[name]" value="" placeholder="Namen eingeben">
              </div>
              <div class="form-group">
                <label>Email: </label>
                <input class="form-control" type="text" name="message[mail]" value="" placeholder="Email eingeben">
              </div>
              <div class="form-group">
                <label>Message: </label>
                <textarea class="form-control" name="message[message]" value="" placeholder="Nachricht eingeben"></textarea>
              </div>
              <button class="btn btn-dark">Absenden</button>
            </form>
          </div>
          <div class="col-md-7 col-sm-7">

          </div>
        </div>
      </div>
    </section>
    </div>

    <footer>
      <p class="text-center">ArtFactory Copyright &copy; 2020</p>
    </footer>


    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
    <script src="./js/anim.js"></script>


  </body>
</html>