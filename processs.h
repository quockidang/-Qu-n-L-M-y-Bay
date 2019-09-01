#ifndef _PROCESSS_H
#define _PROCESSS_H
#include <fstream>//doc ghi file
#include "airplane.h"
#include "flight.h"
#include "passenger.h"

//MAY BAY
void SaveAirplane(PTR_AIRPLANE al, fstream &file)
{
	file << al->soHieuMayBay << endl;
	file << al->loaiMayBay << endl;
	file << al->soDay << endl;
	file << al->soDong << endl;
}

void SaveAirplaneToFile(PTR_LIST_AIRPLANE la)
{
	fstream outFile;
	outFile.open("DSMB.txt", ios::out );
	if (outFile.is_open())
	{
		outFile << la->n <<endl;
		for(int i = 0; i<= la->n;i++)
		{
			SaveAirplane(la->listAirplane[i], outFile);
		}
	}else
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "KET NOI VOI FILE DSMB THAT BAI! ";
	}
	
	outFile.close();
}

//load chuyen bay da luu trong file ra RAM
void LoadAirplaneFromFile(PTR_LIST_AIRPLANE &la)
{
	fstream inFile;
	
	int nAirplane;
	inFile.open("DSMB.txt", ios::in);
	
	if(inFile.is_open())
	{
		string temp;		
		inFile >> nAirplane;
		for(int i = 0; i <= nAirplane; i++)
		{
			la->listAirplane[i] = new AIRPLANE;
			getline(inFile, temp);
			inFile.getline(la->listAirplane[i]->soHieuMayBay, 15, '\n');
			inFile.getline(la->listAirplane[i]->loaiMayBay, 40, '\n');	
			inFile >> la->listAirplane[i]->soDay;
			inFile >> la->listAirplane[i]->soDong;	
			++la->n;
			//delete l->listCreditClass[i];
		}
	}
	inFile.close();//dong file
}
//END MAY BAY

//CHUYEN BAY
//luu cau truc 1 chuyen bay vao file 


void SaveFlight(FLIGHT fl, fstream &file)
{
	file << fl.maChuyenBay << endl;
	file << fl.soHieuMayBay << endl;
	file << fl.sanBayDen << endl;
	
	file << fl.thoiGianDi.y << endl;
	file << fl.thoiGianDi.m << endl;
	file << fl.thoiGianDi.d << endl;
	file << fl.thoiGianDi.h << endl;
	file << fl.thoiGianDi.mi << endl;
	
	file << fl.soLuongVe << endl;
	file << fl.trangThai << endl;
	file << fl.soVeDaBan << endl;
	
	for(int i = 0; i < fl.soLuongVe; i++ )
	{
		file << fl.listTicket[i].tenVe << endl;
		file << fl.listTicket[i].CMND << endl;
	}

}

//ghi cac node Flight vao file
void SaveFlightToFile(LIST_FLIGHT lf)
{
	fstream outFile;
	outFile.open("DSCB.txt", ios::out );//ios::out mo file de luu
	if (outFile.is_open())
	{
		outFile << lf.n << endl;
		for(NODE_FLIGHT* k = lf.pHead; k != NULL; k = k->pNext)
		{
			SaveFlight(k->data, outFile);
		}
	}else
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "KET NOI VOI FILE DSCB THAT BAI! ";
	}
	outFile.close();
}

//load ra file
void LoadFlightFromFile(LIST_FLIGHT &l)
{
	fstream inFile;
	FLIGHT fl;
	int n;
	string temp;
	inFile.open("DSCB.txt", ios::in);//ios::in => mo file de ghi
	if (inFile.is_open())
	{		
		inFile >> n;
		getline(inFile, temp);
		for(int i = 0; i < n; i++)
		{
			inFile.getline(fl.maChuyenBay, 15, '\n');
			inFile.getline(fl.soHieuMayBay, 15, '\n');
			inFile.getline(fl.sanBayDen, 30, '\n');
			
			inFile >> fl.thoiGianDi.y;
			inFile >> fl.thoiGianDi.m;
			inFile >> fl.thoiGianDi.d;
			inFile >> fl.thoiGianDi.h;
			inFile >> fl.thoiGianDi.mi;
			
			inFile >> fl.soLuongVe;
			inFile >> fl.trangThai;
			inFile >> fl.soVeDaBan;	
			
			getline(inFile, temp);	
			for(int j = 0; j < fl.soLuongVe; j++)
			{
				//xoa bo nho dem, doc ky tu rong de bat dau doc chuoi
				inFile.getline(fl.listTicket[j].tenVe, 3, '\n');
				inFile >> fl.listTicket[j].CMND;
			}
			AddTailListFlight(l, fl);
			getline(inFile, temp);
		}
	}
	else {
		cout << "KET NOI VOI FILE DSCB THAT BAI! ";
	}

	inFile.close();
}

//HANH KHACH
void Save(TREE_PASSENGER t, fstream &file)
{
	file << t->data.ho << endl;
	file << t->data.ten << endl;
	file << t->data.CMND<< endl;
	file << t->data.phai << endl;
	file << t->data.isBooked << endl;
}

void WritePassengerToFile(TREE_PASSENGER t, fstream &file)
{
	if (t != NULL)
	{
		Save(t, file);
		WritePassengerToFile(t->pLeft, file);
		WritePassengerToFile(t->pRight, file);	
	}
}

void SavePassengerToFile(TREE_PASSENGER t)
{
	fstream outFile;
	outFile.open("DSHK.txt", ios::out);
	if (outFile.is_open())
	{
		
		outFile << nPassenger << endl;
		WritePassengerToFile(t, outFile);
	}
	else
	{
		cout << "KET NOI VOI FILE DSHK THAT BAI! ";
	}
	outFile.close();
}


void LoadPassengerFormFile(TREE_PASSENGER &t)
{
	fstream inFile;
	PASSENGER pa;
	int n;
	inFile.open("DSHK.txt", ios::in);
	if (inFile.is_open())
	{
		string temp;		
		inFile >> n;
		
		for(int i = 0; i <= n; i++)
		{
			getline(inFile, temp);
			inFile.getline(pa.ho, 30, '\n');
			inFile.getline(pa.ten, 10, '\n');
			inFile >> pa.CMND;
			inFile >> pa.phai;
			inFile >> pa.isBooked;
			
			InsertPassengerToTree(t, pa);
		}
	}
	else {
		cout << "KET NOI VOI FILE DSHK THAT BAI! ";
	}

	inFile.close();
}	


// -----------------------dat ve ----------------------------------
int pageNowTicket = 1;
int totalPageTicket = 0;
int currposTicket = 0;
int currposPrecTicket = 0;

void outputTicket(string nameTicket, int ordinal)
{
	DeleteOldData(1, ordinal);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + ordinal); cout << nameTicket;
}

void outputListTicketPerPage(string *arr, int n, int indexBegin)
{
	for(int i = 0; i + indexBegin < n && i < QUANTITY_PER_PAGE; i++)
	{
		outputTicket(arr[i + indexBegin], i * 2);
	}
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowTicket << "/" << totalPageTicket;
}

void SetDefaultChoseTicket(string* arr, int ordinal)
{
	SetBGColor(1);
	outputTicket(arr[ordinal], (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0);
}

void EffectiveMenuTicket(int index, string* arr)
{
	int current = index;
	SetDefaultChoseTicket(arr, current);
	outputTicket(arr[currposPrecTicket], (currposPrecTicket % QUANTITY_PER_PAGE) * 2);
	currposPrecTicket = current;
}
void ChangePageTicket(string* arr)
{
	clrscr();
	
	Display(keyDisplayTicket, sizeof(keyDisplayTicket) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[7] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	currposTicket = (pageNowTicket - 1) * QUANTITY_PER_PAGE;
	
	currposPrecTicket = (pageNowTicket - 1) * QUANTITY_PER_PAGE;
}

string ChoseTicket(string* arr, int n)
{
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	
	currposTicket = 0;
	currposPrecTicket = 0;
	pageNowTicket = 1;
	totalPageTicket = (n -1) / QUANTITY_PER_PAGE + 1;
	outputListTicketPerPage(arr, n, 0);
	SetDefaultChoseTicket(arr, currposTicket);
	
	while(true)
	{
		while(_kbhit())
		{
			keyboard_read = _getch();
			if (keyboard_read == 0)
				keyboard_read = _getch();
			switch (keyboard_read)
			{
			case KEY_UP:
				if (currposTicket % QUANTITY_PER_PAGE > 0)
				{
					currposTicket = currposTicket - 1;
					EffectiveMenuTicket(currposTicket, arr);
				}
				break;
			case KEY_DOWN:
				if (currposTicket % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposTicket < (n - 1))
				{
					currposTicket = currposTicket + 1;
					EffectiveMenuTicket(currposTicket, arr);
				}
				break;
			case PAGE_DOWN:
				if (pageNowTicket < totalPageTicket)
				{

					
					pageNowTicket++;
					ChangePageTicket(arr);
					Gotoxy(X_TITLE, Y_TITLE); cout << "CHON VE MUON DAT";
					outputListTicketPerPage(arr, n, (pageNowTicket - 1) * QUANTITY_PER_PAGE);
					SetDefaultChoseTicket(arr, currposTicket);

				}
				break;
			case PAGE_UP:
				if (pageNowTicket > 1)
				{
					
					pageNowTicket--;
					ChangePageTicket(arr);
					Gotoxy(X_TITLE, Y_TITLE); cout << "CHON VE MUON DAT";
					outputListTicketPerPage(arr, n, currposTicket);
					SetDefaultChoseTicket(arr, currposTicket);
				}
				break;
			case ESC:
				ShowCur(false);
				return "null";
				break; // no choose
			case ENTER:
				ShowCur(false);
				return arr[currposTicket];
				break;
			}
		}	
	}
}

bool isNumber(string input)
{
	bool flag = true;
	for(int i= 0; i< input.length(); i++)
	{
		if(input[i] >= 48 && input[i] <= 57)
		{
			flag = true;
		}else{
			flag = false;
			break;
		}
	}
	
	return flag;
}


void BookticketIsSucced(LIST_FLIGHT &l, PTR_LIST_AIRPLANE lal, TREE_PASSENGER &t)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON DAT VE";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[4] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	
	NODE_FLIGHT* fl;
	do
	{
		fl = ChooseFlight(l);
		
		if(fl->data.trangThai != STT_REMAIN_TICKET)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "CHON CHUYEN BAY CON VE HOAC CHUA HOAN TAT";
			_getch();
		}
	}while(fl->data.trangThai != STT_REMAIN_TICKET);
	if(fl == NULL) return;
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON VE MUON DAT";
	Display(keyDisplayTicket, sizeof(keyDisplayTicket) /  sizeof(string));
	
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[7] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	
	string* temp = new string[fl->data.soLuongVe - fl->data.soVeDaBan];
	int n = 0;
	for(int i = 0; i < fl->data.soLuongVe; i++)
	{
		if(fl->data.listTicket[i].CMND == 0)
		{
			temp[n++] = fl->data.listTicket[i].tenVe;
		}
	}
	string ticket = ChoseTicket(temp, n);
	if(ticket == "null") return;
	Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Ban da chon ve " +ticket + " tren chuyen bay cho ma la: " + (string)fl->data.maChuyenBay;
	Gotoxy(X_NOTIFY, Y_NOTIFY + 2); cout << "An phim bat ki de tiep tuc dat ve";
	
	_getch();
backMenu:
	clrscr();
	ShowCur(true);
	string idpass;
	Gotoxy(X_TITLE, Y_TITLE); cout << "NHAP THONG TIN HANH KHACH";
	DisplayEdit(keyDisplayEditIdPass, 1, 35);
	
	do{
		Gotoxy(X_ADD + 6, Y_ADD);
		fflush(stdin);
		getline(cin, idpass);
		if(isNumber(idpass) == false || (int)(log10(atoi((char*)idpass.c_str())) + 1) != 9)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "CMND khong dung, xin nhap lai";
			_getch();
			Gotoxy(X_ADD + 6, Y_ADD);
			cout << setw(35) << setfill(' ') << " ";
		}
	}while(!isNumber(idpass) || (int)(log10(atoi((char*)idpass.c_str())) + 1) != 9);
	
	int id = atoi((char*)idpass.c_str());
	
	for(int i = 0; i < fl->data.soLuongVe; i++)
	{
		if(id == fl->data.listTicket[i].CMND)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Moi hanh khach chi duoc mua mot ve";
			_getch();
			return;
		}
	}
	
	NODE_PASSENGER* k = FindPassenger(t, id);
	
	if(k != NULL)
	{
		Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
		OutputPassenger(k->data, 0);
		
		for(int i = 0; i < fl->data.soLuongVe; i++)
		{
			if( strcmp(fl->data.listTicket[i].tenVe, (char*)ticket.c_str()) == 0)
			{
				fl->data.listTicket[i].CMND = id;
				fl->data.soVeDaBan++;
			}
		}
		
		Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Dat ve thanh cong";
		_getch();
		return;
	}else
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "ban khong phai la thanh vien, moi nhap day du thong tin";
		PASSENGER pa;
		DisplayEdit(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string), 35);
		InputPassenger(t, pa, false);
		
		for(int i = 0; i < fl->data.soLuongVe; i++)
		{
			if( strcmp(fl->data.listTicket[i].tenVe, (char*)ticket.c_str()) == 0)
			{
				fl->data.listTicket[i].CMND = pa.CMND;
				fl->data.soVeDaBan++;
				break;
			}
		}
		
		Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
		OutputPassenger(pa, 0);
		Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
		cout << setw(xKeyDisplay[4] - xKeyDisplay[0] - 1) << " " << setfill(' ');
		Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Dat ve thanh cong";
		_getch();
		return;
	}
	
	
}

void UnBookTicketIsSucced(LIST_FLIGHT &l)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY MUON HUY VE";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[4] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	
	NODE_FLIGHT* fl = ChooseFlight(l);
	if(fl == NULL)
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "Huy ve that bai";
		_getch();
		return;
	}else{
		
		string idpass;
		Gotoxy(X_TITLE, Y_TITLE); cout << "NHAP THONG TIN HANH KHACH";
		DisplayEdit(keyDisplayEditIdPass, 1, 35);	
		do{
			Gotoxy(X_ADD + 6, Y_ADD);
			fflush(stdin);
			getline(cin, idpass);
			if(isNumber(idpass) == false || (int)(log10(atoi((char*)idpass.c_str())) + 1) != 9)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "CMND khong dung, xin nhap lai";
				_getch();
				Gotoxy(X_ADD + 6, Y_ADD);
				cout << setw(35) << setfill(' ') << " ";
			}
		}while(!isNumber(idpass) || (int)(log10(atoi((char*)idpass.c_str())) + 1) != 9);
		
		int id = atoi((char*)idpass.c_str());
	
		for(int i = 0; i < fl->data.soLuongVe; i++)
		{
			if(fl->data.listTicket[i].CMND == id)
			{
				fl->data.listTicket[i].CMND = 0;
				fl->data.soVeDaBan--;
				Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Huy Ve thanh cong";
				_getch();
				return;
			}
		}
		
		Gotoxy(X_NOTIFY, Y_NOTIFY); cout << "Huy Ve that bai, CMND khong ton tai tren chuyen bay";
		_getch();
		return;
	}
	
	
	
}

// in danh sach hanh khach tren mot chuyen bay
void OutputStatisticPass(PASSENGER pa, char* nameTicket, int locate)
{
	DeleteOldData(sizeof(keyStaticPassenger) / sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << locate / 2;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << nameTicket;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << pa.CMND;
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << (string)pa.ho + " " + (string)pa.ten;
	Gotoxy(xKeyDisplay[4] + 1, Y_DISPLAY + 3 + locate);
	if (pa.phai == 1)cout << "Nam";
	else cout << "Nu";

}

void PrintListPassengerOnFlight(LIST_FLIGHT l, TREE_PASSENGER t)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[4] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	
	NODE_FLIGHT* fl = ChooseFlight(l);
	clrscr();
	if(fl->data.soVeDaBan == 0)
	{
		Gotoxy(X_NOTIFY, Y_NOTIFY);
		cout << "Chuyen bay nay khong co hanh khach";
		_getch();
		return;
	}
	string* arrTicket = new string[MAX_TICKET];
	PASSENGER arrPass[MAX_TICKET];
	int n = 0;
	
	for(int i = 0; i< fl->data.soLuongVe; i++)
	{
		if(fl->data.listTicket[i].CMND != 0)
		{
			arrPass[n] = FindPassenger(t, fl->data.listTicket[i].CMND)->data;
			strcpy((char*)arrTicket[n].c_str(), fl->data.listTicket[i].tenVe);
			
			n++;
		}
	}
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "DANH SACH HANH KHACH THUOC CHUYEN BAY ";
	Gotoxy(X_TITLE, Y_TITLE + 1); cout << "Ngay khoi hanh:" << fl->data.thoiGianDi.d << "/" << fl->data.thoiGianDi.m <<
	 "/" << fl->data.thoiGianDi.y << "." << " Noi den: " << (string)fl->data.sanBayDen;
	Display(keyStaticPassenger, sizeof(keyStaticPassenger) / sizeof(string));
	
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[7] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	for(int j = 0; j < n; j++)
	{
		OutputStatisticPass(arrPass[j], (char*)arrTicket[j].c_str() ,j * 2);
	}
	
	_getch();
	
}


void PrintListTicketUnBooked(LIST_FLIGHT l)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "CHON CHUYEN BAY";
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	DeleteNote(sizeof(keyDisplayFlight) / sizeof(string));
	
	NODE_FLIGHT* fl = ChooseFlight(l);
	
	if(fl == NULL)
	{
		return;
	}
	clrscr();
	Display(keyDisplayTicket, sizeof(keyDisplayTicket) / sizeof(string));
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 25);
	cout << setw(xKeyDisplay[7] - xKeyDisplay[0] - 1) << " " << setfill(' ');
	string* temp = new string[MAX_TICKET];
	int n = 0;
	for(int i = 0; i< fl->data.soLuongVe; i++)
	{
		if(fl->data.listTicket[i].CMND == 0)
		{
			temp[n++] = fl->data.listTicket[i].tenVe;
		}
	}
	Gotoxy(X_TITLE, Y_TITLE); cout << "Danh Sach Ve Trong Tren Chuyen Bay Co Ma La: " + (string)fl->data.maChuyenBay;
	int keyboard_read;
	pageNowTicket = 1;
	totalPageTicket = (n -1) / QUANTITY_PER_PAGE + 1;
	outputListTicketPerPage(temp, n, 0);
	while(true)
	{
		while(_kbhit())
		{
			keyboard_read = _getch();
			if (keyboard_read == 0)
				keyboard_read = _getch();
			switch (keyboard_read)
			{
			case PAGE_DOWN:
				if (pageNowTicket < totalPageTicket)
				{
					
					pageNowTicket++;
					ChangePageTicket(temp);
					Gotoxy(X_TITLE, Y_TITLE); cout << "Danh Sach Ve Trong Tren Chuyen Bay Co Ma La: " + (string)fl->data.maChuyenBay;
					outputListTicketPerPage(temp, n, (pageNowTicket - 1) * QUANTITY_PER_PAGE);
				
				}
				break;
			case PAGE_UP:
				if (pageNowTicket > 1)
				{
					
					pageNowTicket--;
					ChangePageTicket(temp);
					Gotoxy(X_TITLE, Y_TITLE); cout << "Danh Sach Ve Trong Tren Chuyen Bay Co Ma La: " + (string)fl->data.maChuyenBay;
					outputListTicketPerPage(temp, n, currposTicket);
					
				}
				break;
			case ESC:
				ShowCur(false);
				return ;
				break; // no choose
			}
		}	
	}
}

void Main_Menu(PTR_LIST_AIRPLANE &lal, LIST_FLIGHT &l, TREE_PASSENGER &t)
{
	int chon; 
	
	do
	{
		chon = MenuDong(thucdon);
		clrscr();
		switch(chon)
		{
			case 1: MenuManageAirplane(lal); break;
			case 2: MenuManageFlight(l, lal); break;
			case 3: MenuManagePassenger(t); break;
			case 4: BookticketIsSucced(l, lal, t); break;
			case 5: UnBookTicketIsSucced(l);break;
			case 6: PrintListPassengerOnFlight(l, t); break;
			case 7: PrintListTicketUnBooked(l);break;
			case 8: return;
		}
	}while(1);
}

#endif
