-- triangle numbers, recursion example
--  use if then else

tri :: Integer -> Integer 
tri n =
  if n < 0
    then -1
    else
      if n == 0
        then 0
       else n + tri (n - 1)