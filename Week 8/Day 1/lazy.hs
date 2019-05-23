--lazy.hs  Lazy Evaluation Example

f a b = 2 * a

inf = [1..]

g = f 7 inf

main = do
  putStrLn $ show g
