-- General Recursion Example
-- implement fibonacci number directly from its definition

fib n
  | n == 0     = 0
  | n == 1     = 1
  | otherwise = fib (n - 1) + fib (n - 2)

--This was a bad idea in C
--for the same reason, it is a bad idea in Haskell