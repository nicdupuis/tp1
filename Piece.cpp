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

    Piece::Piece(){}

    Piece::Piece(const std::string & s): nom(s){}

    Piece::Piece(const Piece& source): nom(source.nom){}

    Piece::~Piece(){}

    const Piece& Piece::operator =(const Piece& source){
        if (&source != this){
            nom = source.nom;
        }
        return *this;
    }

    void Piece::setParcourue(bool p){
        parcourue = p;
    }

    void Piece::setDistanceDuDebut(int d){
        distanceDuDebut = d;
    }

    void Piece::ajoutePorte(const Porte& p){}

}
