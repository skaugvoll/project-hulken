def calcRec(height):
    x = 29
    y = height
    z = 29.6
    return (x * y * z)/1000

#print(calcRec(21))
print(calcRec(19))


def calcRightAngle(height):
    x = 29.6
    y = height
    z = 9

    return (0.5*x*z*y) / 1000

print(calcRightAngle(19))

print (calcRec(18) + calcRightAngle(18)) 


def findY():
    found = False
    y = 11.0
    while(found == False):
        r = calcRec(y)
        p = calcRightAngle(y)
        s = str(r+p)
        s = s.split(".")
        print("----------")
        print(s)
        sl = len(s[0])
        print(sl)
        print(s[0][0])
        print(s[0][1])
        found == True
        if(sl == 2 and s[0][0] == '1' and s[0][1] == '3' and s[1][0] == '9'):
            state = True
            return ("Y-verdien : " + str(y) + " gir totalt: " + str(r+p) + "l")
        elif(sl == 2 and s[0][0] == '1' and s[0][1] == '4' and s[1][0] == '0'):
            state = True
            return ("Y-verdien : " + str(y) + " gir totalt: " + str(r+p) + "l")
        else:
            y += 0.1

print(findY())

        
        
