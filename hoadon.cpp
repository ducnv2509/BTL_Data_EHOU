#include "hoadon.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <ctime> // cho std::time, std::strftime
using namespace std;

// toàn bộ code xử lý functions ở đây...

string layNgayHienTai()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm); // định dạng: 2025-05-04
    return string(buffer);
}

string taoMaHoaDonTuDong()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "HD_%Y%m%d_%H%M%S", ltm); // HD_20250504_141523
    return string(buffer);
}

Node *getNode(HoaDonSach x)
{
    Node *p = new Node;
    p->Infor = x;
    p->Next = NULL;
    return p;
}

void insertLast(LIST &Q, Node *p)
{
    if (Q.Head == NULL)
    { // neu danh sach rong
        Q.Head = p;
        Q.Tail = Q.Head;
    }
    else
    { // danh sach khang rong
        Q.Tail->Next = p;
        Q.Tail = p;
    }
}

void inHoaDonSach(HoaDonSach a)
{
    int maHoaDon;        // Ma hoa don
    string ngayTao;      // Ngay tao
    KhachHang khachHang; // Khach hang
    Sach sach;           // sach mua
    float gia;           // Gia tri hoa don
    int soLuongSach;     // So luong sach

    // in thong tin hoa don
    cout << "Ma hoa don: " << a.maHoaDon << "\n";
    cout << "Ngay tao:  " << a.ngayTao << "\n";
    cout << "Ten khach hang: " << a.khachHang.tenKhachHang << "\n";
    cout << "So dien thoai: " << a.khachHang.soDienThoai << "\n";
    cout << "Dia chi: " << a.khachHang.diaChi << "\n";
    cout << "Ten sach: " << a.sach.tenSach << "\n";
    cout << "Gia sach (1 quyen): " << a.sach.gia << "\n";
    cout << "So luong: " << a.soLuongSach << "\n";
    cout << "Thanh tien: " << a.gia << "\n";
}

void inDanhSachHoaDonSach(LIST &Q)
{
    if (Q.Head == NULL)
    { // neu danh sach rong
        cout << "Hien tai ban dang khong co hoa don nao!\n\n";
    }
    else
    {
        Node *p = Q.Head;
        int i = 0;
        while (p != NULL)
        {
            // in thong tin hoa don
            cout << "\nHoa don thu " << (i + 1) << "\n";
            inHoaDonSach(p->Infor);
            p = p->Next;
            i++;
        }
    }
}

void ghiDanhSachHoaDon(LIST &Q)
{
    cout << "Writing to disk... " << endl;
    ofstream fout("hoa_don_sach.txt");
    if (!fout)
    {
        cout << "Error opening file for output" << endl;
        return;
    }
    else
    {
        if (Q.Head == NULL)
        { // neu danh sach rong
            cout << "Hien tai ban dang khong co hoa don nao!\n";
        }
        else
        {
            Node *p = Q.Head;
            int i = 0;
            while (p != NULL)
            {
                fout << p->Infor.maHoaDon;
                fout << "&";
                fout << p->Infor.ngayTao;
                fout << "&";
                fout << p->Infor.khachHang.tenKhachHang;
                fout << "&";
                fout << p->Infor.khachHang.soDienThoai;
                fout << "&";
                fout << p->Infor.khachHang.diaChi;
                fout << "&";
                fout << p->Infor.sach.tenSach;
                fout << "&";
                fout << p->Infor.sach.gia;
                fout << "&";
                fout << p->Infor.soLuongSach;
                fout << "&";
                fout << p->Infor.gia;
                fout << "$";
                p = p->Next;
                i++;
            }
        }
    }
    fout.close();
    cout << "Writing to disk success!" << endl;
}

HoaDonSach docThongTinHoaDon(ifstream &fin)
{
    HoaDonSach hoaDonSach;
    // doc ma hoa don
    getline(fin, hoaDonSach.maHoaDon, '&');
    // doc ngay tao
    getline(fin, hoaDonSach.ngayTao, '&');
    // doc ten khach hang
    getline(fin, hoaDonSach.khachHang.tenKhachHang, '&');
    // doc so dien thoai khach hang
    getline(fin, hoaDonSach.khachHang.soDienThoai, '&');
    // doc dia chi khach hang
    getline(fin, hoaDonSach.khachHang.diaChi, '&');
    // doc ten sach
    getline(fin, hoaDonSach.sach.tenSach, '&');
    // doc gia 1 san pham
    getline(fin, hoaDonSach.sach.gia, '&');
    // doc so luong san pham
    getline(fin, hoaDonSach.soLuongSach, '&');
    // doc thanh tien
    getline(fin, hoaDonSach.gia, '$');

    return hoaDonSach;
}

// doc danh sach hoa don sach tu file
LIST docDanhSachHoaDon()
{
    ifstream fin;
    fin.open("hoa_don_sach.txt");

    // khoi tao danh sach moi
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    if (!fin)
        return rawData;

    // doc den het file
    while (!fin.eof())
    {
        HoaDonSach hoaDonSach = docThongTinHoaDon(fin);
        if (!hoaDonSach.maHoaDon.empty())
        {
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
        }
    }
    fin.close();
    return rawData;
}

// HoaDonSach nhapHoaDon()
// {
//     HoaDonSach hoaDonSach;
//     // Khach hang
//     string tenKhachHang; // Ten Khach Hang
//     string soDienThoai;  // So dien thoai
//     string diaChi;       // Dia Chi

//     // sach
//     string tenSach; // Ten sach
//     int gia;        // Gia sach

//     // Hoa don
//     string maHoaDon;     // Ma hoa don
//     string ngayTao;      // Ngay tao
//     KhachHang khachHang; // Khach hang
//     Sach sach;           // sach mua
//     int soLuongSach;     // So luong sach
//     float giaHoaDon;     // Gia tri hoa don

//     cin.ignore();
//     // Nhap thong tin khach hang
//     cout << "Ten khach hang: ";
//     getline(cin, tenKhachHang);
//     cout << "So dien thoai: ";
//     getline(cin, soDienThoai);
//     cout << "Dia chi: ";
//     getline(cin, diaChi);

//     // Nhap thong tin sach
//     cout << "Ten sach: ";
//     getline(cin, tenSach);
//     cout << "Gia: ";
//     cin >> gia;

//     cin.ignore();
//     // Nhap thong tin hoa don
//     cout << "Ma hoa don: ";
//     getline(cin, maHoaDon);
//     cout << "Ngay tao: ";
//     getline(cin, ngayTao);
//     cout << "So luong sach se mua: ";
//     cin >> soLuongSach;

//     // Tao Khach hang
//     khachHang.tenKhachHang = tenKhachHang;
//     khachHang.soDienThoai = soDienThoai;
//     khachHang.diaChi = diaChi;

//     // Tao sach
//     sach.tenSach = tenSach;
//     sach.gia = patch::to_string(gia);

//     giaHoaDon = gia * soLuongSach;

//     hoaDonSach.khachHang = khachHang;
//     hoaDonSach.sach = sach;
//     hoaDonSach.maHoaDon = maHoaDon;
//     hoaDonSach.ngayTao = ngayTao;
//     hoaDonSach.soLuongSach = patch::to_string(soLuongSach);
//     hoaDonSach.gia = patch::to_string(giaHoaDon);

//     return hoaDonSach;
// }

HoaDonSach nhapHoaDon()
{
    HoaDonSach hoaDonSach;
    // Khach hang
    string tenKhachHang, soDienThoai, diaChi;

    // Sach
    string tenSach;
    int gia;

    // So luong
    int soLuongSach;
    float giaHoaDon;

    cin.ignore();

    // Nhap thong tin khach hang
    cout << "Ten khach hang: ";
    getline(cin, tenKhachHang);
    cout << "So dien thoai: ";
    getline(cin, soDienThoai);
    cout << "Dia chi: ";
    getline(cin, diaChi);

    // Nhap thong tin sach
    cout << "Ten sach: ";
    getline(cin, tenSach);
    cout << "Gia: ";
    cin >> gia;

    cout << "So luong sach se mua: ";
    cin >> soLuongSach;

    // Tạo khách hàng và sách
    KhachHang khachHang = {tenKhachHang, soDienThoai, diaChi};
    Sach sach = {tenSach, patch::to_string(gia)};

    // Tính tổng tiền
    giaHoaDon = gia * soLuongSach;

    // Tự động sinh mã hóa đơn và ngày tạo
    string maHoaDon = taoMaHoaDonTuDong();
    string ngayTao = layNgayHienTai();

    // Gán vào hóa đơn
    hoaDonSach.khachHang = khachHang;
    hoaDonSach.sach = sach;
    hoaDonSach.maHoaDon = maHoaDon;
    hoaDonSach.ngayTao = ngayTao;
    hoaDonSach.soLuongSach = patch::to_string(soLuongSach);
    hoaDonSach.gia = patch::to_string(giaHoaDon);

    return hoaDonSach;
}

void nhapDanhSachHoaDon(int n)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    // Khoi tao List
    //	Q.Head = Q.Tail = NULL;
    for (int i = 0; i < n; i++)
    {
        HoaDonSach hoaDonSach = nhapHoaDon();
        Node *p = getNode(hoaDonSach);
        insertLast(rawData, p);
    }
    // Ghi danh sach hoa don da nhap vao file
    ghiDanhSachHoaDon(rawData);
}

void taoHoaDonSach()
{
    ifstream fin;

    // mo file de doc du lieu
    fin.open("hoa_don_sach.txt");

    // Danh sach hoa don sach
    LIST danhSachHoaDonSach = docDanhSachHoaDon();

    // nhap hoa don
    HoaDonSach hoaDonSach = nhapHoaDon();

    // Them hoa don vao danh sach
    Node *p = getNode(hoaDonSach);
    insertLast(danhSachHoaDonSach, p);

    // Ghi danh sach hoa don moi vao file
    ghiDanhSachHoaDon(danhSachHoaDonSach);

    // dong file sau khi su dung
    fin.close();
}

HoaDonSach timKiemHoaDonTheoMa(string maHoaDon, const LIST &Q)
{
    HoaDonSach hoaDonSach;
    Node *p;
    p = Q.Head;
    int i = 0;
    while (p != NULL)
    {
        if (p->Infor.maHoaDon == maHoaDon)
        {
            hoaDonSach = p->Infor;
            i++;
        }
        p = p->Next;
    }
    return hoaDonSach;
}

Node *timKiemNodeTheoMa(string maHoaDon, LIST &Q)
{
    Node *ketQua = NULL;
    Node *p;
    Node *q;
    p = Q.Head;
    int i = 0;
    while (p != NULL)
    {
        q = p->Next;
        if (q != NULL && q->Infor.maHoaDon == maHoaDon)
        {
            ketQua = p;
            i++;
        }
        p = p->Next;
    }
    return ketQua;
}

LIST timKiemHoaDonTheoTenKhachHang(string tenKhachHang, const LIST &Q)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    Node *p;
    p = Q.Head;
    int i = 0;
    while (p != NULL)
    {
        HoaDonSach hoaDonSach;
        if (p->Infor.khachHang.tenKhachHang.find(tenKhachHang) != std::string::npos)
        {
            hoaDonSach = p->Infor;
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
            i++;
        }
        p = p->Next;
    }
    return rawData;
}

Node *timKiemNodeTruocMaHoaDon(LIST &Q, string maHoaDon)
{
    Node *node = NULL;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        if (p->Next->Infor.maHoaDon == maHoaDon)
        {
            node = p;
        }
    }
    return node;
}

LIST timKiemHoaDonTheoTenSach(string tenSach, const LIST &Q)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    Node *p;
    p = Q.Head;
    int i = 0;
    while (p != NULL)
    {
        HoaDonSach hoaDonSach;
        if (p->Infor.sach.tenSach == tenSach)
        {
            hoaDonSach = p->Infor;
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
            i++;
        }
        p = p->Next;
    }
    return rawData;
}

void xoaDau(LIST &Q)
{
    // tao node p
    Node *p = new Node;
    // gan p bang node Head dau tien cua danh sach
    p = Q.Head;
    // thay doi lai Head cua danh sach
    Q.Head = Q.Head->Next;
    // gan node p ban dau tro den NULL
    p->Next = NULL;
    // xoa node p
    delete p;
}

void xoaCuoi(LIST &Q)
{
    // duyet cac phan tu co trong danh sach
    for (Node *k = Q.Head; k != NULL; k = k->Next)
    {
        // neu duyet den phan tu Tail cuoi trong danh sach
        if (k->Next == Q.Tail)
        {
            // xoa phan tu cuoi
            delete Q.Tail;
            // tro phan tu truoc phan tu cuoi ve NULL
            k->Next = NULL;
            // thay doi lai phan tu cuoi pTail cua danh sach
            Q.Tail = k;
        }
    }
}

void xoaTheoMaHoaDon(LIST &Q, string maHoaDon)
{
    // tao node p de luu tru phan tu truoc node k can xoa
    Node *p = new Node;
    // neu data dau vao bang voi pHead->data thi xoa dau
    if (Q.Head->Infor.maHoaDon == maHoaDon)
    {
        // goi ham xoa dau
        xoaDau(Q);
        // ket thuc ham
        return;
    }
    // neu data bang voi Tail->Infor.maHoaDon thi xoa cuoi
    if (Q.Tail->Infor.maHoaDon == maHoaDon)
    {
        // goi ham xoa cuoi
        xoaCuoi(Q);
        // ket thuc ham
        return;
    }
    // duyet qua cac phan tu co trong danh sach
    for (Node *k = Q.Head; k != NULL; k = k->Next)
    {
        // neu tim thay data trung voi k->data dang duyet
        if (k->Infor.maHoaDon == maHoaDon)
        {
            // gan con tro next cua node p bang con tro next cua node k
            p->Next = k->Next;
            // xoa di node k
            delete k;
            // ket thuc ham
            return;
        }
        // gan node p bang node k de node p luon la node dung truoc node k
        p = k;
    }
}

void xoaHoaDonSach(string maHoaDon)
{
    ifstream fin;

    // mo file de doc du lieu
    fin.open("hoa_don_sach.txt");

    // Danh sach hoa don sach
    LIST danhSachHoaDonSach = docDanhSachHoaDon();

    // thuc hien xoa hoa don theo ma hoa don
    xoaTheoMaHoaDon(danhSachHoaDonSach, maHoaDon);

    // Ghi lai danh sach moi vao file
    ghiDanhSachHoaDon(danhSachHoaDonSach);

    // dong file sau khi su dung
    fin.close();
}

void chenDau(LIST &Q, Node *p)
{
    // neu phan tu dau rong thi danh sach rong
    if (Q.Head == NULL)
    {
        // chen dau va cuoi deu bang node p
        Q.Head = p;
        Q.Tail = p;
    }
    // nguoc lai danh sach khong rong
    else
    {
        // gan con tro next cua node p bang phan tu dang la dau tien cua danh sach
        p->Next = Q.Head;
        // gan Head bang node p
        Q.Head = p;
    }
}

void chenCuoi(LIST &Q, Node *p)
{
    // neu phan tu dau rong thi danh sach rong
    if (Q.Head == NULL)
    {
        // chen dau va cuoi deu bang node p
        Q.Head = p;
        Q.Tail = p;
    }
    // nguoc lai danh sach khong rong
    else
    {
        // gan con tro cua phan tu cuoi trong danh sach bang node p
        Q.Tail->Next = p;
        // gan Tail bang node p
        Q.Tail = p;
    }
}

void chenGiua(LIST &Q, Node *q, Node *p)
{
    // neu ton tai node q thi thuc hien chen giua
    if (q != NULL)
    {
        cout << "q khac null" << endl;
        // gan con tro next node p bang con tro next node q
        p->Next = q->Next;
        // gan con tro next node q bang node p
        q->Next = p;
        // neu q la phan tu cuoi cung thi chen node p vao cuoi
        if (q == Q.Tail)
        {
            Q.Tail = p;
        }
    }
    // nguoc lai khong ton tai node q thi chen node p vao dau
    else
    {
        // goi ham chen dau
        chenDau(Q, p);
    }
}

void suaHoaDonSach(string maHoaDon)
{
    ifstream fin;

    // mo file de doc du lieu
    fin.open("hoa_don_sach.txt");

    // Danh sach hoa don sach
    LIST danhSachHoaDonSach = docDanhSachHoaDon();

    // nhap hoa don
    HoaDonSach hoaDonSach = timKiemHoaDonTheoMa(maHoaDon, danhSachHoaDonSach);
    Node *nodeTheoMa = timKiemNodeTheoMa(maHoaDon, danhSachHoaDonSach);

    if (hoaDonSach.maHoaDon.empty())
    {
        cout << "khong tim thay hoa don can sua!\n";
    }
    else
    {
        cout << "day la hoa don ma ban can sua:\n";
        inHoaDonSach(hoaDonSach);
    }

    // Xoa hoa don vua tim kiem dc
    xoaTheoMaHoaDon(danhSachHoaDonSach, hoaDonSach.maHoaDon);
    cout << "Nhap lai thong tin hoa don:\n";
    HoaDonSach hoaDonMoi = nhapHoaDon();
    Node *nodeMoi = getNode(hoaDonMoi);

    if (danhSachHoaDonSach.Head == NULL)
    {
        // neu danh sach rong
        chenDau(danhSachHoaDonSach, nodeMoi);
    }
    else
    {
        chenGiua(danhSachHoaDonSach, nodeTheoMa, nodeMoi);
    }

    // Ghi danh sach hoa don moi vao file
    ghiDanhSachHoaDon(danhSachHoaDonSach);

    // dong file sau khi su dung
    fin.close();
}

void sapXepTheoGiaTangDan(LIST &Q)
{
    Node *p, *q;
    HoaDonSach tg;
    p = Q.Head;
    while (p != NULL)
    {
        q = p->Next;
        while (q != NULL)
        {
            if (p->Infor.gia > q->Infor.gia)
                swap(p->Infor, q->Infor);
            q = q->Next;
        }
        p = p->Next;
    }
    cout << "\nDanh sach hoa don da sap xep la:\n";
    inDanhSachHoaDonSach(Q);
}

void sapXepTheoGiaGiamDan(LIST &Q)
{
    Node *p, *q;
    HoaDonSach tg;
    p = Q.Head;
    while (p != NULL)
    {
        q = p->Next;
        while (q != NULL)
        {
            if (p->Infor.gia < q->Infor.gia)
                swap(p->Infor, q->Infor);
            q = q->Next;
        }
        p = p->Next;
    }
    cout << "\nDanh sach hoa don da sap xep la:\n";
    inDanhSachHoaDonSach(Q);
}

void sapXepTheoSoluongTangDan(LIST &Q)
{
    Node *p, *q;
    HoaDonSach tg;
    p = Q.Head;
    while (p != NULL)
    {
        q = p->Next;
        while (q != NULL)
        {
            if (p->Infor.soLuongSach > q->Infor.soLuongSach)
                swap(p->Infor, q->Infor);
            q = q->Next;
        }
        p = p->Next;
    }
    cout << "\nDanh sach hoa don da sap xep la:\n";
    inDanhSachHoaDonSach(Q);
}

void sapXepTheoSoluongGiamDan(LIST &Q)
{
    Node *p, *q;
    HoaDonSach tg;
    p = Q.Head;
    while (p != NULL)
    {
        q = p->Next;
        while (q != NULL)
        {
            if (p->Infor.soLuongSach < q->Infor.soLuongSach)
                swap(p->Infor, q->Infor);
            q = q->Next;
        }
        p = p->Next;
    }
    cout << "\nDanh sach hoa don da sap xep la:\n";
    inDanhSachHoaDonSach(Q);
}

int timGiaTriLonNhat(const LIST &Q)
{
    int max = 0;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        int gia = castStringToInt(p->Infor.gia);
        if (gia > max)
        {
            max = gia;
        }
    }
    return max;
}

LIST timHoaDonGiaTriCaoNhat(const LIST &Q)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    Node *p;
    p = Q.Head;
    int giaTriCaoNhat = timGiaTriLonNhat(Q);
    int i = 0;
    while (p != NULL)
    {
        HoaDonSach hoaDonSach;
        int gia = castStringToInt(p->Infor.gia);
        if (gia == giaTriCaoNhat)
        {
            hoaDonSach = p->Infor;
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
            i++;
        }
        p = p->Next;
    }
    return rawData;
}

int timGiaTriThapNhat(const LIST &Q)
{
    int min = 1000000;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        int gia = castStringToInt(p->Infor.gia);
        if (gia < min)
        {
            min = gia;
        }
    }
    return min;
}
LIST timHoaDonGiaTriThapNhat(const LIST &Q)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    Node *p;
    p = Q.Head;
    int giaTriThapNhat = timGiaTriThapNhat(Q);
    int i = 0;
    while (p != NULL)
    {
        HoaDonSach hoaDonSach;
        int gia = castStringToInt(p->Infor.gia);
        if (gia == giaTriThapNhat)
        {
            hoaDonSach = p->Infor;
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
            i++;
        }
        p = p->Next;
    }
    return rawData;
}
int timSoluongNhieuNhat(const LIST &Q)
{
    int max = 0;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        int soLuongSach = castStringToInt(p->Infor.soLuongSach);
        if (soLuongSach > max)
        {
            max = soLuongSach;
        }
    }
    return max;
}
LIST timHoaDonSoluongMuaNhieuNhat(const LIST &Q)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    Node *p;
    p = Q.Head;
    int SoLuongNhieuNhat = timSoluongNhieuNhat(Q);
    int i = 0;
    while (p != NULL)
    {
        HoaDonSach hoaDonSach;
        int gia = castStringToInt(p->Infor.soLuongSach);
        if (gia == SoLuongNhieuNhat)
        {
            hoaDonSach = p->Infor;
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
            i++;
        }
        p = p->Next;
    }
    return rawData;
}
int timSoluongThapNhat(const LIST &Q)
{
    int min = 1000000;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        int soLuongSach = castStringToInt(p->Infor.soLuongSach);
        if (soLuongSach < min)
        {
            min = soLuongSach;
        }
    }
    return min;
}
LIST timHoaDonSoluongMuaItNhat(const LIST &Q)
{
    LIST rawData;
    rawData.Head = rawData.Tail = NULL;
    Node *p;
    p = Q.Head;
    int SoLuongItNhat = timSoluongThapNhat(Q);
    int i = 0;
    while (p != NULL)
    {
        HoaDonSach hoaDonSach;
        int gia = castStringToInt(p->Infor.soLuongSach);
        if (gia == SoLuongItNhat)
        {
            hoaDonSach = p->Infor;
            Node *p = getNode(hoaDonSach);
            insertLast(rawData, p);
            i++;
        }
        p = p->Next;
    }
    return rawData;
}
int tinhTongGiaTriHoaDon(const LIST &Q)
{
    int sum = 0;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        int gia = castStringToInt(p->Infor.gia);
        sum += gia;
    }
    return sum;
}

int tinhTongSoLuongSanPham(const LIST &Q)
{
    int sum = 0;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        int soLuong = castStringToInt(p->Infor.soLuongSach);
        sum += soLuong;
    }
    return sum;
}

int soLuong(const LIST &Q)
{
    int length = 0;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        ++length;
    }
    return length;
}

float tinhTrungBinhGia(const LIST &Q)
{
    int soluong = soLuong(Q);
    int sum = tinhTongGiaTriHoaDon(Q);
    return sum / soluong;
}

void thongKeSoLuongBanRaSach(const LIST &Q)
{
    string tenSanPham[100];
    int soLuong[100];
    int i = 0;
    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        string tenSach = p->Infor.sach.tenSach;
        bool xuatHienRoi = xuatHienTrongDSSach(tenSach, tenSanPham);
        if (xuatHienRoi == true)
        {
            int viTri = viTrixuatHienTrongDSSach(tenSach, tenSanPham);
            int slg = soLuong[viTri];
            slg++;
            soLuong[viTri] = slg;
            tenSanPham[viTri] = tenSach;
        }
        else
        {
            soLuong[i] = 1;
            tenSanPham[i] = tenSach;
        }
        i++;
    }
    // int arrSize = *(&tenSanPham + 1) - tenSanPham;
    for (int j = 0; j < i; j++)
    {
        cout << "Ten sp: " << tenSanPham[j] << ", so luong: " << soLuong[j] << endl;
    }
}

void thongKeSoLuongBanRaTheoTheLoai(const LIST &Q)
{
    map<string, int> soLuongTheoTheLoai;

    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        // Thêm thể loại sách vào thống kê
        soLuongTheoTheLoai[p->Infor.sach.tenSach]++;
    }

    // Thay thế vòng lặp range-based for bằng iterator
    cout << "======== Thong ke so luong ban ra theo the loai ========" << endl;
    for (map<string, int>::iterator it = soLuongTheoTheLoai.begin(); it != soLuongTheoTheLoai.end(); ++it)
    {
        cout << "Sach: " << it->first << ", So luong ban ra: " << it->second << endl;
    }
}

void thongKeSoLuongBanRaCuaKhachHang(const LIST &Q)
{
    map<string, int> soLuongBanRaCuaKhachHang; // Map lưu trữ tên khách hàng và số lượng sách đã mua

    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        string tenKhachHang = p->Infor.khachHang.tenKhachHang; // Lấy tên khách hàng
        int soLuongSach = stoi(p->Infor.soLuongSach);          // Chuyển số lượng sách sang số nguyên

        // Thống kê số lượng sách mà khách hàng đã mua
        soLuongBanRaCuaKhachHang[tenKhachHang] += soLuongSach;
    }

    // In kết quả thống kê
    cout << "======== Thong ke so luong ban ra cua cac khach hang ========" << endl;
    for (auto &pair : soLuongBanRaCuaKhachHang)
    {
        cout << "Khach hang: " << pair.first << ", So luong ban ra: " << pair.second << endl;
    }
}

void thongKeDoanhThuCuaCacCuonSach(const LIST &Q)
{
    map<string, float> doanhThuCuaSach; // Map lưu trữ tên sách và doanh thu của sách

    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        string tenSach = p->Infor.sach.tenSach;       // Lấy tên sách
        float giaSach = stof(p->Infor.sach.gia);      // Chuyển giá sách sang kiểu float
        int soLuongSach = stoi(p->Infor.soLuongSach); // Chuyển số lượng sách sang số nguyên

        // Tính toán doanh thu của sách
        doanhThuCuaSach[tenSach] += giaSach * soLuongSach;
    }

    // In kết quả thống kê
    cout << "======== Thong ke doanh thu cua cac cuon sach ========" << endl;
    for (auto &pair : doanhThuCuaSach)
    {
        cout << "Sach: " << pair.first << ", Doanh thu: " << pair.second << endl;
    }
}

void thongKeDoanhThuCuaCacKhachHang(const LIST &Q)
{
    map<string, float> doanhThuCuaKhachHang; // Map lưu trữ tên khách hàng và doanh thu của khách hàng

    for (Node *p = Q.Head; p != NULL; p = p->Next)
    {
        string tenKhachHang = p->Infor.khachHang.tenKhachHang; // Lấy tên khách hàng
        float giaSach = stof(p->Infor.sach.gia);               // Chuyển giá sách sang kiểu float
        int soLuongSach = stoi(p->Infor.soLuongSach);          // Chuyển số lượng sách sang số nguyên

        // Tính toán doanh thu của khách hàng
        doanhThuCuaKhachHang[tenKhachHang] += giaSach * soLuongSach;
    }

    // In kết quả thống kê
    cout << "======== Thong ke doanh thu cua cac khach hang ========" << endl;
    for (auto &pair : doanhThuCuaKhachHang)
    {
        cout << "Khach hang: " << pair.first << ", Doanh thu: " << pair.second << endl;
    }
}
