import re

f = open('input04.txt', 'r')


#Part 1:
text = ""
arr1 = []
for line in f:
    arr = []
    text += line
    for char in line:
        if char != "\n":
            arr.append(char)
    arr1.append(arr)

i = 0
word = "XMAS"
count = 0
x = re.findall("XMAS", text)

count = len(x)
print("forwards", count)
x = re.findall("SAMX", text)
count += len(x)
print("backwards:", count)
while i < len(arr1[0]):
    y = 0
    while y < len(arr1):
        p = 0
        z = y
        while z < len(arr1) and p < len(word) and arr1[z][i] == word[p]:
            z+=1
            p+=1
        if p == len(word):
            count+=1
        y+=1
    i+=1
i = len(arr1[0])-1
print("vertikal:", count)
while i >= 0:
    y = len(arr1)-1
    while y >= 0:
        p = 0
        z = y
        while z >= 0 and p < len(word) and arr1[z][i] == word[p]:
            z-=1
            p+=1
        if p == len(word):
            count+=1
        y-=1
    i-=1
print("vertikal, backwards:", count)
i = len(arr1)-1
while i >= 0:
    y = len(arr1[0])-1
    while y >= 0:
        p = 0
        y1 = y
        i1 = i
        z = 1
        while y1 < len(arr1[0]) and i1 >= 0 and p < len(word) and arr1[i1][y1] == word[p]:
            #print("hit on", y1,"->" ,i1, "=",arr1[i1][y1])
            y1+=1
            i1-=1
            p+=1
            z+=1
        y1 = y
        i1 = i
        if p == len(word):
            count+=1
        p = 0
        z = 1
        while y1 >= 0 and i1 >= 0 and p < len(word) and arr1[i1][y1] == word[p]:
            #print("hit on", y1,"->" ,i1, "=",arr1[i1][y1])
            p+=1
            i1-=1
            y1-=1
            z+=1
            
        if p == len(word):
            count+=1
        y-=1   
    i-=1
print("Diagonal backwards", count)
i = 0
while i < len(arr1):
    y = 0
    while y < len(arr1[0]):
        p = 0
        y1 = y
        i1 = i
        while y1 < len(arr1[0]) and i1 < len(arr1) and p < len(word) and arr1[i1][y1] == word[p]:
            #print("hit on", y1,"->" ,i1, "=",arr1[i1][y1])
            y1+=1
            i1+=1
            p+=1
        y1 = y
        i1 = i
        if p == len(word):
            count+=1
        p = 0
        while y1 >= 0 and i1 < len(arr1) and p < len(word) and arr1[i1][y1] == word[p]:
            #print("hit on", y1,"->" ,i1, "=",arr1[i1][y1])
            p+=1
            i1+=1
            y1-=1
        if p == len(word):
            count+=1
        y+=1   
    i+=1

print("Diagonal forwards", count)

#Part2:
x = 0
word = "MAS"
print(word)
word2 = "SAM"
masCount = 0
y = 0
for e in arr1:
    print(e)
while y < len(arr1):
    x = 0
    while x < len(arr1[0]):
        p=0
        p2=0
        y1=y
        x1=x
        while y1 < len(arr1[0]) and x1 < len(arr1) and p < len(word) and arr1[y1][x1] == word[p]:
            #print("hit on word", y1,"->" ,x1, "=",arr1[y1][x1])
            x1+=1
            y1+=1
            p+=1
        y1 = y
        x1 = x
        while y1 < len(arr1[0]) and x1 < len(arr1) and p2 < len(word) and arr1[y1][x1] == word2[p2]:
            #print("hit on word2", y1,"->" ,x1, "=",arr1[y1][x1])
            x1+=1
            y1+=1
            p2+=1
        if p == len(word) or p2 == len(word2):
            #print("found")
            p=0
            p2=0
            x1=x
            x1+=2
            y1=y
            while 0 <= x1 < len(arr1) and 0 <= y1 < len(arr1[0]) and p < len(word) and arr1[y1][x1] == word[p]:
                #print("second word hit on", y1,"->" ,x1, "=",arr1[y1][x1])
                y1+=1
                x1-=1
                p+=1
            x1=x
            x1+=2
            y1=y
            while 0 <= x1 < len(arr1) and 0 <= y1 < len(arr1[0]) and p2 < len(word) and arr1[y1][x1] == word2[p2]:
                #print("second word2 hit on", y1,"->" ,x1, "=",arr1[y1][x1])
                y1+=1
                x1-=1
                p2+=1
            #print("try again")
            if p == len(word) or p2 == len(word2):
                masCount+=1
        x+=1   
    y+=1

print("MAS Count:",masCount)


