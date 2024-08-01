#include <iostream>
#include<vector>
#include<string>
#include<fstream>
#include<iomanip>

using namespace std;
void MianMenue();
void Transaction();

const string FileName = "Client.txt";

struct stClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool Mark = false;
};
vector<string>Spilt(string line, string dil)
{
	vector<string>p;
	string word;
	short pos = 0;
	while ((pos = line.find(dil)) != std::string::npos)
	{
		word = line.substr(0, pos);
		if (word != "")
			p.push_back(word);

		line.erase(0, (pos + dil.length()));
	}
	if (line != "")
		p.push_back(line);
	return p;

}


string ConvertRecordToLine(stClient p, string dil = "#//#")
{
	string line = "";
	line +=p.AccountNumber+ dil;
	line += p.PinCode + dil;
	line += p.Name + dil;
	line += p.Phone + dil;
	line += to_string(p.AccountBalance);
	return line;
}
stClient ConvertLineToRecord(string line, string dil = "#//#")
{
	vector<string>o;
	o = Spilt(line,dil);
	stClient p;
	p.AccountNumber = o[0];
	p.PinCode = o[1];
	p.Name = o[2];
	p.Phone = o[3];
	p.AccountBalance = stod(o[4]);
	return p;

}

void AddToFile(string filename,string line)
{
	fstream myfile;
	myfile.open(filename, ios::out | ios::app);
	if (myfile.is_open())
	{
		myfile << line << endl;
		myfile.close();
	}

}

vector<stClient>LoadFileToVector(string filename)
{
	vector<stClient>p;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		string line;
		stClient l;
		while (getline(myfile, line))
		{
			l = ConvertLineToRecord(line);
			p.push_back(l);
		}
		myfile.close();
	}
	return p;
}
bool ClineteExistsByAccountNumber(string filename, string accountnumber)
{
	vector<stClient>p;
	fstream myfile;
	myfile.open(filename, ios::in);
	if (myfile.is_open())
	{
		string line;
		stClient k;
		while (getline(myfile, line))
		{
			k = ConvertLineToRecord(line);
			if (k.AccountNumber == accountnumber)
			{
				myfile.close();
				return true;
			}
			p.push_back(k);
		}
		myfile.close();
	}
	return false;
}
stClient ReadRecord()
{
	stClient o;

	cout << "Enter the Account Number ?";
	getline(cin >> ws, o.AccountNumber);

	while (ClineteExistsByAccountNumber(FileName, o.AccountNumber))
	{
		cout << "\nClient with [" << o.AccountNumber << "] already exists, Enter another Account Number? ";     
		getline(cin >> ws, o.AccountNumber);
	}
		cout << "enter the pin code ?";
		getline(cin, o.PinCode);
		cout << "enter the name ?";
		getline(cin, o.Name);
		cout << "enter the phone ?";
		getline(cin, o.Phone);
		cout << "enter the account balance ?";
		cin >> o.AccountBalance;
	
	return o;
}
void PrintClientCard(stClient p) 
{ 
	cout << "\nThe following are the client details:\n"; 
	cout << "\nAccout Number: " << p.AccountNumber; 
	cout << "\nPin Code     : " << p.PinCode;   
	cout << "\nName         : " << p.Name;    
	cout << "\nPhone        : " << p.Phone;  
	cout << "\nAccount Balance: " << p.AccountBalance; 
}



///////////111111111111111111111111SHOWSCREEN
void PrintRecord(stClient p)
{
	cout << "| " << setw(15) << left << p.AccountNumber;
	cout << "| " << setw(10) << left << p.PinCode;
	cout << "| " << setw(40) << left << p.Name;
	cout << "| " << setw(12) << left << p.Phone;
	cout << "| " << setw(12) << left << p.AccountBalance;
}
void PrintShowScreen()
{
	vector <stClient> vClient = LoadFileToVector(FileName);
	cout << "\n\t\t\t\t\tClient List (" << vClient.size() << ") Client(s).";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n-------------------------------------------------";
	cout << "-------------------------------------------------\n" << endl;
	if (vClient.size() == 0)
	{
		cout << "\t\t\t\tNo Clients Available In the System!";
	}
	else
	{
		for (stClient u : vClient)
		{
			PrintRecord(u);
			cout << endl;
		}
		cout << "\n-------------------------------------------------";
		cout << "-------------------------------------------------\n" << endl;
	}
}


///////2222222222222222222Add SCREEN
void PrintAddScreen1()
{
	cout << "======================================================\n";
	cout << setw(40)  << "Adding Screen" << endl;
	cout << "======================================================\n";
}
void join()
{
	stClient p = ReadRecord();
	AddToFile(FileName, ConvertRecordToLine(p));
}
bool FindAccountNumber(string AccountNumber,stClient &o, vector<stClient>u)
{
	 
	for (stClient i : u)
	{
		if (i.AccountNumber == AccountNumber)
		{
			o = i;
			return true;
		}
		
	}
	return false;


}
stClient ChangeClientRecord(string accountnumber)
{
	stClient p;

	p.AccountNumber = accountnumber;
	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, p.PinCode); 
	cout << "Enter Name? ";   
	getline(cin, p.Name);
	cout << "Enter Phone? ";  
	getline(cin, p.Phone);  
	cout << "Enter AccountBalance? "; 
	cin >> p.AccountBalance;

	return p;




}


void add()
{
	char read = 'n';
	do {
		cout << "\nAdd New Clients :" << endl;
		join();
		cout << "\n\nClient Added successfully ,do you want agin ? Y/N ?";
		cin >> read;
	} while (toupper(read) == 'Y');
		
	
}
void ShowAddScreen()
{
	cout << "======================================================\n";
	cout << "\t\tAdding  Screen" << endl;
	cout << "======================================================\n";
	add();
}
//////////////////333333333333DELETE SCREEN


bool MarkClientByAccountNumber(string accountnumber, vector<stClient>&o)
{
	for (stClient &u : o)
	{
		if (u.AccountNumber==accountnumber)
		{
			u.Mark = true;
			return true;
		}
	}
	return false;

}


vector<stClient>SavaClientDateToFile(string filename,vector<stClient>oo)
{
	string line;
	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{
		for (stClient u : oo)
		{
			if (u.Mark == false)
			{
				line = ConvertRecordToLine(u);
				myfile << line << endl;
			}
		}
		myfile.close();
	}
	return oo;
}
bool DeleteClientByAccountNumber(string AccountNumber, vector<stClient>& vClients) 
{
	stClient Client;
	char Answer = 'n';
	if (FindAccountNumber(AccountNumber, Client, vClients))
	{
		PrintClientCard(Client); 
		cout << "\n\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y') 
		{
			MarkClientByAccountNumber(AccountNumber, vClients); 
			SavaClientDateToFile(FileName, vClients); 
			vClients = LoadFileToVector(FileName);
			           cout <<"\n\nClient Deleted Successfully."; 
					   return true;  
		} 
	} 
	else   
	{      
		cout <<"\nClient with Account Number ("<<AccountNumber<<") is Not Found!"; 
		return false;   
	} 
}
string ReadAccountNumber()
{
	string name = "";
	cout << "\nEnter the Account Number ?";
	cin >> name;

	return name;
}
void DeleteScreen()
{
	cout << "======================================================\n";

	cout << "\t\tDelete Screen" << endl;
	cout << "======================================================\n";
	 vector <stClient> vClients = LoadFileToVector(FileName);
	 string AccountNumber = ReadAccountNumber();  
	 DeleteClientByAccountNumber(AccountNumber, vClients); 
}


//////////////////44444444444444444 UPDATE SCREEN

bool UpdateClientBuAccountNumber(string accountnumber, vector<stClient>& bClient)
{
	stClient p;
	char read = 'n';
	if (FindAccountNumber(accountnumber, p,bClient))
	{
		PrintClientCard(p);

		cout << "\n\nAre you sure you update this client ? Y/N ?";
		cin >> read;
		if (toupper(read) == 'Y')
		{
			for (stClient& u : bClient)
			{
				if (u.AccountNumber == accountnumber)
				{
					u = ChangeClientRecord(accountnumber);
					break;
				}
		   }
			SavaClientDateToFile(FileName, bClient);
			cout << "\n\nClient uptaded successfully .";
			return true;
		}
	}
	else
	cout << "\n\nClient with Account Number [" << accountnumber << "] Not Found .";
		return false;
	
}
void UpdateScreen()
{
	cout << "======================================================\n";
	cout << "\t\tUpdate Screen" << endl;
	cout << "======================================================\n";
	string o = ReadAccountNumber();
	vector<stClient>p = LoadFileToVector(FileName);
	UpdateClientBuAccountNumber(o, p);
}


//////////////////5555555555555555 FIND SCREEN

void FindScreen()
{
	
	cout << "======================================================\n";

	cout  << "\t\tFind Screen" << endl;
	cout << "======================================================\n";
	vector<stClient>p = LoadFileToVector(FileName);
	stClient i;
	string o = ReadAccountNumber();
	if (FindAccountNumber(o, i,p))
	{
		PrintClientCard(i);
	}
	else
		cout << "\nClient with Account Number [" << o << "] is Not Found .";
}


//////////////////666666666666 EXIT SCREEN
void ExitScreen()
{
	system("cls");
}
void ShowEndScreen() {
	cout << "======================================================\n";

	cout << "\t\tProgram Ends :)" << endl;
	cout << "======================================================\n";
}
enum enMianMenue {
	showScreen = 1, Add = 2,
	Dlete = 3, Update = 4,
	Find = 5,Transactionshow=6, Exsit = 7

};
enum enTransactions {Deposit =1,Withdraw=2,TotalBalance=3,Minemenue=4};
void GoToBackMianMenue()
{
	cout << "\nPress any key to go back to main menue ...";
	system("pause>0");
	MianMenue();
}
void GoToBackTransaction()
{
	cout << "\nPress any key to go back to main menue ...";
	system("pause>0");
	system("cls");
	Transaction();

}

////////////////Deposit Screen

bool Depositt(string accountnumber, double number, vector<stClient>& p)
{
	char read = 'n';
	cout << "\nAre you sure you want perfrom this transaction ? y/n ?";
	cin >> read;
	if (toupper(read) == 'Y')
	{
		for (stClient& u : p)
		{
			if (u.AccountNumber == accountnumber)
			{
				u.AccountBalance += number;
				SavaClientDateToFile(FileName, p);
				cout << "\nDone successfully, New balance =" << u.AccountBalance << endl;
				return true;
			}
		}
		return false;

	}
}

void DepositScreen()
{
	stClient vClient;
	double number;
	cout << "======================================================\n";

	cout << "\t\tDeposit Screen" << endl;
	cout << "======================================================\n";
	string p = ReadAccountNumber();
	vector<stClient>i = LoadFileToVector(FileName);
	while (!FindAccountNumber(p, vClient, i))
	{
		cout << "\nClient with [" << p << "] does not exist.";
		p = ReadAccountNumber();
	}
	PrintClientCard(vClient);

	cout << "\n\nPlease enter deposit number ?";
	cin >> number;
	Depositt(p, number, i);

}



void WithDrawScreen()
{
	stClient vClient;
	double number;
	cout << "======================================================\n";

	cout << "\t\tWithDraw Screen" << endl;
	cout << "======================================================\n";
	string p = ReadAccountNumber();
	vector<stClient>o = LoadFileToVector(FileName);
	while (!FindAccountNumber(p,vClient,o))
	{
		cout << "\nClient with [" << p << "] Not exist .";
		p = ReadAccountNumber();
	}
	PrintClientCard(vClient);
	cout << "\n\nPlease enter withdraw amount ?";
	cin >> number;
	while (number > vClient.AccountBalance)
	{
		cout << "\nAmount Exceeds the balance, you can withdraw up to : " << vClient.AccountBalance << endl;
		cout << "\nPlease enter another amount ?";
		cin >> number;
	}
	Depositt(p, number * -1, o);
}

/////////////////Total Balances


void PrintClientTrasaction(stClient p)
{
	cout << "| " << setw(15) << left << p.AccountNumber;
	cout << "| " << setw(40) << left << p.Name;
	cout << "| " << setw(12) << left << p.AccountBalance;


}
void TotalBalancesScreen()
{
	vector<stClient>p = LoadFileToVector(FileName);
	cout << "\n\t\t\t\t\tClient List (" << p.size() << ") Client(s).";   
	cout << "| " << left << setw(15) << "Accout Number"; 
	cout << "| " << left << setw(40) << "Client Name";  
	cout << "| " << left << setw(12) << "Balance";  
	cout << "\n_______________________________________________________";  
	cout << "_________________________________________\n" << endl;
	double number=0;
	if(p.size()==0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else
	{
		for (stClient o : p)
		{
			PrintClientTrasaction(o);
			number += o.AccountBalance;
			cout << endl;
		}
		cout << "\n_______________________________________________________";  
		cout << "_________________________________________\n" << endl; 
		cout << "\t\t\t\t\t   Total Balances = " << number;
	}
	

}

void PerformTransaction(enTransactions transaction)
{
	switch (transaction)
	{
	case enTransactions::Deposit:
		system("cls");
		DepositScreen();
		GoToBackTransaction();
		break;

	case enTransactions::Withdraw:
		system("cls");
		WithDrawScreen();
		GoToBackTransaction();
		break;
	case enTransactions::TotalBalance:
		system("cls");
		TotalBalancesScreen();
		GoToBackTransaction();
		break;
	case enTransactions::Minemenue:
		system("cls");
		MianMenue();
		break;
	}
}









short ReadMainMenueOption() {
	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice; 
	return Choice;
}
short ReadTransactionMenue()
{
	short number;
	cout << "Choose what do you want to do ? [1 to 4] ?";
	cin >> number;
	return number;
}
void Question(enMianMenue mianmeneue)
{
	
	switch (mianmeneue)
	{
	case enMianMenue::showScreen:
	{	system("cls");
	PrintShowScreen();
	GoToBackMianMenue();
	break; }

	case enMianMenue::Add:
	system("cls");
	ShowAddScreen();
	GoToBackMianMenue();
	break; 


	case enMianMenue::Dlete:
	system("cls");
	DeleteScreen();
	GoToBackMianMenue();
	break; 


	case enMianMenue::Update:
	system("cls");
	UpdateScreen();
	GoToBackMianMenue();
	break;
	

	case enMianMenue::Find:
	system("cls");
	FindScreen();
	GoToBackMianMenue();
	break;
	
	case enMianMenue::Transactionshow:
		system("cls");
		Transaction();
		break;
	case enMianMenue::Exsit:
	system("cls");
	ShowEndScreen();
	break;
	
	}
	
}
void Transaction()
{
	cout << "======================================================\n";
	cout << "\t\tTransaction Menue Screen" << endl;
	cout << "======================================================\n";
	cout << "\t[1] Deposit ." << endl;
	cout << "\t[2] WithDraw ." << endl;
	cout << "\t[3] Total Balances ." << endl;
	cout << "\t[4] Mian Menue ." << endl;
	cout << "======================================================\n";
	
	PerformTransaction((enTransactions)ReadTransactionMenue());
}
void MianMenue()
{
	system("cls");
	cout << "======================================================\n";
	cout  << "\t\tMian Menue Screen" << endl;
	cout << "======================================================\n";
	cout  << "\t[1] Show Client List ." << endl;
	cout  << "\t[2] Add New Client  ." << endl;
	cout  << "\t[3] Delete Client  ." << endl;
	cout  << "\t[4] Update Client Info ." << endl;
	cout  << "\t[5] Find  Client ." << endl;
	cout << "\t[6] Transaction ." << endl;
	cout  << "\t[7] Exist ." << endl;
	cout << "======================================================\n";
	
	Question((enMianMenue)ReadMainMenueOption());
	
}


int main()
{
	MianMenue();

	system("pause>0");
	return 0;
}


