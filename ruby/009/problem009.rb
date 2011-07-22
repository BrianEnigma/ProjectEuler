#!/usr/bin/env ruby -wKU

def pythagoreanTriplet?(a, b, c)
  return a * a + b * b == c * c
end

for a in 1..998
  print("#{a}\n")
  for b in (a + 1)..999
    for c in (b + 1)..1000
      if (a + b + c == 1000)
        if (pythagoreanTriplet?(a, b, c))
          print("\n#{a}^2+#{b}^2==#{c}^2, abc=#{a*b*c}\n")
          exit
        end
      elsif (a + b + c > 1000)
        break
      end
    end #for c
  end #for b
end #for a
