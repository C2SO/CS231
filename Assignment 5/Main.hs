module Main where
import HoldMeeting
import System.Environment
import System.IO

--Program to 

--makeOutput concatenates the input line and output list into
--a labelled, readable String for output

makeOutput :: String -> (Int, Bool) -> String
makeOutput inLine (number, verity)
  = "\t" ++ head (words inLine) ++ "\t\t" ++ (show number) ++ "\t\t\t" ++ (yesOrNo verity) ++ "\n"

yesOrNo True = "yes"
yesOrNo _    = "no"


processInput inFileHandle outFileHandle = do
  eof <- hIsEOF inFileHandle
  if eof 
    then return ()
   else do
      inputLine <- hGetLine inFileHandle
      if (length inputLine) < 5 then processInput inFileHandle outFileHandle
      --Above is a kluge to handle empty line at end of file.
      else do
        let result = holdMeeting inputLine
        let outputLine = makeOutput inputLine result
        hPutStrLn outFileHandle outputLine
        processInput inFileHandle outFileHandle
{-
main is the entry point to the program.  Compile the code with command
     ghc --make Main.hs
then run the program with command
     ./Main mtngInput mtngOut
where mtngInput is the name of the input file and mtngOut is the name of the
output file.
-}

main = do
  [inFile, outFile] <- getArgs
  inFileHandle <- openFile inFile ReadMode
  outFileHandle <- openFile outFile WriteMode
  hPutStrLn outFileHandle "               Committee Meeting Held"
  hPutStrLn outFileHandle ""
  hPutStrLn outFileHandle "Members Needed    Members on Time        Meeting Held"
  hPutStrLn outFileHandle ""
  processInput inFileHandle outFileHandle
  hClose inFileHandle
  hClose outFileHandle
  
