# ARC-Algorithm   
###  ARC - Adaptive Replacement Cache Algorithm   
ARC works relying on two types of data: most frequently used and  last recently used. So it also keeps information of pages that has been already removed from the cache to make predictions.   
![arc-algorithm.png](files/arc-algorithm.png)    
### Install and Run   
To make and run a program:   
```
make
./arc
```
**Input:** first number - cache size; second - number of pages; next - pages (consider key = page).   
**Output:**  number of hits.   
To **delete** executable run: `make clean
`   
### Tests   
Tests were written with a help of [GoogleTest](https://google.github.io/googletest/) ([here](https://habr.com/ru/articles/667880/) is how to install it and make a basic tests).    
To make and run tests:   
```
make tests
./runtests
```
To **delete** tests run: `make tclean`    
### Links   
For more information about ARC follow: [https://www.andrew.cmu.edu/course/15-440/assets/READINGS/megiddo-computer2004.pdf](https://www.andrew.cmu.edu/course/15-440/assets/READINGS/megiddo-computer2004.pdf)    
   
