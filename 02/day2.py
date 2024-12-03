def check(data):
    safe = 0
    desc = False
    asc = False
    for i in range(len(data)-1):
        safe = 1
        diff = data[i+1]-data[i]
        if diff > 0:
            desc = True
        if diff < 0:
            asc = True
        if desc == True and asc == True or abs(diff) > 3 or abs(diff) < 1:
            safe = 0
            break
    return safe

file = open('input02.txt', 'r')
safe_count = 0
for line in file:
    data =[int(value)for value in line.split()]
    desc = False
    asc = False
    safe = check(data)
    if safe == 0:
        for i in range(len(data)):
            rem = data.pop(i)
            safe = check(data)
            if safe == 1:
                break
            data.insert(i, rem)
    safe_count += safe
print(safe_count)

file.close()
