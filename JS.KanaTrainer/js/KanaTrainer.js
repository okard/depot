/*
* License AGPLv3
*/

/*TODO
Seperate Queue for false entries faultQueue, faultQueue data
make a lookup and add kana wrongly types faultLookup["wa"] = id(5)
Hepburn -> Kana Mode with three choose right buttons 
statistics wrong, right, right in row, size of faultQueue, avg time to answer (right)
position/of
tips first char, second char and so on
*/

/**
* KanaTrainer Class
*/
function KanaTrainer(pCanvas, pKanas)
{
    //wrapper variable
    var self = this;
    
    //Private Properties
    var prop =
    {
        //basic kana data
        kanaData: undefined,
        //created kana queue
        kanaQueue: [],
        // current pos
        currentPos: 0,
        // current kana obj
        currentKana: undefined,
        
        /* Options */
        optKatakana: true,
        optHiragana: true,
        optExtended: true,
        optYoon: true,
        
        /* UI */
        uiCanvas: undefined,
        uiContex: undefined,
    };
    
    //Ctor
    (function () 
    {
        //check input
        prop.kanaData = pKanas;
        
        //prepare canvas
        prop.uiCanvas = pCanvas;
        prop.uiContex = pCanvas.getContext('2d');
        
        
        createQueue();
    })();
    
    
    //Public Functions
    
    self.validate = function(value)
    {
        if(value === prop.currentKana.hepburn)
            return true;
        else
            return false;
    }
    
    self.next = function()
    {
        //when faultQueue has entries 50:50 Chance to use entry from faultQueue
        
        //go along queue
        //when special queue has entries these first
        prop.currentKana = prop.kanaQueue[prop.currentPos];
        
        prop.currentPos++;
        if(prop.currentPos > prop.kanaQueue.length-1)
             prop.currentPos = 0;
 
        self.draw();
    }
    
    //Draw Kana
    self.draw = function()
    {
        //clear and centerized
        
        var ctx = prop.uiContex;
        var w = prop.uiCanvas.width;
        var h = prop.uiCanvas.height;
       
        ctx.clearRect(0, 0, w, h);
        
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.font = 'italic 100px Calibri';
        ctx.fillText(prop.currentKana.kana, w/2, h/2);
    }
    
    //access to count and position of queue
    
    //Internal Functions
    
    function createQueue()
    {
        //fill kanaQueue with random data from kanaData
        prop.kanaQueue = [];
        prop.currentPos = 0;
        
        //create indices list
        var indices=[];
        for(var i=0; i<prop.kanaData.length; i++)
            indices.push(i);
        
        //fill queue
        while(indices.length > 0)
        {
            var rnd = randomNumber(0, indices.length-1);
            var id = indices[rnd];
            //delete index
            indices.splice(rnd, 1);
            
            //TODO Filter for options here
            var kana = prop.kanaData[id];
            prop.kanaQueue.push(kana);
        }
        
    }
    
    function randomNumber(a,b)
    {
        return a + Math.floor(Math.random()*(b+a+1));
    }
}
