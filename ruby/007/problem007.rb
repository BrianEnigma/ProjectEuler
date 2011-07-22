#!/usr/bin/env ruby -wKU
include Math

def prime?(value)
  max = sqrt(value).floor
  for counter in 2..max
    if (value % counter == 0)
      return false
    end
  end
  return true
end

def findPrime(number)
  counter = 0
  value = 2
  while (true)
    if (prime?(value))
      counter += 1
      if (counter >= number)
        return value
      end
    end
    value += 1
  end
end

def doTest
  print(findPrime(6), "\n")
end

def doAction
  print(findPrime(10001), "\n")
end

doTest
doAction

