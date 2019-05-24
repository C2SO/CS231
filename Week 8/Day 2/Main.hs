import System.Environment
import System.IO
import Data.Maybe

usage = "Hangman dictionary words guesses"

testTooSmall args
  | length args < 3 = Nothing
  | otherwise      = Just args

testTooBig args
  | args == Nothing            = Nothing
  | length (fromJust args) > 4 = Nothing
  | otherwise                  = Just args

play args = do
  putStrLn $ show args


main = do
  argList <- getArgs
  let bigEnough = testTooSmall argList
  let smallEnough = testTooBig bigEnough
  if smallEnough == Nothing
     then putStrLn usage
     else play (fromJust smallEnough)
  
