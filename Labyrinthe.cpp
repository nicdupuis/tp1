/**
 * \file Labyrinthe.cpp
 * \brief Le code des méthodes membres et privés de la classe Labyrinthe.
 * \author IFT-2008, Étudiant(e)
 * \version 0.1
 * \date mai 2022
 * 
 */

//Fichiers à compléter par les autres méthodes de la classe Labyrinthes demandées

#include "Labyrinthe.h"

namespace TP1
{
 using namespace std;

// --------------------------
//	Méthodes à implémenter
// --------------------------

/**
 * \fn	Labyrinthe::Labyrinthe()
 * \brief Constructeur de la classe Labyrinthe
 */
    Labyrinthe::Labyrinthe(): depart(nullptr), arrivee(nullptr), dernier(nullptr){}

/**
 * \fn	Labyrinthe::Labyrinthe(const Labyrinthe& source)
 * \brief Constructeur copie de la classe Labyrinthe
 * \param[in]	source Le labyrinthe à copier
 */
    Labyrinthe::Labyrinthe(const Labyrinthe& source): depart(nullptr), arrivee(nullptr), dernier(nullptr){
        if (source.dernier == nullptr) return;
        recopierListePiece(source.dernier);
        recopierListePorte(source.dernier);
        placeDepart(source.depart->getNom());
        placeArrivee(source.arrivee->getNom());
    }
/**
 * \fn	Labyrinthe::~Labyrinthe()
 * \brief Destructeur de la classe Labyrinthe
 */
    Labyrinthe::~Labyrinthe() {
        effacerListePiece();
    }

/**
 * \fn	Labyrinthe::Labyrinthe(const Labyrinthe& source)
 * \brief Surcharge de l'opérateur assignation de la classe Labyrinthe
 * \param[in]	source Le labyrinthe à assigner
 * \return Le nouvel objet courant
 */
    const Labyrinthe& Labyrinthe::operator =(const Labyrinthe& source) {
        if(&source == this) return *this;
        effacerListePiece();
        recopierListePiece(source.dernier);
        recopierListePorte(source.dernier);
        placeDepart(source.depart->getNom());
        placeArrivee(source.arrivee->getNom());
    }

/**
 * \fn	Labyrinthe::recopierListePorte(NoeudListePieces *adresse)
 * \brief Recopie la liste de portes de chaque pièce d'un labyrinthe
 * \param[in]	*adresse L'adresse de la dernière pièce du labyrinthe source
 * \post	la liste de portes de chaque pièce est recopiée
 */
    void Labyrinthe::recopierListePorte(NoeudListePieces *adresse){
        if (adresse == nullptr) return;
        NoeudListePieces *noeud = adresse;
        do{
            Piece* courante = &(noeud->piece);
            for (auto const& porte: courante->getPortes()){
                ajoutePassage(porte.getCouleur(), courante->getNom()[0], courante->getNom()[2], porte.getDestination()->getNom()[0], porte.getDestination()->getNom()[0]);
            }
            noeud = noeud->suivant;
        }while(noeud != dernier);
    }

/**
 * \fn	void Labyrinthe::recopierListePiece(NoeudListePieces *adresse)
 * \brief Recopie la liste circulaire de pièces d'un autre labyrinthe
 * \param[in]	*adresse L'adresse de la dernière pièce du labyrinthe source
 * \post	la liste circulaire est copiée
 */
    void Labyrinthe::recopierListePiece(NoeudListePieces *adresse){
        if (adresse == nullptr) return;
        NoeudListePieces *noeud = adresse;
        do{
            ajoutePieceLabyrinthe(noeud->piece);
            noeud = noeud->suivant;
        } while (noeud != adresse);
    }

/**
 * \fn	void Labyrinthe::effacerListePiece()
 * \brief Libérer la mémoire associée aux pièces créées dans la liste de pièces circulaire
 * \post	la liste circulaire est supprimée
 */
    void Labyrinthe::effacerListePiece(){
        if (dernier == nullptr) return;
        NoeudListePieces *noeud = dernier;
        NoeudListePieces *suivant = nullptr;
        do{
            suivant = noeud->suivant;
            delete noeud;
            noeud = suivant;
        } while (noeud != dernier);
        dernier = nullptr;
    }
// -------------------------
//	Méthodes fournies
// -------------------------

/**
 * \fn	void Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream &entree)
 * \param[in]	couleur, la couleur du jouer auquel le labyrinthe chargé s'applique
 * \param[in]	entree, fichier contenant la définition du labyrinthe
 */
void Labyrinthe::chargeLabyrinthe(Couleur couleur, std::ifstream &entree)
 {
	int nbCols, nbRangs;

    if (!entree.is_open())
        throw logic_error("Labyrinthe::chargeLabyrinthe: Le fichier n'est pas ouvert !");

	entree >> nbCols >> nbRangs;
	entree.ignore(); //pour consommer le \n (le caractère fin de ligne)

	const int MAX_LIGNE = 1000;
	char ligne[MAX_LIGNE];

	entree.getline(ligne, MAX_LIGNE);
	entree.getline(ligne, MAX_LIGNE);

	std::ostringstream s; //Une chaîne pour écrire dedans, cette chaîne servira pour nommer les pièces du labyrinthe

	for (int i = 0; i < nbCols; i++)
	{
		for (int j = 0; j < nbRangs; j++)
		{
			s << i << "," << j;
			Piece p(s.str());
			s.str("");
			ajoutePieceLabyrinthe(p);
		}
	}

	for (int i = 0; i < nbCols; i++)
	{
		if (ligne[i * 4 + 1] == 'D' || ligne[i * 4 + 1] == 'd')
		{
			std::string nom;
			s << i << ",0";
			nom = s.str();
			s.str("");
			placeDepart(nom);
		}
		if (ligne[i * 4 + 1] == 'F' || ligne[i * 4 + 1] == 'f' || ligne[i * 4
				+ 1] == 'A' || ligne[i * 4 + 1] == 'a')
		{
			std::string nom;
			s << i << ",0";
			nom = s.str();
			s.str("");
			placeArrivee(nom);
		}
	}

	for (int j = 0; j < nbRangs; j++)
	{
		entree.getline(ligne, MAX_LIGNE);

		for (int i = (j == nbRangs - 1 && (j & 1)) ? 1 : 0; i < nbCols; i++)
		{
			if (j & 1)
			{
				if (j < nbRangs - 2 && ligne[i * 4 + 3] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 2);
				}
				if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 1);
				}
				if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
				{
					ajoutePassage(couleur, i - 1, j, i, j + 1);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'D' || ligne[i * 4
						+ 1] == 'd'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeDepart(nom);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 1] == 'F' || ligne[i * 4
						+ 1] == 'f' || ligne[i * 4 + 1] == 'A' || ligne[i * 4
						+ 1] == 'a'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeArrivee(nom);
				}
			}
			else
			{
				if (j < nbRangs - 1 && ligne[i * 4 + 0] == ' ')
				{
					ajoutePassage(couleur, i - 1, j + 1, i, j);
				}
				if (j < nbRangs - 2 && ligne[i * 4 + 1] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 2);
				}
				if (j < nbRangs - 1 && ligne[i * 4 + 2] == ' ')
				{
					ajoutePassage(couleur, i, j, i, j + 1);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'D' || ligne[i * 4
						+ 3] == 'd'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeDepart(nom);
				}
				if (j < nbRangs - 1 && (ligne[i * 4 + 3] == 'F' || ligne[i * 4
						+ 3] == 'f' || ligne[i * 4 + 3] == 'A' || ligne[i * 4
						+ 3] == 'a'))
				{
					std::string nom;
					s << i << "," << j + 1;
					nom = s.str();
					s.str("");
					placeArrivee(nom);
				}
			}
		}
	}
 }

/**
 * \fn	Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
 * \param[in]	Couleur couleur Couleur de la porte à ajouter
 * \param[in]	int i1
 * \param[in]	int j1
 * \param[in]	int i2
 * \param[in]	int j2
 */
 void Labyrinthe::ajoutePassage(Couleur couleur, int i1, int j1, int i2, int j2)
 {

	NoeudListePieces *piece1, *piece2;
	string nomPiece1, nomPiece2;
	ostringstream s;

	s << i1 << "," << j1;
	nomPiece1 = s.str();

	s.str("");

	s << i2 << "," << j2;
	nomPiece2 = s.str();

	s.str("");

	piece1 = trouvePiece(nomPiece1);
	piece2 = trouvePiece(nomPiece2);

	Porte nouvellePorte(couleur, &(piece2->piece));

	piece1->piece.ajoutePorte(nouvellePorte);
 }


/**
 * \fn	Labyrinthe::ajoutePieceLabyrinthe(Piece& p)
 * \brief ajoute une pièce au labyrinthe (si elle ne s'y trouve pas déjà)
 * \param[in]	p La pièce à ajouter
 * \post	la pièce appartient au labyrinthe;
 */
    void Labyrinthe::ajoutePieceLabyrinthe(const Piece& p) {
        if (appartient(p)) return;
        else
        {	Labyrinthe::NoeudListePieces* noeud = new Labyrinthe::NoeudListePieces;
            noeud->piece = p;

            if (dernier == 0)
            {	noeud->suivant = noeud;
                dernier = noeud;
            }
            else
            {	noeud->suivant = dernier->suivant;
                dernier->suivant = noeud;
            }
        }
    }
// -------------------------------
//	Autres méthodes à implémenter
// -------------------------------

/**
 * \fn	int Labyrinthe::solutionner(Couleur joueur)
 * \brief Solutionne le labyrinthe:
 *          1. En passant par tous les noeuds accessibles à partir d'un noeud
 *          2. En enfilant aussi tous les pièces dont une porte de la bonne couleur mène vers la pièce où on se trouve présentement
 * \param[in]	Couleur La couleur du joueur pour lequel on veut solutionner le labyrinthe
 * \return L'attribut distanceDuDébut de la pièce d'arrivée ou -1 si le labyrinthe n'est pas solvable
 */
    int Labyrinthe::solutionner(Couleur joueur) {
        queue<NoeudListePieces*> file;
        auto noeudDebut = trouvePiece(getDepart()->getNom());
        NoeudListePieces* pieceVisitee;
        noeudDebut->piece.setParcourue(true);
        file.push(noeudDebut);
        auto noeud = noeudDebut;
        do{
            pieceVisitee = file.front();
            file.pop();

            //boucle dans la liste de portes de la pieceVisitee, on cherche à enfiler toutes les pieces accessibles par ici
            for (auto const &porte: pieceVisitee->piece.getPortes()){
                //si la porte est de la couleur du joueur et que la destination de la pièce à parcourue = false, enfiler la pièce destination
                if ((porte.getCouleur() == joueur) && !(porte.getDestination()->getParcourue())) {
                     porte.getDestination()->setParcourue(true);
                     porte.getDestination()->setDistanceDuDebut(pieceVisitee->piece.getDistanceDuDebut() + 1);
                     file.push(trouvePiece(porte.getDestination()->getNom()));
                    if (getArrivee()->getParcourue()) {
                        resetParcourue();
                        return getArrivee()->getDistanceDuDebut();
                    }
                }
            }
                //boucle dans les listes de portes de toutes les pièces, cherche destination == pieceVisitee
                do{
                     for (auto const &porte: noeud->piece.getPortes()) {
                        //si la destination de la porte n'est pas parcourue ET si la destination de la porte est la pièce visitée, enfiler cette pièce
                        if (!(noeud->piece.getParcourue()) && (porte.getDestination()->getNom() == pieceVisitee->piece.getNom()) && (porte.getCouleur() == joueur)) {
                            noeud->piece.setParcourue(true);
                            noeud->piece.setDistanceDuDebut(pieceVisitee->piece.getDistanceDuDebut() + 1);
                            file.push(noeud);
                        }
                     }
                    noeud = noeud->suivant;
                }while(noeud != noeudDebut);
            if (getArrivee()->getParcourue()) {
                resetParcourue();
                return getArrivee()->getDistanceDuDebut();
            }
        }while(!file.empty());

        if (getArrivee()->getParcourue()) {
            resetParcourue();
            return getArrivee()->getDistanceDuDebut();
        }
        resetParcourue();
        return -1;
    }

/**
 * \fn	void Labyrinthe::resetParcourue()
 * \brief Remet à 0 l'attribut parcourue de chaque pièce du labyrinthe afin de recommencer à 0
 */
    void Labyrinthe::resetParcourue() {
        auto noeudDebut = trouvePiece(getDepart()->getNom());
        auto noeud = noeudDebut->suivant;
        noeudDebut->piece.setParcourue(false);
        do{
             noeud->piece.setParcourue(false);
             noeud = noeud->suivant;
        }while(noeud != noeudDebut);
    }

/**
 * \fn	Couleur Labyrinthe::trouveGagnant()
 * \brief Solutionne le labyrinthe pour chaque couleur de joueur en trouvant le joueur ayant le chemin le moins long à parcourir pour arriver à la fin
 * \return Couleur du joueur gagnant
 */
    Couleur Labyrinthe::trouveGagnant() {
        Couleur gagnant = Aucun;

        int jaune = solutionner(Jaune);
        int rouge = solutionner(Rouge);
        int bleu = solutionner(Bleu);
        int vert = solutionner(Vert);

        if (jaune == -1) jaune = 5000;
        if (rouge == -1) rouge = 5000;
        if (bleu == -1) bleu = 5000;
        if (vert == -1) vert = 5000;

        int minimum = min(jaune, min(rouge, min(bleu, vert)));

        map<Couleur, int> mymap;
        mymap[Jaune] = jaune;
        mymap[Rouge] = rouge;
        mymap[Bleu] = bleu;
        mymap[Vert] = vert;

        for (auto const& x: mymap){
            if (x.second == minimum){
                gagnant = x.first;
                return gagnant;
            }
        }
        return gagnant;
 }

/**
 * \fn	Labyrinthe::appartient(const Piece& p)
 * \brief vérifie si une pièce avec le même nom se trouve déjà dans le labyrinthe
 * \param[in]	p La pièce à vérifier
 * \return true si la pièce en paramètre appartient déjà au labyrinthe, false sinon
 */
    bool Labyrinthe::appartient(const Piece& p) const {
        if (this->dernier == nullptr) return false;
        for (auto i = dernier->suivant; i != dernier; i = i->suivant){
            if (i->piece.getNom() == p.getNom()) return true;
        }
        return false;
 }

/**
 * \fn	Labyrinthe::placeDepart(const std::string& nom)
 * \brief Ajuste le pointeur depart d'un labyrinthe pour qu'il contienne l'adresse de la pièce correspondant au nom spécifié par nom
 * \param[in]	nom Le nom de la pièce départ
 * \post Le pointeur Depart est placé
 * \except logic_error si aucune pièce du labyrinthe ne porte le nom nom, pris en charge par la méthode trouvePiece
 */
    void Labyrinthe::placeDepart(const std::string& nom) {
        depart = &(trouvePiece(nom)->piece);
 }
/**
 * \fn	Labyrinthe::placeArrivee(const std::string& nom)
 * \brief Ajuste le pointeur arrivee d'un labyrinthe pour qu'il contienne l'adresse de la pièce correspondant au nom spécifié par nom
 * \param[in]	nom Le nom de la pièce arrivée
 * \post Le pointeur Arrivee est placé
 * \except logic_error si aucune pièce du labyrinthe ne porte le nom nom, pris en charge par la méthode trouvePiece
 */
    void Labyrinthe::placeArrivee(const std::string& nom) {
        arrivee = &(trouvePiece(nom)->piece);
 }

/**
 * \fn	Labyrinthe::NoeudListePieces* Labyrinthe::trouvePiece(const std::string& nom) const
 * \brief Retourne l'adresse du noeud de la liste de pièces contenue dans le labyrinthe qui correspond à la pièce portant le nom nom
 * \param[in]	nom nom de la pièce à trouver
 * \except invalid_argument si le nom en paramètre est vide
 * \except logic_error si la pièce est introuvable
 */
    Labyrinthe::NoeudListePieces* Labyrinthe::trouvePiece(const std::string& nom) const {
        if (nom.empty()) throw invalid_argument("trouvePiece: le nom entré est vide");
        Labyrinthe::NoeudListePieces* p = dernier;
        if (p->piece.getNom() == nom) return p;
        for (p = dernier->suivant; p != dernier; p = p->suivant){
            if (p->piece.getNom() == nom) return p;
        }
        throw logic_error("trouvePiece: pièce introuvable");
 }

 }//fin du namespace
