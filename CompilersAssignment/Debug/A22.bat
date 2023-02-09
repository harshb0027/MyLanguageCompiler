:: SCRIPT A22 - CST8152 - Fall 2021
::
:: COMPILERS COURSE - SCRIPT ---------------------------------------------

SET COMPILER=CompilersAssignment.exe

SET FILE1=A32A_Empty
SET FILE2=A32B_Hello
SET FILE3=A32C_Expression
SET FILE4=A32D_General

REM ---------------------------------------------------------------------
REM - Begin of Tests (A22 - S21) ----------------------------------------
REM ---------------------------------------------------------------------

ren *.exe %COMPILER%

::
:: BASIC TESTS  ----------------------------------------------------------
::
REM - Basic Tests (A22 - S21) - - - - - - - - - - - - - - - - - - - - - -

%COMPILER% 2 %FILE1%.chg	> %FILE1%.out	2> %FILE1%.err
%COMPILER% 2 %FILE2%.chg	> %FILE2%.out	2> %FILE2%.err
%COMPILER% 2 %FILE3%.chg	> %FILE3%.out	2> %FILE3%.err
%COMPILER% 2 %FILE4%.chg	> %FILE4%.out	2> %FILE4%.err

REM ---------------------------------------------------------------------
REM - End of Tests (A22 - S21) ------------------------------------------
REM ---------------------------------------------------------------------
