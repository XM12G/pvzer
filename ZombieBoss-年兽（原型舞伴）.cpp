#include <iostream>
#include <thread>
#include <future>
#include "pvzclass.h"

using namespace std;

ZombieType::ZombieType sj() {
	int a = rand() % 10;
	switch (a)
	{
	case 0:
		return ZombieType::BungeeZombie;
	case 1:

	case 2:
		return ZombieType::FootballZombie;
	case 3:
		return ZombieType::NewspaperZombie;
	case 4:
		return ZombieType::BalloonZombie;
	case 5:

	case 6:
		return ZombieType::GatlingPeaZombie;
	case 7:

	case 8:
		return ZombieType::PeashooterZombie;
	}
}
PVZ::Zombie* CreateBoss() {
	PVZ::Zombie* zombie = Creater::CreateZombie(ZombieType::BackupDancer, 5, 8);
	return zombie;
}
void removelawnmover() {
	byte asmcode[] = { 0x8B,0x3D,0xC0,0x9E,0x6A,0x0,
   0x8B,0xB7,0x68,0x7,0x0,0x0,
0x85,0xF6,
0x74,0x23,
0x8B,0x9E,0x4,0x1,0x0,0x0,
0x8B,0xB6,0x0,0x1,0x0,0x0,
0x39,0x3E,
0x75,0xD,
0xE8,0x2,0x0,0x0,0x0,
0xEB,0x6,
0x68,0xA0,0x8D,0x45,0x0,
0xC3,
0x83,0xC6,0x48,
0x4B,
0x7F,0xE9,
0xC3 };
	PVZ::Memory::Execute(asmcode, sizeof(asmcode));
}
void sethp(PVZ::Zombie* zombie) {
	zombie->SetBodyHp(100000, 100000);
}
void fullsun(PVZ* pvz) {
	while (pvz->BaseAddress)
	{
		pvz->Sun = 9990;
	}
}
void NoCoolDown(PVZ* pvz) {
	while (pvz->BaseAddress)
	{
		PVZ::CardSlot* cardsolt = pvz->GetCardSlot();
		for (int i = 0; i < 10; i++)
		{
			PVZ::CardSlot::SeedCard* card = cardsolt->GetCard(i);
			card->CoolDown = 99999;
		}
	}
}
void SJCreateZombie(PVZ* pvz , PVZ::Zombie* zombie){
	while (zombie->Type== ZombieType::BackupDancer) {
		int row = rand() % 5;
		int co = rand() % 4;
		int realco = 8 - co;
		Creater::CreateZombie(sj(), row, realco);
		Sleep(1000);
	}
}
void SJMove(PVZ::Zombie* zombie) {
	while (zombie->Type == ZombieType::BackupDancer) {
		int row = rand() % 5;
		int co = rand() % 8;
		zombie->Row = row;
		double x = (double)80 * co;
		/*此处的原代码是这样的（以X计算列）
		double x = (proj->X - 40.0) / 80.0;
		int col = (int)(x + 0.5);
		*/
		zombie->X = x;
		Sleep(1000);
	}
}
void window(PVZ* pvz,PVZ::Zombie* zombie , int a,int b) {
	if(pvz->BaseAddress){
		while (zombie->Type == ZombieType::BackupDancer) {
			RECT rect;
			RECT rectc;
			GetWindowRect(PVZ::Memory::mainwindowhandle, &rect);//窗口大小
			int a2 = rect.right - rect.left;
			int b2 = rect.bottom - rect.top;
			GetClientRect(PVZ::Memory::mainwindowhandle, &rectc);//获取用户窗体的大小
			if (rectc.right - rectc.left == 0 or rectc.bottom - rectc.top == 0) {
				::SendMessage(PVZ::Memory::mainwindowhandle, WM_CLOSE, 0, 0);//结束游戏
			}
			if (a2 > a) {
				SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a, b2, SWP_SHOWWINDOW);
			}

			if (b2 > b) {
				SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a2, b, SWP_SHOWWINDOW);
			}

			if (b2 > b and a2 > a) {
				SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a, b, SWP_SHOWWINDOW);
			}
			GetWindowRect(PVZ::Memory::mainwindowhandle, &rect);//窗口大小
			a2 = rect.right - rect.left;
			b2 = rect.bottom - rect.top;
			SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a2 - 10, b2 - 10, SWP_SHOWWINDOW);//依据僵尸数量进行递减
			Sleep(1000);
		}
	}
}
void putmouse(PVZ::Mouse* mouse, PVZ::Zombie* zombie) {
	double x = zombie->X;
	double y = zombie->Y;
	double mousex = mouse->X;
	double mousey = mouse->Y;
	if (mousex == x and mousey < y) {
		mouse->Y = mousey + 5;
		mouse->MoveTo(mousex, mousey + 5);
	}
	if (mousex == x and mousey > y) {
		mouse->Y = mousey - 5;
		mouse->MoveTo(mousex, mousey - 5);
	}
	if (mousex > x and mousey == y) {
		mouse->X = mousex - 5;
		mouse->MoveTo(mousex - 5, mousey);
	}
	if (mousex < x and mousey == y) {
		mouse->MoveTo(mousex + 5, mousey);
	}
	if (mousex < x and mousey < y) {
		mouse->MoveTo(mousex + 5, mousey + 5);
	}
	if (mousex > x and mousey > y) {
		mouse->MoveTo(mousex - 5, mousey - 5);
	}
	if (mousex > x and mousey < y) {
		mouse->MoveTo(mousex - 5, mousey + 5);
	}
	if (mousex < x and mousey > y) {
		mouse->MoveTo(mousex + 5, mousey - 5);
	}
}
void ChangeCard(PVZ::CardSlot* cardsolt,PVZ::Zombie* zombie) {
	while (zombie->Type == ZombieType::BackupDancer) {
		for (int i = 0; i < 10; i++)
		{
			PVZ::CardSlot::SeedCard* card = cardsolt->GetCard(i);
			card->ContentCard = (CardType::CardType)(rand() % (6 * 8));

		}
	}
}
//{bossbar}功能，无法正常使用，已废弃
void Bossbar(PVZ::Zombie* zombie , PVZ* pvz) {
	int address = PVZ::Memory::ReadMemory<int>(0x6A9EC0);
	address = PVZ::Memory::ReadMemory<int>(address + 0x768);
	PVZ::Memory::WriteMemory<int>(address + 0x5564,5);
	while (zombie->Type==ZombieType::BackupDancer) {
		int zombiehp;
		int maxhp;
		zombie->GetBodyHp(&zombiehp,&maxhp);
		int address2 = PVZ::Memory::ReadMemory<int>(0x6A9EC0);
		address2 = PVZ::Memory::ReadMemory<int>(address2+0x768);
		PVZ::Memory::WriteMemory<int>(address2+0x5610,(maxhp-zombiehp)/1000);
	}
	int address2 = PVZ::Memory::ReadMemory<int>(0x6A9EC0);
	address2 = PVZ::Memory::ReadMemory<int>(address2+0x768);
	PVZ::Memory::WriteMemory<int>(address2+0x5610 , 100);
	
}
int main() {
	DWORD pid = ProcessOpener::Open();
	
	RECT rect;
	RECT rectc;
	if (pid) {
		PVZ* p = new PVZ(pid);
		
		SetWindowLong(PVZ::Memory::mainwindowhandle, GWL_STYLE, 0x10CF0000);//使窗口可以自由缩放
		GetWindowRect(PVZ::Memory::mainwindowhandle, &rect);
		int a = rect.right - rect.left;
		int b = rect.bottom - rect.top;
		SetWindowPos(PVZ::Memory::mainwindowhandle, NULL, 200, 200, a, b, SWP_SHOWWINDOW);
		PVZ::Mouse* mouse = p->GetMouse();//获取鼠标
		PVZ::CardSlot* cardsolt = p->GetCardSlot();
		
		EnableBackgroundRunning();
		srand(1024);
		if (p->BaseAddress) {
			removelawnmover();
			Sleep(7000);
			PVZ::Zombie* boss = CreateBoss();
			sethp(boss);
			thread fullsun(fullsun,p);
			thread NoCoolDown(NoCoolDown,p);
		    thread SJCreateZombie(SJCreateZombie, p, boss);
		    thread SJMove(SJMove, boss);
			thread window(window, p, boss,a, b);
			thread mouse(putmouse, mouse, boss);
			thread ChangeCard(ChangeCard,cardsolt,boss);
			fullsun.join();
			NoCoolDown.join();
			SJCreateZombie.join();
			SJMove.join();
			window.join();
			mouse.join();
			ChangeCard.join();
		}

		delete p;
	}
	return 0;
}
