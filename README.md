# Ant-Colony-Optimizer
Using ant colony optimizer to solve TSP
## 程式流程
### 簡介
本次作業採用的資料為eil51，總共有51座城市，使用ant-colony-optimizer來解決最短路徑問題<br>
蟻群數量設定為20隻，進行51個run，每個run總共有1000次迭代。
### Initialization
首先將所有可能路徑的距離計算出來，並且給予所有路徑一個初始的費洛蒙值，此次設為0.5。<br>
下方為計算所有城市間可行路徑的所有距離。
```c
for(int i=0;i<location.size();i++){
	for(int j=0;j<location.size();j++){
		double x,y,result;
		x=(location[i].first-location[j].first)*(location[i].first-location[j].first);
		y=(location[i].second-location[j].second)*(location[i].second-location[j].second);
		result=sqrt(x+y);
		distance[i][j]=result;
	}
}
```
將所有路徑上的費洛蒙初始值設為0.5。<br>
```c
for(int j=0;j<51;j++){
	for(int k=0;k<51;k++){
		phermone[j][k]=initialPhermone;
	}
}
```
### Transition
#### 蟻群建立新的路徑
每隻螞蟻會先隨機選一城市作為出發點。<br>
```c
int startCity=rand()%51;
```
#### 費洛蒙的更新
當螞蟻走訪完所有城市，建立一個新的完整的路徑後，便會進行路徑上費洛蒙量的更新。<br>
為了確保從a城市到b城市和b城市到a城市的路徑是識為相同的，因此在下方的for迴圈中有將目的地和出發點對調，以確保之後無論出發點為何，只要是到達此路徑費洛蒙的數量都不會受影響。<br>
其中的`phermoneAmount`為一常數，將其設為`100`，而`dis[k]`則為當前螞蟻k這次疊代的路徑總長<br>
下圖為參考公式和程式碼<br>
<img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/da75f512c94f2b2737112bebbf97539f5f6928c0" alt="drawing" width="500"/><br>
```c
for(int n=0;n<route.size()-1;n++){
	deltaphermone[route[n]][route[n+1]]+=phermoneAmount/dis[k];
	deltaphermone[route[n+1]][route[n]]+=phermoneAmount/dis[k];
}
```
下圖為費洛蒙更新的公式<br>
<img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/62ef8b59ad37970b4e693ee923b6d7db8bbd5c30" alt="drawing" width="500"/><br>
上方已經計算出每個路徑上的Δphermone，接著在每次迭代結束後帶入此公式則能更新每個路徑上存留的費洛蒙數量。<br>
其中的`vaporRate`為一常數，也就是蒸發的量。<br>
```c
for(int n=0;n<51;n++){
	for(int k=0;k<51;k++){
		phermone[n][k]=(1-vaporRate)*phermone[n][k]+deltaphermone[n][k];
	}
}
```
### Evaluation
每一次迭代結束，我們可以得到`n`隻螞蟻新的路徑，在此次作業中為20隻，接著在20個路徑中找尋到最短路徑，即是我這次迭代的最佳結果。<br>
```c
double tmp=2000;
for(int n=0;n<ants;n++){
	if(dis[n]<tmp) tmp=dis[n];
}
result[i][j]=tmp;
```
### Determination
## 程式結果
<img src="https://github.com/chaoyen199611/Ant-Colony-Optimizer/blob/main/Figure_1.png" alt="drawing" width="500"/>

