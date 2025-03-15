#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};

void printboard()
{
	/*for (int i=0;i<3;i++)
	{
		for (int j=0;j<3;j++)
		{*/
			cout<<"\t\t\t      |      |      \n";
			cout<<"\t\t\t  "<<board[0][0]<<"   |   "<<board[0][1]<<"  |   "<<board[0][2]<<"   \n";
			cout<<"\t\t\t______|______|______\n";
			cout<<"\t\t\t      |      |      \n";
			cout<<"\t\t\t  "<<board[1][0]<<"   |   "<<board[1][1]<<"  |   "<<board[1][2]<<"   \n";
			cout<<"\t\t\t______|______|______\n";
			cout<<"\t\t\t      |      |      \n";
		    cout<<"\t\t\t  "<<board[2][0]<<"   |   "<<board[2][1]<<"  |   "<<board[2][2]<<"   \n";
			cout<<"\t\t\t      |      |      \n";
	//	}
		cout<<endl;
//	}
	cout<<" "<<endl;
}

void resetboard()
{
    board[0][0]='1';
    board[0][1]='2';
    board[0][2]='3';
    board[1][0]='4';
    board[1][1]='5';
    board[1][2]='6';
    board[2][0]='7';
    board[2][1]='8';
    board[2][2]='9';
}

bool checkwin(char player)
{
	//For Checking rows
	for (int i=0;i<3;i++)
	{
		if (board[i][0]== player && board[i][1]== player && board[i][2]== player)
		{
			return true;
		}
	}
	
	//For Checking columns 
	for (int i=0;i<3;i++)
	{
		if (board[0][i]== player && board[1][i]== player && board[2][i]== player)
		{
			return true;
		}
	}
	// For Diagonals
	if (board[0][0]==player && board[1][1]==player && board[2][2]==player)
	{
		return true;
	}
	if (board[0][2]==player && board[1][1]==player && board[2][0]==player)
	{
		return true;
	}
    return false;
}

int main()
{
	t:
	t1:
		system("cls");
	string a,b;
	int game;
	cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<"                                                  Game Menu                                                  "<<endl;
	cout<<"-----------------------------------------------------------------------------------------------------------------------"<<endl;
	cout<<""<<endl;
	cout<<"There are two games Available at the moment. Choose What you like: "<<endl;
	cout<<"1. Tic-Tac-Toe(Play with a Friend)\n2. Guess the Number(Single Player)\n0. Quit"<<endl;
	cin>>game;
	if (game == 1)
	{
	system("cls");
	cout<<"Welcome to Tic Tac Toe"<<endl;
	cout<<" "<<endl;
	cout<<"Enter player 1's Name: ";
	cin>>a;
	cout<<"Enter player 2's Name: ";
	cin>>b;
	cout<<endl;

    re:                    //For rematch
	printboard();
	int turn=1;
	while (true)
	{
		int move;
		char player;
		if (turn==1)
		{
			player= 'X';
			cout<<a<<"'s turn (X): ";
			cout<<" "<<endl;
		}
		else 
		{
			player= 'Y';
			cout<<b<<"'s turn (Y): ";
			cout<<" "<<endl;
		}
		cin>>move;
		
		//For updating the board
		int row,col;
		switch (move)
		{
			case 1: row=0; col=0;
			break;
			case 2: row=0; col=1;
			break;
			case 3: row=0; col=2;
			break;
			case 4: row=1; col=0;
			break;
			case 5: row=1; col=1;
			break;
			case 6: row=1; col=2;
			break;
			case 7: row=2; col=0;
			break;
			case 8: row=2; col=1;
			break;
			case 9: row=2; col=2;
			break;
			default:
				cout<<"Invalid move. Try Again."<<endl;
				cout<<" "<<endl;
				continue;
		}
		if (board[row][col]!='X' && board[row][col]!='Y')
		{
			board[row][col]= player;
			system("cls");
			cout<<"Welcome to Tic Tac Toe "<<endl;
			cout<<" "<<endl;
		}
		else
		{
			cout<<"Invalid move. Try again."<<endl;
			cout<<" "<<endl;
			continue;
		}
		
		// For Printing the current Board
		printboard();
		
		// To check if the game is won
		if (checkwin(player))
		{
			if (turn==1)
			{
			cout<<"\a"<<a<<" wins!"<<endl;
			cout<<" "<<endl;
			break;
		    }
		    else
		    {
		    	cout<<"\a"<<b<<" wins!"<<endl;
		    	cout<<" "<<endl;
		    	break;
			}
		}
		
		// To check if a game is drawn
		bool draw=true;
		for (int i=0;i<3;i++)
		{
			for (int j=0;j<3;j++)
			{
				if (board[i][j]!='X' && board[i][j]!='Y')
				{
					draw=false;
					break;
				}
			}
		}
		if (draw)
		{
			cout<<"It's a draw!"<<endl;
			break;
		} 
		
		// For Switching turns using ternary conditional operator
		turn=(turn==1) ? 2: 1;
	}
		// For a rematch
	while (true)
	{
	int choice;
	cout<<"Do you want a rematch? Press 1 for Yes and 2 for No (1/2). Press 0 for Main Menu. ";
	cin>>choice;
	cout<<" "<<endl;	
	if (choice == 1)
	{
		system("cls");
		resetboard();
		goto re;
	}
	else if (choice == 2)
	{
		cout<<"You choose to end the game. Congratulations to player "<<turn<<"!"<<endl;
		break;
	}
	else if (choice == 0)
	{
		goto t1;
	}
	else
	{
		cout<<"Ivalid Choice. Enter again"<<endl;
		cout<<" "<<endl;
	}
}
}
    else if (game == 2)
    {
    	num:
    		system("cls");
    	cout<<"\t\tWelcome To Guess The Number."<<endl;
    	cout<<" "<<endl;
    	int nr;
    	// seed random number generator
    srand(static_cast<unsigned int>(time(0)));
	
	// random number in the range [1, 100]  
    int secretNumber = rand() % 100 + 1;  
    int tries = 0;
    int guess;

    cout << "Enter your guess: ";
    cin >> guess;
    ++tries;

    while (guess != secretNumber)
    {
        if (guess > secretNumber)
        {
            cout << "Too high! \nTry again: ";
        }
        else
        {
            cout << "Too low! \nTry again: ";
        }

        cin >> guess;
        ++tries;
    }

    cout << "\nYou got it in " << tries << " tries!" << endl;
    cout<<" "<<endl;
    cout<<"1. Play again\n0. Return to main Menu\n3. Quit"<<endl;
    cin>>nr;
    if (nr == 1)
    {
    	goto num;
	}
	else if (nr == 0)
	{
		goto t;
	}
	else if (nr == 3)
	{
		goto q;
	}
	else
	{
		cout<<"Invalid Choice.";
	}
    
	}
	else 
	{
	q:
	return 0;
}
}
