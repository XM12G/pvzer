#include "pvzclass.h"
#include <iostream>

using namespace std;

int main() {
	DWORD pid = ProcessOpener::Open();
	RECT rect;
	RECT rectc;
	if (pid) {
		PVZ* p = new PVZ(pid);
		EnableBackgroundRunning();
		//BOSS：梦魇
		//技能1：窗口缩小
		/*
		SetWindowLong(PVZ::Memory::mainwindowhandle, GWL_STYLE, 0x10CF0000);//使窗口可以自由缩放
		//初始化PVZ
		GetWindowRect(PVZ::Memory::mainwindowhandle, &rect);
		int a = rect.right - rect.left;
		int b = rect.bottom - rect.top;
		SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a, b, SWP_SHOWWINDOW);
		while (p->BaseAddress) {
			GetWindowRect(PVZ::Memory::mainwindowhandle, &rect);//窗口大小
			int a2 = rect.right - rect.left;
			int b2 = rect.bottom - rect.top;
			GetClientRect(PVZ::Memory::mainwindowhandle, &rectc);//获取用户窗体的大小
			if (rectc.right - rectc.left == 0 or rectc.bottom - rectc.top == 0) {
				::SendMessage(PVZ::Memory::mainwindowhandle, WM_CLOSE, 0, 0);//结束游戏
			}
			SetWindowPos(PVZ::Memory::mainwindowhandle,NULL,200,200,a2-p->ZombiesCount*2,b2-p->ZombiesCount*2,SWP_SHOWWINDOW);//依据僵尸数量进行递减

			if (a2 > a) {
				SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a, b2, SWP_SHOWWINDOW);
			}

			if (b2 > b) {
				SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a2, b, SWP_SHOWWINDOW);
			}

			if (b2 >b and a2 > a) {
				SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a, b, SWP_SHOWWINDOW);
			}
			Sleep(2000);//延时
			
			
		}*/

		
		delete p;
	}

	//note：常用窗口操作
	/*
	SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 100, 100, 500, 500, SWP_SHOWWINDOW);
	SetWindowLong(PVZ::Memory::mainwindowhandle, GWL_STYLE, 0x10CF0000);
	//::SendMessage(PVZ::Memory::mainwindowhandle,WM_CLOSE,0,0);
	RECT rect;
		// 只获得窗口客户区的大小
	GetClientRect(PVZ::Memory::mainwindowhandle, &rect);

	int client_width = (rect.right - rect.left);
	int client_height = (rect.bottom - rect.top);
	cout << client_height << endl;
	cout << client_width << endl;
	Sleep(5000);
	SetWindowPos(PVZ::Memory::mainwindowhandle,NULL,100,100,client_height,client_width,SWP_SHOWWINDOW);
	*/

	return 0;
	

}