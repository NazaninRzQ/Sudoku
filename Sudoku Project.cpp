#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstring>
using namespace std ;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
void color(int a){
	SetConsoleTextAttribute(hConsole, a | 0);
}
void clear(){
	system("CLS") ;
}
void printTable(int a[9][9] , bool b[9][9]){
	clear() ;
	color(1) ;
	cout << "\n ++" ;
	for(int j = 0 ; j < 9 ; j++)
	{
		if((j+1) % 3 == 0)
		{
			cout << "===++" ;
		}
		else
		{
    	    cout << "===+" ;
		}
	}
	
	
	for(int i = 0 ; i < 9 ; i++)
	{
		color(1) ;
		cout << "\n ||" ;
		color(15) ;
		for(int j = 0 ; j < 9 ; j++)
		{
			if(b[i][j])
			{
				color(15) ;
    			cout << " " ;
    			if(a[i][j] == 0)
    			{
    				cout << " " ;
    			}
    			else
    			{
    				color(2) ;
        			cout << a[i][j] ;
					color(15) ;	
    			}
    			
			}
			else
			{
				if(a[i][j] == 0)
				{
					cout << "  " ;
				}
				else
				{
					cout << " " << a[i][j] ;
				}
			}
			
			
			
			if((j+1) % 3 == 0)
			{
				color(1) ;
    			cout << " ||" ;
    			color(15) ;
			}
			else
			{
				color(15) ;
				cout << " |" ;
			}
			
		}
		
	    color(1) ;    
		cout << "\n ++" ;
		color(15) ;
		for(int j = 0 ; j < 9 ; j++)
		{
		    if((i+1) % 3 == 0)
		    {
		    	color(1) ;
		    	if((j+1) % 3 == 0)
		    	{
		    		cout << "===++" ;
				}
				else
				{
					cout << "===+" ;
            	}
			    color(15) ;
			}
		}

	    if((i+1) % 3 != 0)
	    {
    		for(int j = 0 ; j < 9 ; j++)
    		{
    			if((j+1) % 3 == 0)
    	    	{
    		    	cout << "---" ;
    		    	color(1) ;
    		    	cout << "++" ;
    		    	color(15) ;
        		}
    	    	else
    	    	{
            	    cout << "---+" ;
    	    	}
    		}
		}
 
	}
}
void initialize(int a[9][9] , bool b[9][9]){
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		{
			a[i][j] = 0 ;
			b[i][j] = false ;
		}
	}
}
bool rules(int a[9][9] , int r , int c , int v){
	for(int i = 0 ; i < 9 ; i++)
	{
		if((i != c) && (v == a[r][i]))
		    return false ;
		
		if((i != r) && (v == a[i][c]))
		    return false ;   
	}
	
	int i1 = r - (r % 3) ;
	int j1 = c - (c % 3) ;
	for(int i = i1 ; i < i1+3 ; i++)
	{
		for(int j = j1 ; j < j1+3 ; j++)
		{
			if( !(i == r && j == c) && (v == a[i][j]) )
			{
				return false ;
			}
		}
	}
	return true ;
}
bool isFull(int a[9][9] , bool b[9][9]){
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		{
			if(a[i][j] == 0)
			{
				cout << "\nTable is not compelete yet!" << endl ;
    			return false ;
			}
		}
	}
	return true ;
}
bool finalChecking(int a[9][9] , bool b[9][9]){
	for(int i = 0 ; i < 9 ; i++)
	{
		for(int j = 0 ; j < 9 ; j++)
		{
			if(!b[i][j])
			{
				if(!rules(a , i , j , a[i][j] ))
				{
					color(4) ;
					cout << "\nYour table is not correct... GAME OVER! :(" << endl ;
					color(15) ;
					return false ;	
				}
			}
		}
	}
	color(10) ;
	cout << "\n** YOU WON! :) **" << endl ;
	color(15) ;
	return true ;
}
bool autoSolver(int a[][9] ,int r , int c){
	if(r == 8 && c == 9)
	   return true ;
	   
	if(c == 9)
	{
		r++ ;
		c = 0 ;
	}
	
	if(a[r][c] > 0)
	   return autoSolver(a , r , c+1) ;
	   
	for(int n = 1 ; n <= 9 ; n++)
	{
		if(rules(a , r , c , n))
		{
			a[r][c] = n ;
    		if(autoSolver(a , r , c+1))
	    	   return true ;
		}
		a[r][c] = 0 ;
	}
	return false ;     
}

int main()
{
	string loc ;
	int choise ;
	color(6) ;
	cout << "\nHello! Welcome to Sudoku game!" << endl ;
	color(15) ;
	cout << "\nWhat do you want to do?" << endl ;
	cout << " 1. Create Puzzle" << endl ;
	cout << " 2. Solve Puzzle" << endl ;
	cout << " 3. Exit" << endl ;
	color(8) ;
	cout << "\n Please enter the location that you want to save your file first like an example: "  ;
	cout << "\n Example: C:\\Users\\T460s\\Desktop\\Mabani\\project\\sudoku.txt " ;
	cout << "\n Now Enter: " ;
	cin >> loc ;
	color(15) ;
	cout << "\n Now Enter your choise: " ;
	cin >> choise ;
	
	switch(choise)
	{
		case 1 :
		{
			// code of creating puzzle
			
			string str ;
			
			clear() ;
			color(11) ;
			cout << "Creating a puzzle..." << endl ;
			color(15) ;
			cout << "\n Please enter your coordinates of the table and value as 3 numbers like the given format:" << endl ;
			color(9) ;
			cout << " Format: rcv," << endl ;
			color(15) ;
			cout << " r: for row(0-8) , c: for column(0-8) , v: for value(1-9)" << endl ;
			cout << " \n and type (end) for ending your entering data." << endl ;
			
			do
			{
				cin >> str ;
				
    			ofstream sfile ;
    			sfile.open(loc , ios::app) ;
				sfile << str ;
			
    			sfile.close() ;
			}while(str != "end") ;
    	}
			
			
		break ;
			
			
		case 2 :
		{
    	    // code of solving puzzle
    	    clear() ;
    	    color(11) ;
			cout << "Solving a puzzle..." << endl ;
			color(15) ;
			
			int table[9][9] , r  , c  , v  ;
			bool b[9][9] ;
			initialize(table , b) ;
			
			ifstream sfile(loc , ios::in) ;
			
			string str ;
			while(getline(sfile , str , ','))
			{
				char array[3] ;
				strcpy(array , str.c_str()) ;
				
				for(int i = 0 ; i < 3 ; i++)
				    array[i] ;
				    
				int r = str[0] - '0' ;
				int c = str[1] - '0' ;
				int v = str[2] - '0' ;
				
				table[r][c] = v ;
				b[r][c] = true ;
			}

			sfile.close() ;
			

        	do 
        	{
        		do
        		{
            		printTable(table , b) ;
        			color(6) ;
            		cout << "\n Start filling the table..." << endl ;
            		cout << " and when you're done, enter three (10)s." << endl ;
					color(15) ;
        			cout << "\n r >> c >> value: " ;
        			cin >> r >> c >> v ;
				}while(!((r == 10 && c == 10 && v == 10) || ((r >= 0 && r <= 8) && (c >= 0 && c <= 8) && (v >= 0 && v <= 9)))) ;
				if(b[r][c])
				{
					continue ;
				}
				else if(r == 10)
				{
					cout << "here" ;
					break ;
				}
				table[r][c] = v ;
				
			}while(! ((isFull(table , b)) && (r == 10 && c == 10 && v == 10)) ) ;
			
			// For autosolver comment lines 307-330 and release 3 lines bellow
//			
//			printTable(table , b) ;
//			autoSolver(table , 0 , 0) ;
//			printTable(table , b) ;
			
			finalChecking(table , b) ;
			
		}
    	  
		break ;
		
		
		case 3 :
		{
    	    // code of exiting
	        clear() ;
    	    color(4) ;
    	    cout << " Exit..." ;
    	    color(15) ;
		}	
	    
		break ;	
				
	}
	
	return 0 ;
	
}







