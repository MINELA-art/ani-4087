#include <iostream>
#include <string>

// Fausse session : elle refuse les appels faits dans le mauvais ordre.
class Session
{
public:
    bool Wait()
    {
        if (trameOuverte)
        {
            ++refus;
            return false;
        }
        return true;
    }

    void Begin()
    {
        if (trameOuverte)
        {
            ++refus;
            return;
        }
        trameOuverte = true;
        ++debuts;
    }

    void End()
    {
        if (!trameOuverte)
        {
            ++refus;
            return;
        }
        trameOuverte = false;
        ++fins;
    }

    bool trameOuverte = false;
    int debuts = 0;
    int fins = 0;
    int refus = 0;
};

// Le garde termine la trame dans son destructeur, quel que soit le chemin de sortie.
class GardeTrame
{
public:
    explicit GardeTrame(Session& s) : session(s) {}
    ~GardeTrame() { session.End(); }

    // un garde copie fermerait la trame deux fois
    GardeTrame(const GardeTrame&) = delete;
    GardeTrame& operator=(const GardeTrame&) = delete;

private:
    Session& session;
};

// Boucle sans garde : End est ecrit en bas du corps de boucle.
void boucleSans(Session& session, const std::string& signes, int& images)
{
    for (char signe : signes)
    {
        if (!session.Wait() && (signe == 'N' || signe == 'C'))
            signe = 'V'; // pas d'etat de Wait : rien a rendre
        session.Begin();

        if (signe == 'R')
            return;   // saute End
        if (signe == 'C')
            continue; // saute End
        if (signe == 'N')
            ++images;

        session.End();
    }
}

// Boucle avec garde : le destructeur appelle End sur tous les chemins.
void boucleAvec(Session& session, const std::string& signes, int& images)
{
    for (char signe : signes)
    {
        if (!session.Wait() && (signe == 'N' || signe == 'C'))
            signe = 'V';
        session.Begin();
        GardeTrame garde(session);

        if (signe == 'R')
            return;
        if (signe == 'C')
            continue;
        if (signe == 'N')
            ++images;
    }
}

void afficher(const std::string& nom, const Session& session, int images)
{
    std::cout << nom
              << " DEBUTS " << session.debuts
              << " FINS " << session.fins
              << " REFUS " << session.refus
              << " IMAGES " << images
              << " OUVERTE " << (session.trameOuverte ? "OUI" : "NON") << '\n';
}

int main()
{
    int nombre = 0;
    std::string signes;
    if (!(std::cin >> nombre))
        return 0;
    if (nombre > 0)
        std::cin >> signes;
    signes = signes.substr(0, static_cast<std::size_t>(nombre));

    Session sans;
    int imagesSans = 0;
    boucleSans(sans, signes, imagesSans);
    afficher("SANS", sans, imagesSans);

    Session avec;
    int imagesAvec = 0;
    boucleAvec(avec, signes, imagesAvec);
    afficher("AVEC", avec, imagesAvec);
    return 0;
}
