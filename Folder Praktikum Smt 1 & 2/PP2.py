data2 = {10, 20, 30}
data2.add(40)
print(data2)

data3 = {15, 30, 50}

data_Union = data2.union(data3)
data_Union = data2 |data3
print(data_Union)

data_intersection = data2.intersection(data3)
data_intersection = data2 & data3
print(data_intersection)

data_difference = data2.difference(data3)
data_difference = data2 - data3
print(data_difference)