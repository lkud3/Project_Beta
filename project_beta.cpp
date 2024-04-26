/**************************************************************
SALTYKOV DANIIL 17/03/2023
STATISTICS FOR WORLD CUP QATAR

Copyright: GNU Public License http://www.gnu.org/licenses/
20220372@student.act.edu
***************************************************************/

//include all required libraries
#include <iostream>
#include <sstream>
#include <cmath>  
#include <windows.h>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

//declaring functions
void read_file(string filename);
void displayMenuInstructions();
void displayTable();
void selectionSort(string column, string type);
string extractFromStruct(int i, string column);
void write_file();

//defining structure
struct athlete_struct
{
	string name;
	string team;
	int age;
	int goals;
	int goals_penalty;
	int shots;
	int shots_target;
	double avg_distance;
	double g_s;          //goals/shots rate
	double np_g_s;       //non-penalty-goals/shots rate
	double accuracy;
};

//declaring global variables
double limit_distance(0);    //used for 2nd option
athlete_struct athlete[11];  //declaring the array of structs, each for every football player
athlete_struct temp;         //temporary struct for swap

int main()
{
	
  int option(0); 		// user's entered option will be saved in this variable
  do 					// do-while loop starts here.that display menu again and again 
     					// until user select to exit program
  { 					
  	option = 0;
  	
     displayMenuInstructions();   //Displaying Options for the menu
     
     cin >> option;  // taking option value as input and saving in variable "option"
     cout << endl;
     
     //switch for each menu option
     switch (option){
     	
     	///////////////////////// FIRST OPTION ////////////////////////////
     	case 1:
     		{
     			cout << "-----------------------------------------------------------------" << endl;
     			
     			cout << "Displaying world cup 2023 top scorers statistics from the file: " << endl << endl;
     			
     			//calling function to read data from .csv file and put it to the array fo structs
     			read_file("top_scorers_Qatar2023.csv");
     			
     			//calling function to display table with corresponding data
     			displayTable();
     			
     			//waiting for any users input before proceed further
     			cout <<endl;
				system("PAUSE");
				cout << endl << endl;
				break;
			}
			
		///////////////////////// SECOND OPTION ////////////////////////////	
		case 2:
     		{
     			
     			//checks if data was read from .csv file
     			if (athlete[0].goals == 0){
     				
     				//if not go to the menu
     				cout << "There is no data, execute the 1st option first" << endl << endl;
     				
     				system("PAUSE");
					cout << endl << endl;
					
     				break;
				}
				
				cout << "-----------------------------------------------------------------" << endl;
     			
     			cout << "Displaying football players with average shot distance above or equals to entered threshold in alphabetical order" << endl << endl;
     			
     			//entering the threshold distance
     			cout << "Enter the threshold of average shot distance: " << endl;
     			
     			//checks if the input is integer and less or equal to the maximum possible distance that presented in the file
     			if (cin >> limit_distance && limit_distance <= 21){
     				
     				cout << endl << "The players who meet the given criteria are: " << endl;
     			
     				//calling function to sort the table by player in ascending (alphabetical) order
	     			selectionSort("player", "asc");
	     			
	     			displayTable();
	     			
	     		} else
	     			cout << endl << "There are no players with that average shot distance " << endl << endl;
     			
     			//assigne limit to zero so it will not affect the futher table display
     			limit_distance = 0;
     			
     			cout <<endl;
				system("PAUSE");
				cout << endl << endl;
				break;
		  	}
		 
		///////////////////////// THIRD OPTION ////////////////////////////  	
		case 3:
     		{
     			
     			if (athlete[0].goals == 0){
     				
     				cout << "There is no data, execute the 1st option first" << endl << endl;
     				
     				system("PAUSE");
					cout << endl << endl;
					
     				break;
				}
				
				cout << "-----------------------------------------------------------------" << endl;
     			
     			cout << "Calculates G/S and NPG/S and displays the table" << endl << endl;
     			
     			//calculates the goals/shot and non-penalties-goal/shot rates and puts them in corresponding struct elements
     			for (int i = 0; i < 11; i++){
     				
     				athlete[i].g_s = round((athlete[i].goals / double (athlete[i].shots)) * 100.0) / 100.0; 	//goal/shot, and round it
     				athlete[i].np_g_s = round(((athlete[i].goals - athlete[i].goals_penalty) / double(athlete[i].shots)) * 100.0) / 100.0; //non-penalties-goal/shot, and round it

				 }
				 
				//calling function to create or update .txt file with new statistics
				write_file();
     			
     			//reading new file back
     			read_file("saltykov_qatar2023_stats.txt");
     			
     			displayTable();
     			
     			//notyfing that file was saved successfully
     			cout << endl << "File saltykov_qatar2023_stats.txt is updated successfully!" << endl;
				
     			cout <<endl;
				system("PAUSE");
				cout << endl << endl;
				break;
			}
		
		///////////////////////// FOURTH OPTION (EXTRA CHALLENGE) ////////////////////////////	
		
		//everythting the same as for 3rd option
		case 4:
     		{
     			
     			if (athlete[0].goals == 0){
     				
     				cout << "There is no data, execute the 1st option first" << endl << endl;
     				
     				system("PAUSE");
					cout << endl << endl;
					
     				break;
				}
     			
     			cout << "-----------------------------------------------------------------" << endl;
     			
     			cout << "Calculates accuracy and displays the table" << endl << endl;
     			
     			for (int i = 0; i < 11; i++){
     				
     				//calculates the accuracy (shots on target / all shots), and round it
     				athlete[i].accuracy = round((athlete[i].shots_target / double (athlete[i].shots)) * 1000.0 ) / 10.0; 
     				
     			}
				 
				write_file();
     			
     			read_file("saltykov_qatar2023_stats.txt");
     			
     			displayTable();
     			
     			cout << endl << "File saltykov_qatar2023_stats.txt is updated successfully!" << endl;
				
     			cout <<endl;
				system("PAUSE");
				cout << endl << endl;
				break;
			}
		
		///////////////////////// FIFTH OPTION ////////////////////////////	
		case 5:
     		{
     			
     			//declaring variables for specyfing the parameters for sorting
     			string sort_type;
     			string sort_column;
     			string columns_names[11] = {"player", "team", "age", "gls", "gls_pnlts", "shots", "shots_trgt", "avg_dist", "g/s", "npg/s", "acc"};
     			bool incorrect_column = true;
     			
     			//checks if all aditional parameters from 3rd and 4th options were calculated and the data is not empty
     			if (athlete[0].g_s == -1 || athlete[0].goals == 0 || athlete[0].accuracy == -1){
     				
     				cout << "The data is not full, execute the 3rd and 4th option first" << endl << endl;
     				
     				system("PAUSE");
					cout << endl << endl;
					
     				break;
				}
				
				cout << "-----------------------------------------------------------------" << endl;
     			
     			cout << "Sorts by the entered field" << endl << endl;
				 
				//asking user to input by what column and in which order to sort, and checks if the input is correct
     			do {
				 
	     			cout << endl << "Enter the field you want to sort by (player, team, age, gls, gls_pnlts, shots, shots_trgt, avg_dist, g/s, npg/s, acc): ";
	     			cin >> sort_column;
	     			
	     			cout << endl << "Enter the type of sorting (asc, des): ";
	     			cin >> sort_type;
	     			
	     			//checks if the entered column exists throught the list of columns
	     			for (int i = 0; i < 11; i++){
	     				if (sort_column == columns_names[i])
	     					incorrect_column = false;
					 }
					 
					if (incorrect_column || (sort_type != "asc" && sort_type != "des"))
						cout << endl << "The parameters are wrong, check the input." << endl;
					
				}while (incorrect_column || (sort_type != "asc" && sort_type != "des"));
				
				//calling the sort function with entered parameters
				selectionSort(sort_column, sort_type);
     			
     			displayTable();
				
     			cout << endl;
				system("PAUSE");
				cout << endl << endl;
				break;
			}
		
		///////////////////////// SIXTH END OPTION ////////////////////////////	
		case 6:
     		{
     			cout << "You selected option 6." << endl << endl;
        		cout << "It's time to say goodbye then..." << endl << endl;
        		cout << "Bye!" << endl << endl;
				break;
			}
		
		///////////////////////// DEFAULT OPTION ////////////////////////////
		//in case the input is incorrect		
		default:
			{
				cout << "Invalid Option entered." << endl;
       			cout << "Why don't we try again?" << endl << endl;
       			system("PAUSE");
				cout << endl << endl;
       			break;
			}
	   }
	   
	//clears the input buffer in case of wrong input
	cin.sync();
    while (cin.fail()){
  		cin.clear();
  		cin.ignore(numeric_limits<streamsize>::max(),'\n');
	}
	  
  }
  while(option != 6);  //condition of do-while loop
   
	return 0;
}



///////////////// Write In File Function///////////////////////////////////

void write_file(){
	
	//opening the file to write in
	ofstream fout;
	
	fout.open("saltykov_qatar2023_stats.txt");
	
	//choosing the heading according to data we have to write
	if (athlete[0].accuracy == -1)
		fout << "PLAYER  /  TEAM  /  AGE  /  GLS  /  GLS PNLTS  /  SHOTS  /  SHOTS TRGT  /  AVG DIST  /  G/S RATE  /  NPG/S RATE" << endl << endl;
	
	else if (athlete[0].g_s == -1)
		fout << "PLAYER  /  TEAM  /  AGE  /  GLS  /  GLS PNLTS  /  SHOTS  /  SHOTS TRGT  /  AVG DIST  /  ACC (%)" << endl << endl;
		
	else
		fout << "PLAYER  /  TEAM  /  AGE  /  GLS  /  GLS PNLTS  /  SHOTS  /  SHOTS TRGT  /  AVG DIST  /  G/S RATE  /  NPG/S RATE  /  ACC (%)" << endl << endl;

	
	//for every football player writes all the information we have devided by tab and spaces for better appearence
	for (int i = 0; i < 11; i++){
		
		fout << athlete[i].name << "  " << '\t';
		fout << athlete[i].team << "  " << '\t';
		fout << athlete[i].age << "   " << '\t';
		fout << athlete[i].goals << "   " << '\t';
		fout << athlete[i].goals_penalty << "   " << '\t';
		fout << athlete[i].shots << "   " << '\t';
		fout << athlete[i].shots_target << "   " << '\t';
		fout << athlete[i].avg_distance << "    " << '\t';
		
		if (athlete[i].g_s != -1){
		
			fout << athlete[i].g_s << "    " << '\t';
			fout << athlete[i].np_g_s << "    " << '\t';
		}
		
		if (athlete[i].accuracy == -1)
			fout << endl;
		else 
			fout << athlete[i].accuracy << endl;
		
	}
	
	//closing file
	fout.close();
	
	return;
}



///////////////// Read File Function ////////////////////////////////////

void read_file(string filename)
{
	int i = 0;
	string line, word;
	ifstream fin;
	
	//opens file to read from
	fin.open((filename).c_str());
	
	//checks if name of the file is correct
	if(fin.fail())
  	{
    	cerr << "Could not open the file " << filename << endl;
    	exit(1);
  	}
  	
  	//skip the first line of the heading
  	getline(fin, line);
  	
  	//if it is the .csv file, read it with delimeter ','
  	if (filename[filename.length()-1] == 'v'){
	
		//takes whole line
		while (getline(fin, line)){
			
			//making this line into object
			stringstream str(line);
			
			//parsing the line and investigating each word
			int k = 0;
			while (getline(str, word, ',')){
				
				//each word assigned to corresponding structure element
				switch (k){
					case 0:
						{
							athlete[i].name = word;
							break;
						}
					case 1:
						{
							athlete[i].team = word;
							break;
						}
					case 2:
						{
							athlete[i].age = stoi(word); //converts string to integer
							break;
						}
					case 3:
						{
							athlete[i].goals = stoi(word);
							break;
						}
					case 4:
						{
							athlete[i].goals_penalty = stoi(word);
							break;
						}
					case 5:
						{
							athlete[i].shots = stoi(word);
							break;
						}
					case 6:
						{
							athlete[i].shots_target = stoi(word);
							break;
						}
					case 7:
						{
							athlete[i].avg_distance = stod(word); //converts string to double
							break;
						}
				}
				
				//going to the next word in the line
				k++;
			}
			
			//assigne all additional columns to -1 to make all data clear, as written as .csv file
			athlete[i].g_s = -1;
			athlete[i].np_g_s = -1;
			athlete[i].accuracy = -1;
			
			//going to the next line
			i++;
		}	

	}
	
	//if it is .txt file
	else {
		
		//skipping the sempty line between heading and actual data
		getline(fin, line);
		
		//till the end of file read the needed information
		while(!fin.eof()){
			
			fin >> athlete[i].name;
			fin >> athlete[i].team;
			fin >> athlete[i].age;
			fin >> athlete[i].goals;
			fin >> athlete[i].goals_penalty;
			fin >> athlete[i].shots;
			fin >> athlete[i].shots_target;
			fin >> athlete[i].avg_distance;
			
			if (athlete[i].g_s != -1){
		
				fin >> athlete[i].g_s;
				fin >> athlete[i].np_g_s;
			}
			
			if (athlete[i].accuracy != -1)
				fin >> athlete[i].accuracy;
		
			i++;					
		}
	}
	
	//closing the file
	fin.close();
}

///////////////// Display Menu Function ////////////////////////////////////


void displayMenuInstructions(){
	
	cout << "=================================================================" << endl;
	cout << "USER MENU: TOP SCORER STATISTICS FROM THE FOOTBALL WORLD CUP 2023" << endl;
	cout << "=================================================================" << endl;
	cout << "1. Read & display stats for the top goal scorers (from file top_scorers_Qatar2023.csv)" << endl;
    cout << "2. Display shooters with an average distance past a threshold, in alphabetical order" << endl;
    cout << "3. Calculate G/S and NPG/S, save into new file along with the original stats, display" << endl;
    cout << "4. Calculate accuracy (shots on target / shots), save into new file along with the original stats, display" << endl;
    cout << "5. Sort by a field indicated by the user" << endl;
    cout << "6. Exit the program" << endl << endl;
    //Prompting user to enter an option according to menu
    cout << "Please select an option : ";
	
	return;
}


///////////////// Display Table With Data Function ////////////////////////////////////

void displayTable(){
	
	//display the heading according to the number and order of columns that exists in memory
	if (athlete[0].g_s == -1 && athlete[0].accuracy == -1)
		
		cout << endl << "    PLAYER	|	TEAM	|	AGE	|      GLS	|   GLS PNLTS	|     SHOTS	|   SHOTS TRGT	|    AVG DIST" << endl;
		
	else if (athlete[0].accuracy == -1)
		
		cout << endl << "    PLAYER	 |	TEAM 	 |	AGE	|      GLS	|   GLS PNLTS	|     SHOTS	|   SHOTS TRGT	|    AVG DIST 	 |    G/S RATE   |    NPG/S RATE"  << endl;
	
	else if (athlete[0].g_s == -1)
	
		cout << endl << "    PLAYER	 |	TEAM 	 |	AGE	|      GLS	|   GLS PNLTS	|     SHOTS	|   SHOTS TRGT	|    AVG DIST 	 |      ACC"  << endl;
		
	else 
		
		cout << endl << "    PLAYER	 |	TEAM 	 |	AGE	|      GLS	|   GLS PNLTS	|     SHOTS	|   SHOTS TRGT	|    AVG DIST 	 |    G/S RATE   |    NPG/S RATE  |      ACC"  << endl;

	
	//prints the data that exists in memory
	for (int i = 0; i < 11; i++){
		
		//checks for the average distance to sort by, in case it is assigned in 2nd option
		if (athlete[i].avg_distance >= limit_distance){
		
			cout << athlete[i].name << "	" << '\t';
			cout << athlete[i].team << "	" << '\t';
			cout << athlete[i].age << "	" << '\t';
			cout << athlete[i].goals << "	" << '\t';
			cout << athlete[i].goals_penalty << "	" << '\t';
			cout << athlete[i].shots << "	" << '\t';
			cout << athlete[i].shots_target << "	" << '\t';
			cout << athlete[i].avg_distance << "	" << '\t';
			
			if (athlete[i].g_s != -1){
		
				cout << athlete[i].g_s << "	" << '\t';
				cout << athlete[i].np_g_s << "	" << '\t';
			}
			
			if (athlete[i].accuracy == -1)
				cout << endl;
			else 
				cout << athlete[i].accuracy << "%" << endl;
			
		}
		
	}
	
	//prints the hints for the user for better appearence in the terminal	
	cout << endl << "P.S. Open terminal in the full screen and unzoom for better image." << endl << endl;
	
	//prints the description of acronyms
	cout << "GLS - GOALS; GLS PNLTS - GOALS FROM PENALTY; SHOTS TRGT - SHOTS ON TARGET; AVG DIST - AVG SHOT DISTANCE; G/S - GOALS/SHOT; NPG/S - NON-PENALTY-GOALS/SHOT, ACC - accuracy" << endl;
	
	return;
}


///////////////// Selection Sort Function ////////////////////////////////////

void selectionSort(string column, string type){
	
	int min(0);
	string arr_to_sort[11];
	string temp_string;
	
	//makes additional array to hold the whole column the function will sort by
	for (int i = 0; i < 11; i++){
		arr_to_sort[i] = extractFromStruct(i, column); //uses the function to extract the particular element from the column
	}
	
	//algorithm for descending order
	if (type == "des"){
		
		//goes from the end to the beggining
		for (int i = 10; i > 0; i--){
			
			min = i;
			
			//searching for the minimum element
			for (int j = i - 1; j >= 0; j--){
				if (arr_to_sort[j] < arr_to_sort[min])
					min = j;
			}
			
			//swapping the elements in the additional array
			temp_string = arr_to_sort[i];
			arr_to_sort[i] = arr_to_sort[min];
			arr_to_sort[min] = temp_string;
			
			//swapping the structs (football players) according to the same sort
			temp = athlete[i];
			athlete[i] = athlete[min];
			athlete[min] = temp;
		}
		
	}
	
	//algorithm for ascending order
	else if (type == "asc"){
		
		//goes from the beggining to the end
		for (int i = 0; i < 10; i++){
			
			min = i;
			
			//searching for the minimum element
			for (int j = i + 1; j < 11; j++){
				if (arr_to_sort[j] < arr_to_sort[min])
					min = j;
			}
			
			temp_string = arr_to_sort[i];
			arr_to_sort[i] = arr_to_sort[min];
			arr_to_sort[min] = temp_string;
			
			temp = athlete[i];
			athlete[i] = athlete[min];
			athlete[min] = temp;
		}
		
	}
	
	return;
}

///////////////// Extract From Struct Function ////////////////////////////////////

//this function returns string interpretation of the particular element in the data based on the index of array of structs and of the name of the column (struct element) 

string extractFromStruct(int i, string column){ 
	
	string ans;
	
	//for each column name returns according element from the struct
	if(column == "player")
		ans = athlete[i].name;
		
	else if(column == "team")
		ans = athlete[i].team;
		
	else if(column == "age")
		ans = to_string(athlete[i].age);
		
	else if(column == "gls")
		ans = to_string(athlete[i].goals);
		
	else if(column == "gls_pnlts")
		ans = to_string(athlete[i].goals_penalty);
	
	else if(column == "shots")
		ans = to_string(athlete[i].shots);
		
	else if(column == "shots_trgt")
		ans = to_string(athlete[i].shots_target);

	else if(column == "avg_dist")
		ans = to_string(athlete[i].avg_distance);
	
	else if(column == "g/s")
		ans = to_string(athlete[i].g_s);
		
	else if(column == "npg/s")
		ans = to_string(athlete[i].np_g_s);
		
	else if(column == "acc")
		ans = to_string(athlete[i].accuracy);
		
	//returns string
	return ans;	
}