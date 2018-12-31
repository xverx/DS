class Student
{
    public: 
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor)
	{
             //Your Code
             int z = 0;
             while(z<1)
	     {
             	for(int i=4; i>=0; i--)
             	for(int j=5; j>=0; j--)
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
