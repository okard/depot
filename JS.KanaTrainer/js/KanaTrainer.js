/*
* License AGPLv3
*/

/*TODO
Hepburn -> Kana Mode with three choose right buttons 
statistics  avg time to answer (right)
timelimit for answers
localStorage, save statistics of kanas for next time and
    use it for queue creation
fix fault queue dbls -> with katakana&hiragana
setFont
error handling
mode -> draw hebrun
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
        optBase: true,
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
        prop.uiContex.textAlign = 'center';
        prop.uiContex.textBaseline = 'middle';
        prop.uiContex.font = 'italic 100px Calibri';
        
        //setup fault lookup
        for(var i=0; i<prop.kanaData.length; i++)
        {
            var hepburn = prop.kanaData[i].hepburn;
            if(!(prop.faultLookup[hepburn]))
                prop.faultLookup[hepburn] = [];
            prop.faultLookup[hepburn].push(i);
        }
        
        createQueue();
    })();
    
    
    //Public Functions
    
    /**
     * Validate Input
     */
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
                prop.faultQueue.push.apply(prop.faultQueue, prop.faultLookup[value]);
            
            prop.statWrong++;
            prop.statRightInRow=0;
            return false;
        }
    }
    
    /**
     * Next kana in queue
     */
    self.next = function()
    {
        //when faultQueue has entries 65% Chance to use entry from faultQueue  
        if(prop.faultQueue.length > 0 && Math.random() > 0.35)
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
 
        prop.tipStatus = 0;
        self.draw();
    }
    
    /**
     * Draw Kana on canvas
     */
    self.draw = function()
    {
        //clear and centerized
        
        var ctx = prop.uiContex;
        var w = prop.uiCanvas.width;
        var h = prop.uiCanvas.height;
       
        ctx.clearRect(0, 0, w, h);
        ctx.fillText(prop.currentKana.kana, w/2, h/2);
    }
    
    /**
     * Get queue size
     */
    self.getQueueSize = function()
    {
        return prop.kanaQueue.length;
    }
    
    /**
     * Get current queue position
     */
    self.getQueuePos = function()
    {
        return prop.currentPos-1;
    }
    
    /**
     * Get the size of the fault queue
     */
    self.getFaultQueueSize = function()
    {
        return prop.faultQueue.length;
    }
    
    /**
     * Reset statistics
     */
    self.resetStats = function()
    {
        prop.statRight=0;
        prop.statWrong=0;
        prop.statRightInRow=0;
    }
    
    
    /**
    * get statistics
    */
    self.getStatistics = function()
    {
        return {
            right: prop.statRight,
            wrong: prop.statWrong,
            rightInRow: prop.statRightInRow
        };
    }
    
    /**
     * Enable/Disable Option
     */
    self.setOption = function(key, value)
    {
        if(typeof(value) !== "boolean")
            return;
        
        switch(key)
        {
            case "hiragana":
                prop.optHiragana = value;
                break;
            case "katakana":
                prop.optKatakana = value;
                break;
            case "base":
                prop.optBase = value;
                break;
            case "ext":
                prop.optExtended = value;
                break;
            case "yoon":
                prop.optYoon = value;
                break;
        }
        
        createQueue();
    }
    
    /**
     * Tip Function
     */
    self.tip = function()
    {
        if(prop.tipStatus < prop.currentKana.hepburn.length)
            prop.tipStatus++;
        
        return prop.currentKana.hepburn.substr(0, prop.tipStatus);
    }
    
    //Internal Functions
    
    /// Create the kana queue
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
            if(kana.cat === "base" && !prop.optBase)
                continue;
            if(kana.cat === "ext" && !prop.optExtended)
                continue;
            if(kana.cat === "yoon" && !prop.optYoon)
                continue;
            
            prop.kanaQueue.push(kana);
        }
        
    }
    
    /// Get random number
    function randomNumber(a,b)
    {
        return a + Math.floor(Math.random()*(b+a+1));
    }
}
