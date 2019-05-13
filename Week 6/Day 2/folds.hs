
x = foldr1 (-)  [7,13,21,25]

y = 7 - (13 - (21 - 25))

z = foldr (-) 25 [7,13,21]

--all three of above evaluate to the same value.

a = foldl1 (-) [7,13,21,25]

b = ((7 - 13) - 21) - 25

c = foldl (-) 7 [13, 21, 25]

--all three of above evaluate to same value
