import re

#Part 1:
file = open('input03.txt', 'r')
summe = 0
for line in file:
    liste = re.findall("mul\(\d+,\d+\)", line)
    for entry in liste:
        temp = re.findall("\d+,\d+", entry)
        for e in temp:
            s = e.split(",")
            num1 = s[0]
            num2 = s[1]
            summe = summe + int(num1)*int(num2)

file.close()
print("sum only mul:", summe)
string = ""

#Part 2:
file = open('input03.txt', 'r')
for line in file:
    string = string+line.rstrip("\n")
file.close()


l = len(string)
i = 0
while i < l:
    s = "don't()"
    s2 = ""
    y = 0
    while i < l and y < len(s) and string[i] == s[y]:
        s2 += string[i]
        i +=1
        y +=1
            
    if y == len(s):
        flag = True
        while flag and i < l:
            s2 += string[i]
            if i < l - 3 and string[i] == "d" and string[i+1] == "o" and string[i+2] == "(" and string[i+3] == ")":
                flag = False
            i+=1
    if s2 != "":
        liste = re.findall("mul\(\d+,\d+\)", s2)
        for entry in liste:
            temp = re.findall("\d+,\d+", entry)
            for e in temp:
                s = e.split(",")
                num1 = s[0]
                num2 = s[1]
                summe = summe - int(num1)*int(num2)
    i +=1
print("sum mul with dont and do:", summe)
