#include <iostream>
#include <fstream>

enum EWeapon
{
    none, sword, lance, bow
};

//estructura de datos que deben persisitir

struct SGameData
{
    char name[16];
    EWeapon CurrentWeapon;
    int killStreak;
};

void Log(const char* msg)
{
    std::cout << msg << "\n";
}

int main()
{
    std::cout << "Hello World!\n";

    //leer el archivo de savegame 
    std::fstream savefile("data.sav", std::ios::in | std::ios::out);

    if (savefile.is_open())
    {
        Log("savefile abierto");

        //leer datos del archivo
        SGameData data;
        savefile.read(data.name, 16);
        savefile.read((char*) & data.CurrentWeapon, 4);
        savefile.read((char*)&data.killStreak, 4);

        std::cout << "hola" << data.name;
        std::cout << "tienes arma" << data.CurrentWeapon << "y has matado a" << data.killStreak;
    }
    else
    {
        Log("crear savefile vacio e iniciar");
        SGameData data;
        Log("Elige tu nick");
        std::cin >> data.name;
        data.CurrentWeapon = EWeapon::none;
        data.killStreak = 0;

        savefile.open("data.sav", std::ios::out);
        if (savefile.is_open())
        {
            //dumpear la estructura creada
            savefile.seekp(0, std::ios::beg);
            savefile.write((const char*)&data, sizeof(SGameData));
        }
        else
        {
            Log("no se pudo crear el archivo");
        }
    }

    savefile.close();
    return 0;
}

