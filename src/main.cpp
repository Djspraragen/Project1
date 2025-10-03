#include <iostream>
//import the 
import EntLib;

using namespace std;
using namespace EntSpace;

int main(int argc,char** argv){
	//seed random number generator function
	srand(time(nullptr));
	//check if number of arguments are valid
	if(argc != NUM_ARGS)
	{
	std::cerr<< "Wrong number of arguments, Expected: [ROWS] [COLS] [TURNS] [NUM PARTICES]"<< std::endl;
	exit(ERR_NUM_ARGS);   
	}
	//read in command Line Arguments
	int intRows = getint(argv[1]);
	int intCols = getint(argv[2]);
	int intTurns = getint(argv[3]);
	int intNumP = getint(argv[4]);
	bool blnContinue = true;
	char chInput = '\0';
	SIMSTATE recSim = initRecstate(intRows, intCols, intTurns, intNumP); 

	do{
		system("cls");
		//display the simulation
		displaysim(recSim);
		
		//function to calculate the normal paricles
		int intNCount = countNP(recSim);
		recSim.TotalP = intNCount;
		
		//function to count entangled pairs
		int intECount = countEntp(recSim);
		recSim.Entpairs = intECount;

		
		//check maximum turns 
		if(recSim.Turns > recSim.MaxTurns)
		{
			cout << "Maximun number of generation reached, Simulation is done" << endl;
			blnContinue = false;
			break; //exit loop immediately
		}
		
		//function to display the menu
	    displaymenu(recSim);
		
		//increment the number of turns
		recSim.Turns = recSim.Turns + 1;
		//display max turns
		cout << "max turns: " <<recSim.MaxTurns<< endl;
		
		//read in user imput
		cin >> chInput;
		if(chInput == 'q' || chInput =='Q')
		{
			cout << "BYE BYE .....:D" << endl;
			blnContinue = false;
		}
		
		//function to implement the movement of the particles
		moveNP(recSim);
		
		//function to handle entangledment
	    entP(recSim);
	    moveEntp(recSim);

		//system("pause");
	}while(blnContinue);
	//give memory back to the operating system
    freeupmem(recSim,recSim.worldA);
	freeupmem(recSim,recSim.worldB);
	
	
    return 0;	 
}