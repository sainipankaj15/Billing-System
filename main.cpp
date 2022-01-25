// Pankaj saini 
#include <bits/stdc++.h>
#include <conio.h> // using this library for use getch()
using namespace std;

class item // this is a class which name is item
{
	int total, no;
	char itemname[50][50];
	int Qty[3];
	int price[3];
	int vat[3];
	int totalprice[3];

public:
	void input();
	void output();
	void sumoutput();
	void listout();
	void non(int x)
	{
		no = 100;
		no += x;
	}
};

void item::input() // this is input function of item class
{
	system("CLS");
	cout << "\nEnter the number of items: ";
	cin >> total;
	for (int i = 0; i < total; i++)
	{
		cout << "\nEnter the name of Item " << i + 1 << ":";
		cin >> itemname[i];
		cout << "\nEnter the quantity: ";
		cin >> Qty[i];
		cout << "\nEnter price of item: ";
		cin >> price[i];
		totalprice[i] = Qty[i] * price[i];
		if (totalprice[i] <= 100)
			vat[i] = totalprice[i] + 0.03 * totalprice[i];
		else
			vat[i] = totalprice[i] + 0.12 * totalprice[i];
	}
	output();
}

void item::output() // this is output function of item class
{
	system("CLS");
	cout << "Bill No: " << no << "\n";
	cout << "-------------------------------------------------------------------------------------------\n";
	cout << "S.no\tName of item\tQuantity\tPrice\tToatal Price\n";
	for (int i = 0; i < total; i++)
	{
		cout << i + 1 << ".\t" << itemname[i] << "\t" << Qty[i] << "\t" << price[i] << "\t" << totalprice[i] << "\n";
	}
	sumoutput();
}

void item::sumoutput() // this is sumoutput function of item class
{
	int tot = 0, sum = 0, qty = 0, cash = 0;
	for (int i = 0; i < total; i++)
	{
		sum += totalprice[i];
		tot += vat[i];
		qty += Qty[i];
	}
	cout << "Total: ";
	cout << "\n--------------------------------------------------------------------------------------------";
	cout << "\n\tQuantity: " << qty << "\t\tSum: " << sum << "\tWith Taxes: " << tot;
	cout << "\n--------------------------------------------------------------------------------------------";
pay:
	cout << "\n\n\t\t\t*****PAYMENT DETAILS*****\n";
	cout << "\n\t\t\tTotal cash given: ";
	cin >> cash;
	if (cash >= tot)
		cout << "\n\t\t\tTotal cash repaid: " << cash - tot << "\n";
	else
	{
		cout << "\n\t\t\tCash given is less than total amount!!!";
		goto pay;
	}
	cout << "\n\t\t\t Payment Successfull   ";
}

void item::listout() // this is listout function of item class
{
	cout << "\nBill No.: " << this->no << "\n";
	cout << "----------------------------------------------------------------------------------------------------\n";
	for (int i = 0; i < total; i++)
		cout << "Name: " << this->itemname[i] << " Qty: " << this->Qty[i] << " Price: " << this->totalprice[i] << "\n";
	cout << "-----------------------------------------------------------------------------------------------------\n";
}

int main()
{

	cout << "Welcome in BILLING MANAGEMENT SYSTEM\n\n";
start:
	system("PAUSE");
	system("CLS");

	cout << "\n\nChoose Between from 1 to 3";
	cout << "\n Press 1. Make a new entry";
	cout << "\n Press 2. Check all previous entries";
	cout << "\n Press 3. Exit";
	cout << "\n\n Choose your option: ";

	int option;
	cin >> option;

	if (option == 1)
	{
		item it;
		ofstream outf("database.bin", ios::app | ios::binary);
		outf.seekp(0, ios::end);
		int x = outf.tellp() / sizeof(item);
		it.non(x);
		it.input();
		outf.write(reinterpret_cast<char *>(&it), sizeof(item));
		outf.close();
		goto start;
	}

	else if (option == 2)
	{
		system("CLS");
		item it1;
		ifstream intf("database.bin", ios::in | ios::binary);
		intf.seekg(0, ios::beg);
		if (!intf)
			cout << "\nYou don't have previous entries\n";
		else
		{
			cout << "\n\t*****Sales Details*****\n\n";
			while (intf.read(reinterpret_cast<char *>(&it1), sizeof(item)))
				it1.listout();
		}
		intf.close();
		goto start;
	}

	else if (option == 3)
		exit(0);

	else
	{
		cout << "\n\t\tPlease choose from 1 to 3 (both included)\n";
		goto start;
	}
	return 0;
}