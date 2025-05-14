//Car Parking Management Project.
//Pakeeza_23P-0526.
//Rihab_23P-3072.

#include<iostream>
#include<fstream>
using namespace std;

// Constants
const int BparkingSlot = 30;
const int GparkingSlot = 40;
const int TparkingSlot = 150;
const int ManagerPerDayPay = 1000;
const int floorAttendPerDayPay = 500;
const int GuardPerDayPay = 300;

// struct to hold parking data.
struct ParkingData {
    int totalVanParked = 0;
    int vanCharges = 0;
    int totalCarParked = 0;
    int carCharges = 0;
    int totalMotoParked = 0;
    int bikeCharges = 0;
};

// Function Prototypes.
void displayMenu();
void saveData(const ParkingData& data);
bool loadData(ParkingData& data);
int VanIn(int current);
int VanOut(int current);
int carIn(int current);
int carOut(int current);
int bikeIn(int current);
int bikeOut(int current);
int calculateSalaries();
void generateReport(const ParkingData& data);

int main(){
    ParkingData data;
    
    // load previous data if available
    if(!loadData(data)) {
        cout<< "Starting with fresh data....." << endl;
    }
    
    while (true) {
        displayMenu();
        int input;
        cin >> input;
        
        switch(input) {
            case 1:
                 data.totalVanParked = VanIn(data.totalVanParked);
                 data.vanCharges = 50 * data.totalVanParked;
                 cout<< "Van charges collected: " << data.vanCharges << endl;
                 saveData(data);
                 break;
            
            case 2:
                 data.totalVanParked = VanOut(data.totalVanParked);
                 data.vanCharges = 50 * data.totalVanParked;    
                 saveData(data);
                 break;
                 
            case 3:
                 cout<< "Vans/hi-aces parked:" << data.totalVanParked << endl;
                 break;
                 
            case 4:
                 data.totalCarParked = carIn(data.totalCarParked); 
                 data.carCharges = 30 * data.totalCarParked;
                 cout<< "Car charges collected: " << data.carCharges << endl;
                 saveData(data);
                 break; 
                 
            case 5:
                 data.totalCarParked = carOut(data.totalCarParked);
                 data.carCharges = 30 * data.totalCarParked;    
                 saveData(data);
                 break; 
                 
            case 6:
                 cout<< "Cars parked:" << data.totalCarParked << endl;
                 break;  
                 
            case 7:
                 data.totalMotoParked = bikeIn(data.totalMotoParked); 
                 data.bikeCharges = 20 * data.totalMotoParked;
                 cout<< "Bike charges collected: " << data.bikeCharges << endl;
                 saveData(data);
                 break; 
                 
            case 8:
                 data.totalMotoParked = bikeOut(data.totalMotoParked);
                 data.bikeCharges = 20 * data.totalMotoParked;    
                 saveData(data);
                 break; 
                 
            case 9:
                 cout<< "Bikes parked:" << data.totalMotoParked << endl;
                 break;     
            
            case 0:
                 generateReport(data);
                  // clear data when generating report (end of day)
                 data = ParkingData(); // Reset to default
                 saveData(data);
                 return 0;
                 
            default:
                  cout << "Invalid Choice! Please try again." << endl;
               
        }   
     }    
      return 0;
}   
 
 // Funtion implemetations
  void saveData(const ParkingData& data) {
      ofstream outFile("parking_data.dat", ios::binary);
      if(outFile) {
         outFile.write(reinterpret_cast<const char*>(&data),sizeof(data));
      }
}

bool loadData(ParkingData& data) {
     ifstream inFile("parking_data.dat", ios::binary);
     if(inFile){
        inFile.read(reinterpret_cast<char*> (&data), sizeof(data));
        return true;
      }
      return false;
}

int VanIn(int current){
    if(current < BparkingSlot){
       current++;
       cout << "Van/Hi-aces parked successfully." << endl;
    }else{
        cout << "No more space for van/Hi-aces" << endl;
    }
    return current;
}

int VanOut(int current){
    if(current > 0){
       current--;
       cout << "Van/Hi-aces exited successfully." << endl;
    }else{
        cout << "No van/Hi-aces currently parked" << endl;
    }
    return current;
}

int carIn(int current){
    if(current < GparkingSlot){
       current++;
       cout << "Car parked successfully." << endl;
    }else{
        cout << "No more space for Cars" << endl;
    }
    return current;
}

int carOut(int current){
    if(current > 0){
       current--;
       cout << "Car exited successfully." << endl;
    }else{
        cout << "No Cars currently parked" << endl;
    }
    return current;
}

int bikeIn(int current){
    if(current < TparkingSlot){
       current++;
       cout << "Motorbike/Bicycle parked successfully." << endl;
    }else{
        cout << "No more space for Motorbike/Bicycle " << endl;
    }
    return current;
}

int bikeOut(int current){
    if(current > 0){
       current--;
       cout << "Motorbike/Bicycle  exited successfully." << endl;
    }else{
        cout << "No Motorbike/Bicycle  currently parked" << endl;
    }
    return current;
}
 
int calculateSalaries(){
    return ManagerPerDayPay + (GuardPerDayPay * 2) + (floorAttendPerDayPay * 3);
}    
         
  void displayMenu(){
      cout << "\n------------------------------------------------------" << endl;
      cout << "Welcome To Parking Management system" << endl;
      cout << "1. Van/Hi-ace enters parking" << endl;
      cout << "2. Van/Hi-ace exits parking" << endl;
      cout << "3. Van/Hi-ace in basement" << endl;
      cout << "4. Car enters parking" << endl;
      cout << "5. Car exit parking" << endl;
      cout << "6. check cars in ground floor" << endl;
      cout << "7. MotorBike/Bicycle enters parking" << endl;
      cout << "8. MotorBike/Bicycle exits parking" << endl;
      cout << "9. check bikes in top floor" << endl;
      cout << "0. Generte daily report (end of day)" << endl;
      cout << "\n------------------------------------------------------" << endl;
      cout << "Enter your choice:";      
}      
      
  void generateReport(const ParkingData& data) {
      int totalAmount = data.vanCharges + data.carCharges + data.bikeCharges;
      float tax = totalAmount * 0.05f;
      int salaries = calculateSalaries();
      int netProfit = totalAmount - tax - salaries;
      
      cout << "\nDAILY REPORT" << endl;
      cout << "-------------------------------------------" << endl;
      cout << "Vans/hi-aces parked today:" << data.totalVanParked << endl;
      cout << "Cars parked today:" << data.totalCarParked << endl;
      cout << "Bikes parked today:" << data.totalMotoParked << endl;
      cout << "Total revenue:" << totalAmount << endl;
      cout << "5% tax paid to government:" << tax << endl;
      cout << "Salaries paid:" << salaries << endl;
      cout << "Net Profit:" << netProfit << endl;
      cout << "\nData reset for new day." << endl;
}   
         
                
