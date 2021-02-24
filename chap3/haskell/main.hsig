{-# LANGUAGE FlexibleInstances #-}

module Main where

class Monoid m where
    mempty :: m
    mappend :: m -> m -> m

instance Main.Monoid String where
    mempty = ""
    mappend = (++)