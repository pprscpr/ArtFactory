  <head>
    <meta charset="utf-8">
    <title>ArtFactory</title>
    <!-- google Fonts -->
    <link href="https://fonts.googleapis.com/css?family=Poppins:300,400,500,600,700%7CRoboto%7CJosefin+Sans:100,300,400,500" rel="stylesheet" type="text/css">
    <!-- cdn Link ist fuer Bootstrap notwendig -->
    <link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
    <link rel="stylesheet" href="css/style.css">
    <!-- Scroll Script import, Script muss vor dem Body geladen werden -->
    <script src="https://unpkg.com/scrollreveal/dist/scrollreveal.min.js"></script>
    <script src="./js/script.js"></script>
  </head>
  <body>
    <!-- nav from bootstrap basic Template -->
    <nav class="navbar navbar-expand-md navbar-dark bg-dark shadow-sm navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="{{ __('Toggle navigation') }}">
                    <span class="navbar-toggler-icon"></span>
                </button>
          <a class="navbar-brand" href="./index.php?<?php echo SID;?>">ArtFactory</a>
        </div>
        <div id="navbarSupportedContent" class="collapse navbar-collapse">
          <ul class="nav navbar-nav mr-Auto">
            <li class="nav-item"><a class="nav-link" href="./welcome.php?<?php echo SID; ?>">Home</a></li>
            <li class="nav-item"><a class="nav-link" href="./index.php?<?php echo SID."#info1"; ?>">Über uns</a></li>
            <li class="nav-item"><a class="nav-link" href="./index.php?<?php echo SID."#contact"; ?>">Kontakt</a></li>
            <li class="nav-item"><a class="nav-link" href="./show_gallery.php?<?php echo SID."&sort=All"; ?>">Galerie</a></li>
            <li class="nav-item"><a class="nav-link" href="./datenschutz.php?<?php echo SID."&sort=All"; ?>">Datenschutz</a></li>
            <li class="nav-item"><a class="nav-link" href="./impressum.php?<?php echo SID."&sort=All"; ?>">Impressum</a></li>
          </ul>
           <ul class="navbar-nav ml-auto">
            <!-- Wenn der Kunde noch kein Künstler ist, dann zeige Künstler an -->

            <?php
              if(!$is_logged_in){
                
                echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"./register.php\">Registrieren</a></li>";
                echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"./login.php\">Login</a></li>";
              }
              else{
                if(!$is_artist){
                  echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"./become_artist.php?".SID."\">Künstler werden</a></li>";
                }
                echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"./my_area.php?".SID."\">Mein Bereich</a></li>";
                echo "<li class=\"nav-item\"><a class=\"nav-link\" href=\"./logout.php\">Logout</a></li>";

              }
            ?>
            
          
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>