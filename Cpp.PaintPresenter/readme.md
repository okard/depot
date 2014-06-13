
# Presenter Paint Tool

## TODOS
* timer to own widget
* add a notice dock
* think about scaling of pdf, screenshot and overlay (keep a 4:3 or 16:9 ratio)
  - maybe fixed overlay size?
  - down scaling in main window with docks and so on
* add a preview widget for pdf
* add configuration and config dialog
* add pen size chooser
* better pop menus for toolbar buttons
* add also cmake build?
* write some documentation
* single application support with screenshot command (simple udp receiver?)
* add a PDF TOC DockWidget
    - Tree
* save drawings for pdf pages
* add a status dock? pdf pages, sizes pdf/overlay/screenshot and so on? painttool
* rename classes
* add a tray icon (with screenshot click)
* support for multiple pdfs/screenshots at the same time?

* Redesign
    - overlay notice pdf stuff
        - Filesystem Interface
    - redesign the draw tool stuff
    - add view mode (None, Pdf, Screenshot)

* QML Rewrite?
    - add qml/js to resources?
    
* Streaming?
	-> Use Tablet for presentation/drawings 
	-> Stream to beamer
    
## General Design Notices
	
Switchable views e.g. for an image or PDF file
	
* Views
	- Type
		* PDF View
		* Image View
	- Pageable
		* Pdf View has multpiple pages 
	- Overlay
		* Drawings to a View/Subpage
	
* For Views Exists GUI Elements?
	* Pure readonly show (View -> Subpage + Overlay)
	* Editable?
		- Overlay Editing

* Network interface possibilities
