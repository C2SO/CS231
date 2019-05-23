--sieve of Eratosthenes to produce prime numbers

primes = sieve [2..] --infinite list, 2 is in position 0

sieve (x:xs) = x : sieve [y | y <- xs, mod y x /= 0] -- some elements
                                  -- removed at each step, still infinite

prime n = primes !! (n - 1) -- counting starts at 0

--take the nth prime
memberOf :: [Integer] -> Integer -> Bool
memberOf [] _ = False
memberOf (x:xs) y
  | x == y    = True
  | x > y     = False
  | otherwise = memberOf xs y
  