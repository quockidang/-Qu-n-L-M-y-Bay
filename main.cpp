#include <iostream>
#include "airplane.h"
#include "flight.h"
#include "processs.h"
#include "display.h"
#include "passenger.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	fullscreen();
	//AIRPLANE
	PTR_LIST_AIRPLANE la = new LIST_AIRPLANE;
	LoadAirplaneFromFile(la);

	
	TREE_PASSENGER t;
	InitTreePassenger(t);
	LoadPassengerFormFile(t);
	
//	FLIGHT
	LIST_FLIGHT lf;
	InitListFlight(lf);//khoi tao	
	
	// tao du lieu mau, vi doc ghi file danh sach chuyen bay bi loi
	FLIGHT fl;
	strcpy(fl.maChuyenBay, "cb01");
	strcpy(fl.sanBayDen, "noi bai");
	strcpy(fl.soHieuMayBay, "76456437");
	
	fl.soVeDaBan = 0;
	fl.soLuongVe = 35;

	
	fl.thoiGianDi.d = 7;
	fl.thoiGianDi.m = 8;
	fl.thoiGianDi.y = 2020;
	
	fl.thoiGianDi.h = 10;
	fl.thoiGianDi.mi = 30;
	
	string* temp = new string[35];
	
	temp = CreateArrTicket(5, 7); // tao danh sach ve
	
	for(int i = 0; i < 35; i++)
	{
		strcpy(fl.listTicket[i].tenVe, (char*)temp[i].c_str());
	}
	
	InsertOrderForListFlight(lf, fl);
	
	//  chuyen bay thu 2may bay thu hai
	FLIGHT fl2;
	strcpy(fl2.maChuyenBay, "cb02");
	strcpy(fl2.sanBayDen, "tan son nhat");
	strcpy(fl2.soHieuMayBay, "MTU345");
	
	fl2.soVeDaBan = 0;
	fl2.soLuongVe = 90;

	
	fl2.thoiGianDi.d = 12;
	fl2.thoiGianDi.m = 5;
	fl2.thoiGianDi.y = 2025;
	
	fl2.thoiGianDi.h = 14;
	fl2.thoiGianDi.mi = 30;
	
	string* temp1 = new string[90];
	
	temp1 = CreateArrTicket(5, 18); // tao danh sach ve
	
	for(int j = 0; j < 90; j++)
	{
		strcpy(fl2.listTicket[j].tenVe, (char*)temp1[j].c_str());
	}
	
	InsertOrderForListFlight(lf, fl2);
	
	Main_Menu(la, lf, t);
	
	SavePassengerToFile(t);
	//SaveFlightToFile(lf);
	SaveAirplaneToFile(la);

	return 0;
}

