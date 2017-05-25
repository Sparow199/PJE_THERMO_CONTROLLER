    var ajaxTarget = 'thermostat';
    var timermodeauto = 0;
    var levelKnob = 0;
    var currentTemperature=0;
    var level = 0;
    var red = 30;
    var blue = 10;

    //fonction qui affiche l'heure et la date
    $(function() {

        $('input[name="mode"]').click(function() {
            if ($(this).val() == "manuside") {
                $(".autoside").removeClass("disableSide").addClass("disableSide");
                $(".manuside").removeClass("disableSide");
            } else {
                $(".manuside").removeClass("disableSide").addClass("disableSide");
                $(".autoside").removeClass("disableSide");
            }
        });

        $("#automatiqueMode").click(function() {

        });

        setInterval(function() {
            var seconds = new Date().getTime() / 1000;

            var time = new Date(),
                hours = time.getHours(),
                min = time.getMinutes(),
                sec = time.getSeconds(),
                millSec = time.getMilliseconds(),
                millString = millSec.toString().slice(0, -2),
                day = time.getDay(),
                month = time.getMonth(),
                date = time.getDate(),
                year = time.getFullYear(),
                monthShortNames = ["Jan", "Fev", "Mar", "Avr", "Mai", "Juin",
                    "Juil", "Aout", "Sep", "Oct", "Nov", "Dec"
                ];;

            //add leading zero for min and sec
            if (sec <= 9) sec = "0" + sec;
            if (min <= 9) min = "0" + min;

            $('#hours').text(hours);
            $('#min').text(min);
            $('#sec').text(sec);
            //$("#test").text(day);
            // $('#millSec').text(millString);
            $('.days:nth-child(' + (day + 1) + ')').addClass('active');
            $("#month").text(monthShortNames[month]);
            $('#date').text(date);
            $('#year').text(year);
        }, 100);

    });



    //fonction qui s'execute lors du chargement
    function init() {
        alertify.parent(document.body);
        console.log("init()s'est executée");

        doAjax(ajaxTarget  + "?level=" + level + "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);

        alerteTemp();

        //désatvier le controller
        $(".autoside").removeClass("disableSide").addClass("disableSide");
        $(".manuside").removeClass("disableSide").addClass("disableSide");
        $(".barre").removeClass("disableSide").addClass("disableSide");
        $(".mode").removeClass("disableSide").addClass("disableSide");

        document.getElementById('automatiqueMode').disabled = true;
        document.getElementById('manualMode').disabled = true;

    }

    //fonction qui actualise la temperature avec un timer
    setInterval(function() {

        doAjax(ajaxTarget  + "?level=" + level + "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);
        console.log("long polling getTemperature");

    }, 1000);


    //fonction qui s'execute avec le monde manuel pour controler le niveau du thermostat
    function runManuel() {

        clearInterval(timermodeauto);

        console.log("le mode manuel a démarrer");

        level = Math.floor(levelKnob / 25);

        if (isNaN(level)) {
            level = 0;
        }

        doAjax(ajaxTarget  + "?level=" + level + "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);


    }

    //fonction qui s'execute avec le monde automatique pour controler le niveau du thermostat
    function runAuto() {

        var date = new Date();
        var hours = date.getHours();

        console.log("run automatique");
        console.log("il est heure :" + hours);

        level = Math.floor(document.getElementById("range" + hours).value / 25);;


        console.log("hours: "+ hours + ", level: " + level);


        if (isNaN(level)) {
            level = 0;
        }
       doAjax(ajaxTarget  + "?level=" + level + "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);
    }


function alerteTemp() {

    console.log("Rouge dans alerte est " + red);
    console.log("Blue dans alerte est " + blue);

    if (red != 0) {

        if (currentTemperature > red) {
            alertify.error("Temperature trop haute !");
        }
        if(currentTemperature >= blue && (currentTemperature <= red) ) {
            alertify.success("Temperature Moyenne !");
        }
        if (currentTemperature < blue) {
            alertify.log("Temperature trop basse !");
        }
        console.log("alerte controle s'est executé");
    }

}

//fonction qui gère la puissance du chauffage selon la température
function modeSmart() {
  
    console.log("mode intelligent lancer" );

    if (red != 0) {

        if (currentTemperature > red) {

           doAjax(ajaxTarget  + "?level=0"+ "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);

        }
        if(currentTemperature >= blue && (currentTemperature <= red) ) {
            alertify.success("Smart Mode ON");
        }
        if (currentTemperature < blue) {
            doAjax(ajaxTarget  + "?level=4"+ "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);
        }
    }

}

//fonction qui execute le smartmode tout le temps car c'est son but
function activateSmart(){
  setInterval(function() {
   modeSmart()
      console.log("Smart Mode ON");
  }, 1000);
}


    //fonction qui récupère la temperature a parti du microcontrolleur
    function ajaxCallback(status, currentTemperatureF) {
        if (status == 200 && currentTemperatureF != "") {
            currentTemperatureF = parseInt(currentTemperatureF);
            document.getElementById("text-readout").innerHTML = currentTemperatureF + '&deg;';
            currentTemperature=currentTemperatureF;
        }
    }

    //fonction qui récupère la temperature a parti du microcontrolleur
    function doAjax(ajaxTarget, ajaxCallBack, timeout, timeoutCallBack) {
        var xhr;
        var xhrTimer;
        try {
            xhr = new XMLHttpRequest();
        } catch (e) {
            xhr = new ActiveXObject('Microsoft.XMLHTTP');
        }
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4) {
                ajaxCallBack(xhr.status, xhr.responseText);
                if (timeout > 0)
                    clearTimeout(xhrTimer);
            }
        };
        xhr.open("GET", ajaxTarget, true);
        if (timeout > 0)
            xhrTimer = setTimeout(function() {
                xhr.abort();
                timeoutCallBack();
            }, timeout);
        xhr.send(null);
    }


    function ajaxGet(url) {
        var xhr;
        try {
            xhr = new XMLHttpRequest();
        } catch (e) {
            xhr = new ActiveXObject('Microsoft.XMLHTTP');
        }
        xhr.multipart = true;
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4) {
                if (ajaxRet = xhr.status == 200)
                    ajaxCallback(xhr.responseText);
            }
        };
        xhr.open("GET", url, true);
        xhr.send(null);
    }

    //controleur manuel
    $(function() {
        $(".dial").knob({
            'change': function(v) {
                levelKnob = Math.round(v);
                runManuel();
                console.log(levelKnob);
            }
        });
    });


    //controleur de temps pour le mode automatique
    function startAutoMode() {

        console.log("le mode automatique a démarrer interval");
        timermodeauto = setInterval(function() {
            if (new Date().getMinutes() === 0) {
                runAuto();
            }
        }, 60000);

        setInterval(function() {
            if (new Date().getSeconds() === 0) {
                console.log("new minute !");
            }
        }, 1000);
    }



    //controleur de seuil de temperature
    $(function() {
        $('#slider').slider({
            range: true,
            min: 0,
            max: 100,
            values: [18, 25],

            slide: function(event, ui) {
                $("#sliderValue").html("Température min: <strong>" + ui.values[0] + "&deg;</strong>, max: <strong>" + ui.values[1] + "&deg;</strong>");
                blue = ui.values[0];
                red = ui.values[1];

                console.log("le min de blue est :" + blue);
                console.log("le min de rouge est :" + red);

                doAjax(ajaxTarget  + "?level=" + level + "&red="+ red +"&blue="+blue,ajaxCallback, 0, 0);

                alerteTemp();

            }


        });

    });

    //fonction qui active et désactive le controlleur
    $(function() {
        $('.toggle').click(function(e){
                 e.preventDefault();
                $(this).toggleClass('toggle-on');
                if ($(this).hasClass('toggle-on')){
                    console.log('bouton: ON (1)');

                    $(".manuside").removeClass("disableSide");
                    $(".barre").removeClass("disableSide");

                    $(".mode").removeClass("disableSide");
                    document.getElementById('automatiqueMode').disabled = false;
                    document.getElementById('manualMode').disabled = false;


                } else {
                    console.log('bouton: Off (0) ');


                     $(".autoside").removeClass("disableSide").addClass("disableSide");
                     $(".manuside").removeClass("disableSide").addClass("disableSide");
                     $(".barre").removeClass("disableSide").addClass("disableSide");
                     $(".mode").removeClass("disableSide").addClass("disableSide");

                     document.getElementById('automatiqueMode').disabled = true;
                     document.getElementById('manualMode').disabled = true;
                }
         });
    });
