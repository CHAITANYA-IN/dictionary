import csv
import matplotlib.pyplot as plt
import matplotlib.axes as axes

scale_factor = 0.000001
plt.xlabel("Number of Stop Words")
plt.ylabel("Time")
plt.title('Dictionary') 
plt.yscale('linear')
plt.axis('tight')
axes.Axes.set_yscale('linear', 100000)
c = csv.reader(open("/Users/chaitanya/Desktop/points.csv"))
next(c, 0)
j=0
l=[]

while j < 40:
    l.append([i[j] for i in c])
    c = csv.reader(open("/Users/chaitanya/Desktop/points.csv"))
    next(c, 0)
    j+=1
j=0

for i in l[1:]:
    string = "line " + str(j)
    plt.plot(l[0], i, '-', 2, label=string)
    j+=1
plt.show()