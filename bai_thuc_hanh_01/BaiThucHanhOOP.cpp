#include<bits/stdc++.h>
using namespace std;
const double TY_GIA = 26000; //Em xin được đổi 1 USD = 26000 VND ạ

// Lop xe: mot phuong tien do trong bai
class Vehicle {
private:
    int maXe;
    string loaiXe;
    int gioVao;
    int soGioDo;
    double phiDo;           // don vi VND
    bool coXe;              // true neu dang chua du lieu xe that
    static bool laGioCaoDiem(int gio) {
        return (gio >= 6 && gio <= 9) || (gio >= 15 && gio <= 18);
    }

public:
    //constructor, setter va menu
    static bool maHopLe(int ma) {
        return ma > 0;
    }

    static bool gioVaoHopLe(int gio) {
        return gio >= 0 && gio <= 23;
    }

    static bool soGioHopLe(int soGio) {
        return soGio >= 1 && soGio <= 23;
    }

    static bool khoangGioHopLe(int gio, int soGio) {
        return gioVaoHopLe(gio) && soGioHopLe(soGio) && gio + soGio <= 24;
    }

    // Doi loai xe ve dang chuan khong phan biet hoa thuong
    static string chuanHoaLoai(const string& loai) {
        string ketQua = loai;
        for (size_t i = 0; i < ketQua.length(); i++) {
            ketQua[i] = tolower(ketQua[i]);
        }
        if (ketQua == "car") return "Car";
        if (ketQua == "motorcycle") return "Motorcycle";
        if (ketQua == "bicycle") return "Bicycle";
        return "";
    }

    static bool loaiHopLe(const string& loai) {
        return chuanHoaLoai(loai) != "";
    }

    Vehicle() {
        maXe = 0;
        loaiXe = "Bicycle";
        gioVao = 0;
        soGioDo = 1;
        phiDo = 0;
        coXe = false;
    }
    Vehicle(int ma, const string& loai, int vao, int soGio) {
        maXe = 0;
        loaiXe = "Bicycle";
        gioVao = 0;
        soGioDo = 1;
        phiDo = 0;
        coXe = false;
        string loaiChuan = chuanHoaLoai(loai);
        if (maHopLe(ma) && loaiChuan != "" && khoangGioHopLe(vao, soGio)) {
            maXe = ma;
            loaiXe = loaiChuan;
            gioVao = vao;
            soGioDo = soGio;
            coXe = true;
            tinhPhi();
        }
    }
    int layMaXe() const { return maXe; }
    string layLoaiXe() const { return loaiXe; }
    int layGioVao() const { return gioVao; }
    int laySoGioDo() const { return soGioDo; }
    double layPhiDo() const { return phiDo; }
    bool layCoXe() const { return coXe; }

    bool datMaXe(int ma) {
        if (!maHopLe(ma)) return false;
        maXe = ma;
        return true;
    }

    bool datLoaiXe(const string& loai) {
        string loaiChuan = chuanHoaLoai(loai);
        if (loaiChuan == "") return false;
        loaiXe = loaiChuan;
        tinhPhi();
        return true;
    }

    bool datGioVao(int gio) {
        if (!khoangGioHopLe(gio, soGioDo)) return false;
        gioVao = gio;
        tinhPhi();
        return true;
    }

    bool datSoGioDo(int soGio) {
        if (!khoangGioHopLe(gioVao, soGio)) return false;
        soGioDo = soGio;
        tinhPhi();
        return true;
    }

    bool datPhiDo(double phi) {
        if (phi < 0) return false;
        phiDo = phi;
        return true;
    }

    bool datCoXe(bool trangThai) {
        if (trangThai && !maHopLe(maXe)) return false;
        coXe = trangThai;
        tinhPhi();
        return true;
    }
    // Tinh phi theo muc 3 cua de: tinh bang USD roi doi sang VND
    void tinhPhi() {
        if (!coXe) {
            phiDo = 0;
            return;
        }

        double donGia = 2;
        if (loaiXe == "Car") donGia = 6;
        else if (loaiXe == "Motorcycle") donGia = 4;

        double heSo = 0.95;
        if (laGioCaoDiem(gioVao)) heSo = 1.30;
        int gioDau = soGioDo;
        if (gioDau > 2) gioDau = 2;
        int gioSau = soGioDo - gioDau;

        double phiUSD = gioDau * donGia * heSo + gioSau * donGia * 0.90;

        phiDo = phiUSD * TY_GIA;
    }
    // In dong tieu de cot
    static void inTieuDe() {
        cout << left << setw(12) << "Ma xe"
             << setw(16) << "Loai xe"
             << setw(12) << "Gio vao"
             << setw(16) << "So gio do"
             << "Phi do xe" << endl;
    }

    void inXe() const {
        cout << left << setw(12) << maXe
             << setw(16) << loaiXe
             << setw(12) << gioVao
             << setw(16) << soGioDo
             << fixed << setprecision(0) << phiDo << " VND" << endl;
    }
};
class ParkingLot {
private:
    int maBai;
    char kichThuoc;
    Vehicle xe1;
    Vehicle xe2;
    Vehicle xe3;
    bool coXe1;             // true neu o 1 dang co xe
    bool coXe2;
    bool coXe3;

public:
    static bool kichThuocHopLe(char kt) {
        kt = toupper(kt);
        return kt == 'S' || kt == 'M' || kt == 'L';
    }

    ParkingLot() {
        maBai = 0;
        kichThuoc = 'S';
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;
    }

    ParkingLot(int ma, char kt) {
        maBai = 0;
        kichThuoc = 'S';
        coXe1 = false;
        coXe2 = false;
        coXe3 = false;

        if (ma > 0 && kichThuocHopLe(kt)) {
            maBai = ma;
            kichThuoc = toupper(kt);
        }
    }

    int layMaBai() const { return maBai; }
    char layKichThuoc() const { return kichThuoc; }

    // Suc chua 
    int laySucChua() const {
        if (kichThuoc == 'S') return 1;
        if (kichThuoc == 'M') return 2;
        return 3;
    }

    int demXe() const {
        int dem = 0;
        if (coXe1) dem++;
        if (coXe2) dem++;
        if (coXe3) dem++;
        return dem;
    }

    int soOTrong() const {
        return laySucChua() - demXe();
    }

    // Chi doi ma khi bai dang trong
    bool datMaBai(int ma) {
        if (ma <= 0 || demXe() != 0) return false;
        maBai = ma;
        return true;
    }

    // Chi doi kich thuoc khi cac o dang co xe van nam trong suc chua moi
    bool datKichThuoc(char kt) {
        if (!kichThuocHopLe(kt)) return false;
        kt = toupper(kt);
        int sucChuaMoi = 3;
        if (kt == 'S') sucChuaMoi = 1;
        else if (kt == 'M') sucChuaMoi = 2;

        if (sucChuaMoi < 3 && coXe3) return false;
        if (sucChuaMoi < 2 && coXe2) return false;
        kichThuoc = kt;
        return true;
    }

    bool coChuaXe(int ma) const {
        if (coXe1 && xe1.layMaXe() == ma) return true;
        if (coXe2 && xe2.layMaXe() == ma) return true;
        if (coXe3 && xe3.layMaXe() == ma) return true;
        return false;
    }

    bool themXe(const Vehicle& xe) {
        if (!xe.layCoXe()) return false;
        if (coChuaXe(xe.layMaXe())) return false;
        if (soOTrong() <= 0) return false;

        if (!coXe1) {
            xe1 = xe;
            coXe1 = true;
        }
        else if (laySucChua() >= 2 && !coXe2) {
            xe2 = xe;
            coXe2 = true;
        }
        else if (laySucChua() >= 3 && !coXe3) {
            xe3 = xe;
            coXe3 = true;
        }
        else {
            return false;
        }
        return true;
    }

    // Lay xe ra theo ma xe
    bool layXeRa(int maXe) {
        if (coXe1 && xe1.layMaXe() == maXe) {
            xe1 = Vehicle();
            coXe1 = false;
            return true;
        }
        if (coXe2 && xe2.layMaXe() == maXe) {
            xe2 = Vehicle();
            coXe2 = false;
            return true;
        }
        if (coXe3 && xe3.layMaXe() == maXe) {
            xe3 = Vehicle();
            coXe3 = false;
            return true;
        }
        return false;
    }
    // Cac ham thong ke dung cho bao cao (menu 7 va 8)
    int demTheoLoai(const string& loai) const {
        int dem = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) dem++;
        if (coXe2 && xe2.layLoaiXe() == loai) dem++;
        if (coXe3 && xe3.layLoaiXe() == loai) dem++;
        return dem;
    }

    double phiTheoLoai(const string& loai) const {
        double tong = 0;
        if (coXe1 && xe1.layLoaiXe() == loai) tong += xe1.layPhiDo();
        if (coXe2 && xe2.layLoaiXe() == loai) tong += xe2.layPhiDo();
        if (coXe3 && xe3.layLoaiXe() == loai) tong += xe3.layPhiDo();
        return tong;
    }

    double tongPhi() const {
        double tong = 0;
        if (coXe1) tong += xe1.layPhiDo();
        if (coXe2) tong += xe2.layPhiDo();
        if (coXe3) tong += xe3.layPhiDo();
        return tong;
    }

    // In mot dong tom tat: ma bai, kich thuoc, so xe (dung cho menu 5)
    void inTomTat() const {
        cout << "Ma bai: " << maBai
             << " | Kich thuoc: " << kichThuoc
             << " | So xe: " << demXe() << "/" << laySucChua() << endl;
    }

    // In tom tat bai va danh sach xe hien co (dung cho menu 6)
    void inThongTinBai() const {
        cout << endl;
        inTomTat();

        if (demXe() == 0) {
            cout << "Bai do chua co xe." << endl;
            return;
        }

        Vehicle::inTieuDe();
        if (coXe1) xe1.inXe();
        if (coXe2) xe2.inXe();
        if (coXe3) xe3.inXe();
    }

    // In ma bai va cac xe thuoc loai can tim, khong in gi neu bai khong co xe loai do
    void inXeTheoLoai(const string& loai) const {
        if (demTheoLoai(loai) == 0) return;

        cout << "\nBai do " << maBai << ":" << endl;
        Vehicle::inTieuDe();
        if (coXe1 && xe1.layLoaiXe() == loai) xe1.inXe();
        if (coXe2 && xe2.layLoaiXe() == loai) xe2.inXe();
        if (coXe3 && xe3.layLoaiXe() == loai) xe3.inXe();
    }
};

// Lop SystemInterface: nhap xuat console va dieu phoi chuong trinh
class SystemInterface {
private:
    ParkingLot bai1;
    ParkingLot bai2;
    ParkingLot bai3;
    bool coBai1;
    bool coBai2;
    bool coBai3;
    bool dung;              // true khi het du lieu nhap (EOF) de thoat chuong trinh

    // Cac ham truy cap bai theo vi tri 1..3
    bool baiTonTai(int viTri) const {
        if (viTri == 1) return coBai1;
        if (viTri == 2) return coBai2;
        return coBai3;
    }

    void datBaiTonTai(int viTri, bool giaTri) {
        if (viTri == 1) coBai1 = giaTri;
        else if (viTri == 2) coBai2 = giaTri;
        else coBai3 = giaTri;
    }

    ParkingLot& baiTai(int viTri) {
        if (viTri == 1) return bai1;
        if (viTri == 2) return bai2;
        return bai3;
    }

    const ParkingLot& baiTai(int viTri) const {
        if (viTri == 1) return bai1;
        if (viTri == 2) return bai2;
        return bai3;
    }

    int demBai() const {
        int dem = 0;
        if (coBai1) dem++;
        if (coBai2) dem++;
        if (coBai3) dem++;
        return dem;
    }
    // Cac ham tim kiem tra ve vi tri 
    int timBaiTheoMa(int ma) const {
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri) && baiTai(viTri).layMaBai() == ma) return viTri;
        }
        return 0;
    }

    int timBaiTheoXe(int maXe) const {
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri) && baiTai(viTri).coChuaXe(maXe)) return viTri;
        }
        return 0;
    }

    int timViTriTrong() const {
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (!baiTonTai(viTri)) return viTri;
        }
        return 0;
    }
    int chonBaiTot() const {
        int viTriTot = 0;
        int itTrongNhat = 4;
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri) && baiTai(viTri).soOTrong() > 0) {
                if (baiTai(viTri).soOTrong() < itTrongNhat) {
                    itTrongNhat = baiTai(viTri).soOTrong();
                    viTriTot = viTri;
                }
            }
        }
        return viTriTot;
    }

    int docSoNguyen(const string& loiNhac) {
        int so;
        while (true) {
            cout << loiNhac;
            if (cin >> so) {
                cin.ignore(1000, '\n');
                return so;
            }
            if (cin.eof()) {
                dung = true;
                return 0;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Vui long nhap so nguyen." << endl;
        }
    }
    string docChuoi(const string& loiNhac) {
        string chuoi;
        cout << loiNhac;
        if (!(cin >> chuoi)) {
            dung = true;
            return "";
        }
        cin.ignore(1000, '\n');
        return chuoi;
    }
    void inTien(double tien) const {
        cout << fixed << setprecision(0) << tien << " VND";
    }

    // Dem so xe va tong phi cua mot loai xe tren toan he thong
    void thongKeTheoLoai(const string& loai, int& dem, double& tong) const {
        dem = 0;
        tong = 0;
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri)) {
                dem += baiTai(viTri).demTheoLoai(loai);
                tong += baiTai(viTri).phiTheoLoai(loai);
            }
        }
    }
    // In phi trung binh cua mot loai xe tren toan he thong
    void inTrungBinhTheoLoai(const string& loai) const {
        int dem;
        double tong;
        thongKeTheoLoai(loai, dem, tong);

        cout << loai << ": ";
        if (dem == 0) {
            cout << "Khong co xe" << endl;
        }
        else {
            cout << dem << " xe, trung binh ";
            inTien(tong / dem);
            cout << "/xe" << endl;
        }
    }

    // In so xe, tong phi va phi trung binh cua mot loai xe trong mot bai
    void inLoaiTrongBai(const ParkingLot& bai, const string& loai) const {
        int dem = bai.demTheoLoai(loai);
        double tong = bai.phiTheoLoai(loai);

        cout << "  " << loai << ": ";
        if (dem == 0) {
            cout << "Khong co xe" << endl;
        }
        else {
            cout << dem << " xe, tong phi ";
            inTien(tong);
            cout << ", trung binh ";
            inTien(tong / dem);
            cout << "/xe" << endl;
        }
    }
public:
    SystemInterface() {
        coBai1 = false;
        coBai2 = false;
        coBai3 = false;
        dung = false;
    }

    // Menu 1: kiem tra tung dieu kien
    void taoBai() {
        if (demBai() == 3) {
            cout << "He thong da co toi da 3 bai do." << endl;
            return;
        }
        int maBai = docSoNguyen("Nhap ma bai do: ");
        if (dung) return;
        if (maBai <= 0) {
            cout << "Ma bai phai lon hon 0." << endl;
            return;
        }
        if (timBaiTheoMa(maBai) != 0) {
            cout << "Ma bai do da ton tai." << endl;
            return;
        }
        string kichThuoc = docChuoi("Nhap kich thuoc (S/M/L): ");
        if (dung) return;
        if (kichThuoc.length() != 1 || !ParkingLot::kichThuocHopLe(kichThuoc[0])) {
            cout << "Kich thuoc khong hop le." << endl;
            return;
        }

        int viTri = timViTriTrong();
        baiTai(viTri) = ParkingLot(maBai, kichThuoc[0]);
        datBaiTonTai(viTri, true);
        cout << "Tao bai do thanh cong." << endl;
    }

    // Menu 2: nhap va kiem tra thong tin xe, xep bai 
    void themXeVaoBai() {
        if (demBai() == 0) {
            cout << "Hay tao bai do truoc." << endl;
            return;
        }
        if (chonBaiTot() == 0) {
            cout << "Tat ca bai do deu da day." << endl;
            return;
        }
        int maXe = docSoNguyen("Nhap ma xe: ");
        if (dung) return;
        if (!Vehicle::maHopLe(maXe)) {
            cout << "Ma xe phai lon hon 0." << endl;
            return;
        }
        if (timBaiTheoXe(maXe) != 0) {
            cout << "Ma xe da ton tai." << endl;
            return;
        }

        string loaiXe = docChuoi("Nhap loai xe (Car/Motorcycle/Bicycle): ");
        if (dung) return;
        if (!Vehicle::loaiHopLe(loaiXe)) {
            cout << "Loai xe khong hop le." << endl;
            return;
        }

        int gioVao = docSoNguyen("Nhap gio vao (0-23): ");
        if (dung) return;
        if (!Vehicle::gioVaoHopLe(gioVao)) {
            cout << "Gio vao khong hop le." << endl;
            return;
        }
        int soGioDo = docSoNguyen("Nhap so gio do (1-23): ");
        if (dung) return;
        if (!Vehicle::soGioHopLe(soGioDo)) {
            cout << "So gio do khong hop le." << endl;
            return;
        }
        if (!Vehicle::khoangGioHopLe(gioVao, soGioDo)) {
            cout << "Khong cho phep do xe qua dem." << endl;
            return;
        }

        Vehicle xe(maXe, loaiXe, gioVao, soGioDo);
        int viTri = chonBaiTot();

        if (baiTai(viTri).themXe(xe)) {
            cout << "Them xe thanh cong vao bai " << baiTai(viTri).layMaBai() << "." << endl;
            cout << "Phi do xe: ";
            inTien(xe.layPhiDo());
            cout << endl;
        }
        else {
            cout << "Khong the them xe vao bai do." << endl;
        }
    }

    // Menu 3: xoa bai 
    void xoaBai() {
        int maBai = docSoNguyen("Nhap ma bai do can xoa: ");
        if (dung) return;

        int viTri = timBaiTheoMa(maBai);
        if (viTri == 0) {
            cout << "Khong tim thay bai do." << endl;
            return;
        }

        baiTai(viTri) = ParkingLot();
        datBaiTonTai(viTri, false);
        cout << "Da xoa bai do va cac xe trong bai." << endl;
    }

    // Menu 4: tim bai chua xe roi lay xe ra
    void layXeRaKhoiBai() {
        int maXe = docSoNguyen("Nhap ma xe can lay ra: ");
        if (dung) return;

        int viTri = timBaiTheoXe(maXe);
        if (viTri == 0) {
            cout << "Khong tim thay xe." << endl;
            return;
        }

        baiTai(viTri).layXeRa(maXe);
        cout << "Da lay xe ra khoi bai " << baiTai(viTri).layMaBai() << "." << endl;
    }

    // Menu 5
    void hienThiTatCaBai() const {
        if (demBai() == 0) {
            cout << "Chua co bai do nao." << endl;
            return;
        }

        cout << "\n===== DANH SACH BAI DO =====" << endl;
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri)) baiTai(viTri).inTomTat();
        }
    }

    // Menu 6
    void hienThiXeTheoBai() {
        int maBai = docSoNguyen("Nhap ma bai do: ");
        if (dung) return;

        int viTri = timBaiTheoMa(maBai);
        if (viTri == 0) {
            cout << "Khong tim thay bai do." << endl;
            return;
        }

        baiTai(viTri).inThongTinBai();
    }    // Menu 7: in ten bai, tieu de cot
    void hienThiXeTheoLoai() {
        string loaiXe = docChuoi("Nhap loai xe (Car/Motorcycle/Bicycle): ");
        if (dung) return;
        if (!Vehicle::loaiHopLe(loaiXe)) {
            cout << "Loai xe khong hop le." << endl;
            return;
        }
        loaiXe = Vehicle::chuanHoaLoai(loaiXe);
        int dem;
        double tong;
        thongKeTheoLoai(loaiXe, dem, tong);
        if (dem == 0) {
            cout << "Khong co xe thuoc loai nay." << endl;
            return;
        }

        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri)) baiTai(viTri).inXeTheoLoai(loaiXe);
        }
    }
    // Menu 8: phi trung binh theo loai xe toan he thong, chi tiet tung bai
    void hienThiBaoCaoPhi() const {
        cout << "\n===== BAO CAO PHI TOAN HE THONG =====" << endl;
        inTrungBinhTheoLoai("Car");
        inTrungBinhTheoLoai("Motorcycle");
        inTrungBinhTheoLoai("Bicycle");

        cout << "\n===== PHAN TICH THEO TUNG BAI =====" << endl;
        double tongPhiHeThong = 0;
        int tongSoXe = 0;
        for (int viTri = 1; viTri <= 3; viTri++) {
            if (baiTonTai(viTri)) {
                cout << "\nBai " << baiTai(viTri).layMaBai() << ":" << endl;
                inLoaiTrongBai(baiTai(viTri), "Car");
                inLoaiTrongBai(baiTai(viTri), "Motorcycle");
                inLoaiTrongBai(baiTai(viTri), "Bicycle");
                cout << "  Tong phi bai: ";
                inTien(baiTai(viTri).tongPhi());
                cout << endl;

                tongPhiHeThong += baiTai(viTri).tongPhi();
                tongSoXe += baiTai(viTri).demXe();
            }
        }
        cout << "\nTong phi toan he thong: ";
        inTien(tongPhiHeThong);
        cout << endl;
        cout << "Tong so xe dang do: " << tongSoXe << endl;
    }

    void chayMenu() {
        int luaChon = 0;
        while (!dung && luaChon != 9) {
            cout << "\n========== QUAN LY BAI DO XE ==========" << endl;
            cout << "1. Tao bai do xe moi" << endl;
            cout << "2. Them xe vao bai do" << endl;
            cout << "3. Xoa bai do xe" << endl;
            cout << "4. Lay xe ra khoi bai" << endl;
            cout << "5. Hien thi danh sach bai do" << endl;
            cout << "6. Hien thi xe theo bai do" << endl;
            cout << "7. Liet ke xe theo loai" << endl;
            cout << "8. Bao cao phi do xe" << endl;
            cout << "9. Thoat chuong trinh" << endl;

            luaChon = docSoNguyen("Nhap lua chon: ");
            if (dung) break;
            switch (luaChon) {
            case 1: taoBai(); break;
            case 2: themXeVaoBai(); break;
            case 3: xoaBai(); break;
            case 4: layXeRaKhoiBai(); break;
            case 5: hienThiTatCaBai(); break;
            case 6: hienThiXeTheoBai(); break;
            case 7: hienThiXeTheoLoai(); break;
            case 8: hienThiBaoCaoPhi(); break;
            case 9: cout << "Da thoat chuong trinh." << endl; break;
            default: cout << "Lua chon khong hop le." << endl;
            }
        }
    }
};

int main() {
    SystemInterface app;
    app.chayMenu();
    return 0;
}
