#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <ctime>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

    void cap_nhat_phi() { phi_do = tinh_phi(); }

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    int lay_gio_vao() const;
    int lay_tg_do() const;
    double lay_phi_do() const;
    void dat_ma_xe(int ma);
    void dat_loai_xe(const string& loai);
    void dat_gio_vao(int gio);
    void dat_tg_do(int tg);

    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0), phi_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg), phi_do(0) {
    cap_nhat_phi();
}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
int phuong_tien::lay_gio_vao() const { return gio_vao; }
int phuong_tien::lay_tg_do() const { return tg_do; }
double phuong_tien::lay_phi_do() const { return phi_do; }

void phuong_tien::dat_ma_xe(int ma) { ma_xe = ma; }
void phuong_tien::dat_loai_xe(const string& loai) { loai_xe = loai; cap_nhat_phi(); }
void phuong_tien::dat_gio_vao(int gio) { gio_vao = gio; cap_nhat_phi(); }
void phuong_tien::dat_tg_do(int tg) { tg_do = tg; cap_nhat_phi(); }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << phi_do << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int TOI_DA_XE = 3;      // suc chua vat ly
    phuong_tien ds_xe[TOI_DA_XE];        // mang tinh
    int so_xe_hien_tai;                  // kich thuoc logic

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const;
    int lay_so_xe() const;
    int lay_suc_chua() const;            // suc chua theo kich thuoc S/M/L
    const phuong_tien& lay_xe(int i) const;

    bool da_day() const;
    bool them_xe(const phuong_tien& v);
    bool xoa_xe(int ma_xe);
    int tim_vi_tri_xe(int ma_xe) const;
    void hien_thi_bai() const;
    void hien_thi_xe_theo_loai(const string& loai) const;
    void thong_ke_loai(const string& loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_xe_hien_tai(0) {}
bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_xe_hien_tai(0) {}

int bai_xe::lay_ma() const { return ma_bai; }
char bai_xe::lay_kich_thuoc() const { return kich_thuoc; }
int bai_xe::lay_so_xe() const { return so_xe_hien_tai; }
const phuong_tien& bai_xe::lay_xe(int i) const { return ds_xe[i]; }

int bai_xe::lay_suc_chua() const {
    return (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
}
bool bai_xe::da_day() const {
    return so_xe_hien_tai >= lay_suc_chua();
}

bool bai_xe::them_xe(const phuong_tien& v) {
    if (da_day()) return false;
    ds_xe[so_xe_hien_tai] = v;
    ++so_xe_hien_tai;
    return true;
}

int bai_xe::tim_vi_tri_xe(int ma_xe) const {
    for (int i = 0; i < so_xe_hien_tai; ++i)
        if (ds_xe[i].lay_ma_xe() == ma_xe) return i;
    return -1;
}

bool bai_xe::xoa_xe(int ma_xe) {
    int vt = tim_vi_tri_xe(ma_xe);
    if (vt == -1) return false;
    for (int i = vt; i < so_xe_hien_tai - 1; ++i)
        ds_xe[i] = ds_xe[i + 1];
    --so_xe_hien_tai;
    return true;
}

void bai_xe::hien_thi_bai() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_xe_hien_tai << "/" << lay_suc_chua() << " xe\n";
    for (int i = 0; i < so_xe_hien_tai; ++i)
        ds_xe[i].hien_thi();
}

void bai_xe::hien_thi_xe_theo_loai(const string& loai) const {
    for (int i = 0; i < so_xe_hien_tai; ++i)
        if (ds_xe[i].lay_loai_xe() == loai) {
            cout << "  [Bai " << ma_bai << "]";
            ds_xe[i].hien_thi();
        }
}

void bai_xe::thong_ke_loai(const string& loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_xe_hien_tai; ++i)
        if (ds_xe[i].lay_loai_xe() == loai) {
            ++dem;
            tong += ds_xe[i].lay_phi_do();
        }
}

class SystemInterface {
private:
    static const int TOI_DA_BAI = 10;    // suc chua vat ly
    bai_xe ds_bai[TOI_DA_BAI];           // mang tinh
    int so_bai_hien_tai;                 // kich thuoc logic

    int nhap_so_nguyen(const string& loi_nhac, int tu, int den) const;
    char nhap_kich_thuoc() const;
    string nhap_loai_xe(const string& loi_nhac) const;

    int tim_vi_tri_bai(int ma) const;

public:
    SystemInterface();
    void runMenu();
    bool ma_bai_ton_tai(int ma) const;
    bool ma_xe_ton_tai(int ma) const;
    int sinh_ma_ngau_nhien(bool cho_bai) const;
};

SystemInterface::SystemInterface() : so_bai_hien_tai(0) {
    srand((unsigned)time(0));
}

int SystemInterface::nhap_so_nguyen(const string& loi_nhac, int tu, int den) const {
    int x;
    while (true) {
        cout << loi_nhac;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (x >= tu && x <= den) return x;
            cout << "Gia tri phai nam trong khoang [" << tu << ", " << den << "]. Nhap lai!\n";
        } else {
            if (cin.eof()) exit(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Loi: vui long nhap SO nguyen. Nhap lai!\n";
        }
    }
}

char SystemInterface::nhap_kich_thuoc() const {
    char kt;
    while (true) {
        cout << "Kich thuoc (S/M/L): ";
        if (cin >> kt) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            kt = (char)toupper((unsigned char)kt);
            if (kt == 'S' || kt == 'M' || kt == 'L') return kt;
            cout << "Chi chap nhan S, M hoac L. Nhap lai!\n";
        } else {
            if (cin.eof()) exit(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Loi nhap lieu. Nhap lai!\n";
        }
    }
}

string SystemInterface::nhap_loai_xe(const string& loi_nhac) const {
    string loai;
    while (true) {
        cout << loi_nhac;
        if (cin >> loai) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (loai == "Car" || loai == "Motorcycle" || loai == "Bicycle") return loai;
            cout << "Chi chap nhan Car, Motorcycle hoac Bicycle. Nhap lai!\n";
        } else {
            if (cin.eof()) exit(0);
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Loi nhap lieu. Nhap lai!\n";
        }
    }
}

int SystemInterface::tim_vi_tri_bai(int ma) const {
    for (int i = 0; i < so_bai_hien_tai; ++i)
        if (ds_bai[i].lay_ma() == ma) return i;
    return -1;
}

bool SystemInterface::ma_bai_ton_tai(int ma) const {
    return tim_vi_tri_bai(ma) != -1;
}

bool SystemInterface::ma_xe_ton_tai(int ma) const {
    for (int i = 0; i < so_bai_hien_tai; ++i)
        if (ds_bai[i].tim_vi_tri_xe(ma) != -1) return true;
    return false;
}

int SystemInterface::sinh_ma_ngau_nhien(bool cho_bai) const {
    int ma;
    do {
        ma = 1000 + rand() % 9000;   // 1000 - 9999
    } while (cho_bai ? ma_bai_ton_tai(ma) : ma_xe_ton_tai(ma));
    return ma;
}

void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        chon = nhap_so_nguyen("Chon: ", 1, 9);

        switch (chon) {
        case 1: {
            if (so_bai_hien_tai >= TOI_DA_BAI) {
                cout << "He thong da dat toi da " << TOI_DA_BAI << " bai do!\n";
                break;
            }
            int ma = nhap_so_nguyen("Ma bai: ", 1, 999999);
            char kt = nhap_kich_thuoc();
            if (ma_bai_ton_tai(ma)) {
                int ma_moi = sinh_ma_ngau_nhien(true);
                cout << "Canh bao: Ma bai " << ma << " da ton tai! Tu dong gan ma moi: " << ma_moi << "\n";
                ma = ma_moi;
            }
            ds_bai[so_bai_hien_tai] = bai_xe(ma, kt);
            ++so_bai_hien_tai;
            cout << "Da tao bai " << ma << "\n";
            break;
        }
        case 2: {
            if (so_bai_hien_tai == 0) {
                cout << "Chua co bai do nao! Hay tao bai do truoc.\n";
                break;
            }
            int ma = nhap_so_nguyen("Ma xe: ", 1, 999999);
            string loai = nhap_loai_xe("Loai (Car/Motorcycle/Bicycle): ");
            int gio = nhap_so_nguyen("Gio vao (0-23): ", 0, 23);
            int tg = nhap_so_nguyen("Thoi luong (1-23): ", 1, 23);
            if (ma_xe_ton_tai(ma)) {
                int ma_moi = sinh_ma_ngau_nhien(false);
                cout << "Canh bao: Ma xe " << ma << " da ton tai! Tu dong gan ma moi: " << ma_moi << "\n";
                ma = ma_moi;
            }
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            for (int i = 0; i < so_bai_hien_tai && !ok; ++i) {
                if (!ds_bai[i].da_day()) {
                    ok = ds_bai[i].them_xe(v);
                    if (ok) cout << "Da them xe " << ma << " vao bai " << ds_bai[i].lay_ma()
                                 << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                }
            }
            if (!ok) cout << "Canh bao: Tat ca bai da day!\n";
            break;
        }
        case 3: {
            int ma = nhap_so_nguyen("Ma bai can xoa: ", 1, 999999);
            int vt = tim_vi_tri_bai(ma);
            if (vt == -1) {
                cout << "Khong tim thay bai " << ma << "\n";
                break;
            }
            for (int i = vt; i < so_bai_hien_tai - 1; ++i)
                ds_bai[i] = ds_bai[i + 1];
            --so_bai_hien_tai;
            cout << "Da xoa bai " << ma << "\n";
            break;
        }
        case 4: {
            int ma = nhap_so_nguyen("Ma xe can lay ra: ", 1, 999999);
            bool ok = false;
            for (int i = 0; i < so_bai_hien_tai && !ok; ++i)
                ok = ds_bai[i].xoa_xe(ma);
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
            break;
        }
        case 5: {
            if (so_bai_hien_tai == 0) {
                cout << "Chua co bai do nao.\n";
                break;
            }
            for (int i = 0; i < so_bai_hien_tai; ++i)
                ds_bai[i].hien_thi_bai();
            break;
        }
        case 6: {
            int ma = nhap_so_nguyen("Ma bai: ", 1, 999999);
            int vt = tim_vi_tri_bai(ma);
            if (vt == -1) cout << "Khong tim thay bai " << ma << "\n";
            else ds_bai[vt].hien_thi_bai();
            break;
        }
        case 7: {
            string loai = nhap_loai_xe("Loai xe (Car/Motorcycle/Bicycle): ");
            int tong_dem = 0;
            for (int i = 0; i < so_bai_hien_tai; ++i) {
                int dem; double tong;
                ds_bai[i].thong_ke_loai(loai, dem, tong);
                if (dem > 0) {
                    ds_bai[i].hien_thi_xe_theo_loai(loai);
                    tong_dem += dem;
                }
            }
            if (tong_dem == 0) cout << "Khong co xe loai " << loai << "\n";
            break;
        }
        case 8: {
            const string loai_arr[3] = {"Car", "Motorcycle", "Bicycle"};
            cout << "--- Toan he thong ---\n";
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                for (int i = 0; i < so_bai_hien_tai; ++i) {
                    int d; double s;
                    ds_bai[i].thong_ke_loai(loai_arr[t], d, s);
                    dem += d; tong += s;
                }
                cout << loai_arr[t] << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
            cout << "--- Theo tung bai ---\n";
            for (int i = 0; i < so_bai_hien_tai; ++i) {
                cout << "Bai " << ds_bai[i].lay_ma() << ":\n";
                for (int t = 0; t < 3; ++t) {
                    int d; double s;
                    ds_bai[i].thong_ke_loai(loai_arr[t], d, s);
                    cout << "  " << loai_arr[t] << ": ";
                    if (d == 0) cout << "khong co xe\n";
                    else cout << d << " xe | TB: $" << fixed << setprecision(2) << s / d << "\n";
                }
            }
            break;
        }
        case 9:
            cout << "Tam biet!\n";
            break;
        }
    } while (chon != 9);
}

int main() {
    SystemInterface he_thong;
    he_thong.runMenu();
    return 0;
}