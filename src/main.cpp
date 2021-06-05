//#include "util/graph.cpp"
#include <iostream>
#include <iomanip>

int main()
{
    //Hari::pDayNode jadwal = Hari::inisiasiHari();
    int menu;
    int count = 0;
    std::string nama;
    std::string kode;
    int day;
    char confirm;
    do
    {

    mainmenu:
        std::cout << "Welsch-Powell algorithm implementation" << std::endl;

        std::cout << "1. Input Jadwal\n2. Lihat Jadwal\n3. Hapus Jadwal\n4. Exit\n"
                  << std::endl;
        std::cout << "Pilihan : ";
        std::cin >> menu;

        switch (menu)
        {
        case 1:
        balikmenu1:
            system("cls");
            count = count + 1;
            std::cout << "[Input Jadwal]\n\n";
            std::cout << "Input ke-" << count <<std::endl;
            std::cout << "[Identitas Guru]" << std::endl;
            std::cout << "Nama\t\t: ";
            std::cin >> nama;
            std::cout << "Kode Mapel\t: ";
            std::cin >> kode;
            std::cout << "\n";

            std::cout << "[Ketersediaan]" << std::endl;
            std::cout << "1. Senin\n2. Selasa\n3. Rabu\n4. Kamis\n5. Jumat\n6. Kembali" << std::endl;
            std::cout << "Pilihan\t: ";
            std::cin >> day;
            std::cout << "\n";

            switch (day)
            {
            case 1:
                //isi
                break;
            case 2:
                //isi
                break;
            case 3:
                //isi
                break;
            case 4:
                //isi
                break;
            case 5:
                //isi
                break;
            case 6:
                std::cout << "Kembali ke menu utama\n";
                count = count - 1;
                system("pause");
                system("cls");
                goto mainmenu;
                break;
            }
            reconfirm:
            std::cout << "Input hari/guru lain (y/n)\t: ";
            std::cin >> confirm;
            if (confirm == 'n' || confirm == 'N')
            {
                system("pause");
                system("cls");
                goto mainmenu;
            }
            else if (confirm == 'y' || confirm == 'Y')
            {
                goto balikmenu1;
            }
            else
            {
                goto reconfirm;
            }
            break;
        case 2:

            system("cls");
            std::cout << "[Lihat Jadwal]\n\n";
            std::cout << "[Tabel Jadwal]\n";
            std::cout << "| " << std::setw(3) << std::setfill(' ')<<std::left << "No"
                      << "| " << std::setw(15) <<std::setfill(' ') << std::left << "Nama"
                      << "| " << std::setw(15) <<std::setfill(' ') << std::left << "Kode Mapel"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Senin"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Selasa"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Rabu"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Kamis"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Jumat" << "| \n";
            
            system("pause");
            system("cls");
            goto mainmenu;
            break;
        case 3:

            system("cls");
            std::cout << "[Hapus Jadwal]" << std::endl;
            break;
        case 4:
            std::cout << "Program Terminated..." << std::endl;
            break;
        default:
            std::cout << "Input Invalid" << std::endl;
            system("pause");
        }
    } while (menu < 1 || menu > 4);
}
