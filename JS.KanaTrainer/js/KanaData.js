/*
* License AGPLv3
*/

//kana data
// きゅ -> yōon
// ぷ　-> ext
// cat-> base, ext(ended), yoon
var kanadata = 
[
    /* Hiragana Base*/
    { kana:"あ", hepburn:"a", type:"hiragana", cat:"base", img:"" },
    { kana:"お", hepburn:"o", type:"hiragana", cat:"base" },
    { kana:"え", hepburn:"e", type:"hiragana", cat:"base" },
    { kana:"い", hepburn:"i", type:"hiragana", cat:"base" },
    { kana:"う", hepburn:"u", type:"hiragana", cat:"base" },
    
    { kana:"か", hepburn:"ka", type:"hiragana", cat:"base" },
    { kana:"き", hepburn:"ki", type:"hiragana", cat:"base" },
    { kana:"く", hepburn:"ku", type:"hiragana", cat:"base" },
    { kana:"け", hepburn:"ke", type:"hiragana", cat:"base" },
    { kana:"こ", hepburn:"ko", type:"hiragana", cat:"base" },
    
    { kana:"さ", hepburn:"sa", type:"hiragana", cat:"base" },
    { kana:"し", hepburn:"shi", type:"hiragana", cat:"base" },
    { kana:"す", hepburn:"su", type:"hiragana", cat:"base" },
    { kana:"せ", hepburn:"se", type:"hiragana", cat:"base" },
    { kana:"そ", hepburn:"so", type:"hiragana", cat:"base" },
    
    { kana:"た", hepburn:"ta", type:"hiragana", cat:"base" },
    { kana:"ち", hepburn:"chi", type:"hiragana", cat:"base" },
    { kana:"つ", hepburn:"tsu", type:"hiragana", cat:"base" },
    { kana:"て", hepburn:"te", type:"hiragana", cat:"base" },
    { kana:"と", hepburn:"to", type:"hiragana", cat:"base" },
    
    { kana:"な", hepburn:"na", type:"hiragana", cat:"base" },
    { kana:"に", hepburn:"ni", type:"hiragana", cat:"base" },
    { kana:"ぬ", hepburn:"nu", type:"hiragana", cat:"base" },
    { kana:"ね", hepburn:"ne", type:"hiragana", cat:"base" },
    { kana:"の", hepburn:"no", type:"hiragana", cat:"base" },
    
    { kana:"は", hepburn:"ha", type:"hiragana", cat:"base" },
    { kana:"ひ", hepburn:"hi", type:"hiragana", cat:"base" },
    { kana:"ふ", hepburn:"fu", type:"hiragana", cat:"base" },
    { kana:"へ", hepburn:"he", type:"hiragana", cat:"base" },
    { kana:"ほ", hepburn:"ho", type:"hiragana", cat:"base" },
    
    { kana:"ま", hepburn:"ma", type:"hiragana", cat:"base" },
    { kana:"み", hepburn:"mi", type:"hiragana", cat:"base" },
    { kana:"む", hepburn:"mu", type:"hiragana", cat:"base" },
    { kana:"め", hepburn:"me", type:"hiragana", cat:"base" },
    { kana:"も", hepburn:"mo", type:"hiragana", cat:"base" },
    
    { kana:"や", hepburn:"ya", type:"hiragana", cat:"base" },
    { kana:"ゆ", hepburn:"yu", type:"hiragana", cat:"base" },
    { kana:"よ", hepburn:"yo", type:"hiragana", cat:"base" },
    
    { kana:"ら", hepburn:"ra", type:"hiragana", cat:"base" },
    { kana:"り", hepburn:"ri", type:"hiragana", cat:"base" },
    { kana:"る", hepburn:"ru", type:"hiragana", cat:"base" },
    { kana:"れ", hepburn:"re", type:"hiragana", cat:"base" },
    { kana:"ろ", hepburn:"ro", type:"hiragana", cat:"base" },
    
    { kana:"わ", hepburn:"wa", type:"hiragana", cat:"base" },
    //{ kana:"ゐ", hepburn:"wi", type:"hiragana", cat:"base" },
    //{ kana:"ゑ", hepburn:"we", type:"hiragana", cat:"base" },
    { kana:"を", hepburn:"wo", type:"hiragana", cat:"base" },
    
    /* Hiragana Extended*/
    { kana:"が", hepburn:"ga", type:"hiragana", cat:"ext" },
    { kana:"ぎ", hepburn:"gi", type:"hiragana", cat:"ext" },
    { kana:"ぐ", hepburn:"gu", type:"hiragana", cat:"ext" },
    { kana:"げ", hepburn:"ge", type:"hiragana", cat:"ext" },
    { kana:"ご", hepburn:"go", type:"hiragana", cat:"ext" },
    
    /* Hiragana Yoon*/
    
    /* Katakana Base*/
    { kana:"ア", hepburn:"a", type:"katakana", cat:"base" },
    { kana:"オ", hepburn:"o", type:"katakana", cat:"base" },
    { kana:"エ", hepburn:"e", type:"katakana", cat:"base" },
    { kana:"イ", hepburn:"i", type:"katakana", cat:"base" },
    { kana:"ウ", hepburn:"u", type:"katakana", cat:"base" },
    
    /* Katakana Extended*/
    
    /* Katakana Yoon*/
];


function getKanaData()
{
    return kanadata;
}
