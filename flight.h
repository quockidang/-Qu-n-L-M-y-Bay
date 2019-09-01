#ifndef _FLIGHT_H
#define _FLIGHT_H
#include "airplane.h"
//#include "passenger.h"
#include "ticket.h"
#include "datetime.h"
#include <sstream>

// cau trúc chuyen bay
struct Flight
{
	char maChuyenBay[16]; // ma chuyen bay
	char sanBayDen[31]; // san bay den
	char soHieuMayBay[16];
	DateTime thoiGianDi; // ngay gio khoi hanh
	
	int soLuongVe = 0; // so luong ve
	int  soVeDaBan = 0; // so luong ve da ban
	int trangThai = STT_REMAIN_TICKET;//trag thai chuyen bay
	Ticket *listTicket = new TICKET[MAX_TICKET];//mang con tro
};
typedef struct Flight FLIGHT;

// khai báo cau truc mot cai node chuyen bay
struct NodeFlight
{
	FLIGHT data;
	struct NodeFlight *pNext;
};
typedef struct NodeFlight NODE_FLIGHT;

//Danh sach chuyen bay
struct ListFlight
{
	int n = 0;
	NODE_FLIGHT *pHead, *pTail;
};
typedef struct ListFlight LIST_FLIGHT;

//khoi tao danh sach lien ket don
void InitListFlight(LIST_FLIGHT &l)
{
	l.pHead = l.pTail = NULL;
}

//khoi tao 1 cai nodeFight de them vao danh sach
NODE_FLIGHT* GetNodeFlight(FLIGHT DATA)
{
	NODE_FLIGHT *p = new NODE_FLIGHT; //cap phat 1 NODE_FLIGHT cho dslk, tra ve dia chi cho nut vua cap phat
	if (p == NULL)
	{
		cout<<"Cap phat vung nho that bai!";
		return NULL;
	}		
	p->data = DATA; // dua DATA vao data cua p
	p->pNext = NULL;//node p chua co lien ket voi node nao het
	return p;
}

//kiem tra chuyen bay co rong hay ko
bool ListFlightIsEmpty(ListFlight l)
{
	return l.pHead == NULL;
}

//them vao dau LIST_FLIGHT
void AddHeadListFlight(LIST_FLIGHT &l, FLIGHT data)
{
	NODE_FLIGHT* p = GetNodeFlight(data);//khoi tao 1 cai node co gia tri la data
	p->pNext = l.pHead;//con tro pNext cua p tro den con tro dau tien cua LISTFLIGHT
	l.pHead = p;//con tro p la con tro dau cua LISTFLIGHT
	++l.n;
}

//them vao cuoi
void AddTailListFlight(LIST_FLIGHT &l, FLIGHT data)
{
	NODE_FLIGHT *p = GetNodeFlight(data);
	if (l.pHead == NULL)//chua co ptu nao
		l.pHead = l.pTail = p;
	else//da co ptu
	{
		l.pTail->pNext = p;
		l.pTail = p;
	}
	++l.n;
}

//them vao sau p
void InsertAfter(NODE_FLIGHT* p, FLIGHT &data)
{
	if (p == NULL) return;//rong
	NODE_FLIGHT* q = new NODE_FLIGHT;
	q->data = data;//gan data nhap vao vao data cua q
	q->pNext = p->pNext;//tao moi lien he giua q va p deu tro den con tro phia sau
	p->pNext = q;
}

//them FLIGHT data vao LIST_FLIGHT co thu tu => &l co thu tu
void InsertOrderForListFlight(LIST_FLIGHT &l, FLIGHT data)
{
	if(l.pHead == NULL)//chua co ptu nao => them vao dau danh sach
	{	
		AddHeadListFlight(l, data);
		return;
	}
	
	NODE_FLIGHT *p, *pAfter, *pBefore;
	
	p = GetNodeFlight(data);//khoi tao node p moi co vung nho, co gia tri data
	
	//pAfter = pBefore->pNext;
	
	//maChuyenBay cua pAfter be hon maChuyenBay nhap vao
	for(pAfter = l.pHead; pAfter != NULL && (stricmp(pAfter->data.maChuyenBay, data.maChuyenBay) < 0); pBefore = pAfter, pAfter = pAfter->pNext);
	if(pAfter == l.pHead) //them dau
		AddHeadListFlight(l, p->data);
	else // them nut p vao truoc nut s
	{
		p->pNext = pAfter;
		pBefore->pNext = p;
		++l.n;
	}
}

//tim Flight theo maChuyenBay (id) trong LIST_FLIGHT
NODE_FLIGHT* FindFlight(LIST_FLIGHT l, char *id)
{
	if (l.pHead == NULL) return NULL;//rong
	for (NODE_FLIGHT *p = l.pHead ; p != NULL; p = p->pNext)
		if (_strcmpi(p->data.maChuyenBay, id) == 0)
			return p;
	return NULL;
}

//tim Flight theo thu tu truyen vao
NODE_FLIGHT* FindFlightByOridnal(LIST_FLIGHT l, int thuTu )
{
	if (l.pHead == NULL) return NULL;//rong
	if (l.n -1 < thuTu) return NULL;
	if (thuTu == 0) return l.pHead;//dung dau
	if (l.n - 1 == thuTu) return l.pTail;//dung cuoi
	
	/*int count = -1;
	for (NODE_FLIGHT *p = l.pHead; p != NULL; p = p->pNext)
	{
		++count;
		if (count == ordinal) return p;
	}*/
	NODE_FLIGHT *p = l.pHead;
	int count = 0;
	while (count != thuTu)//count == thuTu thi thoat khoi vong lap => tim ra duoc p
	{
		p = p->pNext;
		count++;
	}
	return p;
}

//tim vitri Flight dua vao id
int FindIndexFlight(LIST_FLIGHT l, char *id)
{
	int index = -1;
	if (l.pHead == NULL) return -1;//rong
	for (NODE_FLIGHT *p = l.pHead; p != NULL; p = p->pNext)
	{
		index++;
		if (_strcmpi(p->data.maChuyenBay, id) == 0)
			return index;
	}
	return 0;
}

//nhap Thoi gian
void InputDatime(DATETIME &dt)
{
	int newOrdinal = 0;
	bool newIsMoveUp = false;
	bool newIsSave = false;
	Gotoxy(X_ADD + 12 + 2, 3 * 2 + Y_ADD);
	cout << ":";
	Gotoxy(X_ADD + 12 + 8, 3 * 2 + Y_ADD);
	cout << "/";
	Gotoxy(X_ADD + 12 + 11, 3 * 2 + Y_ADD);
	cout << "/";
	while (true)
	{
 		switch (newOrdinal)
		{
		case 0://check gio
			CheckMoveAndValidateDateTime(dt.h, newIsMoveUp, newOrdinal, newIsSave, 23, 12);
			break;
		case 1://check phut
			CheckMoveAndValidateDateTime(dt.mi, newIsMoveUp, newOrdinal, newIsSave, 59, 12);
			break;
		case 2://check ngay
			CheckMoveAndValidateDateTime(dt.d, newIsMoveUp, newOrdinal, newIsSave, 31, 12);
			break;
		case 3://check thang
			CheckMoveAndValidateDateTime(dt.m, newIsMoveUp, newOrdinal, newIsSave, 12, 12);
			break;
		case 4://check nam
			CheckMoveAndValidateDateTime(dt.y, newIsMoveUp, newOrdinal, newIsSave, 10000, 12);
			break;
		} // end switch newordinal
		
		//check move
		if (newIsMoveUp)
		{
			if (newOrdinal == 0)
				newIsMoveUp = false;
			else
				newOrdinal--;
		}
		else
		{
			if (newOrdinal == 4)
			{
				newIsMoveUp = true;
				return;
			}
			else
				newOrdinal++;
		}
		//--end check move

		if (newIsSave)
			return;
		else
			newIsSave = false;
	} // end while
}

//xoa dau
bool IsDeletedHead(LIST_FLIGHT &l)
{
	if (ListFlightIsEmpty(l)) return false;//rong
	NODE_FLIGHT* p = l.pHead;//khoi tao con tro o tro den ptu dau tien cua danh sach, node p la node can xoa
	l.pHead = l.pHead->pNext; //cap nhat la pHead la node tiep theo
	delete p;
	--l.n;
	return true;
}

////xoa cuoi
bool IsDeletedTail(LIST_FLIGHT &l)
{
	if (ListFlightIsEmpty(l)) return false;
		for(NODE_FLIGHT *p=l.pHead;p!=NULL;p=p->pNext){
			if(p->pNext == l.pTail){
				delete l.pTail;
				p->pNext = NULL;
				l.pTail = p;
				l.n--;
				return true;	
			}
		}		
}

//xoa cuoi
//bool IsDeletedTail(LIST_FLIGHT &l){
//	if(ListFlightIsEmpty(l)) return false;
//	else{
//		if(l.pHead == NULL){
//			IsDeletedHead(l); 
//		}
//		else{
//			NODE_FLIGHT *pBefore = new NODE_FLIGHT;
//			for(pBefore= l.pHead;pBefore!=NULL;pBefore=pBefore->pNext){
//				if(pBefore->pNext = l.pTail){
//					delete l.pTail;
//					pBefore->pNext = NULL;
//					l.pTail=pBefore;
//					l.n--;
//					return true;
//				}
//			}
//		}
//	}
//}


//xoa node phia sau node p
bool IsDeletedAfter(LIST_FLIGHT &l, NODE_FLIGHT*p)
{
	if (p == NULL || p->pNext == NULL) return false;
	NODE_FLIGHT* nodeDeleted = p->pNext;//nodeDeleted nam sau node p
	p->pNext = nodeDeleted->pNext;
	delete nodeDeleted;
	--l.n;
	return true;
}

//xoa chuyen bay voi maChuyenBay nhap vao
bool IsDeletedFlightWithId(LIST_FLIGHT &l, Flight data)
{
	NODE_FLIGHT* nodeDeleted = FindFlight(l, data.maChuyenBay);
	if (nodeDeleted == NULL) return false;
	if (nodeDeleted == l.pHead) return IsDeletedHead(l);
	if (nodeDeleted == l.pTail) return IsDeletedTail(l);
	else
	{
		NODE_FLIGHT* temp = l.pHead;
		while (temp->pNext != nodeDeleted)
			temp = temp->pNext;
		return IsDeletedAfter(l,temp);
	}
}

//xoa tat ca cac chuyen bay
bool ClearListFlight(LIST_FLIGHT &l)
{
	if (l.pHead) return false;
	NODE_FLIGHT* temp;
	while (l.pHead != NULL)
	{
		temp = l.pHead;
		l.pHead = l.pHead->pNext;
		delete temp;
	}
	return true;
}

//thay doi trang thai chuyen bay
void AutoChangeSttFlight(LIST_FLIGHT &l)
{
	for (NODE_FLIGHT* p = l.pHead ; p != NULL; p = p->pNext)
		if (!DateTimeIsValid(p->data.thoiGianDi)) 
			p->data.trangThai = STT_FINISHED;//trangThai =3 => Hoan tat
}

//tim soHieuMayBay trong ListFlight
void FindnumAironListFlight(LIST_FLIGHT l, LIST_FLIGHT &temp, char* numAir)
{
	for(NODE_FLIGHT* p = l.pHead; p != NULL; p = p->pNext)
	{
		if(stricmp(p->data.soHieuMayBay, numAir) == 0)
		{
			InsertOrderForListFlight(temp, p->data);
		}
	}
}


void OutputFlight(FLIGHT fl, int locate)
{
	DeleteOldData(sizeof(keyDisplayFlight) / sizeof(string), locate);
	Gotoxy(xKeyDisplay[0] + 1, Y_DISPLAY + 3 + locate); cout << fl.maChuyenBay;
	Gotoxy(xKeyDisplay[1] + 1, Y_DISPLAY + 3 + locate); cout << fl.soHieuMayBay;
	Gotoxy(xKeyDisplay[2] + 1, Y_DISPLAY + 3 + locate); OutputDateTime(fl.thoiGianDi);
	Gotoxy(xKeyDisplay[3] + 1, Y_DISPLAY + 3 + locate); cout << fl.sanBayDen;
	Gotoxy(xKeyDisplay[4] + 1, Y_DISPLAY + 3 + locate);
	switch (fl.trangThai)
	{
	case 0: cout << "Da Huy";
		break;
	case 1: cout << "Con ve";
		break;
	case 2: cout << "Het ve";
		break;
	case 3: cout << "Hoan tat";
		break;
	default:
		break;
	}
	Gotoxy(xKeyDisplay[5] + 1, Y_DISPLAY + 3 + locate); cout << fl.soLuongVe;
}


void OutputListFlight(LIST_FLIGHT l)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	AutoChangeSttFlight(l);
	for (NODE_FLIGHT* q = l.pHead; q != NULL; q = q->pNext)
	{
		count++;
		OutputFlight(q->data, count);
	}
}

//in ra danh sach may bay tren 1 trang
void OutputListFlightPerPage(LIST_FLIGHT l, int viTriBatDau)
{
	if (l.pHead == NULL && l.pTail == NULL) return;
	int count = -1;
	//AutoChangeSttFlight(l);
	for (NODE_FLIGHT* q = l.pHead; q != NULL; q = q->pNext)
	{
		count++;
		if (count == viTriBatDau)
		{
			int i = -1; 
			while (q != NULL && i < QUANTITY_PER_PAGE - 1)
			{
				OutputFlight(q->data, (++i) * 2);
				q = q->pNext;
			}
			break;
		}	
	}
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowFlight << "/" << totalPageFlight;
	return;
}

//kiem tra du lieu nhap vao ko duoc rong, return false => nhap du
bool DataFlightIsEmpty(FLIGHT fl)
{
	if (strlen(fl.maChuyenBay) == 0) return true;
	if (strlen(fl.sanBayDen) == 0) return true;
	if (fl.soLuongVe <= 0) return true;
	return false;
}

//tao Ghe
string* CreateArrTicket(int soday, int sodong)
{
	int totalTicket = soday * sodong;
	string* arr = new string[totalTicket];
	int n = 0;
	for(int i = 0; i < soday; i++)
	{
		for(int j =1; j <= sodong; j++)
		{
			if(j < 10)
			{
				ostringstream str; 
				ostringstream str1; 
				str << char(65 + i);
				string temp = str.str();
				
				
				temp += "0";
				str1 << j;
				temp += str1.str();
				arr[n++] = temp;
			}				
			else
			{
				ostringstream str2, str3; 
				str2 << char(65 + i);
				string temp1= str2.str();
				str3 << j;
				temp1 += str3.str();
				arr[n++] = temp1;
			}		
		}
	}
	return arr;
}

//LIST_FLIGHT
void InputFlight(LIST_FLIGHT &l, PTR_LIST_AIRPLANE lal,  FLIGHT &fl, bool isEdited = false)
{
	ShowCur(true);
	int ordinal = 0;
	bool isMoveUp = false;
	bool isSave = false;
	bool idIsExist = false;
	string id, numAir;
	DateTime dt;
	string destiny;
	int stt = STT_REMAIN_TICKET;
	Gotoxy(X_NOTIFY, Y_NOTIFY + 1);
	cout << "F10 luu ngay gio";
	Gotoxy(X_NOTIFY - 10, Y_NOTIFY + 2);
	cout << "Trang thai: 1:Con ve 2:Het ve 3:Hoan tat 4:Huy chuyen";

	if (isEdited)
	{
		//binding data
		id = fl.maChuyenBay;
		dt = fl.thoiGianDi;
		destiny = fl.sanBayDen;
		stt = fl.trangThai;
		numAir = fl.soHieuMayBay;
		//format datetime
		Gotoxy(X_ADD + 12 + 2, 2 * 3 + Y_ADD);
		cout << ":";
		Gotoxy(X_ADD + 12 + 8, 2 * 3 + Y_ADD);
		cout << "/";
		Gotoxy(X_ADD + 12 + 11, 2 * 3 + Y_ADD);
		cout << "/";

		//out datetime
		Gotoxy(X_ADD + 12 + 0 * 3, 2 * 3 + Y_ADD);
		cout << dt.h;
		Gotoxy(X_ADD + 12 + 1 * 3, 2 * 3 + Y_ADD);
		cout << dt.mi;
		Gotoxy(X_ADD + 12 + 2 * 3, 2 * 3 + Y_ADD);
		cout << dt.d;
		Gotoxy(X_ADD + 12 + 3 * 3, 2 * 3 + Y_ADD);
		cout << dt.m;
		Gotoxy(X_ADD + 12 + 4 * 3, 2 * 3 + Y_ADD);
		cout << dt.y;

		//out data
		Gotoxy(X_ADD + 15, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 15, 1 * 3 + Y_ADD);
		cout << numAir;
		Gotoxy(X_ADD + 15, 3 * 3 + Y_ADD);
		cout << destiny;
		Gotoxy(X_ADD + 15, 4 * 3 + Y_ADD);
		cout << stt;
	}
	while (true)
	{
		//input
		switch (ordinal)
		{
			case 0:
			{	if(isEdited) break;			
				CheckMoveAndValidateID(id, isMoveUp, ordinal, isSave, 15);			
				if (FindFlight(l, (char *)id.c_str()) == NULL)
				{
					idIsExist = false;
					break;
				}
				idIsExist = true;
				break;
			}
			case 1:
			{
				CheckMoveAndValidateID(numAir, isMoveUp, ordinal, isSave, 15);
				break;			
			}					
			case 2:
			{
				InputDatime(dt);
				break;
			}
			case 3:
			{
				CheckMoveAndValidateName_1(destiny, isMoveUp, ordinal, isSave, 15, 20);
				break;
			}
			case 4:
			{
				CheckMoveAndValidateNumber(stt, isMoveUp, ordinal, isSave, 15, 4);
				break;
			}
		}//end switch

		 //--move
		if (isMoveUp)
		{
			if (ordinal == 0)
				isMoveUp = false; //block move up
			ordinal--;
		}
		else
		{
			if (ordinal == 4)
				isMoveUp = true; //block move down
			ordinal++;
		}
		//--end move

		if (isSave)
		{
			//binding data
			strcpy(fl.maChuyenBay, id.c_str());
			strcpy(fl.soHieuMayBay, numAir.c_str());
			fl.thoiGianDi = dt;
			strcpy(fl.sanBayDen, destiny.c_str());
			fl.trangThai = stt;
			PTR_AIRPLANE al = FindAirplane(lal, fl.soHieuMayBay);//tim Airplane dua vao soHieuMayBay
			if(al != NULL)
			{
				fl.soLuongVe = (al->soDong * al->soDay);
				string* arrTicket = new string[fl.soLuongVe];
				arrTicket = CreateArrTicket(al->soDay, al->soDong);
				for(int i = 0; i < fl.soLuongVe; i++)
				{
					strcpy(fl.listTicket[i].tenVe, (char*)arrTicket[i].c_str());
				}
				
			} //co ton tai may bay nay
			
			//kiem tra 1 chuyen bay co chung soHieuMayBay ko duoc trung thoi gian di 	
			LIST_FLIGHT temp;
			InitListFlight(temp);
			FindnumAironListFlight(l, temp, fl.soHieuMayBay);//tim so hieu trong danh sach chuyen bay => them vao LIST_FLIGHT temp
			bool flag = false;
			for(NODE_FLIGHT* p = temp.pHead; p != NULL; p = p->pNext)
			{
				if(p->data.thoiGianDi.y == fl.thoiGianDi.y && p->data.thoiGianDi.m == fl.thoiGianDi.m 
							&&  p->data.thoiGianDi.d == fl.thoiGianDi.d && p->data.thoiGianDi.h == fl.thoiGianDi.h
								&& p->data.thoiGianDi.mi == fl.thoiGianDi.mi){
									
					flag = true;
					break;
				}
			}
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";
			if(flag==true && !isEdited)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ngay gio khong hop le. ";
			}
			else if (!DateTimeIsValid(fl.thoiGianDi))
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ngay gio khong hop le. Phai lon hon gio he thong";
			}
			else if(al == NULL)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "May bay khong ton tai";
			}
			else if (DataFlightIsEmpty(fl))
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Cac truong du lieu khong dc de trong";
			}
			else if (idIsExist)
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma chuyen bay khong duoc trung";
			}		
			else
			{
				StandardName(fl.sanBayDen);
				if (isEdited)//duoc sua
				{
					NODE_FLIGHT* p = FindFlight(l, fl.maChuyenBay);
					p->data = fl;
					//int index = FindIndexFlight(l, fl.id);
					//OutputFlight(p->data, (index % QUANTITY_PER_PAGE) * 2);
					/*DeleteMenuAdd();
					return;*/
				}
				else
				{
					InsertOrderForListFlight(l, fl);
					//int index = FindIndexFlight(l, fl.id);
					//OutputFlight(fl, (index % QUANTITY_PER_PAGE) * 2);
					/*DeleteMenuAdd();
					return;*/
				}
				totalPageFlight = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
				DeleteMenuAdd();
				ClearListFlight(temp);//giai phong vung nho
				return;
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);
}
void SetDefaultChosenFlight(FLIGHT fl, int ordinal)
{
	SetBGColor(1);
	OutputFlight(fl, (ordinal % QUANTITY_PER_PAGE) * 2);
	SetBGColor(0);
}
void   EffectiveMenuFlight(int ordinal, FLIGHT flNew, FLIGHT flOld)
{
	int current = ordinal;
	SetDefaultChosenFlight(flNew, current);

	/*SetBGColor(GREEN);
	OutputFlight(flNew, (current % QUANTITY_PER_PAGE) * 2);
	SetBGColor(PURPLE);*/
	OutputFlight(flOld, (currposPrecFlight % QUANTITY_PER_PAGE) * 2);
	currposPrecFlight = current;
}

void ChangePageChooseFlight(LIST_FLIGHT l)
{
	system("cls");
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
	currposFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	currposPrecFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	
}

NODE_FLIGHT* ChooseFlight(LIST_FLIGHT l)
{
	int keyboard_read = 0;
	ShowCur(false);
	pageNowFlight = 1;
	currposFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	currposPrecFlight = (pageNowFlight - 1) * QUANTITY_PER_PAGE;
	totalPageFlight = ((l.n-1) / QUANTITY_PER_PAGE) + 1;
	
	NODE_FLIGHT* newNodeFlight = FindFlightByOridnal(l, currposFlight);
	NODE_FLIGHT* oldNodeFilght = NULL;
	
	OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
	SetDefaultChosenFlight(newNodeFlight->data, currposFlight);
	while (true)
	{
		keyboard_read = _getch();
		if (keyboard_read == 0)
			keyboard_read = _getch();
		switch (keyboard_read)
		{
		case KEY_UP:
			if (currposFlight % QUANTITY_PER_PAGE > 0)
			{
				currposFlight = currposFlight - 1;
				oldNodeFilght = newNodeFlight;
				for (newNodeFlight = l.pHead; newNodeFlight->pNext != oldNodeFilght; newNodeFlight = newNodeFlight->pNext);
				EffectiveMenuFlight(currposFlight, newNodeFlight->data, oldNodeFilght->data);
			}
			break;
		case KEY_DOWN:
			if (currposFlight  % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && newNodeFlight->pNext != NULL) //&& currposFlight < 3)
			{
				currposFlight = currposFlight + 1;
				oldNodeFilght = newNodeFlight;
				newNodeFlight = newNodeFlight->pNext;
				EffectiveMenuFlight(currposFlight, newNodeFlight->data, oldNodeFilght->data);
			}
			break;
		
		case PAGE_DOWN:
			if (pageNowFlight < totalPageFlight)
			{

				pageNowFlight++;
				ChangePageChooseFlight(l);
				OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
				newNodeFlight = FindFlightByOridnal(l, currposFlight);
				SetDefaultChosenFlight(newNodeFlight->data, currposFlight);
				
			}
			break;
		case PAGE_UP:
			if (pageNowFlight > 1)
			{
				pageNowFlight--;	
				ChangePageChooseFlight(l);
				OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
				newNodeFlight = FindFlightByOridnal(l, currposFlight);
				SetDefaultChosenFlight(newNodeFlight->data, currposFlight);
				
			}
			break;


		case ENTER:  //enter
			ShowCur(true);
			return newNodeFlight;
			break;
		case 27: 
			return NULL; 
			break;
		}//end switch  read key
	}
}

void ChangePageManageFlight(LIST_FLIGHT l)
{
	system("cls");
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY!";
	OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
}
void MenuManageFlight(LIST_FLIGHT &l, PTR_LIST_AIRPLANE lal)
{
backMenu:
	system("cls");
	pageNowFlight = 1;
	OutputListFlightPerPage(l, 0);
	Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));

	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY";
	int key;
	while (true)
	{
		while (_kbhit())
		{
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				
				if (key == KEY_F2) //f2
				{
					FLIGHT fl;
					DisplayEdit(keyDisplayAddFlight, sizeof(keyDisplayAddFlight) / sizeof(string), 35);
					InputFlight(l, lal, fl, false);
					
					OutputListFlightPerPage(l, (pageNowFlight - 1) / QUANTITY_PER_PAGE);
					//ChangePageManageFlight(l);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong";
					
					//OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
				}
				else if (key == KEY_F3) //f3
				{	
					NODE_FLIGHT* k = ChooseFlight(l);
					if (k == NULL) goto backMenu;
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y";
					key = _getch();
					if (key == ENTER)
					{
						if (k->data.soVeDaBan  != 0)
						{
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Khong xoa duoc vi da co nguoi dat ve";
							_getch();
							goto backMenu;
						}
						if (IsDeletedFlightWithId(l, k->data))
						{
							totalPageFlight = ((l.n - 1) / QUANTITY_PER_PAGE) + 1;
							//pageNowFlight = 1;
							if (l.n % QUANTITY_PER_PAGE == 0) pageNowFlight--;
							ChangePageManageFlight(l);
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";	
						}

						/*system("cls");
						Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));
						IsDeletedFlightWithId(l, k->data);
						
						OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);*/
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4) //f4
				{
					
					NODE_FLIGHT* k = ChooseFlight(l);
					if (k == NULL) goto backMenu;
					DisplayEdit(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string), 35);
					InputFlight(l, lal, k->data, true);
					OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Sua thanh cong";
				}
				else if (key == PAGE_DOWN && pageNowFlight < totalPageFlight)
				{
					pageNowFlight++;
					ChangePageManageFlight(l);	
				}
				else if (key == PAGE_UP && pageNowFlight > 1)
				{
					pageNowFlight--;
					ChangePageManageFlight(l);

					/*system("cls");
					Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC CHUYEN BAY";
					OutputListFlightPerPage(l, (pageNowFlight - 1) * QUANTITY_PER_PAGE);
					Display(keyDisplayFlight, sizeof(keyDisplayFlight) / sizeof(string));*/
				}
			}
			else if (key == ESC)
				return;
		}//end while kbhit
	}
}
#endif

