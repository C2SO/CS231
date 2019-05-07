-- list.hs

emptyList :: [Integer]
emptyList = []
 -- add elements to head of list with cons operator (:)

makeList x l = x : l

evenList :: [Integer]
evenList = [2,4..20]

-- head is first element of list
getFirst l = head l

-- last is last element of list
getLast l = last l

-- tail is entire list except head
getTail l = tail l

-- init is all of list except last
getInit l = init l


