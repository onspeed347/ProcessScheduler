# ProcessScheduler 

CẤU TRÚC CHƯƠNG TRÌNH MÔ PHỎNG CÁC THUẬT TOÁN ĐIỀU PHỐI TIẾN TRÌNH
Thực hiện: Nhóm 1 - Hệ điều hành (Lớp 66-KHMT)

ProcessScheduler/
│
├── main.cpp			// Hàm main() gọi các module, điều phối tổng thể
├── process.h			// Khai báo struct Process & hằng số chung
├── process.cpp		    // Định nghĩa biến và hằng số chung
├── utils.h			    // Khai báo các hàm in tiêu đề, in Gantt, in waiting list, kết quả
├── utils.cpp			// Định nghĩa các hàm tiện ích
│
├── algorithms/			// Folder chứa các thuật toán điều phối
│   ├── scheduler.h			//Khai báo các hàm thuật toán điều phối
│   ├── runAlgorithm		//Xử lý tiến trình dựa trên thuật toán được người dùng lựa chọn
│   ├── FCFS.cpp
│   ├── SJF.cpp
│   ├── RR.cpp	
│   ├── SRTF.cpp
│   ├── PriorityPreemptive.cpp
│   └── PriorityNonPreemptive.cpp
│
└── input.txt				// File dữ liệu đầu vào
