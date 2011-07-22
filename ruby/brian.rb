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

def factors(value)
    result = Array.new
    counter = 2
    while (counter <= value)
        while (value % counter == 0)
            result << counter
            value /= counter
        end
        counter += 1
    end
    return result
end

def uniqueFactors(value)
    result = Array.new
    counter = 2
    while (counter <= value)
        if (value % counter == 0)
            result << counter
        end
        while (value % counter == 0)
            value /= counter
        end
        counter += 1
    end
    return result
end

def divisors(value)
    max = (value / 2).floor
    result = [1]
    counter = 2
    while (counter <= max)
        if (value % counter == 0)
            result << counter
        end
        counter += 1
    end
    result << value
    return result
end

def divisorCount(value)
    max = (value / 2).floor
    result = 1
    counter = 2
    while (counter <= max)
        if (value % counter == 0)
            result += 1
        end
        counter += 1
    end
    result += 1
    return result
end

class Grid
    @@N   = 1
    @@NE  = 2
    @@E   = 3
    @@SE  = 4
    @@S   = 5
    @@SW  = 6
    @@W   = 7
    @@NW  = 8
    def initialize()
        @grid = Array.new
        @maxWidth = 0
        @maxHeight = 0
    end
    
    def inBounds?(x, y)
        height = @grid.length
        if ((x < 0) || (y < 0))
            print("X and Y must be >= 0\n")
            return false
        end
        if (y >= @grid.length)
            print("Y is off the grid\n")
            return false
        end
        width = @grid[y].length
        if (x >= width)
            print("X is off the grid\n")
            return false
        end
        return true
    end
    
    def canGo?(x, y, length, direction)
        if (!inBounds?(x, y))
            return false
        end
        halfLength = (length / 2).ceil
        # subtract one from length because length includes the space we're referring
        # to.  That is, if length is 4 then it includes "this" space, plus three others.
        length -= 1
        result = true
        height = @grid.length
        width = @grid[y].length
        #print("halfLength is #{halfLength}\n")
        case direction
            when @@N:   if y < length then result = false end
            when @@S:   if y >= height - length then result = false end
            when @@W:   if x < length then result = false end
            when @@E:   if x >= width - length then result = false end
            when @@NW:  if (y <= halfLength) || (x <= halfLength) then result = false end
            when @@NE:  if (y <= halfLength) || (x >= width - halfLength - 1) then result = false end
            when @@SW:  if (y >= height - halfLength - 1) || (x <= halfLength) then result = false end
            when @@SE:  if (y >= height - halfLength - 1) || (x >= width - halfLength - 1) then result = false end
            else        print("Unknown direction\n"); result = false
        end
        return result
    end
    
=begin
    def testCanGo(length)
        for row in 0...@maxHeight
            for column in 0...@maxWidth
                canGo = true
                for direction in @@N..@@NW
                    if (!canGo?(column, row, length, direction))
                        canGo = false
                        break;
                    end
                end
                if (canGo)
                    print("* ")
                else
                    print(". ")
                end
            end
            print("\n")
        end
        print("\n")
        print("At (0,2) can go: ")
        for direction in @@N..@@NW
            if (canGo?(0, 2, length, direction))
                print("#{direction}")
            end
        end
        print("\n")
        print("At (0,3) can go: ")
        for direction in @@N..@@NW
            if (canGo?(0, 3, length, direction))
                print("#{direction}")
            end
        end
        print("\n")
        print("At (19,16) can go: ")
        for direction in @@N..@@NW
            if (canGo?(19, 16, length, direction))
                print("#{direction}")
            end
        end
        print("\n")
    end
=end

    def at(x, y)
        if (!inBounds?(x, y))
            raise StandardError, "(#{x}, #{y}) is not in bounds!"
        end
        return @grid[y][x].to_i
    end
  
    def loadFromFile(filename)
        @grid = Array.new
        row = 0
        if (!File.file?(filename))
            return
        end
        file = File.open(filename)
        file.each { |line|
            lineArray = line.split(/\s+/)
            @grid[row] = lineArray
            if (lineArray.length > @maxWidth)
                @maxWidth = lineArray.length
            end
            row += 1
            @maxHeight = row
        }
        file.close
        print("Loaded #{filename}, @maxWidth is #{@maxWidth}, @maxHeight is #{@maxHeight}\n")
    end

    def to_s
        result = ""
        @grid.each { |line|
          line.each { |column|
            result += "#{column} "
          }
          result += "\n"
        }
        return result
    end

    def display()
      @grid.each { |line|
        line.each { |column|
          print("#{column} ")
        }
        print("\n")
      }
    end
    
    def directionToName(direction)
        case direction
        when @@N:   return "N"
        when @@NE:  return "NE"
        when @@E:   return "E"
        when @@SE:  return "SE"
        when @@S:   return "S"
        when @@SW:  return "SW"
        when @@W:   return "W"
        when @@NW:  return "NW"
        else        return "?"
        end
    end
end
