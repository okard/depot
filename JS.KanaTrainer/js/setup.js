/*
* License AGPLv3
*/

function setup()
{
    //get ui elements
    var canvas = document.getElementById("canvasShow");
    var canvasDraw = document.getElementById("canvasDraw");
    var txtAnswer = document.getElementById("txtInput");
    var btnTip = document.getElementById("btnTip");
    var btnNext = document.getElementById("btnNext");
    var btnReset = document.getElementById("btnReset");
    var lblSymbol = document.getElementById("divSymbol");
    var divStatus = document.getElementById("divStatus");
    var divStatistics = document.getElementById("divStatistics");
    //get sound
    var snd_right = document.getElementById("sndPos");
    var snd_wrong = document.getElementById("sndNeg");
    //options:
    var chkHiragana = document.getElementById("chkHiragana");
    var chkKatakana = document.getElementById("chkKatakana");
    var chkBase = document.getElementById("chkBase");
    var chkExtended = document.getElementById("chkExtended");
    var chkYoon = document.getElementById("chkYoon");
    var chkHepburnMode = document.getElementById("chkHepburnMode");
    
    //setup kana trainer object
    var kanaTrainer = new KanaTrainer(canvas, getKanaData());
    
    //test code
    var painter = new Paint(canvasDraw);
    
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
    
    btnReset.onclick = function()
    {
		kanaTrainer.resetAll();
		kanaTrainer.next();
		setStats();
		return true;
	};
    
    chkHiragana.checked = true;
    chkKatakana.checked = true;
    chkBase.checked = true;
    chkExtended.checked = true;
    chkYoon.checked = true;
    chkHiragana.onclick = checkBoxHelper("hiragana", chkHiragana);
    chkKatakana.onclick = checkBoxHelper("katakana", chkKatakana);
    chkBase.onclick = checkBoxHelper("base", chkBase);
    chkExtended.onclick = checkBoxHelper("ext", chkExtended);
    chkYoon.onclick = checkBoxHelper("yoon", chkYoon);
	chkHepburnMode.onclick = checkBoxHelper("hepburnmode", chkHepburnMode);
    
    txtAnswer.onkeydown = function(event)
    {
		//key alt
        if(event.keyCode == 18)
        {
             btnTip.onclick();
             return false;
        }
    };
    
    txtAnswer.onkeypress = function(event)
    {
		//space and enter
        if(!(event.keyCode == 13 || event.charCode == 32))
            return true;
        
        txtAnswer.style.backgroundColor="transparent";
        if(kanaTrainer.validate(txtAnswer.value))
        {
            try
            {
                snd_right.currentTime = 0;
                snd_right.play();
            }
            catch(e){}
            txtAnswer.value = "";
            kanaTrainer.next();    
            painter.clear();
        }
        else
        {
            try
            {
                snd_wrong.currentTime = 0;
                snd_wrong.play();
            }
            catch(e){}
            txtAnswer.style.backgroundColor="#ff5656";
        }
        
        setStats();
        
        return false;
    };
    
    function checkBoxHelper(option, checkbox)
    {
        return function()
        {
            kanaTrainer.setOption(option, checkbox.checked);
            kanaTrainer.next();
            setStats();
            return true;
        }
    }
    
    function setStats()
    {
        divStatus.innerHTML = kanaTrainer.getQueuePos() + "/" + kanaTrainer.getQueueSize() + "-" + kanaTrainer.getFaultQueueSize();
        var stats = kanaTrainer.getStatistics();
        divStatistics.innerHTML = "Right: " + stats.right + " Wrong: " + stats.wrong + " Right in Row: " + stats.rightInRow;
    }
    
    //initial
    kanaTrainer.next();
    setStats();
    txtAnswer.focus();
    
    

}


//setup
window.onload = setup;
