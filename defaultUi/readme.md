## syntax:
- `[` - begin line
- `]` - end line
- `<` - set
- `>` - send
- `>>` - commit ACTion
- `<<` - get DATa
- `{``|``}` - repeat action, ie: `MAKE >> { var1 <  TYPE_A | var2  < TYPE_B }` `MAKE >> { var1 : var2 } < TYPE` `SET >> 
var1 { ::DATA < "txt" | ::X < 200 }`
- `::` - access
- `""` - string
##  ACTs:
- `XBEG >> "BLOCK"` - begin data block (list lower)
- `XEND >> "BLOCK"` - end data block
- `EXIT` - close program
- `OPEN >> "example.ofui"` - open .ofui (OpenFightUserInterface) file
- `LOAD >> "example.offl` - load .offl (OpenFightFiLe) file
- `XTPT >> "example.ofpt"` - execute .ofpt file.
- `MAKE >> #variable_name#` - make a variable
- `SETX >> group::name` - set parameter
- `PACK >> "Q://example/path/" > "Q://example/path2/example.offl"` - package folder to .offl file
- `UNPK >> "Q://example/path/" > "Q://example/path2/example.off"` - unpack .off to folder 
- `NVBX >> "example.ofbx" < #X coordinate# < #Y coordinate#` - invoke BOX.
- `SHOW >> #variable#` - show ui element
- `FREE >> YOU < DEFAULT` - frees control and changes color
- `WAIT >> YOU < #time#` - freezes control for x milliseconds

## elements:
(replacing parameter with NULL sets the default)
### `TEXT`:
- `MAKE >> #variable# < TEXT`
#### setters:
- `SETX >> #variable#`
  - `::DATA < "text""`
  - `::ID < name`
  - `::X < #X coordinate#`
  - `::Y < #Y coordinate#`
  - `::SIZE < #px size#`
  - `::FONT_N < "font_name"`
  - `::FONT_T < "font_type"`
  - `::COLOR < #hex_color#`
### `RECT`:
 - `MAKE >> #variable# < RECT` 
#### setters:
- << #X coordinate# << #Y coordinate# << #width# << #height# << #border width# << #hex border color# <<  #hex_fill_color#`
- `#variable# < CRCL < #X coordinate# < #Y coordinate# << #width# << #height# << #border width# << #hex border 
color# << 
  #hex_fill_color#`
## data blocks:
### `PRMS` - block to set screen parameters
#### settables:
`SETX >> #SETTABLE# < #parameter#`
- `SIZE` - sets used pixels (NOT ACTUAL RESOLUTION OF THE WINDOW, THE DETALISATION OF INTERFACE);
  - `::X` - width
  - `::Y` - height
- `BKGR` - sets background to color or image.
  - `::TYPE` - sets IMG or CLR
  - `::IMG` - sets image path
  - `::CLR` - sets hex color
- `YOU` - sets YOU texture
  - `DEFAULT` - default, aka RED texture
  - `YELLOW` - [[BIG SHOT]] texture
  - `BLUE` - snas
### `ACT` - block to MAKE and SET ACTion variables
- `MAKE >> ACT_name < #action syntax#`
#### settables:
`XSET >> ACT_name::SETTABLE < #DATA#`
- none yet lol
### `INT` - group to MAKE and SET INTeractable spots
`MAKE >> INT_name`
#### settables:
`SETX >> INT_name::SETTABLE < #DATA#`
- none yet lol
### `LMT` - block to MAKE and SET eLeMenT variables
`MAKE >> LMT_name`
#### settables:
`SETX >> LMT_name::SETTABLE < #DATA#`
- LMT defined
### `TXR` - block to MAKE and SET TeXtuRe variables
`MAKE >> TXR_name`
#### settables:
`SETX >> TXR_name::SETTABLE < #DATA#`
- none yet lol
### `SEQ` - block for eXeCuTable SEQuence
