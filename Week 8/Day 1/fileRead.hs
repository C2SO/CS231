--fileRead.hs use readFile for lazy reading, output using writeFile
-- change all letters to lower case, all digits to character '@'

import Data.Char
import System.Environment
import System.IO

changeChar :: Char -> Char
changeChar c
  | isDigit c  = '@'
  | otherwise  = toLower c

main = do
  [inFile, outFile] <- getArgs

  input <- readFile inFile --read file lazily
  writeFile outFile $ map changeChar input

  