# Traveling-Salesman-Problem (TSP)
1. 使用g++編譯, 於macOS測試
2. 需要安裝萬用標頭 <bits/stdc++.h> 
    - 參考自: https://stackoverflow.com/questions/28994148/how-can-i-include-bits-stdc-in-xcode
3. 編譯C++程式
    - g++ -std=c++11 -o brute_force.exe brute_force.cpp
    - g++ -std=c++11 -o branch_and_bound.exe branch_and_bound.cpp
4. 執行編譯好的程式
    - ./brute_force.exe data/n=5.txt
    - ./branch_and_bound.exe data/n=5.txt

- References
    - brute_force: https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/
    - branch_and_bound: https://www.geeksforgeeks.org/traveling-salesman-problem-using-branch-and-bound-2/

## TODO List
- [ ] 讀檔的start time？
- [ ] Time取到第幾位數？
- [ ] 合併BF和BB的code
- [ ] 上交作業的測資input.txt寫死(路徑會和執行檔相同, 檔名即“input.txt”)
- [x] 出發點一律從 0 出發
- [ ] 生出測資(n:5-15,cost:0-99)並完成表格
