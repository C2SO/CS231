-- triangle numbers, recursion example

tri :: Integer -> Integer 
tri n
  | n < 0     = -1
  | n == 0    = 0
  | otherwise = n + tri (n - 1)