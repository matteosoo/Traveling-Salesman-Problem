# Traveling-Salesman-Problem (TSP)

## How to use?
1. 使用g++編譯, 於macOS測試
2. 需要安裝萬用標頭 <bits/stdc++.h> 
    - 參考自: https://stackoverflow.com/questions/28994148/how-can-i-include-bits-stdc-in-xcode
3. 編譯C++程式
    ```
    $ g++ -std=c++11 -o brute_force.exe brute_force.cpp
    $ g++ -std=c++11 -o branch_and_bound.exe branch_and_bound.cpp
    ```
4. 執行編譯好的程式
    ```
    $ ./brute_force.exe data/n=5.txt
    $ ./branch_and_bound.exe data/n=5.txt
    ```
- (Optional) 新增test data(n=5~15, cost範圍0~99, -1為∞)
    ```
    $ python data_generation
    ```

    
## Experiments results

- Brute Force method with MacBook Pro with 2.4 GHz Quad-Core Intel Core i5
 
| Brute Force | n=5         | n=6         | n=7         | n=8         | n=9         | n=10        | n=11        | n=12         | n=13          | n=14    | n=15    |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ------------ | ------------- | ------- | ------- |
| case1       | 0.0000164 s | 0.0000876 s | 0.0005911 s | 0.0040542 s | 0.0304935 s | 0.2665420 s | 2.4636397 s | 28.0222759 s | 354.4289551 s | >900 s  | >900 s  |
| case2       | 0.0000269 s | 0.0000892 s | 0.0005121 s | 0.0036864 s | 0.0299419 s | 0.2303828 s | 2.3641641 s | 27.2007713 s | 347.3847656 s | >900 s  | >900 s  |
| case 3      | 0.0000283 s | 0.0000882 s | 0.0006351 s | 0.0044859 s | 0.0319539 s | 0.2293398 s | 2.4864314 s | 28.3131065 s | 344.7347412 s | >900  s | >900  s |
|  Average           |      0.0000239 s       |        0.0000883 s     |      0.0005794 s       |  0.0040755 s           |    0.0307964 s         |  0.2420882 s           |    2.4380784 s         |  27.8453846 s            |   348.8494873 s            |   >900 s      |    >900 s     |

- Brach & Bound method with MacBook Pro with 2.4 GHz Quad-Core Intel Core i5

| Branch & Bound | n=5 | n=6  | n=7 | n=8 | n=9 | n=10 | n=11 | n=12 | n=13 | n=14 | n=15 |
| ----------- | --- | ---- | --- | --- | --- | ---- | ---- | ---- | ---- | ---- | ---- |
| case1            |  0.0002337 s   |  0.0004292 s   |  0.0024168 s   |  0.0028669 s   |  0.0328721 s   |  0.1154692 s    | 0.3558037 s     |  1.0865456 s   |   0.6156181 s   |  5.1823344 s    |   18.7746181 s   |
| case2       | 0.0002330 s    |  0.0007600 s    | 0.0047157 s    | 0.0123743 s    |  0.0361437 s   | 0.1006595 s     |  0.1709510 s    | 1.0765845 s     |  0.0974235 s    |  7.6942883 s    |   12.3238401 s   |
| case 3      |  0.0002597 s   | 0.0007564 s |  0.0042115 s   |   0.0088815 s  |  0.0459133 s   | 0.0884868 s     |  0.3559157 s    |  0.3722214 s    |   1.2539816 s   |  1.3930553 s    |  14.6222963 s    |
|    Average         |     0.0002421 s        |  0.0006485 s           |   0.0037813 s          |  0.0080409 s           |   0.0383097 s          |  0.1015385 s           |   0.2942235 s          |  0.8451172 s            |  0.6556744 s             | 4.7565593 s        |  15.2402515 s       |



## TODO List
- [x] 計算程式執行時間
- [x] 執行時間round取小數點到第7位數
- [x] 合併BF和BB的code
- [x] 上交作業的測資input.txt寫死(路徑會和執行檔相同, 檔名即“input.txt”)
- [x] 出發點一律從 0 出發
- [x] 生出測資(n:5-15,cost:0-99)完成表格

## References
- brute_force: 
    - https://www.geeksforgeeks.org/traveling-salesman-problem-tsp-implementation/
- branch_and_bound: 
    - https://www.techiedelight.com/travelling-salesman-problem-using-branch-and-bound/
- https://www.geeksforgeeks.org/traveling-salesman-problem-using-branch-and-bound-2/ commit:[f9f748d](https://github.com/matteosoo/Traveling-Salesman-Problem/commit/f9f748d83dd23239edcc116c665ea402cf24d28f)
