module Main where

import Lib (process)

myDebug :: ([String], String) -> String 
myDebug (xs, log) = 
    let res = concat $ ["["] ++ [s ++ ", " | s <- xs] ++ ["]"]
    in res ++ " " ++ log ++ "   "


main :: IO ()
main = putStrLn $ concatMap (myDebug . process) ["Hello World", "Nothing in the world"]