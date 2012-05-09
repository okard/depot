/*
* License AGPLv3
*/

//to class? O_o

var kanatrainer =
{   
    currentKana: undefined,
    currentPos: 0,
    kanaQueue: [],
    kanaData: undefined,
    
    /*TODO
    Seperate Queue for false entries faultQueue, faultQueue data
    make a lookup and add kana wrongly types 
    Hepburn -> Kana Mode with three choose right buttons 
    */
   
    /* UI Elements */
    txtAnswer: undefined,
    lblSymbol: undefined,
    
    /* OPTION HANDLING */
    optKatakana: true,
    optHiragana: true,
    optExtended: true,
    optYoon: true,
    
     
    /**
    * Initialize
    */
    init: function()
    {
        kanatrainer.txtAnswer.onkeypress=kanatrainer.onInput;  

        kanatrainer.createQueue();
        kanatrainer.next();
    },
    
    
    createQueue: function()
    {
        //fill kanaQueue with random data from kanaData
        kanatrainer.kanaQueue = [];
        kanatrainer.currentPos = 0;
        
        //create indices list
        var indices=[];
        for(var i=0; i<kanatrainer.kanaData.length; i++)
            indices.push(i);
        
        //fill queue
        while(indices.length > 0)
        {
            var rnd = kanatrainer.randomNumber(0, indices.length-1);
            var id = indices[rnd];
            //delete index
            indices.splice(rnd, 1);
            
            //TODO Filter for options here
            var kana = kanatrainer.kanaData[id];
            kanatrainer.kanaQueue.push(kana);
        }
        
    },
    
    /**
    * Validate input and go to next if valid
    */
    validate:function()
    {
        var val = kanatrainer.txtAnswer.value;
        
        kanatrainer.txtAnswer.style.backgroundColor="transparent";
        
        if(val === kanatrainer.currentKana.hepburn)
        {
            //right
            kanatrainer.txtAnswer.value = "";
            return true;
        }
        else
        {
            //wrong
            //Background color:
            kanatrainer.txtAnswer.style.backgroundColor="#ff5656";
            return false;
        }
    },
    
    /**
    * Show next kana in queue
    */
    next: function()
    {
        //go along queue
        //when special queue has entries these first
        kanatrainer.currentKana = kanatrainer.kanaQueue[kanatrainer.currentPos];
        kanatrainer.lblSymbol.innerHTML = kanatrainer.currentKana.kana;
        
        kanatrainer.currentPos++;
        if(kanatrainer.currentPos > kanatrainer.kanaQueue.length-1)
             kanatrainer.currentPos = 0;
    },
    
    /**
    * Answer Input Event from Textbox
    * TODO clean up and move to setup only handle the input here
    */
    onInput: function(event)
    {
        //if(document.getElementById('txtInput').value.length >= 3)
        //    return false;
        
        if(event.keyCode != 13)
            return true;
        
        //limit to 3 in length?
            
            
        if(kanatrainer.validate())
            kanatrainer.next();
    },
    
    //use canvas for drawing
    
    randomNumber: function(a,b)
    {
        return a + Math.floor(Math.random()*(b+a+1));
    }
}


//setup to seperate file

//setup
window.onload = function()
{
    //loading sounds
    
    //setup kanatrainer object:
    kanatrainer.kanaData = getKanaData();
    kanatrainer.txtAnswer = document.getElementById("txtInput");
    kanatrainer.lblSymbol = document.getElementById("divSymbol");
    kanatrainer.init();
} 
