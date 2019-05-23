--efficient fibonacci numbers
fibPair n
  | n == 0    = (0,1)
  | otherwise = fibStep (fibPair (n - 1))

fibStep (u,v) = (v, u + v)

fib = fst . fibPair

