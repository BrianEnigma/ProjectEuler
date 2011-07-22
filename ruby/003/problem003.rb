#!/usr/bin/env ruby -wKU
include Math

def printFactorsXXXXXXXX(value)
  print("The factors of ", value, " are:")
  max = sqrt(value).floor
  for counter in 2..max
    if value % counter == 0
      print(" ", counter)
    end
  end
  print("\n")
end

def printFactors(value)
  print("The factors of ", value, " are:")
  counter = 2
  while (counter <= value)
    while (value % counter == 0)
      print(" ", counter)
      value /= counter
    end
    counter += 1
  end
  print("\n")
end

printFactors(13195)
printFactors(600851475143)
