/*
* License AGPLv3
*/


function setup()
{
    //get ui elements
    var canvas = document.getElementById("canvas");
    var txtAnswer = document.getElementById("txtInput");
    var btnTip = document.getElementById("btnTip");
    var btnNext = document.getElementById("btnNext");
    var lblSymbol = document.getElementById("divSymbol");
    var divStats = document.getElementById("divStats");
    
    //setup kana trainer object
    var kanaTrainer = new KanaTrainer(canvas, getKanaData());
    
    //configure ui elements
    
    btnTip.onclick = function()
    {
        txtAnswer.value = kanaTrainer.tip();
        return true;
    };
    
    btnNext.onclick = function()
    {
        kanaTrainer.next();
        setStats();
        return true;
    };
    
    txtAnswer.onkeypress = function(event)
    {
        if(!(event.keyCode == 13 || event.keyCode == 32))
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
        
        setStats();
        
        return true;
    };
    
    kanaTrainer.next();
    setStats();
    
    
    function setStats()
    {
        divStats.innerHTML = kanaTrainer.getQueuePos() + "/" + kanaTrainer.getQueueSize() + "-" + kanaTrainer.getFaultQueueSize();
    }
    
}


//setup
window.onload = setup;
