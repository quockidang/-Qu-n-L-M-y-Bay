#ifndef _PASSENGER_H
#define _PASSENGER_H

#include "datetime.h"
struct passenger{
	unsigned int CMND;
	char ho[20];
	char ten[10];
	int phai = 1;
	bool isBooked = false;
};
typedef struct passenger PASSENGER;

struct nodepassenger{
	PASSENGER data;
	struct nodepassenger *pLeft, *pRight;
};
typedef struct nodepassenger NODE_PASSENGER;
typedef NODE_PASSENGER* TREE_PASSENGER;

//khoi tao cay, cho chuong trinh hieu day la cay nhi phan rong
void InitTreePassenger(TREE_PASSENGER &t)
{
	nPassenger = -1;
	t = NULL;
}

//kiem tra cay nhi phan rong, return true=>cay rong
bool IsEmpty(TREE_PASSENGER t)
{
	if(t == NULL) return true;
	
	return false;
}

//kiem tra CMND co ton tai chua, retune true =>co ton tai
bool CheckIdIsExisted(TREE_PASSENGER t, unsigned int x)
{
	if (t != NULL)//co phan tu
	{
		if (t->data.CMND == x)//da ton tai
			return true;
		if (t->data.CMND > x)//x < t->_passenger.CMND
			CheckIdIsExisted(t->pLeft, x);//them x vao cay ben trai
		else
			CheckIdIsExisted(t->pRight, x);
	}
	return false;
}

//tim nut co gia tri la idPassenger tren cay nhi phan co goc la t, neu ko co thi them vao
//tim kiem nhi phan
NODE_PASSENGER* FindPassenger(TREE_PASSENGER t, unsigned int idPassenger)
{
	if (t != NULL)
	{
		NODE_PASSENGER* p = t;
		while (p != NULL)
		{
			if (p->data.CMND == idPassenger)
				return p;
			else if (p->data.CMND > idPassenger)
				p = p->pLeft;
			else
				p = p->pRight;
		}
	}
	return NULL;
}

//them vao => tao ra cay nhi phan tim kiem, co ap dung de quy 
void InsertPassengerToTree(TREE_PASSENGER &t, PASSENGER x)
{
	//tree empty, x is root of tree
	if (t == NULL)
	{
		NODE_PASSENGER* p = new NODE_PASSENGER;
		p->data = x;
		p->pLeft = p->pRight = NULL;
		t = p;
		arrPassengerId[++nPassenger] = x.CMND;
	}
	else
	{
		if (x.CMND < t->data.CMND)
			InsertPassengerToTree(t->pLeft, x);
		else if (x.CMND > t->data.CMND)
			InsertPassengerToTree(t->pRight, x);
	}
}

//hàm tìm node the mang de doi
void FindReplace(NODE_PASSENGER* &pDeleted, NODE_PASSENGER* &q)//node q la node the mang cho node can xoa, 														//node nay se tim ra node trai nhat (node trai nhat cua cay con phai)
{
	//duyet sang ben trai nhat
	if (q->pLeft != NULL)
	{
		FindReplace(pDeleted, q->pLeft);
	}
	else//da tim ra duoc node trai
	{
		pDeleted->data = q->data;//cap nhat data cua node q can xoa chinh la node pDeleted
		pDeleted = q;//cho node p(node se duoc xoa) tro den node the mang q => ra khoi ham nay se xoa node pDeleted
		q = q->pRight;//cap nhat lai moi lien ket cho node cha cua node the mang q (node ta se xoa) voi node con cua node the mang
//		q->pRight = NULL;// ko tro den NULL se bi loi 
	}
}

//xoa di 
bool IsDeletedPassenger(TREE_PASSENGER &t, PASSENGER x)
{
	if (t == NULL)
		return false;
	else
	{
		if (x.CMND > t->data.CMND)//x nhap vao lon hon node goc
			IsDeletedPassenger(t->pRight, x);//duyet sang nhanh phai cua cua cay
		else if (x.CMND < t->data.CMND)
			IsDeletedPassenger(t->pLeft, x);
		else // x.id = t->data.id => da tim ra ptu can xoa
		{
			//xoa node cay chi co 0 hoac 1 node con
			NODE_PASSENGER *temp = t;//node temp se la node bi xoa
			if (t->pLeft == NULL) //nhanh trai bang NULL => day la cay chi co 1 con la con phai
				//duyet sang phai cua node can xoa de cap nhap moi lien ket giua node cha cua node can xoa va node con cua node can xoa
				t = t->pRight;
			else if (t->pRight == NULL)
				t = t->pLeft;
			//xoa node cay chi co 0 hoac 1 node con
			else // node have 2 child
			{
				//way 2: rightest of left
				FindReplace(temp, t->pLeft);
			}
			delete temp;
			return true;
		}
	}
}

void OutputPassenger(PASSENGER p, int locate)
{
	DeleteOldData(sizeof(keyDisplayPassenger) / sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << p.CMND;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << p.ho;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); cout << p.ten;
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate);
	if (p.phai == 1)cout << "Nam";
	else cout << "Nu";
}

void OutputListPassengerPerPage(TREE_PASSENGER t, int thuTuBatDau)
{
	for (int i = 0; i + thuTuBatDau <= nPassenger && i < QUANTITY_PER_PAGE; i++)
	{
		NODE_PASSENGER* p = FindPassenger(t, arrPassengerId[i + thuTuBatDau]);
		OutputPassenger(p->data, i * 2);
	}
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowPassenger << "/" << totalPagePassenger;
}

void SetDefaultChosenPassenger(PASSENGER p, int ordinal)
{
	SetBGColor(1);
	OutputPassenger(p, ordinal % QUANTITY_PER_PAGE);
	SetBGColor(0);
}
void   EffectiveMenuPassenger(int index, PASSENGER newPassenger, PASSENGER oldPassenger)
{
	int current = index;
	SetBGColor(1);
	OutputPassenger(newPassenger, (current % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0);
	OutputPassenger(oldPassenger, (currposPrecPassenger % QUANTITY_PER_PAGE) * 2);
	currposPrecPassenger = current;
}

void ChangePagePassenger(TREE_PASSENGER t)
{
	currposPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	currposPrecPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	clrscr();
	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	DeleteNote(sizeof(keyDisplayPassenger) / sizeof(string));
}

NODE_PASSENGER* ChoosePassenger(TREE_PASSENGER &t)
{
	if (t == NULL) return NULL;
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	int PASS = 1;

	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	pageNowPassenger = 1;
	currposPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	currposPrecPassenger = (pageNowPassenger - 1) * QUANTITY_PER_PAGE;
	NODE_PASSENGER* newPassenger = FindPassenger(t, arrPassengerId[0]);
	OutputListPassengerPerPage(t, 0);
	SetDefaultChosenPassenger(newPassenger->data, currposPassenger);
	NODE_PASSENGER* oldPassenger = NULL;
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "trang " << pageNowPassenger << "/" << totalPagePassenger;

	while (PASS)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();

		switch (keyboard_read)
		{


		case KEY_UP:
			if (currposPassenger % QUANTITY_PER_PAGE > 0)
			{
				currposPassenger = currposPassenger - 1;
				oldPassenger = newPassenger;
				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				EffectiveMenuPassenger(currposPassenger, newPassenger->data, oldPassenger->data);
			}
			break;
		case KEY_DOWN:
			if (currposPassenger % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposPassenger < nPassenger)
			{
				currposPassenger = currposPassenger + 1;
				oldPassenger = newPassenger;
				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				EffectiveMenuPassenger(currposPassenger, newPassenger->data, oldPassenger->data);
			}
			break;


		case PAGE_DOWN:
			if (pageNowPassenger < totalPagePassenger)
			{
				pageNowPassenger++;
				ChangePagePassenger(t);

				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				oldPassenger = newPassenger;


				OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
				SetDefaultChosenPassenger(newPassenger->data, currposPassenger);


			}
			break;
		case PAGE_UP:
			if (pageNowPassenger > 1)
			{

				pageNowPassenger--;
				ChangePagePassenger(t);

				newPassenger = FindPassenger(t, arrPassengerId[currposPassenger]);
				oldPassenger = newPassenger;


				OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
				SetDefaultChosenPassenger(newPassenger->data, currposPassenger);

			}
			break;


		case ENTER:  //enter
			PASS = 0;
			ShowCur(true);
			return newPassenger;
			break;
		case ESC:
			ShowCur(true);
			return NULL;
			break;
		}
	}
}




void InputPassenger(TREE_PASSENGER &t, PASSENGER &pa, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;

	unsigned int id = 0;
	string firstName, lastName;
	int sex = 0;
	bool idIsExist = false;
	Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
	cout << "1: Nam 2: Nu";
	if (isEdited)
	{
		id = pa.CMND;
		firstName = pa.ho;
		lastName = pa.ten;
		sex = pa.phai;

		Gotoxy(X_ADD + 10, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 10, 1 * 3 + Y_ADD);
		cout << firstName;
		Gotoxy(X_ADD + 10, 2 * 3 + Y_ADD);
		cout << lastName;
		Gotoxy(X_ADD + 10, 3 * 3 + Y_ADD);
		cout << sex;
	}
	while (true)
	{
		switch (ordinal)
		{
		case 0:
		{
			if (isEdited) break;
			CheckMoveAndValidateIdentityCard(id, isMoveUp, ordinal, isSave, 10);

			if (FindPassenger(t, id) == NULL)
			{
				idIsExist = false;
				break;
			}
			idIsExist = true;
			break;
		}

		case 1:
			CheckMoveAndValidateName_1(firstName, isMoveUp, ordinal, isSave, 10, 20);
			break;
		case 2:
			CheckMoveAndValidateName_1(lastName, isMoveUp, ordinal, isSave, 10, 10);
			break;
		case 3:
			CheckMoveAndValidateNumber(sex, isMoveUp, ordinal, isSave, 10, 2);
			break;
		}

		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false;
			ordinal--;

		}
		else
		{
			if (ordinal == 4)
				isMoveUp = true;
			ordinal++;
		}
		if (isSave)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if (firstName.empty() || lastName.empty() || sex == 0 || int((log10(id) + 1)) != 9)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "ID khong duoc trung";
			}
			else
			{
				pa.CMND = id;
				strcpy(pa.ho, firstName.c_str());
				strcpy(pa.ten, lastName.c_str());
				pa.phai = sex;

				StandardName(pa.ho);
				StandardName(pa.ten);
				if (isEdited)
				{
					NODE_PASSENGER* p = FindPassenger(t, id);
					p->data = pa;
					int index = 0;
					while (index <= nPassenger && arrPassengerId[index] != pa.CMND) index++;

				}
				else
				{
					InsertPassengerToTree(t, pa);

				}
				DeleteMenuAdd();
				Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
				cout << "                    ";
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);

}

void MenuManagePassenger(TREE_PASSENGER &t)
{
	
backMenu:
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << " QUAN LY HANH KHACH ";
	Gotoxy(X_PAGE, Y_PAGE);
	totalPagePassenger = nPassenger / QUANTITY_PER_PAGE + 1;
	pageNowPassenger = 1;

	Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
	OutputListPassengerPerPage(t, 0);
	int key;
	while (true)
	{
		while (_kbhit())
		{
			
			cout << "trang " << pageNowPassenger << "/" << totalPagePassenger;
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << setw(35) << setfill(' ') << " ";
				if (key == KEY_F2) //f2
				{
					PASSENGER pa;
					DisplayEdit(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string), 35);
					InputPassenger(t, pa);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
					totalPagePassenger = nPassenger / QUANTITY_PER_PAGE + 1;
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
				}
				else if (key == KEY_F3) //f3
				{
					clrscr();
					NODE_PASSENGER* k = ChoosePassenger(t);
					if (k == NULL) goto backMenu;

					if (k->data.isBooked)
					{
						Gotoxy(X_NOTIFY, Y_NOTIFY);
						cout << "Nguoi nay dang giu ve. K xoa duoc";
						key = _getch();
						DeleteNotify();
						goto backMenu;
					}

					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					if (key == ENTER)
					{
						clrscr();
						Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
						for (int i = 0; i <= nPassenger; i++)
						{
							if (arrPassengerId[i] == k->data.CMND)
							{
								for (int j = i; j < nPassenger; j++)
									arrPassengerId[j] = arrPassengerId[j + 1];
								nPassenger--;
								break;
							}
						}
						if (IsDeletedPassenger(t, k->data))
						{
							OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						}
						/*IsDeletedPassenger(t, k->data);
						indexOutPassenger = -1;
						OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);*/
					}
					else
						goto backMenu;


				}
				else if (key == KEY_F4) //f4
				{
					NODE_PASSENGER* k = ChoosePassenger(t);
					if (k == NULL) goto backMenu;
					DisplayEdit(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string), 35);
					InputPassenger(t, k->data, true);
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);

				}
				else if (key == PAGE_DOWN && pageNowPassenger < totalPagePassenger)
				{
					system("cls");
					pageNowPassenger++;
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
					Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
				}
				else if (key == PAGE_UP && pageNowPassenger > 1)
				{
					system("cls");
					pageNowPassenger--;
					OutputListPassengerPerPage(t, (pageNowPassenger - 1) * QUANTITY_PER_PAGE);
					Display(keyDisplayPassenger, sizeof(keyDisplayPassenger) / sizeof(string));
				}
			}
			else if (key == ESC)
				return;
		}
	}
}

#endif



