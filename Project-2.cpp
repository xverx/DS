#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <vector>
#include <stack>
using namespace std;
typedef struct block_data
{
	int dist = -1;
	bool visited = false;
}Block;  //紀錄地圖上每個區塊的資料
int total = 0; //total:總共需要掃的格數；
queue<int> xque, yque, td_xque, td_yque;
stack<int> xstack, ystack;
int i, j;

void BFS(char **map, Block **distmap, int start_row, int start_col, int max_row, int max_col);
bool miss(Block **distmap, int test_row, int test_col, int max_row, int max_col);

int main()
{
	ifstream fin;
	fin.open("floor.txt"); //開測資檔，準備把資料寫進 
	
	int row, col, battery, entry_num = 0; //row:橫列數；column:直行數；battery:電量
	int R_row, R_col; //充電的位置   
	int cur_row, cur_col, cur_bat, step = 0, direc = 0 ;  //step:所用的步數  direc:方向代號 
	int back_row, back_col;
	vector<int> xvec, yvec; //用來記錄每步的座標 
	fin >> row;
	fin >> col;
	fin >> battery;
	char **map = new char* [row]; //造出一個動態二維矩陣(map)
	for(i=0; i<row; i++)
	    map[i] = new char [col];
	
	for(i=0; i<row; i++)   //將地圖的資料存入 map 
	    for(j=0; j<col; j++)
	        { 
			    fin >> map[i][j];
			    if(map[i][j] == 'R') //輸入地圖時，順便記錄 R 的位置 
			    {
			    	R_row = i;
			    	R_col = j;
				}
			}		
	fin.close();
	
	//以下為記錄入口 (起點) 的數量跟位置 
	if( (R_row-1 >= 0) && (map[R_row-1][R_col] == '0') )
	{
		xque.push(R_row-1); yque.push(R_col);  entry_num++;
	}
	if( (R_col-1 >= 0) && (map[R_row][R_col-1] == '0') )
	{
		xque.push(R_row); yque.push(R_col-1);  entry_num++;
	}
	if( (R_row+1 < row) && (map[R_row-1][R_col] == '0') )
	{
		xque.push(R_row+1);  yque.push(R_col); entry_num++;
	}
	if( (R_row+1 < col) && (map[R_row-1][R_col] == '0') )
	{
		xque.push(R_row);  yque.push(R_col+1); entry_num++;
	}
	int *entry_x = new int [entry_num];
	int *entry_y = new int [entry_num];
	for(i=0; i < entry_num; i++)
	{
		entry_x[i] = xque.front();  xque.pop();
		entry_y[i] = yque.front();  yque.pop();
	}
    
    Block **distmap = new Block* [row]; //造出一個動態二維矩陣(distmap)來存距離 
	for(i=0; i<row; i++)
	    distmap[i] = new Block [col];
	    
    Block **tempmap = new Block* [row]; //造出一個動態二維矩陣(distmap)來存某點至其他格的距離 
	for(i=0; i<row; i++)
	    tempmap[i] = new Block [col];    

    BFS(map, distmap, R_row, R_col, row, col); /*利用BFS找出各點離充電處的最短距離 
	   	  			 		      	 			       並找出需要掃的格數*/
															
	int hit = 0;    
	cur_row = R_row;
	cur_col = R_col;
	cur_bat = battery;
//	while(total > 0)
//	{
		hit = 0;
		while(hit < 4)
		{
			while( (cur_row-1 >= 0) && (cur_bat-1 >= distmap[cur_row-1][cur_col].dist)
			&& (distmap[cur_row-1][cur_col].dist>0) && (distmap[cur_row-1][cur_col].visited == false) ) //往上 
			{
				distmap[cur_row-1][cur_col].visited = true;
				cur_row = cur_row-1;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				xstack.push(cur_row);  ystack.push(cur_col);
				total--; step++; cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
				hit = 0;
				continue;
			}
			hit++;
			
			while(  (cur_col-1 >= 0) && (cur_bat-1 >= distmap[cur_row][cur_col-1].dist)
			&& (distmap[cur_row][cur_col-1].dist>0) && (distmap[cur_row][cur_col-1].visited == false) ) //往左 
			{
				distmap[cur_row][cur_col-1].visited = true;
				cur_col = cur_col-1;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				xstack.push(cur_row);  ystack.push(cur_col);
				total--; step++; cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
				hit = 0;
				continue;
			}
			hit++;
			
			while( (cur_row+1 < row) && (cur_bat-1 >= distmap[cur_row+1][cur_col].dist)
			&& (distmap[cur_row+1][cur_col].dist>0) && (distmap[cur_row+1][cur_col].visited == false) ) //往下 
			{
				distmap[cur_row+1][cur_col].visited = true;
				cur_row = cur_row+1;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				xstack.push(cur_row);  ystack.push(cur_col);
				total--; step++; cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
				hit = 0;
				continue;
			}
			hit++;
			
			while(  (cur_col+1 < col ) && (cur_bat-1 >= distmap[cur_row][cur_col+1].dist)
			&& (distmap[cur_row][cur_col+1].dist>0) && (distmap[cur_row][cur_col+1].visited == false) ) //往左 
			{
				distmap[cur_row][cur_col+1].visited = true;
				cur_col = cur_col+1;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				xstack.push(cur_row);  ystack.push(cur_col);
				total--; step++; cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
				hit = 0;
				continue;
			}
			hit++;
		}
		
		cout << cur_row << 'C' << cur_col << endl;
		if(cur_bat > distmap[cur_row][cur_col].dist)
		{
			map[R_row][R_col] = '1';
			BFS(map, tempmap, cur_row, cur_col, row, col);
			tempmap[cur_row][cur_col].dist = 0; //因為這格在原本的 map中是 0, 經BFS後那格會變 2而非 0 
			
			for(i=0; i<row; i++) //用來印出 tempmap 
			for(j=0; j<col; j++)
			{
        	cout.width(2); 
			cout << tempmap[i][j].dist << " ";
        	if(j == col-1)
        	cout << endl;
			}
		
		    xstack.pop();  ystack.pop(); //因為第一個是 cur_rol & cur_col 
		    back_row = xstack.top();  back_col = ystack.top();
		    while( !miss(distmap, back_row, back_col, row, col) )
		    {
	 	        xstack.pop();  ystack.pop();
	 	        back_row = xstack.top();  back_col = ystack.top();
		    }
		    cout << back_row << 'B' << back_col << endl;
		}
		
		if(cur_bat > tempmap[back_row][back_col].dist + distmap[back_row][back_col].dist)
		{
			
			continue;
		}
		
		while(distmap[cur_row][cur_col].dist > 1)  //聰明的回去 
		{
			if( (cur_row-1 >=0) && (distmap[cur_row-1][cur_col].dist>0) && (distmap[cur_row][cur_col].dist > distmap[cur_row-1][cur_col].dist) )
			{
				cur_row = cur_row-1;  cur_col = cur_col;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
			}
			
			else if( (cur_col-1 >=0) && (distmap[cur_row][cur_col-1].dist>0) && (distmap[cur_row][cur_col].dist >= distmap[cur_row][cur_col-1].dist) )
			{
				cur_row = cur_row;  cur_col = cur_col-1;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
			}
			
			else if( (cur_row+1 < row) && (distmap[cur_row+1][cur_col].dist>0) && (distmap[cur_row][cur_col].dist >= distmap[cur_row+1][cur_col].dist) ) 
			{
				cur_row = cur_row+1;  cur_col = cur_col;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
			}
			
			else if( (cur_col+1 < col) && (distmap[cur_row][cur_col+1].dist>0) && (distmap[cur_row][cur_col].dist >= distmap[cur_row][cur_col+1].dist) )
			{
				cur_row = cur_row;  cur_col = cur_col+1;
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
				cout << cur_row << " " << cur_col << " " << cur_bat << endl;
			}
			//xstack.pop();  ystack.pop();	
		}
		xvec.push_back(R_row);  yvec.push_back(R_col); step++; cur_bat = battery;
		cout << R_row << " " << R_col << " " << cur_bat << endl;
		if(total > 0)
		{
		    xvec.push_back(cur_row);  yvec.push_back(cur_col); step++; cur_bat--;
			//xstack.push(cur_row);  ystack.push(cur_col);
			cout << cur_row << " " << cur_col << " " << cur_bat << endl;
		}
//	}
	cout << total << " " << step << endl;
	for(i=0; i<row; i++) //用來印出 distmap.dist 
	for(j=0; j<col; j++)
	{
        cout.width(2); 
		cout << distmap[i][j].dist << " ";
        if(j == col-1)
        cout << endl;
	}
	cout << endl;
	for(i=0; i<row; i++) //用來印出 distmap.visited
	for(j=0; j<col; j++)
	{
        cout.width(2); 
		cout << distmap[i][j].visited << " ";
        if(j == col-1)
        cout << endl;
	}
	
	i = 0;  cout << step << endl; 
	while(xvec[i]!=NULL)
	{
		cout<< xvec[i] << " " << yvec[i] << endl;
		i++;
	}

	return 0;
}

void BFS(char **map, Block **distmap, int start_row, int start_col, int max_row, int max_col)
{
	int distance = 0, cur_row, cur_col;
	distmap[start_row][start_col].dist = 0;
	xque.push(start_row);
	yque.push(start_col);
	while( ( !xque.empty() )&& ( !yque.empty() ) )
	{
		cur_row = xque.front();   xque.pop();
		cur_col = yque.front();  yque.pop();
		distance = distmap[cur_row][cur_col].dist;
		
		if( (cur_row-1 >=0) && (distmap[cur_row-1][cur_col].visited == false) && (map[cur_row-1][cur_col] == '0') )//考慮上面 
		{
			xque.push(cur_row-1);  yque.push(cur_col);
			distmap[cur_row-1][cur_col].visited = true;
			distmap[cur_row-1][cur_col].dist = distance + 1 ;
			total++;
		}
		
		if( (cur_col-1 >=0) && (distmap[cur_row][cur_col-1].visited == false) && (map[cur_row][cur_col-1] == '0') )//考慮左邊 
		{
			xque.push(cur_row);  yque.push(cur_col-1);
			distmap[cur_row][cur_col-1].visited = true;
			distmap[cur_row][cur_col-1].dist = distance + 1 ;
			total++;
		}
		
		if( (cur_row+1 < max_row) && (map[cur_row+1][cur_col] == '0') && (distmap[cur_row+1][cur_col].visited == false) )//考慮下面 
		{
			xque.push(cur_row+1);  yque.push(cur_col);
			distmap[cur_row+1][cur_col].visited = true;
			distmap[cur_row+1][cur_col].dist = distance + 1 ;
			total++;
		}
		
		if( (cur_col+1 < max_col) && (map[cur_row][cur_col+1] == '0') && (distmap[cur_row][cur_col+1].visited == false) )//考慮右邊 
		{
			xque.push(cur_row);  yque.push(cur_col+1);
			distmap[cur_row][cur_col+1].visited = true;
			distmap[cur_row][cur_col+1].dist = distance + 1 ;
			total++;
		}
	}
	
	for(i=0; i<max_row; i++)
	    for(j=0; j<max_col; j++)
	    distmap[i][j].visited = false;
}

bool miss(Block **distmap, int test_row, int test_col, int max_row, int max_col)
{
	if ( (test_row-1 >= 0) && (distmap[test_row-1][test_col].dist > 0) && (distmap[test_row-1][test_col].visited == false) ) //上面
	return true; 
	if ( (test_col-1 >= 0) && (distmap[test_row][test_col-1].dist > 0) && (distmap[test_row][test_col-1].visited == false) ) //左邊
	return true;
	if ( (test_row+1 < max_row) && (distmap[test_row+1][test_col].dist > 0) && (distmap[test_row+1][test_col].visited == false) ) //下面
	return true;
	if ( (test_col+1 < max_col) && (distmap[test_row][test_col+1].dist > 0) && (distmap[test_row][test_col+1].visited == false) ) //右邊
	return true;
}
