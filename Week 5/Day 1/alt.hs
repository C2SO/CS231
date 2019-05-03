
alt x y
  | x == 0      = y
  | otherwise   = x

alt1 0 y = y
alt1 x _ = x

alt2 x y =
  case x of
    0 -> y
    _ -> x
    