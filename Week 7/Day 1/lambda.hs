-- lambda.hs lambda abstractions

-- double a value
double x = 2 * x

--function to compute 3 + 2*x
f x = 3 + (double x)

--use a lambda abstraction instead of named function double

f' y = 3 + (\x -> 2*x) y

--often used with maps, double all elements of a list

doubleList xs = map (\x -> 2*x) xs

--Can have multiple arguments with lambda abstraction

g x y = (\a b -> 3*a - 2*b) x y




