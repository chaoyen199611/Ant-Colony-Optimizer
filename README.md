# Ant-Colony-Optimizer
Using ant colony optimizer to solve TSP
## 程式流程
###簡介
    本次作業採用的資料為eil51，總共有51座城市，使用ant-colony-optimizer來解決最短路徑問題
    蟻群數量設定為20隻，進行51個run，每個run總共有1000次迭代。
###Initialize
    首先將所有可能路徑的距離計算出來，並且給予所有路徑一個初始的費洛蒙值，此次設為。
    ```c++
    for(int i=0;i<location.size();i++){
		for(int j=0;j<location.size();j++){
			double x,y,result;
			x=(location[i].first-location[j].first)*(location[i].first-location[j].first);
			y=(location[i].second-location[j].second)*(location[i].second-location[j].second);
			result=sqrt(x+y);
			distance[i][j]=result;
		}
	}
    for(int j=0;j<51;j++){
		for(int k=0;k<51;k++){
			phermone[j][k]=initialPhermone;
		}
	}
    ```
## 程式結果
![](https://github.com/chaoyen199611/Ant-Colony-Optimizer/blob/main/Figure_1.png)
