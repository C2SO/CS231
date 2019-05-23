--contentsRead.hs use hGetContents for lazy reading
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
  inFileHandle <- openFile inFile ReadMode
  outFileHandle <- openFile outFile WriteMode
  input <- hGetContents inFileHandle --read file lazily
  hPutStrLn outFileHandle $ map changeChar input
  hClose inFileHandle
  hClose outFileHandle
  