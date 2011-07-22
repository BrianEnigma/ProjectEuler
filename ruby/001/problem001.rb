#!/usr/bin/env ruby -wKU

sum = 0
for value in 1...1000 # one is inclusive, 1000 is exclusive
  if ((value % 3 == 0) || (value % 5 == 0))
    print value, "\n"
    sum += value;
  end #if
end #for
print("sum is ", sum, "\n")