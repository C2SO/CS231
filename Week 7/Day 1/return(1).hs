main = do
  x <- sample
  putStrLn x


sample = do
  return ()
  return 5
  return "abc"

