/*
* License AGPLv3
*/

/*
 Painter Class to getting a Paint working on a Canvas
 For Learning Kana/Kanji the way

*/


function Paint(pCanvas)
{
    var self = this;
    var prop = {};
    
    prop.uiCanvas = undefined;
    prop.uiContex = undefined;
    
    //Stroke counter for validation
    
    prop.mouseDown = false;
    prop.strokeCount = 0;
    
    //color
    //stroke weight
    
    
    /**
     * Ctor
     */
    (function () 
    {   
        //prepare canvas
        prop.uiCanvas = pCanvas;
        prop.uiContex = pCanvas.getContext('2d');
        
        //mousedown and mouseup
        
        //register mouse move paint
        prop.uiCanvas.onmousemove = onMouseMove;
        
        prop.uiCanvas.onmousedown = function(e)
        {
            prop.mouseDown = true;
        };
        
        prop.uiCanvas.onmouseup = function(e)
        {
            prop.strokeCount++;
            prop.mouseDown = false;
        };
        
    })();
    
    /**
    * Clear Canvas
    */
    self.clear = function()
    {
        var ctx = prop.uiContex;
        var w = prop.uiCanvas.width;
        var h = prop.uiCanvas.height;
        ctx.clearRect(0, 0, w, h);
        
        prop.strokeCount = 0;
    }
    
    //get stroke count
    
    function onMouseMove(e)
    {
        if(!prop.mouseDown)
            return true;
        
        var ctx = prop.uiContex;
        var can = prop.uiCanvas;
        
        var x = e.pageX - can.offsetLeft;
        var y = e.pageY - can.offsetTop;
        
        //draw a circle
        ctx.beginPath();
        ctx.arc(x, y, 10, 0, Math.PI*2, true); 
        ctx.closePath();
        ctx.fill();
        
        return false;
    }
    
    
}