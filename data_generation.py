import random
import numpy as np
import os

for i in range(5,16):
    # cost範圍0-99, matrix size = i*i
    random_matrix = np.random.randint(0, 99, (i, i))

    # 對角線給-1(INF)
    for j in range(i):
        random_matrix[j][j] = -1
    
    file_name = 'n=' + str(i) + '.txt'
    folder = 'data2/'
    # check whether the folder exist (python>=3.2)
    os.makedirs(folder, exist_ok=True)
    file_path = folder + file_name

    # 開啟檔案
    fp = open(file_path, "w")

    # 將 lines 所有內容寫入到檔案
    fp.write(str(i))
    fp.write('\n')
    for j in range(i):
        for k in range(i):
            fp.write(str(random_matrix[j][k]) + ' ')
        fp.write('\n')
    
    # 關閉檔案
    fp.close()

    print(random_matrix)