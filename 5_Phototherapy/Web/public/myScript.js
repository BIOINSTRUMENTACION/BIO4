// UPPER LEFT
var slider = document.getElementById("RA");
var slider1 = document.getElementById("GA");
var slider2 = document.getElementById("BA");
var output  = document.getElementById("demo");
var output1 = document.getElementById("demo1");
var output2 = document.getElementById("demo2");

output.innerHTML = slider.value;
output1.innerHTML = slider1.value;
output2.innerHTML = slider2.value;

slider.oninput = function() {output.innerHTML = this.value;}
slider1.oninput = function() {output1.innerHTML = this.value;}
slider2.oninput = function() {output2.innerHTML = this.value;}


// LOWER LEFT
var slider3 = document.getElementById("RB");
var slider4 = document.getElementById("GB");
var slider5 = document.getElementById("BB");
var output3  = document.getElementById("demo3");
var output4 = document.getElementById("demo4");
var output5 = document.getElementById("demo5");



output3.innerHTML = slider3.value;
output4.innerHTML = slider4.value;
output5.innerHTML = slider5.value;

slider3.oninput = function() {output3.innerHTML = this.value;}
slider4.oninput = function() {output4.innerHTML = this.value;}
slider5.oninput = function() {output5.innerHTML = this.value;}



// UPPER RIGHT
var slider6 = document.getElementById("RC");
var slider7 = document.getElementById("GC");
var slider8 = document.getElementById("BC");
var output6  = document.getElementById("demo6");
var output7 = document.getElementById("demo7");
var output8 = document.getElementById("demo8");

output6.innerHTML = slider6.value;
output7.innerHTML = slider7.value;
output8.innerHTML = slider8.value;

slider6.oninput = function() {output6.innerHTML = this.value;}
slider7.oninput = function() {output7.innerHTML = this.value;}
slider8.oninput = function() {output8.innerHTML = this.value;}


// LOWER RIGHT

var slider9  = document.getElementById("RD");
var slider10 = document.getElementById("GD");
var slider11 = document.getElementById("BD");
var output9  = document.getElementById("demo9");
var output10 = document.getElementById("demo10");
var output11 = document.getElementById("demo11");

output9.innerHTML = slider9.value;
output10.innerHTML = slider10.value;
output11.innerHTML = slider11.value;

slider9.oninput = function() {output9.innerHTML = this.value;}
slider10.oninput = function() {output10.innerHTML = this.value;}
slider11.oninput = function() {output11.innerHTML = this.value;}

// Time
var slider13 = document.getElementById("time");
var output13 = document.getElementById("demo13");

output13.innerHTML = slider13.value;
slider13.oninput = function() {output13.innerHTML = this.value;}
// Pattern
var slider12 = document.getElementById("nb");
var output12 = document.getElementById("demo12");

output12.innerHTML = slider12.value;
slider12.oninput = function() {output12.innerHTML = this.value;}

function Submit(){

   
    var slider = document.getElementById("RA").value;
    var slider1 = document.getElementById("GA").value;
    var slider2 = document.getElementById("BA").value;
    var slider3 = document.getElementById("RB").value;
    var slider4 = document.getElementById("GB").value;
    var slider5 = document.getElementById("BB").value;
    var slider6 = document.getElementById("RC").value;
    var slider7 = document.getElementById("GC").value;
    var slider8 = document.getElementById("BC").value;
    var slider9  = document.getElementById("RD").value;
    var slider10 = document.getElementById("GD").value;
    var slider11 = document.getElementById("BD").value;
    var slider12 = document.getElementById("nb").value;
    var slider13 = document.getElementById("time").value;
    
    var path = "hi"
    if (slider12 == 1) {
         path = "p1";
      }

    else if (slider12 == 2) {
        path = "p2";
      }

    else if (slider12 == 3) {
        path = "p3";
      }

    else if (slider12 == 4) {
        path  = "p4";
      }
   
    var reference =  firebase.database().ref(path);
    var Status =  firebase.database().ref("Status" + path);
    reference.set(
        {RA:slider,
         GA:slider1,
         BA:slider2,
    
         RB:slider3,
         GB:slider4,
         BB:slider5,
    
         RC:slider6,
         GC:slider7,
         BC:slider8,
    
         RD:slider9,
         GD:slider10,
         BD:slider11,

         Time:slider13,
        
         
    
        }
        )
      Status.set({status:1})
    
    alert("Submition succesfull for pattern: "+path);
    }


function Switch(){
  var reference =  firebase.database().ref("Switch");
  reference.set({switch:1});
  alert("Switched to Camara");

}