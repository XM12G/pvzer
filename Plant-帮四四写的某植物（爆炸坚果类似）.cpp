#include "pvzclass.h"

#include <iostream>



using namespace std;



int main() {

	DWORD pid = ProcessOpener::Open();
	if (pid) {

		PVZ* p = new PVZ(pid);

		EnableBackgroundRunning();

		PVZ::Plant* plant[300];

		int tong[300];

		int plantnum = 0;

		

		while (p->BaseAddress) {

			if (p->PlantsCount != plantnum) {

				for (int i = 0; i < plantnum; i++)

				{

					delete plant[i];

				}

				plantnum = p->GetAllPlants(plant);

			}

			for (int i = 0; i < plantnum; i++)

			{

				if (tong[i]!=1) {

					tong[i] = 0;

					cout <<"tong"<< i<<endl;

				}

			}

			for (int i = 0; i < plantnum; i++)

			{

				if (plant[i]->Type==PlantType::Scaredyshroon and tong[i]==0) {

					plant[i]->Sleeping = true;

					plant[i]->MaxHp = 5000;

					plant[i]->Hp = 5000;

					

					tong[i] = 1;

					cout << "plant" << i << endl;

				}

				if (plant[i]->Type==PlantType::Scaredyshroon and plant[i]->Hp==0) {

					plant[i]->Hp = -9999;

					PVZ::Plant* plant2 = Creater::CreatePlant(PlantType::CherryBomb,plant[i]->Row,plant[i]->Column);



					plant2->ShootingCountdown = 1;

					plant2->AttributeCountdown = 1;

					plant2->EffectiveCountdown = 1;

					plant2->ShootOrProductCountdown = 1;

				}

				

				

			}

			//初始化ok

			

		}

		

		delete p;

	}







		

	return 0;

	



}
