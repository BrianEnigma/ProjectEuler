#!/usr/bin/env ruby -wKU
require('../brian.rb')

class GridProducts < Grid
    attr_reader :bestProduct, :bestProductLocation, :bestProductDirection
    
    def initialize()
        super()
        @bestProduct = 0
        @bestProductLocation = [0,0]
        @bestProductDirection = -1
    end
    
    def scanAtWithDirection(x, y, length, direction)
        originalX = x
        originalY = y
        product = at(x, y)
        if (!inBounds?(x, y) || !canGo?(x, y, length, direction))
            return
        end
        begin #try
            for i in 0...(length - 1)
                if ([@@NW, @@N, @@NE].include?(direction)) then y -= 1 end
                if ([@@SW, @@S, @@SE].include?(direction)) then y += 1 end
                if ([@@NE, @@E, @@SE].include?(direction)) then x += 1 end
                if ([@@NW, @@W, @@SW].include?(direction)) then x -= 1 end
                product *= at(x, y)
            end
            if (product > @bestProduct)
                @bestProduct = product
                @bestProductLocation = [x, y]
                @bestProductDirection = direction
                print("New local record found (#{x}, #{y}):#{direction} = #{product}\n")
            end
        rescue => ex #catch
            print("Got exception \"#{ex.message}\" at (#{originalX}, #{originalY}):#{directionToName(direction)}\n")
            exit
        end #end try
    end

    def scanAt(x, y, length)
        for direction in @@N..@@NW
            scanAtWithDirection(x, y, length, direction)
        end
    end

    def scan(length)
        for row in 0...@grid.length
            for column in 0...@grid[row].length
                scanAt(column, row, length)
            end
        end
    end
end

grid = GridProducts.new
grid.loadFromFile('grid.txt')
print(grid)
#grid.testCanGo(4)
grid.scan(4)
print("Best record found (#{grid.bestProductLocation[0]}, #{grid.bestProductLocation[1]}):#{grid.directionToName(grid.bestProductDirection)} = #{grid.bestProduct}\n")
