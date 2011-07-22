#!/usr/bin/env ruby -wKU

def sumOfSquareUpTo(value)
  sum = 0
  for counter in 1..value
    sum += counter * counter
  end
  return sum
end

def squareOfSumUpTo(value)
  sum = 0
  for counter in 1..value
    sum += counter
  end
  return sum * sum
end

def doTest
  value1 = sumOfSquareUpTo(10)
  value2 = squareOfSumUpTo(10)
  print(" #{value2} - #{value1} = #{value2-value1}\n")
end

def doAction
  value1 = sumOfSquareUpTo(100)
  value2 = squareOfSumUpTo(100)
  print(" #{value2} - #{value1} = #{value2-value1}\n")
end

doTest
doAction
