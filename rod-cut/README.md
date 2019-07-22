## The following are required to avoid seg fault:
https://github.com/Mrunmoy/dynamic-programming/blob/master/rod-cut/main.cpp#L29
https://github.com/Mrunmoy/dynamic-programming/blob/master/rod-cut/main.cpp#L46




## This is required to avoid underflow:
https://github.com/Mrunmoy/dynamic-programming/blob/master/rod-cut/main.cpp#L28




## This was done so as to avoid using a cost that would be less if this length was re-built using smaller sizes:
https://github.com/Mrunmoy/dynamic-programming/blob/master/rod-cut/main.cpp#L16

for example: if a rod of length 4 had a price of $5 but rod of length 2 costs $3, then we should consider using lenghts 2 & 2 to get a revenue of $6 instead of a single piece of 4 (revenue $5) when solving for rod of length 5.
