
function checkField(element,regex,whattext){
    var text = whattext;
    var regex1 = new RegExp(regex);
    var input = element.value;
    //document.getElementById("demo").innerHTML = input.length ;
    if(input.match(regex1)){
        element.style.background = "white";
        document.getElementById("demo").innerHTML = "";
        document.getElementById("demo").style.background = "#ffffff";
        console.log("match");
    }
    else{
        element.style.background = "#" + "ffcccc";
        document.getElementById("demo").innerHTML = text;
        document.getElementById("demo").style.background = "#ffffcc";
        console.log("no match");
    }
    
}


function checkFieldKontakt(element){
    
    var KontaktArt = document.getElementById("KontaktArt").value ;
    var input = element.value;

    document.getElementById("demo").innerHTML = KontaktArt;

    switch(KontaktArt){
        case '0': var regex = new RegExp('^[^\\d\\w\\s]*$') ;
                  var mode = "No";
            break;
        case '1': var regex = new RegExp('^[0-9]{5,16}$') ;
                  var mode = "Tel";
            break;
        case '2': var regex = new RegExp('^[0-9]{5,16}$') ;
                  var mode = "Mobile";
            break;
        case '3': var regex = new RegExp('^\\S+@\\S+\\.\\S+$') ;
                  var mode = "Email";
            break;
        case '4': var regex = new RegExp('^[0-9]{5,16}$') ;
                  var mode = "Fax";
            break;
    }
    if(input.match(regex)){
        element.style.background = "white";
        document.getElementById("demo").innerHTML = "";
        document.getElementById("demo").style.background = "#ffffff";
    }
    else {
        element.style.background = "#" + "ffcccc";
        document.getElementById("demo").style.background = "#ffffcc";
        
        switch(mode){
            case 'Tel': document.getElementById("demo").innerHTML = "ungültiges Zeichen in Kontak, unzzulässige Länge -- Bsp.:03015648798" ;
                  
                break;
            case 'Mobile': document.getElementById("demo").innerHTML = "ungültiges Zeichen in Kontak, unzzulässige Länge -- Bsp.:03015648798" ;
                  
                break;
            case 'Email': document.getElementById("demo").innerHTML = "Keine gültige EmailAdresse -- Bsp.: user@example.com" ;
                  
                break;
            case 'Fax': document.getElementById("demo").innerHTML = "ungültiges Zeichen in Kontak, unzzulässige Länge -- Bsp.:03015648798" ;
                break;
            case 'No': document.getElementById("demo").innerHTML = "Bitte zuerst eine Kontaktart auswählen." ;
                break;      
                
        }

    }
}


function checkPw(element,otherpw){
    var pw = element.value;
    var pw2 = document.getElementById(otherpw).value;
    if(pw == pw2){
        element.style.background = "white";
        document.getElementById("demo").innerHTML = "";
        document.getElementById("demo").style.background = "#ffffff";
    }
    else {
        element.style.background = "#" + "ffcccc";
        document.getElementById("demo").innerHTML = "Passwörter stimmen nicht überein";
        document.getElementById("demo").style.background = "#ffffcc";

    }
}

function btnClick(){
    var cookie = document.getElementById("cookie") ;
    cookie.style.display = "none";

}



