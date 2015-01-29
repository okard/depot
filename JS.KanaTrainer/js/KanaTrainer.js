/*
* License AGPLv3
*/

/*TODO
Hepburn -> Kana Mode with three choose right buttons 
statistics  avg time to answer (right)
timelimit for answers
localStorage, save statistics of kanas for next time and
    use it for queue creation
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
        
        //current elements for hepburn mode
        currentElements: [], 
        //safe solution position
        
        //fault handling
        faultQueue: [],
        faultLookup: {},
        
        tipStatus: 0,
        
        //Statistics
        statRight: 0,
        statWrong: 0,
        statRightInRow: 0,
        
        /* Options */
        optKatakana: true, //ask katakana
        optHiragana: true, //ask hiragana
        optBase: true,	   //only base kanas
        optExtended: true,	//extended kanas e.g. ga
        optYoon: true,	//yoon kanas
        optHepburnMode: false, //how hepburn instead of kana
        
        //optHepburnModeLimit: 9,  //limit of symbols to choose from
        
        /* UI */
        uiCanvas: undefined,
        uiContex: undefined,
        
        //callback function for validation
        cbValidated: function(result) {},
    };
    
    //Ctor
    (function () 
    {
        //check input
        prop.kanaData = pKanas;
        
        //prepare canvas
        prop.uiCanvas = pCanvas;
        prop.uiCanvas.onclick = onCanvasClick;
        prop.uiContex = pCanvas.getContext('2d');
        prop.uiContex.textAlign = 'center';
        prop.uiContex.textBaseline = 'middle';
        prop.uiContex.font = '100px Calibri';
        
        //TODO calculate font size from canvas size?
        
        setupFaultLookup();
        createQueue();
    })();
    
    
    //Public Functions
    
    /**
     * Validate Input given by value
     */
    self.validate = function(value)
    {
		var result = prop.optHepburnMode ?  prop.currentKana.kana : prop.currentKana.hepburn;
		
        if(value === result)
        {
            prop.statRight++;
            prop.statRightInRow++;
            prop.cbValidated(true);
            return true;
        }
        else
        {
            if(prop.faultLookup[value])
                prop.faultQueue.push.apply(prop.faultQueue, prop.faultLookup[value]);
            
            prop.statWrong++;
            prop.statRightInRow=0;
            prop.cbValidated(false);
            return false;
        }
    }
    
    /**
     * Show next kana in queue
     */
    self.next = function()
    {
		//TODO different modes:
		
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
        
        //setup stuff for hepburn mode
        if(prop.optHepburnMode)
		{
			prop.currentElements = [];
			for(var i=0; i < 9; i += 1)
			{
				//only from current list
				prop.currentElements.push(prop.kanaQueue[randomNumber(0, prop.kanaQueue.length-1)].kana);
			}
			prop.currentElements[0] = prop.currentKana.kana; //solution
			shuffleArray(prop.currentElements);
			//no current element in middle?
			while(prop.currentElements[4] == prop.currentKana.kana)
			{
				shuffleArray(prop.currentElements);
			}
			prop.currentElements[4] = prop.currentKana.hepburn; //question
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
        
        //in hepburn mode the question data is setup in next function
        //the mode renders 9 symbols with requested kana in center 
        if(prop.optHepburnMode && prop.currentElements.length > 0)
		{
			ctx.clearRect(0, 0, w, h);
			ctx.save();
			ctx.font = '30px Calibri';
			
			var step_x = (w/3.0);
			var step_y = (h/3.0);
			var idx_element = 0;
			
			//assert(prop.currentElements.length == 9)
			
			//render 3x3 cells with values
			for(var r=0; r < 3; r += 1)
			{
				for(var c=0; c < 3; c += 1)
				{
					ctx.fillText(prop.currentElements[idx_element], (step_x/2) + c*step_x, (step_y/2) + r*step_y);
					idx_element++;
				}
			}
			
			ctx.restore();
			return;
		}
		else
		{
			ctx.clearRect(0, 0, w, h);
			ctx.fillText(prop.currentKana.kana, w/2, h/2);
		}
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
			case "hepburnmode":
				prop.optHepburnMode = value;
				break;
        }
        
        self.resetAll();
    }
    
    self.setValidateCallback = function(cb)
    {
		if(typeof cb === 'function')
		{
			prop.cbValidated = cb;
		}
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
    
    
    self.resetAll = function()
    {
		self.resetStats();
		setupFaultLookup();
        createQueue();
	}
    
    //Internal Functions
    
    /// Create the kana queue
    //     write all selected kanas in random order into a queue
    function createQueue()
    {
		prop.faultQueue = []; //reset fault queue
		
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
    
    ///setup fault lookup
    // create a lookup hashmap to find the wrong answer and queue them into fault queue
    function setupFaultLookup()
    {
		prop.faultLookup = []; //clear lookup 
		
        for(var i=0; i<prop.kanaData.length; i++)
        {
			var kana = prop.kanaData[i];
			
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
                
            //add to fault lookup table
            var hepburn = kana.hepburn;
            if(!(prop.faultLookup[hepburn]))
                prop.faultLookup[hepburn] = [];
            prop.faultLookup[hepburn].push(i);
        }
	}
	
	/**
	* Handle click events in the canvas element
	* it is required to validate result in hepburn mode
	*/
	function onCanvasClick(e)
	{	
		if(!prop.optHepburnMode)
		{
			//not required for no hepburn mode
			return;
		}
		
		var rect = prop.uiCanvas.getBoundingClientRect();
		var pos = { x: e.clientX - rect.left, y: e.clientY - rect.top };
		
		var step_x = (rect.width/3.0);
		var step_y = (rect.height/3.0);
		
		var x_cell = Math.floor(pos.x / step_x);
		var y_cell = Math.floor(pos.y / step_y);
		
		var index = (3*(y_cell+1)) - (3-x_cell);
		
		var value = prop.currentElements[index];
		//alert(value);
		if(self.validate(value))
		{
			self.next();
		}
	}
	
	/**
	* shuffle an array
	*/
	function shuffleArray(array)
	{
		for (var i = array.length - 1; i > 0; i--) 
		{
			var j = Math.floor(Math.random() * (i + 1));
			var temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		}
		return array;
	}
	
}
