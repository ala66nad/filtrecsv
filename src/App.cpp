#include "App.hpp"
#include "ControlA.hpp"

int App::OnExecute(int argc, char *argv[])
{
    PARAMS p = Params(argc, argv);
    if (p.option)
    {
        const auto controla = std::make_unique<ControlA>();
        controla->Control1A();
    }

    RecupCSVTemp(To_lower(p.c));
    return 0;
}

std::vector<std::string> App::ListOfCSV()
{
    std::vector<std::string> vTmp{};
    for (const auto &file : std::filesystem::directory_iterator(".\\test"))
        if (file.path().extension() == ".csv")
            vTmp.push_back(file.path().string());

    return vTmp;
}

std::string App::To_lower(std::string s)
{
    for (char &x : s)
        x = tolower(x);
    return s;
}

bool App::Contains(std::string_view s, std::string c)
{
    size_t i{0};
    std::string_view tmp{""};
    char* sTmp = new char[s.size() + 1]{""};
    for (auto it = std::begin(s); it != std::end(s); it++)
        if (!(*it == '(' || *it == ')' || *it == '-' || *it == ' ' || *it == '.' || *it == '_'))
            sTmp[i++] = tolower(*it);

    tmp = std::string_view(sTmp);
    delete[] sTmp;
    return tmp.contains(c);
}

void App::FileRead(std::string file, std::string c)
{
    m.lock();
    std::cout << _fileIndex++ << " " << file << std::endl;
    m.unlock();
    std::string line{""};
    std::ifstream f(file);
    if (f.is_open())
    {
        while (getline(f, line, '\n'))
        {
            if (Contains(line, c))
            {
                m.lock();
                _ofs << ++_i << ";" << line << "\n";
                m.unlock();
            }
        }
        f.close();
    }
    else
        std::cout << "Unable to open file";
}

void App::openCSV()
{
    _ofs.open("./tmp.csv");
    _ofs << "id;"
         << "no_rame;no_vehicule;code_serie;date_intervention;duree_intervention;type_op_cri;date_signalement;localisation;specialite;nom_chantier;intervenant;anom_nom;cri_numero;commentaire;km_rame;libelle_sign;type_signalement_cri;defaut_majeur;incident_confort;conclusion_interv;fonction;ensemble;niveau_3;niveau_4;niveau_5;niveau_6;reparation_nom;org_desig_nom_1;org_type_nom_1;org_numero_1;org_desig_nom_2;org_type_nom_2;org_numero_2;libelle_motif_depose;nom_etablissement;cri_suite;"
         << "\n";
}

void App::closeCSV()
{
    _ofs.close();
}

void App::RecupCSVTemp(std::string c)
{
     openCSV();
 
    const auto a = ListOfCSV();
    std::vector<std::thread> threads;
    for (size_t i = 0; i < a.size(); i++)
        threads.push_back(std::thread(&App::FileRead, this, a[i], c));

    for (auto &th : threads)
        th.join();

    closeCSV();
}
