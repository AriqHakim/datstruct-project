#include "util/graph.cpp"
#include <limits>

void ignore_line();

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
        system("cls");
        std::cout << "Program Tabel Jadwal Guru" << std::endl;

        std::cout << "1. Input Jadwal\n2. Lihat Jadwal\n3. Exit\n"
                  << std::endl;
        std::cout << "Pilihan : ";
        std::cin >> menu;
        if (std::cin.fail())
        {
            std::cin.clear();
            ignore_line();
            std::cout << "Input tidak boleh berupa string atau karakter!\n\n";
            system("pause");
            goto mainmenu;
        }

        switch (menu)
        {
        case 1:
        menu1:
            system("cls");
            count = count + 1;
            std::cout << "[Input Jadwal]\n\n";
            std::cout << "Input ke-" << count << std::endl;
            std::cout << "[Identitas Guru]" << std::endl;
            std::cout << "Nama\t\t: ";
            std::cin >> nama;
            std::cout << "Kode Mapel\t: ";
            std::cin >> kode;
            if (!isEmpty(searchByKode(head.adjacencyList, kode)))
            {
                std::cout << "\nKode mapel tidak boleh sama\n";
                system("pause");
                count = count - 1;
                goto menu1;
            }
            std::cout << "\n";
            pNew = createNode(Guru{kode, nama});
            Graph::insertNode(head, pNew);

        balikmenu1:
            system("cls");
            std::cout << "[Ketersediaan]" << std::endl;
            std::cout << "1. Senin\n2. Selasa\n3. Rabu\n4. Kamis\n5. Jumat\n6. Kembali" << std::endl;
            std::cout << "Pilihan\t: ";
            std::cin >> day;
            if (std::cin.fail())
            {
                std::cin.clear();
                ignore_line();
                std::cout << "Input tidak boleh berupa string atau karakter!\n\n";
                system("pause");
                goto balikmenu1;
            }
            std::cout << "\n";

            switch (day)
            {
            case 1:
                temp = Hari::searchByHari(jadwal, "Senin");
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusSenin(pNew);
                break;
            case 2:
                temp = Hari::searchByHari(jadwal, "Selasa");
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusSelasa(pNew);
                break;
            case 3:
                temp = Hari::searchByHari(jadwal, "Rabu");
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusRabu(pNew);
                break;
            case 4:
                temp = Hari::searchByHari(jadwal, "Kamis");
                Graph::addEdge(head, pNew, temp);
                Hari::setStatusKamis(pNew);
                break;
            case 5:
                temp = Hari::searchByHari(jadwal, "Jumat");
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
                std::cout << "Input Invalid...\n"
                          << std::endl;
                system("pause");
                system("cls");
                goto balikmenu1;
            }
        reconfirm:
            std::cout << "Input hari lain (y/n)\t: ";
            std::cin >> confirm;
            if (confirm == 'n' || confirm == 'N')
            {
                std::cout << "\nKembali ke menu utama\n";
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
            head = Graph::colorIt(head, 'A');
            system("cls");
            std::cout << "[Lihat Jadwal]\n\n";
            std::cout << "[Tabel Jadwal]\n";
            std::cout << "+" << std::setw(5) << std::setfill('-') << std::right
                      << "+" << std::setw(17) << std::setfill('-') << std::right
                      << "+" << std::setw(17) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(10) << std::setfill('-') << std::right << "+\n";
            std::cout << "| " << std::setw(3) << std::setfill(' ') << std::left << "No"
                      << "| " << std::setw(15) << std::setfill(' ') << std::left << "Nama"
                      << "| " << std::setw(15) << std::setfill(' ') << std::left << "Kode Mapel"
                      << "| " << std::setw(7) << std::setfill(' ') << std::left << "Senin"
                      << "| " << std::setw(7) << std::setfill(' ') << std::left << "Selasa"
                      << "| " << std::setw(7) << std::setfill(' ') << std::left << "Rabu"
                      << "| " << std::setw(7) << std::setfill(' ') << std::left << "Kamis"
                      << "| " << std::setw(7) << std::setfill(' ') << std::left << "Jumat"
                      << "| " << std::setw(7) << std::setfill(' ') << std::left << "kelas"
                      << "| \n";
            std::cout << "+" << std::setw(5) << std::setfill('-') << std::right
                      << "+" << std::setw(17) << std::setfill('-') << std::right
                      << "+" << std::setw(17) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(9) << std::setfill('-') << std::right
                      << "+" << std::setw(10) << std::setfill('-') << std::right << "+\n";
            Graph::printGraph(head);
            Graph::setUncolored(head);

            system("pause");
            system("cls");
            goto mainmenu;
            break;
        case 3:

            std::cout << "Program Terminated..." << std::endl;
            break;
        default:
            std::cout << "\nInput Invalid...\n"
                      << std::endl;
            system("pause");
            system("cls");
        }
    } while (menu < 1 || menu > 3);

    delete pNew;
    delete temp;
    Hari::deleteListHari(jadwal);
    Graph::deleteGraph(head);

    return 0;
}

void ignore_line()
{
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
