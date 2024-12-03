#include "car_rental.h"
#include <iostream>

using namespace std;

// INIT LIST ======================
void createCarList(CarList &C){
    firstCar(C) = NULL;
    lastCar(C) = NULL;
}
void createCustList(CustomerList &C){
    firstCust(C) = NULL;
}
void createRentalList(RentalList &R){
    firstRental(R) = NULL;
    lastRental(R) = NULL;
}

// NEW ELEMENT =================
void createNewCar(infoCar x, adrCar &p){
    p = new carElm;
    infoCar(p) = x;
    nextCar(p) = NULL;
    prevCar(p) = NULL;
}

void createNewCust(infoCust x, adrCust &p){
    p =  new custElm;
    infoCust(p) = x;
    nextCust(p) = NULL;
}

void createNewRental(infoRental x, adrRental &p){
    p =  new rentalElm;
    infoRental(p) = x;
    nextRental(p) = NULL;
    prevRental(p) = NULL;
}

// UTILS ==========================

bool isCarEmpty(CarList C){
    return (firstCar(C) == NULL && lastCar(C) == NULL);
}

bool isCustEmpty(CustomerList C){
    return firstCust(C) == NULL;
}

bool isRentalEmpty(RentalList R){
    return (firstRental(R) == NULL && lastRental(R) == NULL);
}

void showAllCar(CarList C){

  adrCar p = firstCar(C);
  if (p == NULL){
    cout << "BELUM ADA MOBIL" << endl;
    return;
  }
  int n = 1;
    cout << "=========== DATA MOBIL =============" << endl;
  while (p != NULL){
    cout << n << ") " << infoCar(p).carID << " | " << infoCar(p).brand << " | " << infoCar(p).model << "." << endl;
    n += 1;
    p = nextCar(p);
  }
  cout << "====================================" << endl << endl;
}
void showAllCust(CustomerList C){
  adrCust p = firstCust(C);
  int n = 1;
  if (p == NULL){
    cout << "BELUM ADA CUSTOMER" << endl;
    return;
  }
    cout << "=========== DATA CUSTOMER =============" << endl;
  while (p != NULL){
    cout << n << ") " << infoCust(p).customerID << " | " << infoCust(p).name << " | " << infoCust(p).contact << "." << endl;
    n += 1;
    p = nextCust(p);
  }
  cout << "=====================================" << endl << endl;
}

void connectRentalToCarAndCust(adrRental p, adrCar carp, adrCust custp){
    carRent(p) = carp;
    customerRent(p) = custp;
}

adrCust findCustById(CustomerList C, string id){
    adrCust p = firstCust(C);
    while (p != NULL) {
        if (infoCust(p).customerID == id) {
            return p;
        }
        p = nextCust(p);
    }
    return NULL;
}
adrCar findCarById(CarList C, string id){
 adrCar p = firstCar(C);
    while (p != NULL) {
        if (infoCar(p).carID == id) {
            return p;
        }
        p = nextCar(p);
    }
    return NULL;
}

// TUGAS ===========================

void insertRentalLast(RentalList &R, adrRental p, adrCar carp, adrCust custp){
    if (isRentalEmpty(R)){
        firstRental(R) = p;
        lastRental(R) = p;
    } else {
        adrRental tp = firstRental(R);
        while (nextRental(tp) != NULL){
            tp = nextRental(tp);
        }
        nextRental(tp) = p;
        prevRental(p) = tp;
        lastRental(R) = p;
    }
    connectRentalToCarAndCust(p, carp, custp);
}

void insertRentalFirst(RentalList &R, adrRental p, adrCar carp, adrCust custp){
    if (isRentalEmpty(R)){
        firstRental(R) = p;
        lastRental(R) = p;
    } else {
        adrRental tp = firstRental(R);
        prevRental(tp) = p;
        nextRental(p) = tp;
        firstRental(R) = p;
    }
    connectRentalToCarAndCust(p, carp, custp);
}

void showAllDataRental(RentalList R){
  adrRental p = firstRental(R);
  int n = 1;
  if (p == NULL){
    cout << "BELUM ADA DATA RENTAL" << endl;
    return;
  }
    cout << "=========== DATA RENTAL =============" << endl;
  while (p != NULL){
    cout << n << ") " << infoRental(p).rentalID << " |  Harga: " << infoRental(p).amount << " |  Durasi: " << infoRental(p).duration  << " Hari ." << endl;
    n += 1;
    p = nextRental(p);
  }
  cout << "====================================" << endl << endl;
}

// search
adrCar seachCarById(CarList C, string cid){
    if (isCarEmpty(C)) {
        cout << "BELUM ADA DATA MOBIL" << endl;
        return NULL;
    }
    adrCar p = firstCar(C);
    while (p != NULL){
       if (infoCar(p).carID == cid) {
            return p;
       }
       p = nextCar(p);
    }
    return NULL;
}
adrCust searchCustFromCar(RentalList R, string carId, string custId){
    if (isRentalEmpty(R)) {
        cout << "BELUM ADA DATA RENTAL" << endl;
        return NULL;
    }
    adrRental p = firstRental(R);
    while (p != NULL) {
        if (infoCar(carRent(p)).carID == carId && infoCust(customerRent(p)).customerID == custId){
            return customerRent(p);
        }
    }
    return NULL;
}

// delete utilitity
void deleteRentalFirst(RentalList &R) {
   if (isRentalEmpty(R)) {
       return;
   }

   adrRental tmp = firstRental(R);

   if (firstRental(R) == lastRental(R)) {
       firstRental(R) = NULL;
       lastRental(R) = NULL;
   } else {
       firstRental(R) = nextRental(tmp);
       prevRental(firstRental(R)) = NULL;
   }

   carRent(tmp) = NULL;
   customerRent(tmp) = NULL;
   nextRental(tmp) = NULL;
   prevRental(tmp) = NULL;
}

void deleteRentalLast(RentalList &R) {
   if (isRentalEmpty(R)) {
       return;
   }

   adrRental tmp = lastRental(R);

   if (firstRental(R) == lastRental(R)) {
       firstRental(R) = NULL;
       lastRental(R) = NULL;
   } else {
       lastRental(R) = prevRental(tmp);
       nextRental(lastRental(R)) = NULL;
   }

   carRent(tmp) = NULL;
   customerRent(tmp) = NULL;
   nextRental(tmp) = NULL;
   prevRental(tmp) = NULL;
}

void deleteRentalAfter(RentalList &R, adrRental prec) {
   if (prec == NULL || nextRental(prec) == NULL) {
       return;
   }

   adrRental tmp = nextRental(prec);

   if (tmp == lastRental(R)) {
       lastRental(R) = prec;
       nextRental(prec) = NULL;
   } else {
       nextRental(prec) = nextRental(tmp);
       prevRental(nextRental(tmp)) = prec;
   }

   carRent(tmp) = NULL;
   customerRent(tmp) = NULL;
   nextRental(tmp) = NULL;
   prevRental(tmp) = NULL;
}
// delete tugas
void deleteCar(RentalList &R, CarList &C, string cid) {
    if (!isRentalEmpty(R)) {
        adrRental rp = firstRental(R);
        while (rp != NULL) {
            adrRental nextRp = nextRental(rp);
            if (carRent(rp) != NULL && infoCar(carRent(rp)).carID == cid) {
                if (rp == firstRental(R)) {
                    deleteRentalFirst(R);
                } else if (rp == lastRental(R)) {
                    deleteRentalLast(R);
                } else {
                    deleteRentalAfter(R, prevRental(rp));
                }
            }
            rp = nextRp;
        }
    }

    if (isCarEmpty(C)) {
        cout << "TAK ADA DATA MOBIL" << endl;
        return;
    }

    adrCar cp = firstCar(C);

    if (infoCar(cp).carID == cid) {
        if (firstCar(C) == lastCar(C)) {
            firstCar(C) = NULL;
            lastCar(C) = NULL;
        } else {
            firstCar(C) = nextCar(cp);
            prevCar(firstCar(C)) = NULL;
        }
        return;
    }

    while (cp != NULL && infoCar(cp).carID != cid) {
        cp = nextCar(cp);
    }

    if (cp == NULL) {
        cout << "MOBIL TIDAK DITEMUKAN" << endl;
        return;
    }

    if (cp == lastCar(C)) {
        lastCar(C) = prevCar(cp);
        nextCar(lastCar(C)) = NULL;
    }
    else {
        nextCar(prevCar(cp)) = nextCar(cp);
        prevCar(nextCar(cp)) = prevCar(cp);
    }
}

void deleteCust(RentalList &R, CustomerList &C, string cid) {
    if (!isRentalEmpty(R)) {
        adrRental rp = firstRental(R);
        while (rp != NULL) {
            adrRental nextRp = nextRental(rp);
            if (customerRent(rp) != NULL && infoCust(customerRent(rp)).customerID == cid) {
                if (rp == firstRental(R)) {
                    deleteRentalFirst(R);
                } else if (rp == lastRental(R)) {
                    deleteRentalLast(R);
                } else {
                    deleteRentalAfter(R, prevRental(rp));
                }
            }
            rp = nextRp;
        }
    }

    if (isCustEmpty(C)) {
        cout << "TAK ADA DATA CUSTOMER" << endl;
        return;
    }

    adrCust cp = firstCust(C);
    adrCust prevCp = NULL;

    if (infoCust(cp).customerID == cid) {
        firstCust(C) = nextCust(cp);
        return;
    }

    while (cp != NULL && infoCust(cp).customerID != cid) {
        prevCp = cp;
        cp = nextCust(cp);
    }

    if (cp == NULL) {
        cout << "CUSTOMER TIDAK DITEMUKAN" << endl;
        return;
    }

    nextCust(prevCp) = nextCust(cp);
}

// insert child:
void insertCustLast(CustomerList &C, adrCust p){
    if (isCustEmpty(C)){
        firstCust(C) = p;
        return;
    }
    adrCust tmp = firstCust(C);
    while (nextCust(tmp) != NULL){
        tmp = nextCust(tmp);
    }
    nextCust(tmp) = p;
}

void insertCarLast(CarList &C, adrCar p) {
    if (isCarEmpty(C)) {
        firstCar(C) = p;
        lastCar(C) = p;
        return;
    }

    prevCar(p) = lastCar(C);
    nextCar(lastCar(C)) = p;
    lastCar(C) = p;
}


void insertCarFirst(CarList &C, adrCar p){
    if (isCarEmpty(C)){
        firstCar(C) = p;
        lastCar(C) = p;
        return;
    }
    adrCar tmp = firstCar(C);
    nextCar(p) = tmp;
    prevCar(tmp) = p;
    firstCar(C) = p;
}

void showAllDataCarCustAndRent(RentalList R){
    adrRental rp = firstRental(R);
    if (isRentalEmpty(R)){
        cout << "TIDAK ADA DATA RENTAL" << endl << endl;
        return;
    }
    int n = 1;
    while (rp != NULL){
        cout << n << ") " << "Transaksi: " << infoRental(rp).rentalID << " - " << infoRental(rp).duration << " Hari - Jumlah: " << infoRental(rp).amount << "|| Mobil: " << infoCar(carRent(rp)).carID << " - " << infoCar(carRent(rp)).brand << " - " << infoCar(carRent(rp)).model << " || Pelanggan:  " << infoCust(customerRent(rp)).customerID << " - " << infoCust(customerRent(rp)).name << " - " << infoCust(customerRent(rp)).contact << endl;
        rp = nextRental(rp);
    }
}
// cari data child di parent tertentu (parentnya apakah ini rental atau car, karena kalo rental jadinya aneh)
// hapus data child parent tertentu (parentnya apakah ini rental atau car, karena kalo rental jadinya aneh)
void showCustomersByCarId(RentalList R, string carId) {
        if (isRentalEmpty(R)) {
        cout << "TIDAK ADA DATA RENTAL" << endl;
        return;
    }

    bool customerFound = false;
    int n = 1;

    cout << "=========== DATA CUSTOMER PEMINJAM MOBIL " << carId << " =============" << endl;

    adrRental p = firstRental(R);
    while (p != NULL) {
        if (infoCar(carRent(p)).carID == carId) {
            cout << n << ") "
                 << infoCust(customerRent(p)).customerID << " | "
                 << infoCust(customerRent(p)).name << " | "
                 << infoCust(customerRent(p)).contact << " | "
                 << "Rental ID: " << infoRental(p).rentalID << " - "
                 << "Durasi: " << infoRental(p).duration << " Hari" << endl;
            customerFound = true;
            n += 1;
        }
        p = nextRental(p);
    }
    if (!customerFound) {
        cout << "TIDAK ADA CUSTOMER YANG PERNAH MEMINJAM MOBIL INI" << endl;
    }

    cout << "=====================================" << endl << endl;
}


// EDIT
void editCar(CarList &C, string carId, string newBrand, string newModel) {
    if (isCarEmpty(C)) {
        cout << "TAK ADA DATA MOBIL" << endl;
        return;
    }

    adrCar cp = firstCar(C);
    while (cp != NULL && infoCar(cp).carID != carId) {
        cp = nextCar(cp);
    }

    if (cp == NULL) {
        cout << "MOBIL TIDAK DITEMUKAN" << endl;
        return;
    }

    infoCar(cp).brand = newBrand;
    infoCar(cp).model = newModel;
}

void editCustomer(CustomerList &C, string custId, string newName, string newContact) {
    if (isCustEmpty(C)) {
        cout << "TAK ADA DATA CUSTOMER" << endl;
        return;
    }

    adrCust cp = firstCust(C);
    while (cp != NULL && infoCust(cp).customerID != custId) {
        cp = nextCust(cp);
    }

    if (cp == NULL) {
        cout << "CUSTOMER TIDAK DITEMUKAN" << endl;
        return;
    }

    infoCust(cp).name = newName;
    infoCust(cp).contact = newContact;
}

void editRental(RentalList &R, string rentalId, int newDuration, float newAmount) {
    if (isRentalEmpty(R)) {
        cout << "TAK ADA DATA RENTAL" << endl;
        return;
    }

    adrRental rp = firstRental(R);
    while (rp != NULL && infoRental(rp).rentalID != rentalId) {
        rp = nextRental(rp);
    }

    if (rp == NULL) {
        cout << "RENTAL TIDAK DITEMUKAN" << endl;
        return;
    }

    infoRental(rp).duration = newDuration;
    infoRental(rp).amount = newAmount;
}

int sumAllTransaction(RentalList R){
    adrRental p = firstRental(R);
    int sum = 0;
    while (p != NULL){
        sum += infoRental(p).amount;
        p = nextRental(p);
    }
    return sum;
}


