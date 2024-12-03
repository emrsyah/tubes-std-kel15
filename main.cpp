#include <iostream>
#include "car_rental.h"

using namespace std;

void showMenu() {
    cout << "\n=== RENTAL MOBIL SYSTEM ===\n";
    cout << "1. Insert mobil baru\n";
    cout << "2. Insert customer baru\n";
    cout << "3. Buat data transaksi rental baru\n";
    cout << "4. Hapus data mobil\n";
    cout << "5. Hapus data customer\n";
    cout << "6. Hapus data transaksi\n";
    cout << "7. Tampilkan semua list mobil\n";
    cout << "8. Tampilkan semua list customer\n";
    cout << "9. Tampilkan semua list transaksi\n";
    cout << "10. Hitung total transaksi\n";
    cout << "-1. Exit\n";
}

int getChoice() {
    int choice;
    cout << "Pilihan anda: ";
    cin >> choice;
    cin.ignore();
    return choice;
}

void menuInsertCar(CarList &carList) {
    infoCar newCarInfo;
    cout << "\n=== INSERT MOBIL BARU ===\n";
    cout << "Masukkan ID Mobil: ";
    getline(cin, newCarInfo.carID);
    cout << "Masukkan Brand: ";
    getline(cin, newCarInfo.brand);
    cout << "Masukkan Model: ";
    getline(cin, newCarInfo.model);

    adrCar newCar;
    createNewCar(newCarInfo, newCar);
    insertCarLast(carList, newCar);
    cout << "Mobil berhasil ditambahkan!\n";
}

void menuInsertCustomer(CustomerList &custList) {
    infoCust newCustInfo;
    cout << "\n=== INSERT CUSTOMER BARU ===\n";
    cout << "Masukkan ID Customer: ";
    getline(cin, newCustInfo.customerID);
    cout << "Masukkan Nama: ";
    getline(cin, newCustInfo.name);
    cout << "Masukkan Contact: ";
    getline(cin, newCustInfo.contact);

    adrCust newCust;
    createNewCust(newCustInfo, newCust);
    insertCustLast(custList, newCust);
    cout << "Customer berhasil ditambahkan!\n";
}

void menuInsertRental(RentalList &rentalList, CarList &carList, CustomerList &custList) {
    if (isCarEmpty(carList)) {
        cout << "Tidak ada mobil tersedia untuk dirental!\n";
        return;
    }
    if (isCustEmpty(custList)) {
        cout << "Tidak ada customer terdaftar!\n";
        return;
    }

    showAllCar(carList);
    showAllCust(custList);

    infoRental newRentalInfo;
    string carId, custId;

    cout << "\n=== BUAT TRANSAKSI RENTAL BARU ===\n";
    cout << "Masukkan ID Rental: ";
    getline(cin, newRentalInfo.rentalID);
    cout << "Masukkan ID Mobil: ";
    getline(cin, carId);
    cout << "Masukkan ID Customer: ";
    getline(cin, custId);
    cout << "Masukkan Durasi (hari): ";
    cin >> newRentalInfo.duration;
    cout << "Masukkan Jumlah Pembayaran: ";
    cin >> newRentalInfo.amount;
    cin.ignore();

    adrCar selectedCar = findCarById(carList, carId);
    adrCust selectedCust = findCustById(custList, custId);

    if (selectedCar == NULL) {
        cout << "Mobil dengan ID tersebut tidak ditemukan!\n";
        return;
    }
    if (selectedCust == NULL) {
        cout << "Customer dengan ID tersebut tidak ditemukan!\n";
        return;
    }

    adrRental newRental;
    createNewRental(newRentalInfo, newRental);
    insertRentalLast(rentalList, newRental, selectedCar, selectedCust);
    cout << "Transaksi rental berhasil dibuat!\n";
}

void menuDeleteCar(RentalList &rentalList, CarList &carList) {
    if (isCarEmpty(carList)) {
        cout << "Tidak ada data mobil yang bisa dihapus!\n";
        return;
    }

    showAllCar(carList);
    string carId;
    cout << "\n=== HAPUS DATA MOBIL ===\n";
    cout << "Masukkan ID Mobil yang akan dihapus: ";
    getline(cin, carId);

    adrCar car = findCarById(carList, carId);
    if (car == NULL) {
        cout << "Mobil dengan ID tersebut tidak ditemukan!\n";
        return;
    }

    deleteCar(rentalList, carList, carId);
    cout << "Data mobil berhasil dihapus!\n";
}

void menuDeleteCustomer(RentalList &rentalList, CustomerList &custList) {
    if (isCustEmpty(custList)) {
        cout << "Tidak ada data customer yang bisa dihapus!\n";
        return;
    }

    showAllCust(custList);
    string custId;
    cout << "\n=== HAPUS DATA CUSTOMER ===\n";
    cout << "Masukkan ID Customer yang akan dihapus: ";
    getline(cin, custId);

    adrCust cust = findCustById(custList, custId);
    if (cust == NULL) {
        cout << "Customer dengan ID tersebut tidak ditemukan!\n";
        return;
    }

    deleteCust(rentalList, custList, custId);
    cout << "Data customer berhasil dihapus!\n";
}

void menuDeleteRental(RentalList &rentalList) {
    if (isRentalEmpty(rentalList)) {
        cout << "Tidak ada data rental yang bisa dihapus!\n";
        return;
    }

    showAllDataCarCustAndRent(rentalList);
    string rentalId;
    cout << "\n=== HAPUS DATA RENTAL ===\n";
    cout << "Masukkan ID Rental yang akan dihapus: ";
    getline(cin, rentalId);

    // Find and delete the rental
    adrRental p = firstRental(rentalList);
    adrRental prev = NULL;

    while (p != NULL && infoRental(p).rentalID != rentalId) {
        prev = p;
        p = nextRental(p);
    }

    if (p == NULL) {
        cout << "Data rental tidak ditemukan!\n";
        return;
    }

    if (prev == NULL) {
        deleteRentalFirst(rentalList);
    } else if (nextRental(p) == NULL) {
        deleteRentalLast(rentalList);
    } else {
        deleteRentalAfter(rentalList, prev);
    }

    cout << "Data rental berhasil dihapus!\n";
}

void menuInsertCarFirst(CarList &carList) {
    infoCar newCarInfo;
    cout << "\n=== INSERT MOBIL BARU (DARI DEPAN) ===\n";
    cout << "Masukkan ID Mobil: ";
    getline(cin, newCarInfo.carID);
    cout << "Masukkan Brand: ";
    getline(cin, newCarInfo.brand);
    cout << "Masukkan Model: ";
    getline(cin, newCarInfo.model);

    adrCar newCar;
    createNewCar(newCarInfo, newCar);

    insertCarFirst(carList, newCar);
    cout << "Mobil berhasil ditambahkan di depan!\n";
}

void menuSearchCar(CarList carList) {
    if (isCarEmpty(carList)) {
        cout << "Tidak ada data mobil!\n";
        return;
    }

    string carId;
    cout << "\n=== CARI DATA MOBIL ===\n";
    cout << "Masukkan ID Mobil yang dicari: ";
    getline(cin, carId);

    adrCar car = seachCarById(carList, carId);
    if (car == NULL) {
        cout << "Mobil tidak ditemukan!\n";
    } else {
        cout << "Mobil ditemukan:\n";
        cout << "ID: " << infoCar(car).carID << endl;
        cout << "Brand: " << infoCar(car).brand << endl;
        cout << "Model: " << infoCar(car).model << endl;
    }
}

void menuShowCustomersByCarId(RentalList rentalList) {
    if (isRentalEmpty(rentalList)) {
        cout << "Tidak ada data rental!\n";
        return;
    }

    string carId;
    cout << "\n=== TAMPILKAN PELANGGAN BERDASARKAN MOBIL ===\n";
    cout << "Masukkan ID Mobil: ";
    getline(cin, carId);

    cout << "Daftar pelanggan yang pernah meminjam mobil " << carId << ":\n";
    showCustomersByCarId(rentalList, carId);
}

void menuEditCar(CarList &C) {
    if (isCarEmpty(C)) {
        cout << "TIDAK ADA DATA MOBIL" << endl;
        return;
    }

    showAllCar(C);

    string carId, newBrand, newModel;
    cout << "\n=== EDIT DATA MOBIL ===\n";
    cout << "Masukkan ID Mobil yang akan diedit: ";
    getline(cin, carId);
    cout << "Masukkan Brand baru: ";
    getline(cin, newBrand);
    cout << "Masukkan Model baru: ";
    getline(cin, newModel);

    editCar(C, carId, newBrand, newModel);
}

void menuEditCustomer(CustomerList &C) {
    if (isCustEmpty(C)) {
        cout << "TIDAK ADA DATA CUSTOMER" << endl;
        return;
    }

    showAllCust(C);

    string custId, newName, newContact;
    cout << "\n=== EDIT DATA CUSTOMER ===\n";
    cout << "Masukkan ID Customer yang akan diedit: ";
    getline(cin, custId);
    cout << "Masukkan Nama baru: ";
    getline(cin, newName);
    cout << "Masukkan Contact baru: ";
    getline(cin, newContact);

    editCustomer(C, custId, newName, newContact);
}

void menuEditRental(RentalList &R) {
    if (isRentalEmpty(R)) {
        cout << "TIDAK ADA DATA RENTAL" << endl;
        return;
    }

    showAllDataCarCustAndRent(R);

    string rentalId;
    int newDuration;
    float newAmount;
    cout << "\n=== EDIT DATA RENTAL ===\n";
    cout << "Masukkan ID Rental yang akan diedit: ";
    getline(cin, rentalId);
    cout << "Masukkan Durasi baru (hari): ";
    cin >> newDuration;
    cout << "Masukkan Jumlah Pembayaran baru: ";
    cin >> newAmount;
    cin.ignore();

    editRental(R, rentalId, newDuration, newAmount);
}

void showMainMenu() {
    cout << "\n==== SISTEM RENTAL MOBIL ====\n";
    cout << "1. Manajemen Mobil\n";
    cout << "2. Manajemen Customer\n";
    cout << "3. Manajemen Rental\n";
    cout << "4. Laporan dan Pencarian\n";
    cout << "0. Keluar\n";
    cout << "==============================\n";
}

void showCarMenu() {
    cout << "\n=== MANAJEMEN MOBIL ===\n";
    cout << "1. Tambah mobil (depan)\n";
    cout << "2. Tambah mobil (belakang)\n";
    cout << "3. Hapus data mobil\n";
    cout << "4. Edit data mobil\n";
    cout << "5. Tampilkan semua mobil\n";
    cout << "0. Kembali ke menu utama\n";
    cout << "=====================\n";
}

void showCustomerMenu() {
    cout << "\n=== MANAJEMEN CUSTOMER ===\n";
    cout << "1. Tambah customer baru\n";
    cout << "2. Hapus data customer\n";
    cout << "3. Edit data customer\n";
    cout << "4. Tampilkan semua customer\n";
    cout << "0. Kembali ke menu utama\n";
    cout << "========================\n";
}

void showRentalMenu() {
    cout << "\n=== MANAJEMEN RENTAL ===\n";
    cout << "1. Buat transaksi rental baru\n";
    cout << "2. Hapus data rental\n";
    cout << "3. Edit data rental\n";
    cout << "4. Tampilkan semua transaksi\n";
    cout << "0. Kembali ke menu utama\n";
    cout << "======================\n";
}

void showReportMenu() {
    cout << "\n=== LAPORAN & PENCARIAN ===\n";
    cout << "1. Cari data mobil\n";
    cout << "2. Lihat customer peminjam mobil\n";
    cout << "3. Total pendapatan transaksi\n";
    cout << "0. Kembali ke menu utama\n";
    cout << "========================\n";
}

void processingMenu(CarList &carList, CustomerList &custList, RentalList &rentalList) {
    int mainChoice = -1;

    while (mainChoice != 0) {
        showMainMenu();
        cout << "Pilih menu: ";
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
            case 1: {
                // Car Management
                int carChoice = -1;
                while (carChoice != 0) {
                    showCarMenu();
                    cout << "Pilih operasi: ";
                    cin >> carChoice;
                    cin.ignore();

                    switch (carChoice) {
                        case 1: menuInsertCarFirst(carList); break;
                        case 2: menuInsertCar(carList); break;
                        case 3: menuDeleteCar(rentalList, carList); break;
                        case 4: menuEditCar(carList); break;
                        case 5: showAllCar(carList); break;
                        case 0: break;
                        default: cout << "Pilihan tidak valid!\n";
                    }
                }
                break;
            }
            case 2: {
                // Customer Management
                int custChoice = -1;
                while (custChoice != 0) {
                    showCustomerMenu();
                    cout << "Pilih operasi: ";
                    cin >> custChoice;
                    cin.ignore();

                    switch (custChoice) {
                        case 1: menuInsertCustomer(custList); break;
                        case 2: menuDeleteCustomer(rentalList, custList); break;
                        case 3: menuEditCustomer(custList); break;
                        case 4: showAllCust(custList); break;
                        case 0: break;
                        default: cout << "Pilihan tidak valid!\n";
                    }
                }
                break;
            }
            case 3: {
                // Rental Management
                int rentChoice = -1;
                while (rentChoice != 0) {
                    showRentalMenu();
                    cout << "Pilih operasi: ";
                    cin >> rentChoice;
                    cin.ignore();

                    switch (rentChoice) {
                        case 1: menuInsertRental(rentalList, carList, custList); break;
                        case 2: menuDeleteRental(rentalList); break;
                        case 3: menuEditRental(rentalList); break;
                        case 4: showAllDataCarCustAndRent(rentalList); break;
                        case 0: break;
                        default: cout << "Pilihan tidak valid!\n";
                    }
                }
                break;
            }
            case 4: {
                // Reports and Search
                int reportChoice = -1;
                while (reportChoice != 0) {
                    showReportMenu();
                    cout << "Pilih operasi: ";
                    cin >> reportChoice;
                    cin.ignore();

                    switch (reportChoice) {
                        case 1: menuSearchCar(carList); break;
                        case 2: menuShowCustomersByCarId(rentalList); break;
                        case 3: {
                            int total = sumAllTransaction(rentalList);
                            cout << "Total semua transaksi: Rp." << total << endl;
                            break;
                        }
                        case 0: break;
                        default: cout << "Pilihan tidak valid!\n";
                    }
                }
                break;
            }
            case 0:
                cout << "Terima kasih telah menggunakan sistem ini!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }
}

int main()
{
    CarList carList;
    CustomerList custList;
    RentalList rentalList;

    createCarList(carList);
    createCustList(custList);
    createRentalList(rentalList);

    processingMenu(carList, custList, rentalList);

    return 0;
}
