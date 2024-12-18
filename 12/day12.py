class Solution:
    fences = 0
    plant = ""
    regionSize = 0

def getInput(string):
    file = open(string ,"r")

    plants = []
    for line in file:
        temp = []
        for char in line:
            if not char == '\n':
                temp.append(char)

        plants.append(temp)
    return plants

def findRegion(sol, plants, x, y, lenX, lenY):
    N = (-1,0)
    E = (0,1)
    S = (1,0)
    W = (0,-1)
    sol.regionSize += 1
    sol.fences += 4
    directions = (N,E,S,W)
    plants[y][x] = chr(ord(sol.plant)+32)
    for direction in directions:
        newX = x + direction[1]
        newY = y + direction[0]
        if newX < lenX and newX >= 0 and newY < lenY and newY >= 0:
            if sol.plant == plants[newY][newX] or chr(ord(sol.plant)+32) == plants[newY][newX]:
                sol.fences -=1
            if sol.plant == plants[newY][newX]:
                findRegion(sol, plants, newX, newY, lenX, lenY)            
    
plants = getInput("input12.txt")

solArr = []
print(len(plants))
print(len(plants[0]))
y = 0
for y in range(len(plants)):
    x = 0
    for x in range(len(plants[y])):
        if ord(plants[y][x]) < 97:
            sol = Solution()
            sol.plant = plants[y][x]
            findRegion(sol, plants, x, y, len(plants[y]), len(plants))
            print("Fences:", sol.fences, "Regions Size:", sol.regionSize, "Plant:", sol.plant)
            solArr.append(sol)

val = 0
for entry in solArr:
    val += entry.fences * entry.regionSize

print("Summe:", val)
