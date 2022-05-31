/**
 * \file Piece.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Piece
 * \author Étudiant(e)
 * \version 0.1
 * \date mai 2022
 *
 */

#include "Piece.h"

namespace TP1
{
    //Complétez ou modifiez l'implémentation des méthodes demandées.

/**
 * \fn	Piece::Piece()
 * \brief Constructeur par défaut de la classe Piece
 */
    Piece::Piece():nom("default"), parcourue(false), distanceDuDebut(0), portes(){}

/**
 * \fn	Piece::Piece(const std::string & s)
 * \brief Constructeur avec paramètres de la classe Piece
 * \param[in]	s Le nom de la pièce
 */
    Piece::Piece(const std::string & s): nom(s), parcourue(false), distanceDuDebut(0), portes(){}

/**
 * \fn	Piece::Piece(const Piece& source)
 * \brief Le constructeur copie de la classe Piece
 * \param[in]	source La pièce à copier
 */
    Piece::Piece(const Piece& source): nom(source.nom), parcourue(source.parcourue), distanceDuDebut(source.distanceDuDebut), portes(source.portes){}

/**
 * \fn	Piece::~Piece()
 * \brief Destructeur de la classe Labyrinthe
 */
    Piece::~Piece(){}

/**
 * \fn	Piece& Piece::operator =(const Piece& source)
 * \brief Surcharge de l'opérateur assignation de la classe Piece
 * \param[in]	source La pièce à assigner à l'objet courant
 * \return Le nouvel objet courant
 */
    const Piece& Piece::operator =(const Piece& source){
        if (&source != this){
            nom = source.nom;
            parcourue = source.parcourue;
            distanceDuDebut = source.distanceDuDebut;
            portes = source.portes;
        }
        return *this;
    }

/**
 * \fn	Piece::setParcourue(bool p)
 * \brief Modifier le membre parcourue
 * \param[in]	p La valeur bool parcourue
 * \post L'attribut parcourue est modifié
 */
    void Piece::setParcourue(bool boolean){
        parcourue = boolean;
    }

/**
 * \fn	Piece::setDistanceDuDebut(int d)
 * \brief Modifier le membre distanceDuDebut
 * \param[in]	d La nouvelle distance du début à assigner à l'attribut
 * \post L'attribut distanceDuDebut est modifié
 */
    void Piece::setDistanceDuDebut(int d){
        distanceDuDebut = d;
    }

/**
 * \fn	Piece::ajoutePorte(const Porte& p)
 * \brief Ajouter une porte à la liste des portes qui partent de la pièce
 * \param[in]	p La porte à ajouter
 * \post La porte est ajoutée à la liste
 */
    void Piece::ajoutePorte(const Porte& p){
        portes.push_back(p);
    }

}
