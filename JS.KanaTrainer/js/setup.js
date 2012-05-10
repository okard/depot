/*
* License AGPLv3
*/



function setup()
{
    //get ui elements
    var canvas = document.getElementById("canvas");
    var txtAnswer = document.getElementById("txtInput");
    var lblSymbol = document.getElementById("divSymbol");
    
    var kanaTrainer = new KanaTrainer(canvas, getKanaData());
    
    
    //configure ui elements
    txtAnswer.onkeypress = function(event)
    {
        if(event.keyCode != 13)
            return true;
        
        txtAnswer.style.backgroundColor="transparent";
        if(kanaTrainer.validate(txtAnswer.value))
        {
            txtAnswer.value = "";
            kanaTrainer.next();
        }
        else
        {
            txtAnswer.style.backgroundColor="#ff5656";
        }
    }
    
    kanaTrainer.next();
}


//setup
window.onload = setup;