import Data.List
import Data.Char
import System.Environment
import System.Exit
import System.IO

comp :: String -> String -> Ordering
comp a b = compare (map toLower a) (map toLower b)

isEqual :: String -> String -> Bool
isEqual a b = comp a b == EQ

sortFunc :: [String] -> [String]
sortFunc = sortBy comp

groupFunc :: [String] -> [[String]]
groupFunc = groupBy isEqual

unique :: [String] -> [String]
unique = map head . groupFunc . sortFunc

splitWords :: String -> [String]
splitWords x =  case dropWhile (not . isAlpha) x of
  "" -> []
  xs -> word : splitWords xss
    where (word, xss) =
            break (not . isAlpha) xs

spellCheck :: [String] -> [String] -> [String]
spellCheck [] _ = []
spellCheck (word:words) dict
  | elem (map toLower word) dict = ("Correct: " ++ word) : spellCheck words dict
  | otherwise = ("Incorrect: " ++ word) : spellCheck words dict

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