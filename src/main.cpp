#include "util/graph.cpp"

int main()
{
    Hari::pDayNode jadwal = Hari::inisiasiHari();
    Graph::graph head = Graph::inisiasiGraph();
    int menu;
    int count = 0;
    std::string nama;
    std::string kode;
    int day;
    char confirm;
    pNode pNew = nullptr;
    Hari::pDayNode temp = nullptr;
    do
    {

    mainmenu:
        std::cout << "Program Tabel Jadwal Guru" << std::endl;

        std::cout << "1. Input Jadwal\n2. Lihat Jadwal\n3. Exit\n"
                  << std::endl;
        std::cout << "Pilihan : ";
        std::cin >> menu;

        switch (menu)
        {
        case 1:
        
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
            pNew = createNode(Guru{kode, nama, {'0', '0', '0', '0', '0'}, inisiasiKelas()});
            Graph::insertNode(head, pNew);
        balikmenu1:
            system("cls");
            std::cout << "[Ketersediaan]" << std::endl;
            std::cout << "1. Senin\n2. Selasa\n3. Rabu\n4. Kamis\n5. Jumat\n6. Kembali" << std::endl;
            std::cout << "Pilihan\t: ";
            std::cin >> day;
            std::cout << "\n";

            switch (day)
            {
            case 1:
                temp = Hari::searchByHari(jadwal, "Senin");
                // Hari::addVertex(temp, pNew);
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusSenin(pNew);
                break;
            case 2:
                temp = Hari::searchByHari(jadwal, "Selasa");
                // Hari::addVertex(temp, pNew);
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusSelasa(pNew);
                break;
            case 3:
                temp = Hari::searchByHari(jadwal, "Rabu");
                // Hari::addVertex(temp, pNew);
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusRabu(pNew);
                break;
            case 4:
                temp = Hari::searchByHari(jadwal, "Kamis");
                // Hari::addVertex(temp, pNew);
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusKamis(pNew);
                break;
            case 5:
                temp = Hari::searchByHari(jadwal, "Jumat");
                // Hari::addVertex(temp, pNew);
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusJumat(pNew);
                break;
            case 6:
                std::cout << "Kembali ke menu utama\n";
                count = count - 1;
                system("pause");
                system("cls");
                goto mainmenu;
                break;
            default:
                count = count - 1;
                std::cout << "Input Invalid...\n" << std::endl;
                system("pause");
                system("cls");
                goto balikmenu1;
            }
            reconfirm:
            std::cout << "Input hari/guru lain (y/n)\t: ";
            std::cin >> confirm;
            if (confirm == 'n' || confirm == 'N')
            {
                std::cout << "Kembali ke menu utama\n";
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
            Graph::sortGraph(head);
            system("cls");
            std::cout << "[Lihat Jadwal]\n\n";
            std::cout << "[Tabel Jadwal]\n";
            std::cout << "+" << std::setw(94) << std::setfill('-') << "+\n";
            std::cout << "| " << std::setw(3) << std::setfill(' ') << std::left << "No"
                      << "| " << std::setw(15) <<std::setfill(' ') << std::left << "Nama"
                      << "| " << std::setw(15) <<std::setfill(' ') << std::left << "Kode Mapel"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Senin"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Selasa"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Rabu"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Kamis"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "Jumat"
                      << "| " << std::setw(7) <<std::setfill(' ') << std::left << "kelas" << "| \n";
            Graph::printGraph(head);
            
            system("pause");
            system("cls");
            goto mainmenu;
            break;
        case 3:
            std::cout << "\nProgram Terminated..." << std::endl;
            break;
        default:
            std::cout << "\nInput Invalid...\n" << std::endl;
            system("pause");
            system("cls");
        }
    } while (menu < 1 || menu > 3);
}
