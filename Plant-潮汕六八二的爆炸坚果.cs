using System;
using PlantsVsZombies_setmaker;
//啃咬到它的僵尸被打死的话会有爆炸效果，坚果死后所有僵尸后退3格
namespace Main
{
    class Program
    {
        public static void Main()
        {
            Memory.GetPid("PlantsVsZombies Plus Version 95");
            Memory.Init();
            PvzEvent.ClearEvent();
            while(true)
            {
                if(Game.PlaingAndNotPause)
                {
                    foreach(var Event in PvzEvent.GetEvent())
                    {
                        if(Event.EventType == PvzEventType.PlantHit && Event.ThisPlant.Type == PlantType.高坚果)
                        {
                            Event.ThisZombie.Free_Addres_1 = 1;
                        }
                    }
                    foreach(var Zombie in Zombie.GetZombies())
                    {
                        if(Zombie.Free_Addres_1 == 1 && Zombie.Life[0] <= 0)
                        {
                            Plant plant = Plant.CreatPlant(PlantType.樱桃炸弹, Zombie.Line, Zombie.Column);
                            plant.A_灰烬植物立刻爆炸();
                            Zombie.Free_Addres_1 = 0;//取消标记
                        }
                    }
                    foreach(var Plant in Plant.GetPlants())
                    {
                        if(Plant.Life <= 0 && Plant.Type == PlantType.高坚果)
                        {
                            foreach(var Zombie in Zombie.GetZombies())
                            {
                                Zombie.Column += 3;
                            }
                        }
                    }
                }
                System.Threading.Thread.Sleep(10);
            }
        }
    }
}
