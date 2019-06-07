import Data.Char
import Data.List
import Data.Maybe
import System.Directory
import System.Environment
import System.IO
import System.Exit

-- This is a recursive function that iterates through the string passed in to check all characters if they are digits
isNum :: String -> Bool
isNum [] = True -- If there are no more characters, that means the function ran its course and will return true
isNum (a:as)
    | isDigit a = isNum as -- If the current character is a digit, then the function runs with the following character(s)
    | otherwise = False -- The character is not a digit, the function fails and returns false

-- This validates the arguments the user passed in when starting the program
validateArgs :: [String] -> Bool
validateArgs args
    | length args /= 2 = True -- If the number of arguments are wrong, return false
    | not $ isNum (args !! 1) = True -- If the 2nd argument is not a number, return false
    | not $ isNum (args !! 2) = True -- If the 3rd argument is not a number, return false
    | otherwise = False -- If it made it here, that means all arguments look good. Return true!

-- This takes the user's arguments and splits them into variables for the program
parseArgs :: [String] -> (String, Int, Int)
parseArgs args = (fileName, wordLength, guesses) where
    fileName = args !! 0
    wordLength = read (args !! 1)
    guesses = adjGuessCount $ read (args !! 2)

-- This adjusts the user's amount of guesses.
adjGuessCount :: Int -> Int
adjGuessCount n
    | n < 5 = 5 -- If the user wants less than 5 guesses, it sets the amount to 5
    | n > 10 = 10 -- If the user wants more than 10 guesses, it sets the guesses to 10
    | otherwise = n -- Leave the number of guesses as is

-- This function checks if the the designated word fits the already used words the user covered
-- Returning 0 ignores the word
findSinglePattern :: String -> String -> Char -> [Char] -> Int
findSinglePattern [] [] _ _ = 1 -- If the user has not guessed and a word is set, return 1
findSinglePattern [] _  _ _ = 0 -- If the user has not guess and a word is not set, return 0
findSinglePattern _ [] _ _ = 0 -- If the dictionary argument is blank, return 0
findSinglePattern (dict:dicts) (word:words) currLetter usedChars
    | elem dict usedChars && word /= dict = 0 -- If the pattern contains a used character, return 0
    | dict == currLetter && word /= currLetter = 0 -- If the current word contains the most recent letter, return 0
    | word == '_' = findSinglePattern dicts words currLetter usedChars -- If the current letter in the word is blank, run the function again with the next arguments
    | dict == word = findSinglePattern dicts words currLetter usedChars -- If the current dictionary word is the current word, run the function again with the next arguments
    | otherwise = 0 -- Otherwise, return 0

-- This function is used as a loop to make the calls to findSinglePattern
findPatternMatches :: [String] -> String -> Char -> [Char] -> Int
findPatternMatches [] _ _ _ = 0 -- If there is only the dictionary file, return 0
findPatternMatches (a:as) pattern currLetter usedChars = 
    -- Call findSinglePattern with current arguments, then call this function again with next arguments
    (findSinglePattern a pattern currLetter usedChars) + findPatternMatches as pattern currLetter usedChars

-- This function replaces the first character of a string
replaceFirstChar :: String -> Char -> String
replaceFirstChar [] _ = "" -- If there is no argument for the character to be replaced, set it to blank
replaceFirstChar (a:as) chr
    | a == '_' = chr : as -- If the character is '_', then replace it
    | otherwise = a : replaceFirstChar as chr -- Otherwise, continue with the next arguments

-- This replaces all * in a word with the provided character
replaceAllChar :: String -> Char -> String
replaceAllChar [] _ = "" -- If there is no charcter provided, return blank
replaceAllChar (a:as) chr
    | a == '*' = chr : replaceAllChar as chr -- If a is '*', then replace it with the provided character and continue with the next arguments
    | otherwise = a : replaceAllChar as chr -- otherwise, continue with the next arguments

-- This is used to find patterns in the current word to be guessed
findPatterns :: String -> Char -> [String]
findPatterns str chr
    -- If there is an '_' in the word, then call itself with replaceFirstChar called, then concat it with itself called with the next arguments
    | elem '_' str = (findPatterns (replaceFirstChar str '*') chr) ++ (findPatterns (replaceFirstChar str chr) chr) 
    | otherwise = [str] -- Otherwise, return the current string as is

-- This function resets the word to be guessed
cheatAtHangman :: [String] -> [Char] -> String -> Char -> (String, Int)
cheatAtHangman dictionary usedChars currentWord specifiedChar = (maximumGroupWord, maxGroup) where
    allPossibilities = [replaceAllChar x '_' | x <- findPatterns currentWord specifiedChar] -- This sets all word possibilities with what letters have been called
    patternMatches = [findPatternMatches dictionary x specifiedChar usedChars | x <- allPossibilities ] -- This finds all the possible words that could match the current template
    maxGroup = maximum patternMatches -- This returns the maximum value from the list
    maxIndex = fromMaybe 0 $ findIndex (==maxGroup) patternMatches -- Retrieves the index where the strongest word is held
    maximumGroupWord = allPossibilities !! maxIndex -- Sets the return word to be of the index set at maxIndex

-- This retrieves a word with the current pattern
findWordWithPattern :: [String] -> String -> Char -> [Char] -> String
findWordWithPattern (dict:dicts) currWord currLetter usedChars
    | findSinglePattern dict currWord currLetter usedChars > 0 = dict -- Finds a word that matches the pattern of the current word
    | otherwise = findWordWithPattern dicts currWord currLetter usedChars -- Otherwise, continue onto the next word of the dictionary

-- This function runs each "round" once everything has been initialized by the main function
processUserInput :: [String] -> String -> [Char] -> Int -> Char -> IO ()
processUserInput dictionary currentWord usedChars guesses letter = do
        -- This changes the word that is being guessed
        let (nextWord, nextGroup) = cheatAtHangman dictionary usedChars currentWord letter
        if elem '_' nextWord then -- If there remains a character that has not been guessed
            return () -- Continue on
        else do
            putStrLn $ "You solved it! The word is: " ++ nextWord
            exitSuccess
        
        if nextWord == currentWord then -- If no correct characters were guessed from the previous round
            putStrLn "Wrong guess!"
        else
            putStrLn "Correct guess!"

        let nextGuesses = do
            if nextWord == currentWord then -- If no correct characters were guessed from the previous round
                guesses - 1
            else
                guesses
        
        if nextGuesses == 0 then do -- If there are no more guesses
            putStrLn "You're out of guesses!"
            putStrLn $ "The word was: " ++ (findWordWithPattern dictionary currentWord letter usedChars)
            exitSuccess
        else
            return ()
        
        putStrLn $ "You have " ++ (show nextGuesses) ++ " guesses left"

        putStrLn $ "Current word is: " ++ (concatMap (:" ") nextWord)
        
        putStrLn $ "Current used chars are: " ++ (sort (letter : usedChars))
        nextChar <- getNextChar (letter : usedChars) -- Set the next guessed letter to be what the user guesses

        processUserInput dictionary nextWord (letter : usedChars) nextGuesses $ toUpper nextChar -- Recall this function with the new parameters

-- This "initializes" the word by changing all the characters to blanks
initializeWord :: Int -> String
initializeWord a
    | a == 0 = "" -- If there are no more characters
    | otherwise = "_" ++ initializeWord (a - 1) -- Add "_ " and continue

-- This gets the next character from the user and validates it
getNextChar :: [Char] -> IO Char
getNextChar usedChars = do
    putStrLn "What's your guess?"
    userLine <- getLine -- Grabs the user input
    if null userLine then do -- If there was nothing
        putStrLn "You didn't say anything"
        getNextChar usedChars -- Call the function again
    else do
        let userChar = head userLine -- Add the character to a list 
        if not $ isAlpha userChar then do -- If the input is not a letter
            putStrLn "This is not a letter"
            getNextChar usedChars -- Call the function again
        else do -- If the user input is a letter
            if (length userLine /= 1) then do -- If the user inputs more than one letter at a time
                putStrLn "One letter at a time, please..."
                getNextChar usedChars -- Call the function again
            else do
                if elem (toUpper userChar) usedChars then do -- If the letter was already used
                    putStrLn "You already used this letter"
                    getNextChar usedChars -- Call the function again
                else
                    return (userChar) -- Return the user's guess

-- Removes words that do not have the correct length
removeWrongLength :: [String] -> Int -> [String]
removeWrongLength [] _ = [] -- If there is no argument, return a blank list
removeWrongLength (a:as) specifiedLen
    | length a == specifiedLen = [a] ++ (removeWrongLength as specifiedLen) -- If the length is equal to the input, add it to a list and continue with the next argument
    | otherwise = removeWrongLength as specifiedLen -- Otherwise, continue with the next arguments

-- Main Program
main = do
    commandArguments <- getArgs -- Retrieves the user's arguments
    let validated = validateArgs commandArguments -- Validates the user's arguments
    if not validated then do -- If the commands are not validated
        putStrLn "Usage: ./hangman <dictionary_file.txt> <word_length> <guesses>"
        exitFailure -- Exit the program
    else
        return ()
    
    exists <- doesFileExist (commandArguments !! 0) -- Checks if the file provided by the user exists
    if not exists then do -- if the file does not exist
        putStrLn "Dictionary File does not exist"
        exitFailure -- Exit program
    else
        return ()

    -- Set local variables equal to the user's input
    let (fileName, wordLength, guesses) = parseArgs commandArguments 

    dictionaryFile <- openFile fileName ReadMode -- Opens the dictionary file
    dictionaryWords <- hGetContents dictionaryFile -- Retrieves the contents of the dictionary file
    let dictionaryWordsUpper = map (map toUpper) (words dictionaryWords) -- Sets all the words in the dictionary to upper case

    if elem wordLength $ map length dictionaryWordsUpper then -- If there is word in the dictionary that matches the length that the user desires
        return ()
    else do -- If there are no words in the dictionary that have the desired length
        putStrLn "Invalid word length, there are no words of that length!"
        exitFailure -- Exit the program

    putStrLn $ "Guesses are: " ++ show guesses 

    let evilWord = (initializeWord wordLength) -- Creates a string that has the number of blanks desired by the user
    putStrLn $ "The word is: " ++ (concatMap (:" ") evilWord)
    guessedChar <- getNextChar "" -- Retrieves the user's guess
    processUserInput (removeWrongLength dictionaryWordsUpper wordLength) evilWord "" guesses $ toUpper guessedChar -- Continue's the program