#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
using namespace std;
string ClientsFileName = "bank_1.txt";
struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
};
enum enpromittransactions
{
	Deposit = 1,
	Wathdraw = 2,
	total_balances = 3,
	Main_Menue = 4
};
enum enpromitmenue
{
	enshow = 1,
	enadd = 2,
	endeleted = 3,
	enupdate = 4,
	enfind = 5,
	EnTransactions_Menue = 6,
	enexit = 7
};
int read_amount(string massage);
bool is_account_exist(string account_num, vector<sClient>& clients);
sClient ReadNewClient(vector<sClient>& clients);
string ConvertRecordToLine(sClient Client, string Seperator = "#//#");
vector<string> split(string sentnce, string delim);
sClient line_to_record(string line, string delim = "#//#");
void AddDataLineToFile(string FileName, string stDataLine);
void AddNewClient(vector<sClient>& clients);
void AddClients(vector<sClient>& clients);
void load_data_from_file_in_vector(string FileName, vector <sClient>& clients);
void print_client_record(sClient& Client);
void print_client_card(sClient& Client);
void print_all_clients_data(vector<sClient>& clients);
string read_account_num();
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client);
void load_data_from_vector_in_file(vector<sClient>& clients, string filename);
sClient update_client(sClient& update);
void delete_client_by_account_num(vector<sClient>& clients, string filename, string accountnum);
void update_client_by_account_num(vector<sClient>& clients, string filename, string accountnum);
short ReadMainMenueOption();
short Read_Transaction_Menue_Option();
void Go_Main_Menue_Screen();
void Go_transactions_Screen(vector<sClient>& vclients);
void show_main_menue_screen();
void deposit_withdraw(vector<sClient>& vclients, string account_num, int many_deposit);
void screen_find_clients(vector<sClient>& vclients, sClient client_);
void ShowEndScreen();
void show_transactions_menue_screen(vector<sClient>& vclients);
void perform_option_transaction_menue(vector<sClient>& vclients, enpromittransactions option);
void perform_option_main_menue(enpromitmenue option);
void show_withdrw_screen(vector<sClient>& vclients);
void show_deposit_screen(vector<sClient>& vclients);
void show_total_balanc(vector<sClient>& vclients);
void print_client_record_(sClient& vclients);
int main()
{

	show_main_menue_screen();

	return 0;
}
int read_amount(string massage)
{
	int num;
	cout << massage << endl;
	cin >> num;
	return num;
}
bool is_account_exist(string account_num, vector<sClient>& clients)
{
	for (sClient& c : clients)
	{
		if (c.AccountNumber == account_num)
		{
			return true;
		}
	}
	return false;
}
sClient ReadNewClient(vector<sClient>& clients)
{
	sClient Client;
	cout << "enter accunt number ? ";
	getline(cin >> ws, Client.AccountNumber);
	while (is_account_exist(Client.AccountNumber, clients))
	{
		cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
		getline(cin >> ws, Client.AccountNumber);
	}
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance ? ";
	cin >> Client.AccountBalance;
	return Client;
}
string ConvertRecordToLine(sClient Client, string Seperator )
{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}
vector<string>split(string sentnce, string delim)
{
	vector<string>my_word;
	string word;
	size_t pos;//المكان الي بوقف عنده لما يلاقي الفراغ اوdelim
	while ((pos = sentnce.find(delim)) != string::npos)
	{
		word = sentnce.substr(0, pos);
		if (word != "")
			my_word.push_back(word);
		sentnce.erase(0, pos + delim.length());
	}
	if (sentnce != "")
		my_word.push_back(sentnce);
	return my_word;
}
sClient line_to_record(string line, string delim)
{
	sClient Client;
	vector<string>vecline = split(line, delim);
	Client.AccountNumber = vecline[0];
	Client.PinCode = vecline[1];
	Client.Name = vecline[2];
	Client.Phone = vecline[3];
	Client.AccountBalance = stod(vecline[4]);
	return Client;
}
void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);
	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;
		MyFile.close();
	}
}
void AddNewClient(vector<sClient>& clients)
{
	sClient Client;
	Client = ReadNewClient(clients);
	AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}
void AddClients(vector<sClient>& clients)
{

	char AddMore = 'Y';
	do
	{
		cout << "\n-----------------------------------\n";
		cout << "\tAdd New Clients Screen";
		cout << "\n-----------------------------------\n\n";
		system("cls");
		cout << "Adding New Client:\n\n";
		AddNewClient(clients);
		cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
		cin >> AddMore;
	} while (toupper(AddMore) == 'Y');
}
void load_data_from_file_in_vector(string FileName, vector <sClient>& clients)
{
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		while (getline(MyFile, Line))
		{
			clients.push_back(line_to_record(Line));
		}
		MyFile.close();
	}
	else
	{
		cout << "Error: Could not open the file!" << endl;
	}
}
void print_client_record(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
	cout << endl;
}
void print_client_card(sClient& Client)
{
	cout << "account number : " << Client.AccountNumber << endl;
	cout << "pin code : " << Client.PinCode << endl;
	cout << "name : " << Client.Name << endl;
	cout << "phon : " << Client.Phone << endl;
	cout << "account balanc : " << Client.AccountBalance << endl;

}
void print_all_clients_data(vector<sClient>& clients)
{

	cout << "\n-----------------------------------\n";
	cout << "\tshow Clients Screen";
	cout << "\n-----------------------------------\n";
	cout << setw(50) << "Clients List (" << clients.size() << ") client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient& client : clients)
	{
		print_client_record(client);
	}
}
string read_account_num()
{
	string num;
	cout << "pleas enter account number :\n";
	getline(cin >> ws, num);
	return num;
}
bool FindClientByAccountNumber(string AccountNumber, vector<sClient>& vClients, sClient& Client)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}
void load_data_from_vector_in_file(vector<sClient>& clients, string filename)
{
	fstream myfile;
	myfile.open(filename, ios::out);
	if (myfile.is_open())
	{
		for (sClient& c : clients)
		{
			myfile << ConvertRecordToLine(c) << "\n";
		}
		myfile.close();
	}
}
sClient update_client(sClient& update)
{
	cout << "Enter PinCode? \n";
	getline(cin >> ws, update.PinCode);
	cout << "Enter Name? \n";
	getline(cin, update.Name);
	cout << "Enter Phone? \n";
	getline(cin, update.Phone);
	cout << "Enter AccountBalance? \n";
	cin >> update.AccountBalance;
	return update;
}
void delete_client_by_account_num(vector<sClient>& clients, string filename, string accountnum)
{
	sClient client_;

	cout << "\n-----------------------------------\n";
	cout << "\tDelete Client Screen";
	cout << "\n-----------------------------------\n";
	if (FindClientByAccountNumber(accountnum, clients, client_))
	{
		print_client_card(client_);
		char deleted;
		cout << "\nDo you want to delete this client? y/n: ";
		cin >> deleted;

		if (deleted == 'y' || deleted == 'Y')
		{
			for (int i = 0; i < clients.size(); i++)
			{
				if (clients[i].AccountNumber == client_.AccountNumber)
				{
					clients.erase(clients.begin() + i);
					break;
				}
			}
			load_data_from_vector_in_file(clients, filename);
			cout << "\nClient Deleted Successfully.\n";
		}
	}
	else
		cout << "not found client";
}
void update_client_by_account_num(vector<sClient>& clients, string filename, string accountnum)
{
	sClient client_;

	cout << "\n-----------------------------------\n";
	cout << "\tUpdate Client Screen";
	cout << "\n-----------------------------------\n";
	// نبعت الفيكتور الجاهز لدالة البحث
	if (FindClientByAccountNumber(accountnum, clients, client_))
	{
		print_client_card(client_);
		char update;
		cout << "\nDo you want to update this client? y/n: ";
		cin >> update;

		if (update == 'y' || update == 'Y')
		{
			for (int i = 0; i < clients.size(); i++)
			{
				if (clients[i].AccountNumber == client_.AccountNumber)
				{
					update_client(clients[i]);
					break;
				}
			}
			load_data_from_vector_in_file(clients, filename);
			cout << "\nClient updated Successfully.\n";
		}
	}
	else
		cout << "not found client";
}
short ReadMainMenueOption()
{
	cout << "Choose what do you want to do? [1 to 7]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
short Read_Transaction_Menue_Option()
{
	cout << "Choose what do you want to do? [1 to 4]? ";
	short Choice = 0;
	cin >> Choice;
	return Choice;
}
void Go_Main_Menue_Screen()
{
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause>0");
	show_main_menue_screen();
}
void screen_find_clients(vector<sClient>& vclients, sClient client_)
{

	cout << "\n-----------------------------------\n";
	cout << "\tFind Client Screen";
	cout << "\n-----------------------------------\n";
	if (FindClientByAccountNumber(read_account_num(), vclients, client_))
		print_client_card(client_);
	else
		cout << "clients not found!\n";
}
void ShowEndScreen()
{
	cout << "\n-----------------------------------\n";
	cout << "\tProgram Ends :-)";
	cout << "\n-----------------------------------\n";
}
void perform_option_transaction_menue(vector<sClient>& vclients, enpromittransactions option)
{
	sClient client_;
	switch (option)
	{
	case enpromittransactions::Deposit:
		system("cls");
		show_deposit_screen(vclients);
		Go_transactions_Screen(vclients);
		break;
	case enpromittransactions::Wathdraw:
		system("cls");
		show_withdrw_screen(vclients);
		Go_transactions_Screen(vclients);
		break;
	case enpromittransactions::total_balances:
		system("cls");
		show_total_balanc(vclients);
		Go_transactions_Screen(vclients);
		break;
	case enpromittransactions::Main_Menue:
		system("cls");
		Go_Main_Menue_Screen();
		break;
	}
}
void show_transactions_menue_screen(vector<sClient>& vclients)
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\ttransaction Menue Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] Total Balances.\n";
	cout << "\t[4] Back Main Menue.\n";
	perform_option_transaction_menue(vclients, (enpromittransactions)Read_Transaction_Menue_Option());
}
void perform_option_main_menue(enpromitmenue option)
{
	vector<sClient> vclients;
	sClient client_;
	load_data_from_file_in_vector(ClientsFileName, vclients);
	switch (option)
	{
	case enpromitmenue::enshow:
		system("cls");
		print_all_clients_data(vclients);
		Go_Main_Menue_Screen();
		break;
	case enpromitmenue::enadd:
		system("cls");
		AddClients(vclients);
		Go_Main_Menue_Screen();
		break;
	case enpromitmenue::endeleted:
		system("cls");
		delete_client_by_account_num(vclients, ClientsFileName, read_account_num());
		Go_Main_Menue_Screen();
		break;
	case enpromitmenue::enupdate:
		system("cls");
		update_client_by_account_num(vclients, ClientsFileName, read_account_num());
		Go_Main_Menue_Screen();
		break;
	case enpromitmenue::enfind:
		system("cls");
		screen_find_clients(vclients, client_);
		Go_Main_Menue_Screen();
		break;
	case enpromitmenue::EnTransactions_Menue:
		system("cls");
		show_transactions_menue_screen(vclients);
		break;
	case enpromitmenue::enexit:
		ShowEndScreen();
		break;
	}
}
void show_main_menue_screen()
{
	system("cls");
	cout << "=============================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "=============================================\n";
	cout << "\t[1] Show Clients List.\n";
	cout << "\t[2] Add New Clients.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transactions.\n";
	cout << "\t[7] Exit.\n";
	perform_option_main_menue((enpromitmenue)ReadMainMenueOption());
}
void Go_transactions_Screen(vector<sClient>& vclients)
{
	cout << "\n\nPress any key to go back to transaction Menue...";
	system("pause>0");
	show_transactions_menue_screen(vclients);
}
void show_withdrw_screen(vector<sClient>& vclients)
{
	cout << "\n-----------------------------------\n";
	cout << "\twithdraw Screen";
	cout << "\n-----------------------------------\n";
	string account_num = read_account_num();
	sClient client_;
	while (!FindClientByAccountNumber(account_num,vclients,client_))
	{
		cout << "\nClient with [" << account_num << "] does not exist.\n";
		account_num = read_account_num();
	}
	int withdraww= read_amount("pleas enter a how mach withdraw");
	deposit_withdraw(vclients, account_num, withdraww * (-1));

}
void show_deposit_screen(vector<sClient>& vclients)
{
	cout << "\n-----------------------------------\n";
	cout << "\tdeposit Screen";
	cout << "\n-----------------------------------\n";
	string account_num = read_account_num();
	sClient client_;
	while (!FindClientByAccountNumber(account_num, vclients, client_))
	{
		cout << "\nClient with [" << account_num << "] does not exist.\n";
		account_num = read_account_num();
	}
	int deposit = read_amount("pleas enter a how mach deposit");
	deposit_withdraw(vclients, account_num, deposit);

}
void deposit_withdraw(vector<sClient>& vclients, string account_num, int many_deposit) // مافي داعي نمرر client_ هون
{
	sClient client_;
	if (FindClientByAccountNumber(account_num, vclients, client_))
	{
		print_client_card(client_);
		char answer = 'n';
		cout << "\nAre you sure you want perform this transaction? y/n: ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			for (sClient& C : vclients)
			{
				if (C.AccountNumber == account_num)
				{
					while (many_deposit<0 && (many_deposit * (-1))>C.AccountBalance)
					{//اذ كانت العمليه سحب
						cout << "the withdraw more than account balanc,enter a new withdraw\n";
						cin >> many_deposit;
						many_deposit = many_deposit * (-1);
					}
					C.AccountBalance += many_deposit;
					cout << "\nthe opreation was completed successfully, new balance is: " << C.AccountBalance << "\n";
					break;
				}
			}
			load_data_from_vector_in_file(vclients, ClientsFileName);
		}
	}
	else
	{
		cout << "\nClient with account number [" << account_num << "] is not found!\n";
	}
}
void show_total_balanc(vector<sClient>& vclients)
{
	cout << "\n-----------------------------------\n";
	cout << "\tshow Clients Screen";
	cout << "\n-----------------------------------\n";
	cout << setw(50) << "Clients List (" << vclients.size() << ") client(s).";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(23) << "Accout Number";
	cout << "| " << left << setw(47) << "Client Name";
	cout << "| " << left << setw(19) << "Balance";
	cout <<
		"\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	int total_balanc = 0;
	for (sClient& client : vclients)
	{
		print_client_record_(client);
		total_balanc += client.AccountBalance;
	}

	cout << "Total Balanc = " << total_balanc << endl;
}
void print_client_record_(sClient& vclient)
{
	cout << "| " << setw(23) << left << vclient.AccountNumber;
	cout << "| " << setw(47) << left << vclient.Name;
	cout << "| " << setw(19) << left << vclient.AccountBalance;
	cout << endl;
}
