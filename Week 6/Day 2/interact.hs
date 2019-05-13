--interact example
main = interact revLines

revLines s = unlines $ map reverse $ reverse $ lines s  