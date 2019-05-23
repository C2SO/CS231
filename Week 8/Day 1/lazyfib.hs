-- Lazy evaluation
-- Fibonacci numbers
--  from presentation by Andrew Rademacher

--- Look at two lists [0,1,1,2,3,5,8,13,...
---                   [1,1,2,3,5,8,13,21,...
--- Note that the second list is the tail of the first
--- Also note that adding corresponding elements of the two lists
---  gives the next element of the first list
---  Use this to create an infinite list of fibonacci numbers

fibs = 0:1:[a+b| (a,b) <- zip fibs (tail fibs)]

-- fibonacci function just selects the appropriate element from the list

fib n = fibs !! n

