{-
  Program to ask a user for a name, then print name in a message.

  This illustrates a multiline or nested comment.
-}

main = do  -- create an imperative program
  putStrLn "Who are you? "
  name <- getLine
  putStrLn ( "Hello " ++ name)
  
  
