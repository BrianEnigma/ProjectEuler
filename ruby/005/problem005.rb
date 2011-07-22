#!/usr/bin/env ruby -wKU

def divisibleToValue?(value, maxValue)
  for counter in 2..maxValue
    if (value % counter != 0)
      return false
    end
  end
  return true
end

def doTest
  counter = 10
  while true
    if (divisibleToValue?(counter, 10))
      print("#{ counter } is evenly divisible by every number from 1..10\n")
      break
    end
    counter += 10
  end
end

def doAction
  counter = 20
  while true
    if (divisibleToValue?(counter, 20))
      print("#{ counter } is evenly divisible by every number from 1..20\n")
      break
    end
    counter += 20
  end
end

doTest()
doAction()
