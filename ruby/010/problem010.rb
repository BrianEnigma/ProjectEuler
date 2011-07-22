#!/usr/bin/env ruby -wKU

require('../brian.rb')

def sumOfPrimes(value)
  sum = 0
  for i in 2...value
    if (prime?(i))
      sum += i
    end
  end
  return sum
end

print(sumOfPrimes(10), "\n")
print(sumOfPrimes(2_000_000), "\n")
