#!/usr/bin/env ruby -wKU
require('../brian.rb')

class TriangleNumbers
    attr_reader :triangleCounter
    def initialize()
        @triangleCounter = 1
        @triangleValue = 1
    end
    def nextTriangle
        @triangleCounter += 1
        @triangleValue += @triangleCounter
        return @triangleValue
    end
end

def doTest
    tri = TriangleNumbers.new
    for i in 1..7
        number = tri.nextTriangle()
        print("#{tri.triangleCounter}: #{number}: ", divisors(number).join(' '), "\n")
    end
end

def doActionBruteForce
    tri = TriangleNumbers.new
    while true
        number = tri.nextTriangle()
        count = divisorCount(number)
        if ((count >= 500) || (tri.triangleCounter % 100 == 0))
            print("#{tri.triangleCounter}: #{number}: #{count}\n")
        end
        if (count >= 500)
            break
        end
    end
end

def doActionBinary
    tri = TriangleNumbers.new
    triangles = Array.new
    triangles[0] = 1
    for i in 0..5000
        triangles << tri.nextTriangle()
    end
    print("Triangle number #{triangles.length} is #{triangles[triangles.length - 1]} has #{divisorCount(triangles[triangles.length - 1])}\n")
    # Won't work because we can't binary-search the divisor counts because they're
    # all over the place, not constantly increasing
end

doTest
doActionBruteForce
#doActionBinary
