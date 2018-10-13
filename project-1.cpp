#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc,char *argv[])
{ 
    for( int i = 0; i <= argc; i++)
    printf( "argv[%d]:%s\n", i, argv[i] );

    string s1 = argv[1];
    s1 += "/matrix.data" ;
 
	vector<int> myvec;
	ifstream fin(s1);
    int row, column, num=0;
    fin >> row;
    fin >> column;
    int** temp = new int*[row]; //�Q��temp �ʺA�O�Хh�y�@�ӤG���x�} 
	for(int k = 0; k < row; k++)
    temp[k] = new int[column];
    
    for(int k = 0; k < row; k++)
        for(int l = 0; l < column; l++)
        	fin >> temp[k][l];
	fin.close();
	
	for(int k=0; k<row; k++)
	{
      for(int l=0; l<column; l++)
      {
      	if(l>0)
      	{
        if(temp[k][l] >= temp[k][l-1]); //������� 
        else continue;
    	}
    	
    	if(l<column-1)
    	{
        if(temp[k][l] >= temp[k][l+1]); //����k�� 
        else continue;
    	}
    	
    	if(k<row-1)
    	{
        if(temp[k][l] >= temp[k+1][l]); //����U����
        else continue;
    	}
		
        if(k>0)
        {
        	if(temp[k-1][l] <= temp[k][l]); //����W���面
        	else continue;
		}
        
        myvec.push_back(k);
        myvec.push_back(l);
        if(temp[k][l] != temp[k][l+1])
        l++;
	  }
	  
    }
    num = myvec.size()/2;
    cout << num << endl;
    string s2 = argv[1];
    s2 += "/final.peak";

    ofstream file;
	file.open(s2);
	if(file.is_open())
	{
        file << num << endl;
		for(int i=0; i<num; i++)
        {
            file << myvec[i*2]+1 << ' ' << myvec[i*2+1]+1 << endl;
        }
	}
	file.close();
    return 0;
}
