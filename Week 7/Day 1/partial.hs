--partial.hs
--demonstrate partial applications

add4 w x y z = w + x + y + z

add3to42 = add4 42  --partially apply add4

add2to42and7 = add3to42 7 --partially apply add3to42 which uses
                          --partially applied add4

add1to42and7and6 = add2to42and7 6  --similar to previous

anotherAdd = add4 4 3 --partially apply add4 by supplying 2 arguments

whiteSpace = " \n\t"

{-
isWhite = elem whiteSpace
The above is not a partial application, the order of arguments matters.
Write a new function which reverses order of arguments,
 then do partial application
-}

member s c = elem c s
isWhite = member whiteSpace


