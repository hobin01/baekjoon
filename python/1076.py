s1 = input()
s2 = input()
s3 = input()
color = {"black" : 0, "brown" : 1, "red" : 2, "orange" : 3, "yellow" : 4, "green" : 5, "blue" : 6, "violet" : 7, "grey" : 8, "white" : 9}
ans = (color[s1] * 10 + color[s2]) * (10 ** color[s3])
print(ans)