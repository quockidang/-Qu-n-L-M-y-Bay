#pragma once
#include "airplane.h"

int currposAirplane = 0;
int currposPrecAirplane = 0;
int pageNowAirplane = 1;
int totalPageAirplane = 0;

int currposFlight = 0;
int currposPrecFlight = 0;
int pageNowFlight = 1;
int totalPageFlight = 1;

int currposPassenger = 0;
int currposPrecPassenger = 0;
int pageNowPassenger = 1;
int totalPagePassenger = 0;

int currposMainMenu = 0;
int currposPreMainMenu = 0;

unsigned int arrPassengerId[100];
int nPassenger;

////AIRPLANE
////HAM XU LY
////tim May bay theo So hieu may bay nhap vao
//PTR_AIRPLANE FindAirplane(PTR_LIST_AIRPLANE l, char soHieuMayBayCanTim[]){}
//
////tim Vi tri may bay theo So hieu may bay da nhap vao
//int FindIndexAirplane(PTR_LIST_AIRPLANE l, char soHieuMayBayCanTim[]){}
//
////xac nhan nhap du => return false la nhap du
//bool DataAirplaneIsEmpty(PTR_AIRPLANE al){}
//
////xac nhan xoa thanh cong hay that bai => return true la xoa thanh cong
//bool DeleteAirplaneIsSucceed(PTR_LIST_AIRPLANE &l, char *soHieuMayBayCanXoa){}
//
////doi vi tri 2 chuyen bay
//void SwapAirplane(PTR_AIRPLANE &a, PTR_AIRPLANE &b){}
//
//
////IN RA MAN HINH
////in Airplane[thuTu] ra tung hang, co du soHieuMayBay, loaiMayBay, soDay, soDong
//void OutputAirplane(PTR_AIRPLANE al, int thuTu){}
//
////in List Airplane theo tung trang, voi quy uoc QUANTITY_PER_PAGE moi trang
//void OutputListAirplanePerPage(PTR_LIST_AIRPLANE l, int viTriBatDau){}
//
////set mau chon, co chon la mau 1, ko chon la mau 0
//void SetDefaultChosenAirplane(PTR_LIST_AIRPLANE l, int thuTu){}
//
////len xuong menu, xac dinh vitri dang chon va vitri truoc khi thay doi
//void EffectiveMenuAirplane(int thuTu, PTR_LIST_AIRPLANE l){}
//
////thay doi cac trang dua vao so luong cac may bay
//void ChangePageAirplane(PTR_LIST_AIRPLANE l){}
//
////cac thao tac voi cac phim de chon may bay, doi trang
//int ChooseAirplane(PTR_LIST_AIRPLANE l){}


























