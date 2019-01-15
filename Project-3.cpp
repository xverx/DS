class Student
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
             		z = 1;
             		break;
	 			}
	 			
	 			if(Record[0][5] == 0)
             	{
             		x = 0;
             		y = 5;
             		z = 1;
             		break;
	 			}
	 			
	 			if(Record[4][0] == 0)
             	{
             		x = 4;
             		y = 0;
             		z = 1;
             		break;
	 			}
	 			
	 			if(Record[4][5] == 0)
             	{
             		x = 4;
             		y = 5;
             		z = 1;
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
