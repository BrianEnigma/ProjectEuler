#!/usr/bin/env python
#coding:utf-8
#Name:Find the pair of pentagonal numbers for which their sum and difference is pentagonal
#Date:04/12/2008
#Author: benben http://www.119797.com
import math

def isPentagonal(sum):
    num = (1 + math.sqrt(1 + 24*sum))/6.0
    return num == int(num)

def getMinDif1():
    diflist=[0,4]
    for i in range(3,10000):
        'dif= 3n-2'
        dif=3*i-2
        if isPentagonal(dif):
            if isPentagonal(3*i*i-4*i+1):
                return dif

        tmp=dif
        for j in range(len(diflist)-1,-1,-1):
            tmp+=diflist[j]
            if isPentagonal(tmp):
                'sum(i,j)=i*(3*i-1)/2+j*(3*j-1)/2'
                if isPentagonal(i*(3*i-1)/2+j*(3*j-1)/2):
                    return tmp
        diflist.append(dif)

def getMidDif2():
    pentas=set()
    dic={}

    p=0
    n=1
    while 1:
        p+=n*3-2
        if dic.has_key(p):
            return dic[p]
        for penta in pentas:
            diff=p-penta
            if diff in pentas:
                dic[p+penta]=diff
        pentas.add(p)
        n+=1
def main():
   print getMinDif1()
   print getMidDif2()

if __name__ == '__main__':
    main()