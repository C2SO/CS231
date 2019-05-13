-- Nicholas Rahbany
-- CS231 Programing Language Paradigms
-- Assignment 5 - HoldMeeting.hs

module HoldMeeting where

-- This function is the "main" function of this file
-- It takes in the user's string and returns if the
--    list provided has a meeting hosted or not

holdMeeting :: String -> (Int, Bool) -- Takes in a string, returns an int and a boolean
holdMeeting inputString =
    (membersPresent, meetingRunning) where -- The function returns membersPresent and meetingRunning, where
    inputList = map read (words inputString) -- inputList is equal to a list of the strings passed in
    meetingRunning = membersPresent >= head inputList -- meetingRunning is equal to the number at the head of inputList
    membersPresent = checkPresent inputList (length inputList) -- membersPresent is equal to the number of members that arrived early enough


-- This function checks how many members got to the
--    meeting on time

checkPresent :: [Int] -> Int -> Int
checkPresent list length
    | length == 2                     = 0 -- If the list length is 2, return 0
    | list!!(length - 1) <= list!!1   = 1 + checkPresent list (length - 1) -- If a member is here before, or when they should, increase the total by one
    | otherwise                       = checkPresent list (length - 1) -- Otherwise, check the next member