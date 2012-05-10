/*
* License AGPLv3
*/

/*TODO
Hepburn -> Kana Mode with three choose right buttons 
statistics wrong, right, right in row, avg time to answer (right)
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
        
        //fault handling
        faultQueue: [],
        faultLookup: {},
        
        tipStatus: 0,
        
        //Statistics
        statRight: 0,
        statWrong: 0,
        statRightInRow: 0,
        
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
        
        //setup fault lookup
        for(var i=0; i<prop.kanaData.length; i++)
            prop.faultLookup[prop.kanaData[i].hepburn] = i;
        
        createQueue();
    })();
    
    
    //Public Functions
    
    self.validate = function(value)
    {
        if(value === prop.currentKana.hepburn)
        {
            prop.statRight++;
            prop.statRightInRow++;
            return true;
        }
        else
        {
            if(prop.faultLookup[value])
                prop.faultQueue.push(prop.faultLookup[value]);
            
            prop.statWrong++;
            prop.statRightInRow=0;
            return false;
        }
    }
    
    self.next = function()
    {
        //when faultQueue has entries 50:50 Chance to use entry from faultQueue  
        if(prop.faultQueue.length > 0 && randomNumber(0,1))
        {
            prop.currentKana = prop.kanaData[prop.faultQueue.pop()];
        }
        else
        {
            //go along queue
            prop.currentKana = prop.kanaQueue[prop.currentPos];
            
            prop.currentPos++;
            if(prop.currentPos > prop.kanaQueue.length-1)
                prop.currentPos = 0;
        }
 
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
    
    self.getQueueSize = function()
    {
        return prop.kanaQueue.length;
    }
    
    self.getQueuePos = function()
    {
        return prop.currentPos-1;
    }
    
    self.getFaultQueueSize = function()
    {
        return prop.faultQueue.length;
    }
    
    self.resetStats = function()
    {
        prop.statRight=0;
        prop.statWrong=0;
        prop.statRightInRow=0;
    }
    //get Statistics
    
    //setOptions
    //tip();
    
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
            
            var kana = prop.kanaData[id];
            
            //Filter for options
            if(kana.type === "hiragana" && !prop.optHiragana)
                continue;
            if(kana.type === "katakana" && !prop.optKatakana)
                continue;
            if(kana.cat === "ext" && !prop.optExtended)
                continue;
            if(kana.cat === "yoon" && !prop.optYoon)
                continue;
            
            prop.kanaQueue.push(kana);
        }
        
    }
    
    function randomNumber(a,b)
    {
        return a + Math.floor(Math.random()*(b+a+1));
    }
}
