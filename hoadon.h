#ifndef HOADON_H
#define HOADON_H

#include <string>
#include <fstream>
using namespace std;

struct KhachHang
{
    string tenKhachHang;
    string soDienThoai;
    string diaChi;
};

struct Sach
{
    string tenSach;
    string gia;
};

struct HoaDonSach
{
    string maHoaDon;
    string ngayTao;
    KhachHang khachHang;
    Sach sach;
    string gia;
    string soLuongSach;
};

struct Node
{
    HoaDonSach Infor;
    Node *Next;
};

struct LIST
{
    Node *Head;
    Node *Tail;
};

// Nguyên mẫu hàm
Node *getNode(HoaDonSach x);
void insertLast(LIST &Q, Node *p);
void ghiDanhSachHoaDon(LIST &Q);
void inDanhSachHoaDonSach(LIST &Q);
void inHoaDonSach(HoaDonSach a);
HoaDonSach nhapHoaDon();
LIST docDanhSachHoaDon();
void taoHoaDonSach();
HoaDonSach docThongTinHoaDon(ifstream &fin);
HoaDonSach timKiemHoaDonTheoMa(string maHoaDon, const LIST &Q);
Node *timKiemNodeTheoMa(string maHoaDon, LIST &Q);
LIST timKiemHoaDonTheoTenKhachHang(string tenKhachHang, const LIST &Q);
LIST timKiemHoaDonTheoTenSach(string tenSach, const LIST &Q);
void suaHoaDonSach(string maHoaDon);
void xoaHoaDonSach(string maHoaDon);
void sapXepTheoGiaTangDan(LIST &Q);
void sapXepTheoGiaGiamDan(LIST &Q);
void sapXepTheoSoluongTangDan(LIST &Q);
void sapXepTheoSoluongGiamDan(LIST &Q);
LIST timHoaDonGiaTriCaoNhat(const LIST &Q);
LIST timHoaDonGiaTriThapNhat(const LIST &Q);
LIST timHoaDonSoluongMuaNhieuNhat(const LIST &Q);
LIST timHoaDonSoluongMuaItNhat(const LIST &Q);
int tinhTongGiaTriHoaDon(const LIST &Q);
float tinhTrungBinhGia(const LIST &Q);
int tinhTongSoLuongSanPham(const LIST &Q);
int soLuong(LIST &Q);
void thongKeSoLuongBanRaSach(const LIST &Q);
void thongKeSoLuongBanRaTheoTheLoai(const LIST &Q);
void thongKeSoLuongBanRaCuaKhachHang(const LIST &Q);
void thongKeDoanhThuCuaCacCuonSach(const LIST &Q);
void thongKeDoanhThuCuaCacKhachHang(const LIST &Q);

#endif
