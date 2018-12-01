#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include <string>
using namespace std;
typedef struct block_data
{
	int dist = -1;
	bool visited = false;
}Block;  //紀錄地圖上每個區塊的資料
int total = 0; //total:總共需要掃的格數；
queue<int> xque, yque;
stack<int> xstack, ystack;
int i, j, step = 0, cur_bat; //step: 總共步數   cur_bat:剩下電量
int cur_row, cur_col; 
vector<int> xvec, yvec; //用來記錄每步的座標 

void BFS(char **map, Block **distmap, int start_row, int start_col, int max_row, int max_col);
void BFS_temp(Block **distmap, Block **tempmap, int start_row, int start_col, int max_row, int max_col);
bool miss(Block **distmap, int test_row, int test_col, int max_row, int max_col);


int main(int argc,char *argv[])
{
	for( int i = 0; i <= argc; i++)
    printf( "argv[%d]:%s\n", i, argv[i] );

    string s1 = argv[1];
    s1 += "/floor.data" ;
    s1 = "./" + s1;
	
	ifstream fin(s1);
	
	int row, col, battery; //row:橫列數；column:直行數；battery:電量
	int R_row, R_col; //充電的位置    
	int back_row, back_col, temptotal;
	int stack_empty_row, stack_empty_col;
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

    Block **distmap = new Block* [row]; //造出一個動態二維矩陣(distmap)來存距離 
	for(i=0; i<row; i++)
	    distmap[i] = new Block [col];
	    
    Block **tempmap = new Block* [row]; //造出一個動態二維矩陣(distmap)來存某點至其他格的距離 
	for(i=0; i<row; i++)
	    tempmap[i] = new Block [col];    

    BFS(map, distmap, R_row, R_col, row, col); /*利用BFS找出各點離充電處的最短距離 
	   	  			 		      	 			       並找出需要掃的格數*/
	delete map;
														
	int hit = 0;    
	cur_row = R_row;
	cur_col = R_col;
	cur_bat = battery;
	while(total > 0) //讓機器人一直線走，撞牆就換方向，直到被卡住為止。 
	{
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
				hit = 0;
				continue;
			}
			hit++;
		}
		
		if(total > 0)
		{
			temptotal = total; //因為BFS會動到total，所以要先暫時存在temptotal 
			if(cur_bat > distmap[cur_row][cur_col].dist)
			{
			BFS_temp(distmap, tempmap, cur_row, cur_col, row, col);
			tempmap[cur_row][cur_col].dist = 0; //因為這格在原本的 map中是 0, 經BFS後那格會變 2而非 0 
			}
			total = temptotal;
			
			if(!xstack.empty())
			{                               //直走到因為電量不夠而非撞牆而停止時，除了會讓他回去
				stack_empty_row = cur_row,  //也會讓 x_stack 會空掉，會導致找不到下個目的地 
				stack_empty_col = cur_col;  //所以要記錄原本的位置，好讓機器人能找到下個目的地 
				if( (xstack.top() == cur_row) && (ystack.top() == cur_col) )//如果第一個是 cur_rol & cur_col就 pop,其他狀況怕會把找到的back誤刪 
				{
			        xstack.pop();  ystack.pop();
				}
			}
			if(!xstack.empty())
		    {
		    	back_row = xstack.top();  back_col = ystack.top();
			}
			else
			{
				back_row = stack_empty_row;  back_col = stack_empty_col; 
			}
			
			while( (!xstack.empty()) && ( !miss(distmap, back_row, back_col, row, col) ) )
		    {
	 	        xstack.pop();  ystack.pop();
	 	        if(!xstack.empty())
	 	        {
	 	        	back_row = xstack.top();  back_col = ystack.top();
		 		}
 	        	else break;
		    }
//		    if(!xstack.empty())
//		    {
				if(cur_bat > tempmap[back_row][back_col].dist + distmap[back_row][back_col].dist) //還沒考慮到中間的充電機會 
				{
			 	    int temp_row = back_row, temp_col = back_col;
					stack<int> tempx_stack, tempy_stack;
					tempx_stack.push(temp_row);  tempy_stack.push(temp_col);
					while(tempmap[temp_row][temp_col].dist > 0) //記錄最短路程 
					{
						if( (temp_row-1 >=0) && (tempmap[temp_row-1][temp_col].dist >= 0) && (tempmap[temp_row-1][temp_col].dist < tempmap[temp_row][temp_col].dist) ) //上面 
					    {
							temp_row--;
							tempx_stack.push(temp_row);  tempy_stack.push(temp_col);  continue;
						}
					
						if( (temp_col-1 >=0) && (tempmap[temp_row][temp_col-1].dist >= 0) && (tempmap[temp_row][temp_col-1].dist < tempmap[temp_row][temp_col].dist) ) //左邊 
						{ 
							temp_col--;
							tempx_stack.push(temp_row);  tempy_stack.push(temp_col);  continue;
					    }
					
						if( (temp_row+1 < row) && (tempmap[temp_row+1][temp_col].dist >= 0) && (tempmap[temp_row+1][temp_col].dist < tempmap[temp_row][temp_col].dist) ) //下面 
						{
							temp_row++;
							tempx_stack.push(temp_row);  tempy_stack.push(temp_col);  continue;
						}
					
						if( (temp_col+1 < col) && (tempmap[temp_row][temp_col+1].dist >= 0) && (tempmap[temp_row][temp_col+1].dist < tempmap[temp_row][temp_col].dist) ) //右邊 
						{
							temp_col++;
							tempx_stack.push(temp_row);  tempy_stack.push(temp_col);  continue;
						}
				    }
					tempx_stack.pop();  tempy_stack.pop();//因為最上面會是現在的位置，不需要再園地打轉一次 
					
					while(!tempx_stack.empty())
					{
					    cur_row = tempx_stack.top();  cur_col = tempy_stack.top();
						tempx_stack.pop();  tempy_stack.pop();
						xvec.push_back(cur_row);  yvec.push_back(cur_col);
						step++; cur_bat--;
					}
					//到了需要再檢查的點後，如果最近的充電入口較近，就讓他回去充電
					//go to back_row & back_col
					//讓他走到[back_row][back_col]
					//電量如果還夠回去就continue;
					if( (cur_bat > distmap[cur_row][cur_col].dist)  )  continue;
   					//這個if的右邊條件覺得可有可無哈哈哈哈哈 
				}
//			} 
		}

		while(distmap[cur_row][cur_col].dist > 1)  //聰明的回去 (go back)
		{
			if( (cur_row-1 >=0) && (distmap[cur_row-1][cur_col].dist>0) && (distmap[cur_row][cur_col].dist > distmap[cur_row-1][cur_col].dist) )
			{
		
				cur_row = cur_row-1;  cur_col = cur_col;
				if(distmap[cur_row][cur_col].visited == false)
				{
					distmap[cur_row][cur_col].visited = true;  total--;
				}
				
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
			}
			
			else if( (cur_col-1 >=0) && (distmap[cur_row][cur_col-1].dist>0) && (distmap[cur_row][cur_col].dist >= distmap[cur_row][cur_col-1].dist) )
			{
				cur_row = cur_row;  cur_col = cur_col-1;
				if(distmap[cur_row][cur_col].visited == false)
				{
					distmap[cur_row][cur_col].visited = true;  total--;
				}
				
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
			}
			
			else if( (cur_row+1 < row) && (distmap[cur_row+1][cur_col].dist>0) && (distmap[cur_row][cur_col].dist >= distmap[cur_row+1][cur_col].dist) ) 
			{
				cur_row = cur_row+1;  cur_col = cur_col;
				if(distmap[cur_row][cur_col].visited == false)
				{
					distmap[cur_row][cur_col].visited = true;  total--;
				}
				
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
			}
			
			else if( (cur_col+1 < col) && (distmap[cur_row][cur_col+1].dist>0) && (distmap[cur_row][cur_col].dist >= distmap[cur_row][cur_col+1].dist) )
			{
				cur_row = cur_row;  cur_col = cur_col+1;
				if(distmap[cur_row][cur_col].visited == false)
				{
					distmap[cur_row][cur_col].visited = true;  total--;
				}
				
				xvec.push_back(cur_row);  yvec.push_back(cur_col);
				step++;  cur_bat--;
			}	
		}
		
		xvec.push_back(R_row);  yvec.push_back(R_col); step++; cur_bat = battery;
		if(total > 0)
		{
		    xvec.push_back(cur_row);  yvec.push_back(cur_col); step++; cur_bat--;
		}
	}
	
    string s2 = argv[1];
    s2 += "/final.path";

    ofstream file;
	file.open(s2);
	if(file.is_open())
	{
        file << step << endl;
		for(i=0; i<step; i++)
        {
            file << xvec[i] << " " << yvec[i] << " " << endl;
        }
	}
	file.close();

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

void BFS_temp(Block **distmap, Block **tempmap, int start_row, int start_col, int max_row, int max_col)
{
	int distance = 0, cur_row, cur_col;
	tempmap[start_row][start_col].dist = 0;
	xque.push(start_row);
	yque.push(start_col);
	while( ( !xque.empty() )&& ( !yque.empty() ) )
	{
		cur_row = xque.front();   xque.pop();
		cur_col = yque.front();  yque.pop();
		distance = tempmap[cur_row][cur_col].dist;
		
		if( (cur_row-1 >=0) && (tempmap[cur_row-1][cur_col].visited == false) && (distmap[cur_row-1][cur_col].dist > 0) )//考慮上面 
		{
			xque.push(cur_row-1);  yque.push(cur_col);
			tempmap[cur_row-1][cur_col].visited = true;
			tempmap[cur_row-1][cur_col].dist = distance + 1 ;
			total++;
		}
		
		if( (cur_col-1 >=0) && (tempmap[cur_row][cur_col-1].visited == false) && (distmap[cur_row][cur_col-1].dist > 0) )//考慮左邊 
		{
			xque.push(cur_row);  yque.push(cur_col-1);
			tempmap[cur_row][cur_col-1].visited = true;
			tempmap[cur_row][cur_col-1].dist = distance + 1 ;
			total++;
		}
		
		if( (cur_row+1 < max_row) && (tempmap[cur_row+1][cur_col].visited == false) && (distmap[cur_row+1][cur_col].dist > 0) )//考慮下面 
		{
			xque.push(cur_row+1);  yque.push(cur_col);
			tempmap[cur_row+1][cur_col].visited = true;
			tempmap[cur_row+1][cur_col].dist = distance + 1 ;
			total++;
		}
		
		if( (cur_col+1 < max_col) && (tempmap[cur_row][cur_col+1].visited == false) && (distmap[cur_row][cur_col+1].dist > 0) )//考慮右邊 
		{
			xque.push(cur_row);  yque.push(cur_col+1);
			tempmap[cur_row][cur_col+1].visited = true;
			tempmap[cur_row][cur_col+1].dist = distance + 1 ;
			total++;
		}
	}
	
	for(i=0; i<max_row; i++)
	    for(j=0; j<max_col; j++)
	    tempmap[i][j].visited = false;
}
