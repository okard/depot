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
    
    //な na    に ni    ぬ nu    ね ne    の no
    //は ha    ひ hi    ふ fu    へ he    ほ ho
    //ま ma    み mi    む mu    め me    も mo
    //や ya        ゆ yu        よ yo
    //ら ra    り ri    る ru    れ re    ろ ro
    //わ wa    (ゐ wi)      (ゑ we)  を o/wo
    
    /* Hiragana Extended*/
    /* Hiragana Yoon*/
    
    /* Katakana Base*/
    /* Katakana Extended*/
    /* Katakana Yoon*/
];


function getKanaData()
{
    return kanadata;
}
