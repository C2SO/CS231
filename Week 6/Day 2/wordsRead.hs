
breakUp = words "1 2 3 4 5"

--number = read "7"
--cannot do above, "7" is ambiguous, it could be more than one possible type

number = read "7" :: Int

--listNums = map read breakUp
--fails for the same reason as above statement failed

listNums = map readInt breakUp

readInt :: String -> Int
readInt = read


