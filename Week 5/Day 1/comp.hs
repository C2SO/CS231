
--triangle number function
tri n = sum [x | x <- [1..n]]

--nth square
sq1 n = sum [2*x-1 | x <- [1..n]]

sq2 n = sum [x | x <- [1,3..5*n], x < 2*n]

