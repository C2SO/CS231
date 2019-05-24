-- Nicholas Rahbany
-- CS231 - Vineyard
-- spellCheck.hs

import Data.List
import Data.Char
import System.Environment
import System.Exit
import System.IO

-- Used to compare the two words, then will return EQ if they are equal
comp :: String -> String -> Ordering
comp a b = compare (map toLower a) (map toLower b)

-- Will call comp to check if the two words are equal, then will return a boolean
isEqual :: String -> String -> Bool
isEqual a b = comp a b == EQ

-- This sorts the list of words based on their comparrisons ot each other
sortFunc :: [String] -> [String]
sortFunc = sortBy comp

-- This removes duplicate words by calling isEqual
groupFunc :: [String] -> [[String]]
groupFunc = groupBy isEqual

-- Head is a function of groupFunc of sortFunc
-- Maps the list that is sent in, and returns a new list
unique :: [String] -> [String]
unique = map head . groupFunc . sortFunc

-- Splits words on non-alphabet characters
splitWords :: String -> [String]
splitWords x =  case dropWhile (not . isAlpha) x of
  "" -> []
  xs -> word : splitWords xss
    where (word, xss) =
            break (not . isAlpha) xs

-- If the word appears in the dict file, then it is correct.
-- This prints the result into the output file
spellCheck :: [String] -> [String] -> [String]
spellCheck [] _ = []
spellCheck (word:words) dict
  | elem (map toLower word) dict = ("Correct: " ++ word) : spellCheck words dict
  | otherwise = ("Incorrect: " ++ word) : spellCheck words dict

-- The main function that is run
-- This retrieves your arguments, sets your arguments to the file definitions,
-- then calls the proper functions in order to complete the spellcheck application
main = do
    args <- getArgs
    if length args /= 3 then
        die ("List the three arguments as so: input, dictionary, output")
    else
        return ()
    let [inFileInput, dictFileInput, outFileInput] = args
    inFile <- readFile inFileInput
    dictFile <- readFile dictFileInput
    outFile <- openFile outFileInput WriteMode
    let inWords = unique $ splitWords inFile
    let dictWords = map (map toLower) $ splitWords dictFile
    mapM (hPutStrLn outFile) $ spellCheck inWords dictWords
    hClose outFile
    putStrLn "Complete."