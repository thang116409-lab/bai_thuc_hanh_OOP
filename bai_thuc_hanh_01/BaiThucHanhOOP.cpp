#include<bits/stdc++.h>
using namespace std;

const double EXCHANGE_RATE = 26000; //Em xin được đổi 1 USD = 26000 VND ạ

// Lop Vehicle: mot phuong tien do trong bai
class Vehicle {
private:
    int vehicleID;
    string vehicleType;
    int entryTime;
    int parkingDuration;
    double parkingFee;      // don vi VND
    bool isOccupied;        // true neu dang chua du lieu xe that

    // Gio cao diem
    static bool isPeakHour(int hour) {
        return (hour >= 6 && hour <= 9) || (hour >= 15 && hour <= 18);
    }

public:
    //constructor, setter va menu
    static bool isValidID(int id) {
        return id > 0;
    }

    static bool isValidEntryTime(int time) {
        return time >= 0 && time <= 23;
    }

    static bool isValidDuration(int duration) {
        return duration >= 1 && duration <= 23;
    }

    static bool isValidTimeRange(int time, int duration) {
        return isValidEntryTime(time) && isValidDuration(duration) && time + duration <= 24;
    }

    // Doi loai xe ve dang chuan khong phan biet hoa thuong
    static string normalizeType(const string& type) {
        string result = type;
        for (size_t i = 0; i < result.length(); i++) {
            result[i] = tolower(result[i]);
        }
        if (result == "car") return "Car";
        if (result == "motorcycle") return "Motorcycle";
        if (result == "bicycle") return "Bicycle";
        return "";
    }

    static bool isValidType(const string& type) {
        return normalizeType(type) != "";
    }

    Vehicle() {
        vehicleID = 0;
        vehicleType = "Bicycle";
        entryTime = 0;
        parkingDuration = 1;
        parkingFee = 0;
        isOccupied = false;
    }

    Vehicle(int id, const string& type, int entry, int duration) {
        vehicleID = 0;
        vehicleType = "Bicycle";
        entryTime = 0;
        parkingDuration = 1;
        parkingFee = 0;
        isOccupied = false;

        string t = normalizeType(type);
        if (isValidID(id) && t != "" && isValidTimeRange(entry, duration)) {
            vehicleID = id;
            vehicleType = t;
            entryTime = entry;
            parkingDuration = duration;
            isOccupied = true;
            calculateFee();
        }
    }

    int getVehicleID() const { return vehicleID; }
    string getVehicleType() const { return vehicleType; }
    int getEntryTime() const { return entryTime; }
    int getParkingDuration() const { return parkingDuration; }
    double getParkingFee() const { return parkingFee; }
    bool getIsOccupied() const { return isOccupied; }

    bool setVehicleID(int id) {
        if (!isValidID(id)) return false;
        vehicleID = id;
        return true;
    }

    bool setVehicleType(const string& type) {
        string t = normalizeType(type);
        if (t == "") return false;
        vehicleType = t;
        calculateFee();
        return true;
    }

    bool setEntryTime(int time) {
        if (!isValidTimeRange(time, parkingDuration)) return false;
        entryTime = time;
        calculateFee();
        return true;
    }

    bool setParkingDuration(int duration) {
        if (!isValidTimeRange(entryTime, duration)) return false;
        parkingDuration = duration;
        calculateFee();
        return true;
    }

    bool setParkingFee(double fee) {
        if (fee < 0) return false;
        parkingFee = fee;
        return true;
    }

    bool setIsOccupied(bool status) {
        if (status && !isValidID(vehicleID)) return false;
        isOccupied = status;
        calculateFee();
        return true;
    }

    // Tinh phi theo muc 3 cua de: tinh bang USD roi doi sang VND
    void calculateFee() {
        if (!isOccupied) {
            parkingFee = 0;
            return;
        }

        double price = 2;
        if (vehicleType == "Car") price = 6;
        else if (vehicleType == "Motorcycle") price = 4;

        double rate = 0.95;
        if (isPeakHour(entryTime)) rate = 1.30;

        int firstHours = parkingDuration;
        if (firstHours > 2) firstHours = 2;
        int lateHours = parkingDuration - firstHours;

        double feeUSD = firstHours * price * rate + lateHours * price * 0.90;

        parkingFee = feeUSD * EXCHANGE_RATE;
    }

    // In dong tieu de cot
    static void displayHeader() {
        cout << left << setw(12) << "Ma xe"
             << setw(16) << "Loai xe"
             << setw(12) << "Gio vao"
             << setw(16) << "So gio do"
             << "Phi do xe" << endl;
    }

    void display() const {
        cout << left << setw(12) << vehicleID
             << setw(16) << vehicleType
             << setw(12) << entryTime
             << setw(16) << parkingDuration
             << fixed << setprecision(0) << parkingFee << " VND" << endl;
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    Vehicle vehicle1;
    Vehicle vehicle2;
    Vehicle vehicle3;
    bool hasVehicle1;       // true neu o 1 dang co xe
    bool hasVehicle2;
    bool hasVehicle3;

public:
    static bool isValidSize(char sz) {
        sz = toupper(sz);
        return sz == 'S' || sz == 'M' || sz == 'L';
    }

    ParkingLot() {
        parkID = 0;
        size = 'S';
        hasVehicle1 = false;
        hasVehicle2 = false;
        hasVehicle3 = false;
    }

    ParkingLot(int id, char sz) {
        parkID = 0;
        size = 'S';
        hasVehicle1 = false;
        hasVehicle2 = false;
        hasVehicle3 = false;

        if (id > 0 && isValidSize(sz)) {
            parkID = id;
            size = toupper(sz);
        }
    }

    int getParkID() const { return parkID; }
    char getSize() const { return size; }

    // Suc chua 
    int getCapacity() const {
        if (size == 'S') return 1;
        if (size == 'M') return 2;
        return 3;
    }

    int countVehicles() const {
        int count = 0;
        if (hasVehicle1) count++;
        if (hasVehicle2) count++;
        if (hasVehicle3) count++;
        return count;
    }

    int freeSlots() const {
        return getCapacity() - countVehicles();
    }

    // Chi doi ma khi bai dang trong
    bool setParkID(int id) {
        if (id <= 0 || countVehicles() != 0) return false;
        parkID = id;
        return true;
    }

    // Chi doi kich thuoc khi cac o dang co xe van nam trong suc chua moi
    bool setSize(char sz) {
        if (!isValidSize(sz)) return false;
        sz = toupper(sz);
        int newCapacity = 3;
        if (sz == 'S') newCapacity = 1;
        else if (sz == 'M') newCapacity = 2;

        if (newCapacity < 3 && hasVehicle3) return false;
        if (newCapacity < 2 && hasVehicle2) return false;
        size = sz;
        return true;
    }

    bool containsVehicle(int id) const {
        if (hasVehicle1 && vehicle1.getVehicleID() == id) return true;
        if (hasVehicle2 && vehicle2.getVehicleID() == id) return true;
        if (hasVehicle3 && vehicle3.getVehicleID() == id) return true;
        return false;
    }

    bool addVehicle(const Vehicle& v) {
        if (!v.getIsOccupied()) return false;
        if (containsVehicle(v.getVehicleID())) return false;
        if (freeSlots() <= 0) return false;

        if (!hasVehicle1) {
            vehicle1 = v;
            hasVehicle1 = true;
        }
        else if (getCapacity() >= 2 && !hasVehicle2) {
            vehicle2 = v;
            hasVehicle2 = true;
        }
        else if (getCapacity() >= 3 && !hasVehicle3) {
            vehicle3 = v;
            hasVehicle3 = true;
        }
        else {
            return false;
        }
        return true;
    }

    // Lay xe ra theo ma xe
    bool removeVehicle(int vID) {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) {
            vehicle1 = Vehicle();
            hasVehicle1 = false;
            return true;
        }
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) {
            vehicle2 = Vehicle();
            hasVehicle2 = false;
            return true;
        }
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) {
            vehicle3 = Vehicle();
            hasVehicle3 = false;
            return true;
        }
        return false;
    }
    // Cac ham thong ke dung cho bao cao (menu 7 va 8)
    int countByType(const string& type) const {
        int count = 0;
        if (hasVehicle1 && vehicle1.getVehicleType() == type) count++;
        if (hasVehicle2 && vehicle2.getVehicleType() == type) count++;
        if (hasVehicle3 && vehicle3.getVehicleType() == type) count++;
        return count;
    }

    double feeByType(const string& type) const {
        double total = 0;
        if (hasVehicle1 && vehicle1.getVehicleType() == type) total += vehicle1.getParkingFee();
        if (hasVehicle2 && vehicle2.getVehicleType() == type) total += vehicle2.getParkingFee();
        if (hasVehicle3 && vehicle3.getVehicleType() == type) total += vehicle3.getParkingFee();
        return total;
    }

    double totalFee() const {
        double total = 0;
        if (hasVehicle1) total += vehicle1.getParkingFee();
        if (hasVehicle2) total += vehicle2.getParkingFee();
        if (hasVehicle3) total += vehicle3.getParkingFee();
        return total;
    }

    // In mot dong tom tat: ma bai, kich thuoc, so xe (dung cho menu 5)
    void displaySummary() const {
        cout << "Ma bai: " << parkID
             << " | Kich thuoc: " << size
             << " | So xe: " << countVehicles() << "/" << getCapacity() << endl;
    }

    // In tom tat bai va danh sach xe hien co (dung cho menu 6)
    void displayLotInfo() const {
        cout << endl;
        displaySummary();

        if (countVehicles() == 0) {
            cout << "Bai do chua co xe." << endl;
            return;
        }

        Vehicle::displayHeader();
        if (hasVehicle1) vehicle1.display();
        if (hasVehicle2) vehicle2.display();
        if (hasVehicle3) vehicle3.display();
    }

    // In ma bai va cac xe thuoc loai can tim, khong in gi neu bai khong co xe loai do
    void displayVehiclesByType(const string& type) const {
        if (countByType(type) == 0) return;

        cout << "\nBai do " << parkID << ":" << endl;
        Vehicle::displayHeader();
        if (hasVehicle1 && vehicle1.getVehicleType() == type) vehicle1.display();
        if (hasVehicle2 && vehicle2.getVehicleType() == type) vehicle2.display();
        if (hasVehicle3 && vehicle3.getVehicleType() == type) vehicle3.display();
    }
};

// Lop SystemInterface: nhap xuat console va dieu phoi chuong trinh
class SystemInterface {
private:
    ParkingLot parkingLot1;
    ParkingLot parkingLot2;
    ParkingLot parkingLot3;
    bool hasLot1;           
    bool hasLot2;
    bool hasLot3;
    bool stop;              // true khi het du lieu nhap (EOF) de thoat chuong trinh

    // Cac ham truy cap bai theo vi tri 1..3
    bool lotExists(int pos) const {
        if (pos == 1) return hasLot1;
        if (pos == 2) return hasLot2;
        return hasLot3;
    }

    void setLotExists(int pos, bool value) {
        if (pos == 1) hasLot1 = value;
        else if (pos == 2) hasLot2 = value;
        else hasLot3 = value;
    }

    ParkingLot& lotAt(int pos) {
        if (pos == 1) return parkingLot1;
        if (pos == 2) return parkingLot2;
        return parkingLot3;
    }

    const ParkingLot& lotAt(int pos) const {
        if (pos == 1) return parkingLot1;
        if (pos == 2) return parkingLot2;
        return parkingLot3;
    }

    int countLots() const {
        int count = 0;
        if (hasLot1) count++;
        if (hasLot2) count++;
        if (hasLot3) count++;
        return count;
    }
    // Cac ham tim kiem tra ve vi tri 
    int findLotByID(int id) const {
        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos) && lotAt(pos).getParkID() == id) return pos;
        }
        return 0;
    }

    int findLotByVehicle(int vehicleID) const {
        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos) && lotAt(pos).containsVehicle(vehicleID)) return pos;
        }
        return 0;
    }

    int findEmptyPosition() const {
        for (int pos = 1; pos <= 3; pos++) {
            if (!lotExists(pos)) return pos;
        }
        return 0;
    }
    int chooseBestLot() const {
        int best = 0;
        int fewestFree = 4;
        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos) && lotAt(pos).freeSlots() > 0) {
                if (lotAt(pos).freeSlots() < fewestFree) {
                    fewestFree = lotAt(pos).freeSlots();
                    best = pos;
                }
            }
        }
        return best;
    }

    int readInt(const string& prompt) {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x) {
                cin.ignore(1000, '\n');
                return x;
            }
            if (cin.eof()) {
                stop = true;
                return 0;
            }
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Vui long nhap so nguyen." << endl;
        }
    }
    string readString(const string& prompt) {
        string s;
        cout << prompt;
        if (!(cin >> s)) {
            stop = true;
            return "";
        }
        cin.ignore(1000, '\n');
        return s;
    }
    void printMoney(double money) const {
        cout << fixed << setprecision(0) << money << " VND";
    }

    // Dem so xe va tong phi cua mot loai xe tren toan he thong
    void summarizeByType(const string& type, int& count, double& total) const {
        count = 0;
        total = 0;
        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos)) {
                count += lotAt(pos).countByType(type);
                total += lotAt(pos).feeByType(type);
            }
        }
    }
    // In phi trung binh cua mot loai xe tren toan he thong
    void printAverageByType(const string& type) const {
        int count;
        double total;
        summarizeByType(type, count, total);

        cout << type << ": ";
        if (count == 0) {
            cout << "Khong co xe" << endl;
        }
        else {
            cout << count << " xe, trung binh ";
            printMoney(total / count);
            cout << "/xe" << endl;
        }
    }

    // In so xe, tong phi va phi trung binh cua mot loai xe trong mot bai
    void printTypeInLot(const ParkingLot& lot, const string& type) const {
        int count = lot.countByType(type);
        double total = lot.feeByType(type);

        cout << "  " << type << ": ";
        if (count == 0) {
            cout << "Khong co xe" << endl;
        }
        else {
            cout << count << " xe, tong phi ";
            printMoney(total);
            cout << ", trung binh ";
            printMoney(total / count);
            cout << "/xe" << endl;
        }
    }
public:
    SystemInterface() {
        hasLot1 = false;
        hasLot2 = false;
        hasLot3 = false;
        stop = false;
    }

    // Menu 1: kiem tra tung dieu kien
    void createLot() {
        if (countLots() == 3) {
            cout << "He thong da co toi da 3 bai do." << endl;
            return;
        }
        int id = readInt("Nhap ma bai do: ");
        if (stop) return;
        if (id <= 0) {
            cout << "Ma bai phai lon hon 0." << endl;
            return;
        }
        if (findLotByID(id) != 0) {
            cout << "Ma bai do da ton tai." << endl;
            return;
        }
        string sz = readString("Nhap kich thuoc (S/M/L): ");
        if (stop) return;
        if (sz.length() != 1 || !ParkingLot::isValidSize(sz[0])) {
            cout << "Kich thuoc khong hop le." << endl;
            return;
        }

        int pos = findEmptyPosition();
        lotAt(pos) = ParkingLot(id, sz[0]);
        setLotExists(pos, true);
        cout << "Tao bai do thanh cong." << endl;
    }

    // Menu 2: nhap va kiem tra thong tin xe, xep bai 
    void addVehicleToLot() {
        if (countLots() == 0) {
            cout << "Hay tao bai do truoc." << endl;
            return;
        }
        if (chooseBestLot() == 0) {
            cout << "Tat ca bai do deu da day." << endl;
            return;
        }
        int id = readInt("Nhap ma xe: ");
        if (stop) return;
        if (!Vehicle::isValidID(id)) {
            cout << "Ma xe phai lon hon 0." << endl;
            return;
        }
        if (findLotByVehicle(id) != 0) {
            cout << "Ma xe da ton tai." << endl;
            return;
        }

        string type = readString("Nhap loai xe (Car/Motorcycle/Bicycle): ");
        if (stop) return;
        if (!Vehicle::isValidType(type)) {
            cout << "Loai xe khong hop le." << endl;
            return;
        }

        int entry = readInt("Nhap gio vao (0-23): ");
        if (stop) return;
        if (!Vehicle::isValidEntryTime(entry)) {
            cout << "Gio vao khong hop le." << endl;
            return;
        }
        int duration = readInt("Nhap so gio do (1-23): ");
        if (stop) return;
        if (!Vehicle::isValidDuration(duration)) {
            cout << "So gio do khong hop le." << endl;
            return;
        }
        if (!Vehicle::isValidTimeRange(entry, duration)) {
            cout << "Khong cho phep do xe qua dem." << endl;
            return;
        }

        Vehicle v(id, type, entry, duration);
        int pos = chooseBestLot();

        if (lotAt(pos).addVehicle(v)) {
            cout << "Them xe thanh cong vao bai " << lotAt(pos).getParkID() << "." << endl;
            cout << "Phi do xe: ";
            printMoney(v.getParkingFee());
            cout << endl;
        }
        else {
            cout << "Khong the them xe vao bai do." << endl;
        }
    }

    // Menu 3: xoa bai 
    void deleteLot() {
        int id = readInt("Nhap ma bai do can xoa: ");
        if (stop) return;

        int pos = findLotByID(id);
        if (pos == 0) {
            cout << "Khong tim thay bai do." << endl;
            return;
        }

        lotAt(pos) = ParkingLot();
        setLotExists(pos, false);
        cout << "Da xoa bai do va cac xe trong bai." << endl;
    }

    // Menu 4: tim bai chua xe roi lay xe ra
    void removeVehicleFromLot() {
        int id = readInt("Nhap ma xe can lay ra: ");
        if (stop) return;

        int pos = findLotByVehicle(id);
        if (pos == 0) {
            cout << "Khong tim thay xe." << endl;
            return;
        }

        lotAt(pos).removeVehicle(id);
        cout << "Da lay xe ra khoi bai " << lotAt(pos).getParkID() << "." << endl;
    }

    // Menu 5
    void displayAllLots() const {
        if (countLots() == 0) {
            cout << "Chua co bai do nao." << endl;
            return;
        }

        cout << "\n===== DANH SACH BAI DO =====" << endl;
        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos)) lotAt(pos).displaySummary();
        }
    }

    // Menu 6
    void displayVehiclesByLot() {
        int id = readInt("Nhap ma bai do: ");
        if (stop) return;

        int pos = findLotByID(id);
        if (pos == 0) {
            cout << "Khong tim thay bai do." << endl;
            return;
        }

        lotAt(pos).displayLotInfo();
    }
    // Menu 7: in ten bai, tieu de cot
    void displayVehiclesByType() {
        string type = readString("Nhap loai xe (Car/Motorcycle/Bicycle): ");
        if (stop) return;
        if (!Vehicle::isValidType(type)) {
            cout << "Loai xe khong hop le." << endl;
            return;
        }

        type = Vehicle::normalizeType(type);
        int count;
        double total;
        summarizeByType(type, count, total);
        if (count == 0) {
            cout << "Khong co xe thuoc loai nay." << endl;
            return;
        }

        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos)) lotAt(pos).displayVehiclesByType(type);
        }
    }
    // Menu 8: phi trung binh theo loai xe toan he thong, chi tiet tung bai
    void displayFeeReport() const {
        cout << "\n===== BAO CAO PHI TOAN HE THONG =====" << endl;
        printAverageByType("Car");
        printAverageByType("Motorcycle");
        printAverageByType("Bicycle");

        cout << "\n===== PHAN TICH THEO TUNG BAI =====" << endl;
        double allFee = 0;
        int allVehicles = 0;
        for (int pos = 1; pos <= 3; pos++) {
            if (lotExists(pos)) {
                cout << "\nBai " << lotAt(pos).getParkID() << ":" << endl;
                printTypeInLot(lotAt(pos), "Car");
                printTypeInLot(lotAt(pos), "Motorcycle");
                printTypeInLot(lotAt(pos), "Bicycle");
                cout << "  Tong phi bai: ";
                printMoney(lotAt(pos).totalFee());
                cout << endl;

                allFee += lotAt(pos).totalFee();
                allVehicles += lotAt(pos).countVehicles();
            }
        }
        cout << "\nTong phi toan he thong: ";
        printMoney(allFee);
        cout << endl;
        cout << "Tong so xe dang do: " << allVehicles << endl;
    }

    void runMenu() {
        int choice = 0;
        while (!stop && choice != 9) {
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

            choice = readInt("Nhap lua chon: ");
            if (stop) break;

            switch (choice) {
            case 1: createLot(); break;
            case 2: addVehicleToLot(); break;
            case 3: deleteLot(); break;
            case 4: removeVehicleFromLot(); break;
            case 5: displayAllLots(); break;
            case 6: displayVehiclesByLot(); break;
            case 7: displayVehiclesByType(); break;
            case 8: displayFeeReport(); break;
            case 9: cout << "Da thoat chuong trinh." << endl; break;
            default: cout << "Lua chon khong hop le." << endl;
            }
        }
    }
};

int main() {
    SystemInterface app;
    app.runMenu();
    return 0;
}