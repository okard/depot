
# Tools for creating token stuff



## Usage

For creating the token svg library run

    ./create_svg.sh

This creates the tokenlib.svg which contains svg symbol definitions of all token defined in tokendb.txt,
it also runs the gentokensvg.py a second time to create din a4 overview sheets 

To create printable pdfs from the overview files run the script

    ./create_pdf.sh

which uses the merge_svg script to merge the token definition from tokenlib.svg because it seems 
most tools like graphicsmagick or inkscape can't work with referenced symbols. Then it creates
the pdf files.

## TODO

* Split gentokensvg in single classes and components.

* Create a command language tool to create game situations
    - CSV Style
    - Example: TOK;1;5;220010022 set token on 1,5
    - Example: BOARD;10;10 creates a 10x10 board
    - Example: CIRC;10;10;F creates a circle with text F on 10,10

* Add functionality to create a final overview table in latex
    - First step create for each token in tokendb a svg file
    - Second step create for each svg a result pdf file
    - Third step create a latex table with references to pdf files
