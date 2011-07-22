#!/usr/bin/env ruby -wKU

def palindrome?(value)
  s = value.to_s
  length = s.length
  halfLength = (length / 2).floor
  for position in 0..halfLength
    if (s[position] != s[length - position - 1])
      return false
    end
  end
  return true
end

def doTest
  print palindrome?(123321), "\n"
  print palindrome?(12321), "\n"
  print palindrome?(123123), "\n"
  print palindrome?(1231231), "\n"
end

# Maybe make this more efficient so that we don't do 123*321 and then later 321*123?
def doAction
  largest = 0
  for value1 in 100..999
    for value2 in 100..999
      product = value1 * value2
      if (palindrome?(product))
        print("#{ value1 } * #{ value2 } is #{ product }\n")
        if (product > largest)
          largest = product
        end
      end
    end
  end
  print("The largest palindrome made from multiplying two 3-digit numbers was #{ largest }\n")
end

doTest
doAction