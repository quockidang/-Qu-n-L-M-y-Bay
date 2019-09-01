#ifndef _AIRPLANE_H
#define _AIRPLANE_H
#include "validate.h"
#include "globalvariable.h"

//cau truc may bay
struct Airplane
{
	char soHieuMayBay[16];//soHieuMayBay
	char loaiMayBay[41];//loaiMaybay
	int soDay;//soDay
	int soDong;//soDong
};
typedef struct Airplane AIRPLANE;
typedef AIRPLANE* PTR_AIRPLANE;

//cau truc danh sach may bay => mang con tro
struct ListAirplane
{
	int n = -1; //so luong ptu 
	PTR_AIRPLANE *listAirplane = new PTR_AIRPLANE[MAX_AIRPLANE];//khoi tao mang con tro listAirplane co so luong ptu MAX_AIRPLANE
};
typedef struct ListAirplane LIST_AIRPLANE;
typedef LIST_AIRPLANE* PTR_LIST_AIRPLANE;

//tim May bay theo So hieu may bay nhap vao
PTR_AIRPLANE FindAirplane(PTR_LIST_AIRPLANE l, char soHieuMayBayCanTim[])
{
	if (l->n < 0) return NULL;//danh sach rog
	for (int i = 0; i <= l->n; i++)//duyet danh sach
		if (_stricmp(l->listAirplane[i]->soHieuMayBay, soHieuMayBayCanTim) == 0) //So hieu may bay cua ptu thu i trong mang con tro trung voi id nhap vao
			return l->listAirplane[i];//tim ra dia chi cua con tro nay
	return NULL;
}

//tim Vi tri may bay theo So hieu may bay da nhap vao
int FindIndexAirplane(PTR_LIST_AIRPLANE l, char soHieuMayBayCanTim[])
{
	if (l->n < 0) return -1;
	for (int i = 0; i <= l->n; i++)
		if (_strcmpi(l->listAirplane[i]->soHieuMayBay, soHieuMayBayCanTim) == 0) 
			return i;
	return -1;
}

//kiem tra dieu kien phai nhap du moi xac nhan thanh cong, return false la thoa dieu kien => xac nhan nhap du
bool DataAirplaneIsEmpty(PTR_AIRPLANE al)
{
	if (strlen(al->soHieuMayBay) == 0 || strlen(al->loaiMayBay) == 0) return true;
	if (al->soDay == 0 || al->soDong == 0) return true;
	return false;
}

//doi vi tri 2 chuyen bay
void SwapAirplane(PTR_AIRPLANE &a, PTR_AIRPLANE &b)
{
	PTR_AIRPLANE temp = a;
	a = b;
	b = temp;
}

//xac nhan xoa thanh cong hay that bai => return true la xoa thanh cong
bool DeleteAirplaneIsSucceed(PTR_LIST_AIRPLANE &l, char *soHieuMayBayCanXoa)
{
	int viTri = FindIndexAirplane(l, soHieuMayBayCanXoa);//tim ra vi tri cua may bay co So hieu may bay la soHieuMayBayCanXoa
	if (viTri == -1) return false; //khong co soHieuMayBayCanXoa nay
	for (int i = viTri; i < l->n; i++)
		l->listAirplane[i] = l->listAirplane[i + 1];//don ve truoc
	l->n--;//giam so luong phan tu cua mang di
	return true;//xoa thanh cong
}


//in Danh sach may bay theo tung hang
void OutputAirplane(PTR_AIRPLANE al, int thuTu)
{
	DeleteOldData(sizeof(keyDisplayAirplane) / sizeof(string), thuTu);//xoa hang dau truoc 
//	string keyDisplayAirplane[4] = { "SH MB: ", "Loai MB: ", "So day: ", "So dong: " };
	Gotoxy(xKeyDisplay[0] + 3, Y_DISPLAY + 3 + thuTu); cout << al->soHieuMayBay;
	Gotoxy(xKeyDisplay[1] + 3, Y_DISPLAY + 3 + thuTu); cout << al->loaiMayBay;
	Gotoxy(xKeyDisplay[2] + 8, Y_DISPLAY + 3 + thuTu); cout << al->soDay;
	Gotoxy(xKeyDisplay[3] + 8, Y_DISPLAY + 3 + thuTu); cout << al->soDong;
//	int xKeyDisplay[7] = {1,20,45,65,80,95, 107};
}

//in OutputAirplane theo tung trang
void OutputListAirplanePerPage(PTR_LIST_AIRPLANE l, int viTriBatDau)
{
	if (l == NULL) return;
	for (int i = 0; i + viTriBatDau <= l->n && i < QUANTITY_PER_PAGE; i++)
		OutputAirplane(l->listAirplane[i + viTriBatDau], i*2);//in ra ptu thu i bao nhieu nhieu => xac dinh vi tri in
	Gotoxy(1,3);
	cout << "So luong May Bay: " << (l->n)+1;
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowAirplane << "/" << totalPageAirplane;
}

//set mau chon, co chon la mau 1, ko chon la mau 0
void SetDefaultChosenAirplane(PTR_LIST_AIRPLANE l, int thuTu)
{
	SetBGColor(1);//darkblue
	OutputAirplane(l->listAirplane[thuTu], (thuTu % QUANTITY_PER_PAGE)*2);
	SetBGColor(0);//black
}

//len xuong menu
void EffectiveMenuAirplane(int thuTu, PTR_LIST_AIRPLANE l)
{
	int viTriHienTai = thuTu;
	SetDefaultChosenAirplane(l, viTriHienTai);
	OutputAirplane(l->listAirplane[currposPrecAirplane], (currposPrecAirplane % QUANTITY_PER_PAGE) * 2);
	//OutputAirplane(node MayBay o vi tri currposPrecAirplane, 
	currposPrecAirplane = viTriHienTai;
}

//thay doi cac trang dua vao so luong cac may bay
void ChangePageAirplane(PTR_LIST_AIRPLANE l)
{
	clrscr();
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	DeleteNote(sizeof(keyDisplayAirplane) / sizeof(string));
	currposAirplane = (pageNowAirplane - 1) * QUANTITY_PER_PAGE;//vi tri tren cung cua 1 trang chua currposAirplane
	currposPrecAirplane = (pageNowAirplane - 1) * QUANTITY_PER_PAGE;///vi tri tren cung cua 1 trang chua currposAirplane
	Gotoxy(X_PAGE, Y_PAGE);
	cout << "Trang " << pageNowAirplane << "/" << totalPageAirplane;
}

//thao tac voi cac phim
int ChooseAirplane(PTR_LIST_AIRPLANE l)
{
	ShowCur(false);
	int key;
	int keyboard_read = 0;
	pageNowAirplane = 1;
	currposAirplane = 0;
	currposPrecAirplane = 0;
	if(l->n != -1)//co ptu
	{
		OutputListAirplanePerPage(l,0);
		SetDefaultChosenAirplane(l, currposAirplane);
	}
	
	while (true)
	{
		while (_kbhit())//kbhit(void): kiem tra nguoi dung co nhap vao hay khong
		{
			keyboard_read = _getch();//lay gia tri phim vua nhap vao bang lenh getch()
			if (keyboard_read == 0)
				keyboard_read = _getch();//cho nhan gia tri nhap vao
			switch (keyboard_read)
			{
			case KEY_UP:
				if (currposAirplane % QUANTITY_PER_PAGE > 0)//vitri dau tien trong moi trang
				{
					currposAirplane = currposAirplane - 1;
					EffectiveMenuAirplane(currposAirplane, l);
					//len xuong menu
//					void EffectiveMenuAirplane(int thuTu, PTR_LIST_AIRPLANE l)
//					{
//						int viTriHienTai = thuTu;
//						SetDefaultChosenAirplane(l, viTriHienTai);
//						OutputAirplane(l->listAirplane[currposPrecAirplane], (currposPrecAirplane % QUANTITY_PER_PAGE) * 2);
//						//OutputAirplane(node MayBay o vi tri currposPrecAirplane, 
//						currposPrecAirplane = viTriHienTai;
//					}
				}
				break;
			case KEY_DOWN:
				//VD: vitri =8, 8 % 5 = 3 <5 && 8 khong phai la ptu cuoi cung mang => co the di xuong tiep
				if (currposAirplane % QUANTITY_PER_PAGE < QUANTITY_PER_PAGE - 1 && currposAirplane < l->n)
				{
					currposAirplane = currposAirplane + 1;
					EffectiveMenuAirplane(currposAirplane, l);
				}
				break;
			case PAGE_DOWN:
				if (pageNowAirplane < totalPageAirplane)
				{
					pageNowAirplane++;//tang so trang hien tai
					ChangePageAirplane(l);//thay doi trang may bay
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);//in danh sach may bay theo tung theo voi QUANTITY_PER_PAGE
					SetDefaultChosenAirplane(l, currposAirplane);
				}
				break;
			case PAGE_UP:
				if (pageNowAirplane > 1)
				{
					pageNowAirplane--;
					ChangePageAirplane(l);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					SetDefaultChosenAirplane(l, currposAirplane);
				}
				break;
			case ESC:
				ShowCur(false);
				return -1;
				break; // no choose
			case ENTER:
				ShowCur(false);
				return currposAirplane;
				break;
			}
		}	
	}
}

//nhap cac Node ChuyenBay vao 
void InputAirplane(PTR_LIST_AIRPLANE &l, PTR_AIRPLANE al, bool isEdited = false)//idIsExist = false => nhap moi
{
	ShowCur(true);
	int thuTu = 0;
	bool isMoveUp = false;
	bool isSave = false;
	string id, typeAir;
	int numSequence = 0;
	int numLine = 0;
	bool idIsExist = false;
	
	if (isEdited)//isEdited = true => sua lai, isEdited = false => nhap moi
	{
		id = al->soHieuMayBay;
		typeAir = al->loaiMayBay;
		numLine = al->soDong;
		numSequence = al->soDay;
		//binding data
		Gotoxy(X_ADD + 6, 0 * 3 + Y_ADD);
		cout << id;
		Gotoxy(X_ADD + 7, 1 * 3 + Y_ADD);
		cout << typeAir;
		Gotoxy(X_ADD + 7, 2 * 3 + Y_ADD);
		cout << numSequence;
		Gotoxy(X_ADD + 7, 3 * 3 + Y_ADD);
		cout << numLine;
	}

	while (true)
	{
		switch (thuTu)
		{
		case 0:
			if(isEdited) break;//isEdited =true => sua => phan CheckMoveAndValidateID() bi vo hieu hoa ko nhap lai duoc
			CheckMoveAndValidateID(id, isMoveUp, thuTu, isSave, 6);
			//sosanh soHieuMaybay voi id nhap vao trung nhau
			//kiem tra id nay co ton tai chua
			if (_stricmp(al->soHieuMayBay, id.c_str()) == 0)//trung nhau
			{
				idIsExist = true;//da ton tai
				break;  // no change ID, ket thuc vong lap ngay lap tuc, cau lenh tiep theo se duoc thuc hien
			}
			//khong tim ra Maybay trong listMayBay
			else if (FindAirplane(l, (char *)id.c_str()) == NULL)
			{
				idIsExist = false;
				break;
			}
			else idIsExist = true;//sua lai
			break;
		case 1:
			CheckMoveAndValidateName(typeAir, isMoveUp, thuTu, isSave, 7);
//			void CheckMoveAndValidateName(string &result, bool &isMove, int &ordinal, bool &isSave,int distance)
			break;
		case 2:
			CheckMoveAndValidateNumber(numSequence, isMoveUp, thuTu, isSave, 7, 5);//chi duoc nhap so Day < 5 
			break;
		case 3:
			CheckMoveAndValidateNumber(numLine, isMoveUp, thuTu, isSave, 7, 20);
		}//end switch 

		if (isMoveUp)
		{
			if (thuTu == 0)
			{
				isMoveUp = false;
			}
			thuTu--;
		}
		else
		{
			if (thuTu == 3)isMoveUp = true;
			thuTu++;
		}
		
		if (isSave)
		{
			Gotoxy(X_NOTIFY, Y_NOTIFY);
			cout << setw(50) << setfill(' ') << " ";

			if (idIsExist)//nhap vao bi trung du lieu
			{
				Gotoxy(X_NOTIFY, Y_NOTIFY);
				cout << "Ma so nhap vao khong duoc trung";		
			}
			else//ko bi trung
			{
				PTR_AIRPLANE temp = new AIRPLANE;//khoi tao con tro temp co kieu du lieu PTR_AIRPLANE
				strcpy(temp->soHieuMayBay, id.c_str());//copy chuoi tu id nhap vao de gan vao temp->soHieuMayBay
				strcpy(temp->loaiMayBay, typeAir.c_str());//copy chuoi tu typeAir nhap vao de gan vao temp->typeAir
				temp->soDay = numSequence;
				temp->soDong = numLine;
				//chua nhap du
				if (DataAirplaneIsEmpty(temp) == true)
				{
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Cac truong du lieu khong dc de trong";
				}
				else//da nhap du
				{
					strcpy(al->soHieuMayBay, id.c_str());
					strcpy(al->loaiMayBay, typeAir.c_str());
					al->soDay = numSequence;
					al->soDong = numLine;
					if (isEdited)//sua
					{
						int index = FindIndexAirplane(l, al->soHieuMayBay);//tim vi tri cua soHieuMayBay do trong listMaYBay 
						l->listAirplane[index] = al;						
					}
					else//nhap moi
					{
						l->listAirplane[++l->n] = new AIRPLANE;
						l->listAirplane[l->n] = al;
					}
					DeleteMenuAdd();
					totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
					delete temp;
					return;
				}
			}
			isSave = false;
		}
		else
			isSave = false;
	}
	ShowCur(false);
}

//thay doi trang 
void ChangePageManageAirplane(PTR_LIST_AIRPLANE l)
{
	clrscr();
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC MAY BAY";
	OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
}

//menu quan ly may bay
void MenuManageAirplane(PTR_LIST_AIRPLANE &l)
{
backMenu:
	clrscr();
	pageNowAirplane = 1;
	totalPageAirplane = (l->n - 1) / QUANTITY_PER_PAGE + 1;
	
	OutputListAirplanePerPage(l, 0);//in ra man hinh trang dau tien
	Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
	int key;
	Gotoxy(X_TITLE, Y_TITLE); cout << "QUAN LY CAC MAY BAY!";
	Gotoxy(X_PAGE, Y_PAGE);
	while (true)
	{
		while (_kbhit())
		{		
			key = _getch();
			if (key == 0 || key == 224)
			{
				key = _getch();
				if (key == KEY_F2)
				{
					PTR_AIRPLANE al = new AIRPLANE;//cap phat cho bien al 1 vung nho moi
					DisplayEdit(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string), 35);
					InputAirplane(l, al);
					totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
//					pageNowAirplane = 1;
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Them thanh cong!";
				}
				else if (key == KEY_F3) //f3
				{
					int k = ChooseAirplane(l);
					if (k == -1) goto backMenu;
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Ban co chac chan xoa? Enter dong y!";
					key = _getch();
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << setw(50) << setfill(' ') << " ";
					if (key == ENTER)
					{
						bool isDeleted = DeleteAirplaneIsSucceed(l, l->listAirplane[k]->soHieuMayBay);
						if (!isDeleted)
						{
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa that bai. An phim bat ki de tiep tuc."<<endl;
							_getch();
							goto backMenu;
						}
						else
						{
							clrscr();
							Display(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string));
							if ((l->n + 1) % QUANTITY_PER_PAGE == 0) pageNowAirplane--;//tinh de co nen giam di so trang hien co hay khong
							totalPageAirplane = l->n / QUANTITY_PER_PAGE + 1;
							OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
							Gotoxy(X_NOTIFY, Y_NOTIFY);
							cout << "Xoa thanh cong";
						}
					}
					else
						goto backMenu;
				}
				else if (key == KEY_F4)
				{
					int k = ChooseAirplane(l);
					if (k == -1) goto backMenu;;
					Gotoxy(X_ADD, 40);
					DisplayEdit(keyDisplayAirplane, sizeof(keyDisplayAirplane) / sizeof(string), 35);
					InputAirplane(l, l->listAirplane[k], true);
					OutputListAirplanePerPage(l, (pageNowAirplane - 1) * QUANTITY_PER_PAGE);
					Gotoxy(X_NOTIFY, Y_NOTIFY);
					cout << "Sua thanh cong";
				}
				else if (key == PAGE_DOWN && pageNowAirplane < totalPageAirplane)
				{
					
					pageNowAirplane++;
					ChangePageManageAirplane(l);
				}
				else if (key == PAGE_UP && pageNowAirplane > 1)
				{
					
					pageNowAirplane--;
					ChangePageManageAirplane(l);
					
				}
			}
			else if (key == ESC)
				return;
		}
	}
}

#endif

