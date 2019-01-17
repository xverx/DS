class Student //暴力人定勝天法
{
    public:
	void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor)
		{
             //Your Code
             int i,j;
             int z = 0;
             while(z<1)
             {
             	if(Record[0][0] == 0)
             	{
             		x = 0;
             		y = 0;
             		break;
	 			}
	 			
	 			if(Record[0][5] == 0)
             	{
             		x = 0;
             		y = 5;
             		break;
	 			}
	 			
	 			if(Record[4][0] == 0)
             	{
             		x = 4;
             		y = 0;
             		break;
	 			}
	 			
	 			if(Record[4][5] == 0)
             	{
             		x = 4;
             		y = 5;
             		break;
	 			}
	 			
	 			if( (Record[0][2] == 0) || ( (Record[0][2] == 1)  &&  (color[0][2] == inputColor) ) )
             	{
             		x = 0;
             		y = 2;
             		break;
	 			}
	 			
	 			if( (Record[4][2] == 0) || ( (Record[4][2] == 1)  &&  (color[4][2] == inputColor) ) )
             	{
             		x = 4;
             		y = 2;
             		break;
	 			}
	 			
	 			if( (Record[2][0] == 0) || ( (Record[2][0] == 1)  &&  (color[2][0] == inputColor) ) )
	 			{
	 				x = 2;
	 				y = 0;
	 				break;
 				}
	 			
	 			if( (Record[2][5] == 0) || ( (Record[2][5] == 1)  &&  (color[2][5] == inputColor) ) )
	 			{
	 				x = 2;
	 				y = 5;
	 				break;
 				}
 				
 				if( (Record[1][1] == 0) || ( (Record[1][1] < 3)  &&  (color[1][1] == inputColor) ) )
	 			{
	 				x = 1;
	 				y = 1;
	 				break;
 				}
 				
 				if( (Record[3][4] == 0) || ( (Record[3][4] < 3)  &&  (color[3][4] == inputColor) ) )
	 			{
	 				x = 3;
	 				y = 4;
	 				break;
 				}
 				
 				if( (Record[1][3] == 0) || ( (Record[1][3] < 3)  &&  (color[1][3] == inputColor) ) )
	 			{
	 				x = 1;
	 				y = 3;
	 				break;
 				}
 				
 				if( (Record[3][2] == 0) || ( (Record[3][2] < 3)  &&  (color[3][2] == inputColor) ) )
	 			{
	 				x = 3;
	 				y = 2;
	 				break;
 				}
 				
 				if( (Record[1][4] == 0) || ( (Record[1][4] < 2)  &&  (color[1][4] == inputColor) ) )
	 			{
	 				x = 1;
	 				y = 4;
	 				break;
 				}
 				
 				if( (Record[3][1] == 0) || ( (Record[3][1] < 2)  &&  (color[3][1] == inputColor) ) )
	 			{
	 				x = 3;
	 				y = 1;
	 				break;
 				}
 				
 				if( (Record[4][2] < 3)  &&  (color[4][2] == inputColor) )
	 			{
	 				x = 4;
	 				y = 2;
	 				break;
 				}
 				
 				if( (Record[3][4] < 4)  &&  (color[3][4] == inputColor) )
	 			{
	 				x = 3;
	 				y = 4;
	 				break;
 				}
 				
 				if( (Record[2][2] < 4)  &&  (color[2][2] == inputColor) )
	 			{
	 				x = 2;
	 				y = 2;
	 				break;
 				}
 				
 				if( (Record[1][0] == 0) || ( (Record[1][0] < 2)  &&  (color[1][0] == inputColor) ) )
             	{
             		x = 1;
             		y = 0;
             		break;
	 			}
	 			
	 			if( (Record[3][1] == 0) || ( (Record[3][1] < 4)  &&  (color[3][1] == inputColor) ) )
             	{
             		x = 3;
             		y = 1;
             		break;
	 			}
	 			if( (Record[1][5] == 0) || ( (Record[1][5] < 4)  &&  (color[1][5] == inputColor) ) )
             	{
             		x = 1;
             		y = 5;
             		break;
	 			}
 				
	 			
	 				for(i=0; i<=4; i++)
             		{
             		for(j=0; j<=5; j++)
             		    {
             	            if(Record[i][j] == 0)
             			    {		
             	            x = i; 
	 					    y = j;
	 					    z = 1;
	 					    break;
					        }
					        else if(color[i][j] == inputColor)
					        {
				 	        x = i;
						    y = j;
						    z = 1;
						    break;
					        }
				        }
		 			}
             	
			 }
        }
        //Any Code You Want to Add
        int getX()
		{
             //Your Code
             return x;
        }
        int getY()
		{
             //Your Code
             return y;
        }
    private: 
        int x;
        int y;
    };
