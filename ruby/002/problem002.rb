#!/usr/bin/env ruby -wKU
MAXIMUM = 4_000_000
#MAXIMUM = 89

previousTerms = [1, 2]
sum = 2

while true do
  thisTerm = previousTerms[0] + previousTerms[1]
  if thisTerm > MAXIMUM
    break
  end
  print(thisTerm, "\n")
  previousTerms[0] = previousTerms[1]
  previousTerms[1] = thisTerm
  if (thisTerm % 2 == 0) 
    sum += thisTerm
  end
end

print("sum is ", sum, "\n")
