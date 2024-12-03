#include <string>
#ifndef CAR_RENTAL_H_INCLUDED
#define CAR_RENTAL_H_INCLUDED
using namespace std;
#define firstCar(L) L.firstCar
#define lastCar(L) L.lastCar
#define firstCust(L) L.firstCust
#define firstRental(L) L.firstRental
#define lastRental(L) L.lastRental


// PAKE 1 - N KARENA BISA AJA SEORANG PENYEWA SEWA LAGI MOBIL YANG SAMA, KALO M KE N GA BISA KARENA CUSTOMERNYA BAKAL DOUBLE DAN BIKIN GA UNIK

#define nextCar(p) p->nextCar
#define prevCar(p) p->prevCar
#define infoCar(p) p->info
#define nextCust(p) p->nextCust
#define infoCust(p) p->info
#define nextRental(p) p->nextRental
#define prevRental(p) p->prevRental
#define infoRental(p) p->info
#define customerRent(p) p->customerRent
#define carRent(p) p->carRent

// tipe alias pointer ke elemen
typedef struct custElm *adrCust;
typedef struct carElm *adrCar;
typedef struct rentalElm *adrRental;

// tipe bentukan struktur data dan juga elemennya
struct customer {
    string customerID;
    string name;
    string contact;
};

typedef customer infoCust;

struct custElm{
    infoCust info;
    adrCust nextCust;
};

struct car {
    string carID;
    string brand;
    string model;
};

typedef car infoCar;

struct carElm{
    infoCar info;
    adrCar nextCar;
    adrCar prevCar;
};

struct rental {
    string rentalID;
    int duration;
    float amount;
};

typedef rental infoRental;

struct rentalElm {
    infoRental info;
    adrRental nextRental;
    adrRental prevRental;
    adrCust customerRent;
    adrCar carRent;
};

// tipe bentukan list
struct CarList {
    adrCar firstCar;
    adrCar lastCar;
};

struct CustomerList {
    adrCust firstCust;
};

struct RentalList {
    adrRental firstRental;
    adrRental lastRental;
};

// function dan prosedur

// INIT LIST
void createCarList(CarList &C);
void createCustList(CustomerList &C);
void createRentalList(RentalList &R);

// NEW ELEMENT
void createNewCar(infoCar x, adrCar &p);
void createNewCust(infoCust x, adrCust &p);
void createNewRental(infoRental x, adrRental &p);

// Utility:
bool isCarEmpty(CarList C);
bool isCustEmpty(CustomerList C);
bool isRentalEmpty(RentalList R);
void showAllCar(CarList C);
void showAllCust(CustomerList C);
void connectRentalToCarAndCust(adrRental p, adrCar carp, adrCust custp);
adrCust findCustById(CustomerList C, string id);
adrCar findCarById(CarList C, string id);

// TUGAS
void insertRentalLast(RentalList &R, adrRental p, adrCar carp, adrCust custp);
void insertRentalFirst(RentalList &C, adrRental p, adrCar carp, adrCust custp);
void showAllDataRental(RentalList R);

// search
adrCar seachCarById(CarList C, string cid);

// delete utility
void deleteRentalFirst(RentalList &R);
void deleteRentalLast(RentalList &R);
void deleteRentalAfter(RentalList &R, adrRental prec);

// delete
void deleteCar(RentalList &R, CarList &C, string cid);
void deleteCust(RentalList &R, CustomerList &C, string cid);


// insert child:
void insertCustLast(CustomerList &C, adrCust p);
void insertCarLast(CarList &C, adrCar p);
void insertCarFirst(CarList &C, adrCar p);

void showAllDataCarCustAndRent(RentalList R);
void showCustomersByCarId(RentalList R, string carId);
// cari data child di parent tertentu (parentnya apakah ini rental atau car, karena kalo rental jadinya aneh)
adrCust searchCustFromCar(RentalList R, string carId, string custId);


// EDIT
 void editCar(CarList &C, string carId, string newBrand, string newModel);
 void editCustomer(CustomerList &C, string custId, string newName, string newContact);
 void editRental(RentalList &C, string rentalId, int newDuration, float newAmount);


// hapus data child parent tertentu (parentnya apakah ini rental atau car, karena kalo rental jadinya aneh)
//adrCust()

int sumAllTransaction(RentalList R);



#endif // CAR_RENTAL_H_INCLUDED
