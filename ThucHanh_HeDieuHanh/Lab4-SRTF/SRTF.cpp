//SRTF (SJF preemtive)
#include <iostream>
#include <algorithm> 
#include <iomanip>
#include <string.h> 
using namespace std;
struct Process {
    int proc; //số thứ tự của tiến trình 
    int arrivalTime; //thời gian tiến trình được cấp CPU hoặc đưa vào hàng đợi (nếu có tiến trình khác đang thực thi)
    int burstTime;
    int startTime; //thời gian khi tiến trình được cấp CPU 
    int completionTime; //thời gian từ lúc tiến trình được cấp CPU đến khi thực thi xong (khác với thời gian hoàn thành)
    int turnaroundTime; //thời gian hoàn thành 
    int waitingTime; //thời gian chờ 
    int responseTime; //thời gian đáp ứng 
};
int Random(int min, int max) {
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}
int main() {
    int n; //số lượng tiến trình 
    struct Process p[100];
    int burstRemaining[100]; //mảng chứa Burst Time còn lại (nếu có) sau khi kết thúc 1 lần thực thi của tiến trình 
    int isCompleted[100]; //mảng chứa các tiến trình đã hoàn thành
    memset(isCompleted, 0, sizeof(isCompleted)); //khởi tạo các phần tử trong mảng trên bằng 0 
    cout << "\t\t\tDEMO SHORTEST REMAINING TIME FIRST" << endl;
    cout << "Enter the number of processes: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        p[i].arrivalTime = Random(0, 20); //Arrival Time được chọn ngẫu nhiên từ 0 đến 20
        p[i].burstTime = Random(2, 12); //Burst Time được chọn ngẫu nhiên từ 2 đến 12
        p[i].proc = i + 1; //tăng số thứ tự của tiến trình lên 1 
        burstRemaining[i] = p[i].burstTime;
    }
    int currentTime = 0; //thời gian hiện tại của hệ thống 
    int completed = 0; //số tiến trình đã hoàn thành
    while (completed != n) { //lặp khi chưa hoàn thành các tiến trình
        int index = -1; //biến index chỉ số thứ tự của tiến trình 
        int min_burstTime = 12; //biến này dùng để so sánh với các Burst Time của tiến trình 
        for (int i = 0; i < n; i++) { //tìm tiến trình có Burst Time nhỏ nhất để thực thi 
            if (p[i].arrivalTime <= currentTime && isCompleted[i] == 0) { //xét tiến trình có Arrival Time nhỏ hơn hoặc bằng thời gian hiện tại và chưa hoàn thành 
                if (burstRemaining[i] < min_burstTime) {
                    min_burstTime = burstRemaining[i];
                    index = i;
                }
                if (burstRemaining[i] == min_burstTime) {
                    if (p[i].arrivalTime < p[index].arrivalTime) {
                        min_burstTime = burstRemaining[i];
                        index = i;
                    }
                }
            }
        }
        if (index != -1) { //đã chọn được tiến trình hợp lí để thực thi 
            if (burstRemaining[index] == p[index].burstTime) {
                p[index].startTime = currentTime;
            }
            burstRemaining[index] -= 1; //giảm Burst Time đi 1 
            currentTime++; //tăng thời gian hiện tại của hệ thống thêm 1 
            if (burstRemaining[index] == 0) { //xét khi Burst Time còn lại đã hết (tiến trình đã hoàn thành)
                p[index].completionTime = currentTime;
                p[index].turnaroundTime = p[index].completionTime - p[index].arrivalTime;
                p[index].waitingTime = p[index].turnaroundTime - p[index].burstTime;
                p[index].responseTime = p[index].startTime - p[index].arrivalTime;
                isCompleted[index] = 1; //cập nhật tiến trình vị trí index đã hoàn thành
                completed++; //tăng số lượng tiến trình đã hoàn thành thêm 1
            }
        }
        else {
            currentTime++; //nếu chưa chọn được tiến trình hợp lí để thực thi thì tăng thời gian hiện tại của hệ thống thêm 1
        }
    }
    cout << endl << endl;
    cout << "#Process\t" << "ArrivalTime\t" << "BurstTime\t" << "TurnaroundTime\t" << "WaitingTime\t" << "ResponseTime\t" << "\n" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].proc << "\t\t" << p[i].arrivalTime << "\t\t" << p[i].burstTime << "\t\t" << p[i].turnaroundTime << "\t\t" << p[i].waitingTime << "\t\t" << p[i].responseTime << "\t\t" << "\n" << endl;
    }
}