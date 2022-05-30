/**
 * \file Porte.cpp
 * \brief Ce fichier contient une implantation des méthodes de la classe Porte
 * \author Étudiant(e)
 * \version 0.1
 * \date mai 2022
 *
 */

#include "Porte.h"

namespace TP1
{
    //Complétez ou modifiez l'implémentation des méthodes demandées.

/**
 * \fn	Porte::Porte()
 * \brief Constructeur par défaut de la classe Porte
 */
    Porte::Porte(): color(Aucun){}

/**
 * \fn	Porte::Porte(Couleur c, Piece* d)
 * \brief Constructeur avec paramètres de la classe Porte
 * \param[in]	c, d La couleur de la porte, la destination de la porte
 */
    Porte::Porte(Couleur c, Piece* d): color(c), destination(d){}

/**
 * \fn	Porte::Porte(const Porte& source)
 * \brief Constructeur copie de la classe Porte
 * \param[in]	source La porte à copier
 */
    Porte::Porte(const Porte& source): color(source.color), destination(source.destination){
    }

/**
 * \fn	Porte::~Porte()
 * \brief Destructeur de la classe Porte
 */
    Porte::~Porte() {}

/**
 * \fn	const Porte& Porte::operator =(const Porte& source)
 * \brief Surcharge de l'opérateur d'assignation de la classe Porte
 * \param[in]	source La porte à assigner à l'objet courant
 * \return Le nouvel objet courant
 */
    const Porte& Porte::operator =(const Porte& source) {
        if (&source != this){
            color = source.color;
            destination = source.destination;
        }
        return *this;
    }

/**
 * \fn	Porte::operator ==(const Porte& source) const
 * \brief Surcharge de l'opérateur == de la classe Porte
 * \param[in]	source La porte à comparer à l'objet courant
 * \return true si la porte en paramètre est identique (mêmes attributs couleur et destination) à l'objet courant, false sinon
 */
    bool Porte::operator ==(const Porte& source) const {
        return (color == source.color) && (destination == source.destination);
    }

}
