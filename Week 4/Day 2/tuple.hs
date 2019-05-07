--tuple.hs

type Person = (String, Int)

--Person is a synonym for (String, Int) pair
ldSngr :: Person
ldSngr = ("John", 25)

name1 :: Person -> String
name1 (n,_) = n  -- pattern matching

name2 :: Person -> String
name2 x = fst x  -- function call

age1 :: Person -> Int
age1 (_, a) = a -- pattern matching

age2 :: Person -> Int
age2 x = snd x -- function call

