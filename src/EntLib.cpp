module;

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstdlib>

export module EntLib;

using namespace std;
namespace EntSpace{
	//number of arguments
	export const int NUM_ARGS = 5;
	//aliases 
	using ONEDARRAY = int*;
	export using TWODARRAY = ONEDARRAY*;
	//error codes
	export enum EXIT_CODES
	{
		ERR_NUM_ARGS = -2,
		ERR_CONV_ARG
	};
	
	///SIMULATION FEATURES
	export enum SIM_FEATURES
	{
		SPACE,
		NORMAL_STAR,
		E_STAR,
		E2_STAR,
		E3_STAR
	};
	export const char FEATURES[]={' ', '.', '#', '*','@'};
	//SIMULATION STRUCTURE
	export struct SIMSTATE
	{
		int Rows;
		int Cols;
		int Numstars;
		int Turns =0;
		int Entpairs = 0;
		int TotalP = 0;
		int MaxTurns;
		TWODARRAY worldA;
		TWODARRAY worldB;
	};
	//FUNCTION PROTOTYPES
	export int getint(string strArg);
	export SIMSTATE initRecstate(int ROWS, int COLS, int TURNS, int numP); 
	export void displaysim(SIMSTATE recState);
	export void displaymenu(SIMSTATE recState);
	export int countNP(SIMSTATE recState);
	export void moveNP(SIMSTATE& recState);
	export void freeupmem(SIMSTATE recState,TWODARRAY& arrWorld);
	export void entP(SIMSTATE& recState);
	export void moveEntp(SIMSTATE& recState);
	export int countEntp(SIMSTATE recState);
	

	
	
	///FUNCTION IMPLEMENTATIONS
	//function to convert CLA to integer
	 int getint(string strArg)
	{
		int intReturn = 0;
		stringstream ss(strArg);
		ss >> intReturn;
		if(std::cin.fail())
		{
			std::cerr<<"Failed to convert string to integer"<<std::endl;
			exit(ERR_CONV_ARG);
		}
		
	 return intReturn;	
	}
	
	//utility function to allocate memory
	TWODARRAY allocmem(int intRows, int intCols)
	{
		TWODARRAY arrWorld;
		arrWorld = new ONEDARRAY[intRows];
		for(int r =0;r< intRows; r++)
		{
			arrWorld[r] = new int[intCols];
			//initialise to space
			for(int c=0 ; c < intCols; c++)
			{
				arrWorld[r][c] = SPACE;
			}
		}
	 return arrWorld;	
	}
	
	//utility function to generate random numbers
	int randnumgen(int intLB, int intUP)
	{
		int intRange = intUP - intLB +1;
	 return (rand()%intRange) + intLB;
	}
	
	//utility function to place features world A
	void placeFeatureA(SIMSTATE recState, int feature)
	{
		for(int i = 0; i < recState.Numstars; i++)
		{
			int randRow = randnumgen(0,recState.Rows -1);
			int randCol = randnumgen(0,recState.Cols -1);
			//check for space
			while(recState.worldA[randRow][randCol] != SPACE)
			{
				randRow = randnumgen(0,recState.Rows -1);
				randCol = randnumgen(0,recState.Cols -1);
			}
			//place feature if there is space at that location
			recState.worldA[randRow][randCol] = feature;
		}
		
	}
	//utility function to place features for world B
	void placefearureB(SIMSTATE recState, int feature)
	{
		for(int i =0 ; i < recState.Numstars; i++)
		{
			int randRow = randnumgen(0, recState.Rows -1);
			int randCol = randnumgen(0, recState.Cols -1);
			//check for space 
		    while(recState.worldB[randRow][randCol] != SPACE)
			{
				randRow = randnumgen(0, recState.Rows -1);
			    randCol = randnumgen(0, recState.Cols -1);
			}
			//place featutre
			recState.worldB[randRow][randCol] = feature;	
		}
	}
	
	//function implimentation to initialise the record state of the simulation
    SIMSTATE initRecstate(int ROWS, int COLS, int TURNS, int numP)
	{
		SIMSTATE recState;
		recState.Rows = ROWS;
		recState.Cols = COLS;
		recState.Numstars = numP;
		recState.MaxTurns = TURNS;
		//allocate memory to the two worlds
		recState.worldA = allocmem(ROWS,COLS);
		recState.worldB = allocmem(ROWS,COLS);
		//call function to place normal particles/stars
		placeFeatureA(recState,NORMAL_STAR);
		placefearureB(recState,NORMAL_STAR);
		
	 return recState; 	
	}
	
	//function implimentation to display the simulation
    void displaysim(SIMSTATE recState)
	{
		cout<<"World A" <<endl;
		for(int r =0; r < recState.Rows; r++)
		{
			for(int c =0; c < recState.Cols; c++)
			{
				cout<< FEATURES[recState.worldA[r][c]]<<' ';
			}
			cout << endl;
		}
		
		cout << "Worl B" << endl;
		for(int r =0; r < recState.Rows; r++)
		{
			for(int c =0; c < recState.Cols; c++)
			{
				cout << FEATURES[recState.worldB[r][c]]<<' ';
			}
			cout << endl;
		}
		
	}
	
	//function implimentation to display the menu
	void displaymenu(SIMSTATE recState)
	{
		cout << "Generations: " << recState.Turns << endl;
		cout << "Entangled pairs: " << recState.Entpairs << endl;
		cout << "Total Particles: " << recState.TotalP << endl;
		cout << "C : Continue" << endl;
		cout << "Q : Quit" << endl;
	}
	
	int countNP(SIMSTATE recState)
	{
		int intCount = 0;
		//count normal particles in world A
		for(int r = 0; r < recState.Rows; r++)
		{
			for(int c = 0; c < recState.Cols; c++)
			{ 
		        if(recState.worldA[r][c] == NORMAL_STAR 
				|| recState.worldA[r][c] == E_STAR
				|| recState.worldA[r][c] == E2_STAR
				|| recState.worldA[r][c] == E3_STAR)
					intCount = intCount + 1;
			}
		}
		//count normal particles in world B
		for(int r = 0; r < recState.Rows; r++)
		{
			for(int c = 0; c < recState.Cols; c++)
			{
				if(recState.worldB[r][c] == NORMAL_STAR 
				||recState.worldB[r][c] == E_STAR
				||recState.worldB[r][c] == E2_STAR
				||recState.worldB[r][c] == E3_STAR)
					intCount = intCount +1;
			}
		}
		return intCount;
	}
	
	// function implementation to free up memory
	void freeupmem(SIMSTATE recState,TWODARRAY& arrWorld)
	{
		for(int r = 0 ; r < recState.Rows; r++)
		{
			delete[] arrWorld[r];
		}
		delete[] arrWorld;
		arrWorld = nullptr;
	}
	
	//function implementaion to move normal particles
	void moveNP(SIMSTATE& recState)
	{
		//clone world A
		TWODARRAY arrcloneA = allocmem(recState.Rows,recState.Cols);
		for(int r =0; r < recState.Rows; r++)
		{
			for(int c =0; c < recState.Cols; c ++)
			{
				arrcloneA[r][c] = recState.worldA[r][c];
			}
		}
		
	//movement WorldA
	for(int r =0; r < recState.Rows; r++)
	{
		for(int c=0; c < recState.Cols; c ++)
		{
			if(recState.worldA[r][c] == NORMAL_STAR)
			{
				int intrr = randnumgen(-1,1);
				int intrc = randnumgen(-1,1);
				int newrow = r + intrr;
				int newcol = c + intrc;
				//check for space and bounds
				if(newrow < 0 || newrow >= recState.Rows
				||newcol < 0 || newcol >= recState.Cols)
				continue; //skip current iteration since is not suitable for the movement
				//do the movement if the destination is in bounds and is = space
				else if(recState.worldA[newrow][newcol] == SPACE)
				{
					arrcloneA[newrow][newcol] = NORMAL_STAR;
					arrcloneA[r][c] = SPACE;
				}
			}
		}
	}
	//update the arrays
	for(int r =0 ; r < recState.Rows; r++)
	{
		for(int c =0 ; c < recState.Cols; c++)
		{
			recState.worldA[r][c] = arrcloneA[r][c];
		}
	}
	//free up memory 
	freeupmem(recState,arrcloneA);

  }
  
  //function implementation to entangle particles in the same coordinates
   void entP(SIMSTATE& recState)
   {
	   //clone world A
	   TWODARRAY arrcloneA = allocmem(recState.Rows,recState.Cols);
	   for(int r =0; r < recState.Rows; r++)
	   {
		   for(int c=0; c <recState.Cols; c++)
		   {
			   arrcloneA[r][c] = recState.worldA[r][c];
		   }
	   }
	   
	    //clone world B
	   TWODARRAY arrcloneB = allocmem(recState.Rows,recState.Cols);
	   for(int r =0; r < recState.Rows; r++)
	   {
		   for(int c=0; c <recState.Cols; c++)
		   {
			   arrcloneB[r][c] = recState.worldB[r][c];
		   }
	   }
	   //entangle particles
	   for(int r =0; r <recState.Rows;r++)
	   {
		   for(int c=0; c < recState.Cols; c++)
		   {
			   if(recState.worldA[r][c] == NORMAL_STAR && recState.worldB[r][c] == NORMAL_STAR)
			   {
				   int randEnt = randnumgen(2,4);
				   arrcloneA[r][c] = randEnt;
				   arrcloneB[r][c] = randEnt;
			   }
		   }
	   }
	   //update the worlds
	   for(int r =0; r <recState.Rows;r++)
	   {
		   for(int c=0; c < recState.Cols;c++)
		   {
			   recState.worldA[r][c] = arrcloneA[r][c];
			   recState.worldB[r][c] = arrcloneB[r][c];
		   }
	   }
	   //delete the clones
	   freeupmem(recState,arrcloneA);
	   freeupmem(recState,arrcloneB);
   }
   
   //function implementation to move entangled particles
   	void moveEntp(SIMSTATE& recState)
	{
         //clone world A
	   TWODARRAY arrcloneA = allocmem(recState.Rows,recState.Cols);
	   for(int r =0; r < recState.Rows; r++)
	   {
		   for(int c=0; c <recState.Cols; c++)
		   {
			   arrcloneA[r][c] = recState.worldA[r][c];
		   }
	   }
	   
	    //clone world B
	   TWODARRAY arrcloneB = allocmem(recState.Rows,recState.Cols);
	   for(int r =0; r < recState.Rows; r++)
	   {
		   for(int c=0; c <recState.Cols; c++)
		   {
			   arrcloneB[r][c] = recState.worldB[r][c];
		   }
	   }
	   //loop to check entangled particles
	   for(int r=0;r < recState.Rows; r++)
	   {
		   for(int c =0; c < recState.Cols; c++)
		   {
			   if(recState.worldA[r][c] == E_STAR && recState.worldB[r][c] ==E_STAR
			    || recState.worldA[r][c] == E2_STAR && recState.worldB[r][c] == E2_STAR
				|| recState.worldA[r][c] ==E3_STAR && recState.worldB[r][c] == E3_STAR)
				{
					int rrow = randnumgen(-1,1);
					int rcol = randnumgen(-1,1);
					int newRow = r + rrow;
					int newCol = c + rcol;
					//check bounds
					if(newRow < 0 || newRow >= recState.Rows || newCol < 0 || newCol >= recState.Cols)
						continue; //skip current iteration if it's out of bounds
					else if((recState.worldA[newRow][newCol] == SPACE) && (recState.worldB[newRow][newCol] == SPACE))
					{
						arrcloneA[newRow][newCol] = recState.worldA[r][c];
						arrcloneB[newRow][newCol] = recState.worldB[r][c];
						arrcloneA[r][c] = SPACE;
						arrcloneB[r][c] = SPACE;
					}
				}
		   }
	   }
	   //update the worlds
	   for(int r=0; r <recState.Rows;r++)
	   {
		   for(int c =0; c < recState.Cols; c++)
		   {
			   recState.worldA[r][c] = arrcloneA[r][c];
			   recState.worldB[r][c] = arrcloneB[r][c];
		   }
	   }
	   //delete the clones
	   freeupmem(recState,arrcloneA);
	   freeupmem(recState,arrcloneB);
	   
	}
	
	//function to count entangled particles/stars
	int countEntp(SIMSTATE recState)
	{
		int intcount = 0;
		//count in world A
		for(int r=0; r < recState.Rows; r++)
		{
			for(int c=0 ; c < recState.Cols; c++)
			{
				if(recState.worldA[r][c] == E_STAR 
				|| recState.worldA[r][c] == E2_STAR
				|| recState.worldA[r][c] == E3_STAR)
				intcount++;	
			}
		}
		//count in world B
		for(int r=0; r < recState.Rows; r++)
		{
			for(int c=0 ; c < recState.Cols; c++)
			{
				if(recState.worldB[r][c] == E_STAR 
				|| recState.worldB[r][c] == E2_STAR
				|| recState.worldB[r][c] == E3_STAR)
				intcount++;	
			}
		}
	  return intcount;	
	}




}
