#include <iostream>
#include "hoadon.h"

using namespace std;

int main()
{
    ifstream fin("hoa_don_sach.txt");
    int choice = 0;
    while (choice != 24)
    {
        cout << "======== Danh muc ========\n";
        cout << "1. Tao hoa don sach\n";
        cout << "2. Xem danh sach hoa don sach\n";
        cout << "3. Sua hoa don sach\n";
        cout << "4. Xoa hoa don sach\n";
        cout << "5. Tim kiem hoa don theo ma\n";
        cout << "6. Tim kiem hoa don theo ten khach hang\n";
        cout << "7. Tim kiem hoa don theo ten sach\n";
        cout << "8. Sap xep danh sach theo gia tang dan\n";
        cout << "9. Sap xep danh sach theo gia giam dan\n";
        cout << "10. Sap xep danh sach theo so luong tang dan\n";
        cout << "11. Sap xep danh sach theo so luong giam dan\n";
        cout << "12. Tim hoa don co gia tri cao nhat\n";
        cout << "13. Tim hoa don co gia tri thap nhat\n";
        cout << "14. Tim hoa don co so luong mua nhieu nhat\n";
        cout << "15. Tim hoa don co so luong mua it nhat\n";
        cout << "16. Tinh tong gia tri hoa don\n";
        cout << "17. Tinh trung binh gia hoa don\n";
        cout << "18. Tinh tong so luong san pham\n";
        cout << "19. Thong ke so luong ban ra sach\n";
        cout << "20. Thong ke so luong ban ra cua cac khach hang\n"; // Thêm chức năng 21
        cout << "21. Thong ke doanh thu cua cac cuon sach\n";        // Thêm chức năng 22
        cout << "22. Thong ke doanh thu cua cac khach hang\n";       // Thêm chức năng 23
        cout << "23. Thong ke so luong ban ra theo the loai sach\n";
        cout << "24. Thoat\n";
        cout << "Lua chon cua ban la: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            taoHoaDonSach();
            break;
        case 2:
        {
            LIST l = docDanhSachHoaDon();
            inDanhSachHoaDonSach(l);
            break;
        }
        case 3:
        {
            string ma;
            cout << "Nhap ma hoa don: ";
            cin >> ma;
            suaHoaDonSach(ma);
            break;
        }
        case 4:
        {
            string ma;
            cout << "Nhap ma hoa don: ";
            cin >> ma;
            xoaHoaDonSach(ma);
            break;
        }
        case 5:
        {
            string ma;
            cout << "Nhap ma hoa don: ";
            cin >> ma;
            LIST hoaDonList = docDanhSachHoaDon(); // Lưu danh sách vào biến
            // HoaDonSach hoaDon = timKiemHoaDonTheoMa(ma, hoaDonList);
            HoaDonSach hoaDon = timKiemHoaDonTheoMa(ma, docDanhSachHoaDon());
            if (hoaDon.maHoaDon != "")
            {
                inHoaDonSach(hoaDon);
            }
            else
            {
                cout << "Khong tim thay hoa don voi ma: " << ma << endl;
            }
            break;
        }
        case 6:
        {
            string tenKhachHang;
            cout << "Nhap ten khach hang: ";
            cin.ignore(); // Để xử lý đúng dấu cách trong tên
            getline(cin, tenKhachHang);
            LIST hoaDonTheoKhachHang = timKiemHoaDonTheoTenKhachHang(tenKhachHang, docDanhSachHoaDon());
            inDanhSachHoaDonSach(hoaDonTheoKhachHang);
            break;
        }
        case 7:
        {
            string tenSach;
            cout << "Nhap ten sach: ";
            cin.ignore();
            getline(cin, tenSach);
            LIST hoaDonTheoSach = timKiemHoaDonTheoTenSach(tenSach, docDanhSachHoaDon());
            inDanhSachHoaDonSach(hoaDonTheoSach);
            break;
        }
        case 8:
        {
            LIST l = docDanhSachHoaDon();
            sapXepTheoGiaTangDan(l);
            inDanhSachHoaDonSach(l);
            break;
        }
        case 9:
        {
            LIST l = docDanhSachHoaDon();
            sapXepTheoGiaGiamDan(l);
            inDanhSachHoaDonSach(l);
            break;
        }
        case 10:
        {
            LIST l = docDanhSachHoaDon();
            sapXepTheoSoluongTangDan(l);
            inDanhSachHoaDonSach(l);
            break;
        }
        case 11:
        {
            LIST l = docDanhSachHoaDon();
            sapXepTheoSoluongGiamDan(l);
            inDanhSachHoaDonSach(l);
            break;
        }
        case 12:
        {
            LIST l = timHoaDonGiaTriCaoNhat(docDanhSachHoaDon());
            inDanhSachHoaDonSach(l);
            break;
        }
        case 13:
        {
            LIST l = timHoaDonGiaTriThapNhat(docDanhSachHoaDon());
            inDanhSachHoaDonSach(l);
            break;
        }
        case 14:
        {
            LIST l = timHoaDonSoluongMuaNhieuNhat(docDanhSachHoaDon());
            inDanhSachHoaDonSach(l);
            break;
        }
        case 15:
        {
            LIST l = timHoaDonSoluongMuaItNhat(docDanhSachHoaDon());
            inDanhSachHoaDonSach(l);
            break;
        }
        case 16:
        {
            int tongGiaTri = tinhTongGiaTriHoaDon(docDanhSachHoaDon());
            cout << "Tong gia tri hoa don: " << tongGiaTri << endl;
            break;
        }
        case 17:
        {
            float trungBinhGia = tinhTrungBinhGia(docDanhSachHoaDon());
            cout << "Trung binh gia hoa don: " << trungBinhGia << endl;
            break;
        }
        case 18:
        {
            int tongSoLuong = tinhTongSoLuongSanPham(docDanhSachHoaDon());
            cout << "Tong so luong san pham: " << tongSoLuong << endl;
            break;
        }
        case 19:
        {
            thongKeSoLuongBanRaSach(docDanhSachHoaDon());
            break;
        }
        case 20:
        {
            thongKeSoLuongBanRaCuaKhachHang(docDanhSachHoaDon());
            break;

        }
        case 21:
        {
            thongKeDoanhThuCuaCacCuonSach(docDanhSachHoaDon());
            break;

        }
        case 22:
        {
            thongKeDoanhThuCuaCacKhachHang(docDanhSachHoaDon());
            break;

        }
        case 23:
        {
            thongKeSoLuongBanRaTheoTheLoai(docDanhSachHoaDon());
            break;
        }
        case 24:
            cout << "Thoat chuong trinh\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
    }
    return 0;
}
