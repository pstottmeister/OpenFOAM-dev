/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2024 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "metis.H"
#include "addToRunTimeSelectionTable.H"
#include "Time.H"

static const char* notImplementedMessage =
"You are trying to use metis but do not have the metis library loaded."
"\nThis message is from the dummy metis stub library instead.\n"
"\n"
"Please install metis and make sure that libmetis.so is in your "
"LD_LIBRARY_PATH.\n"
"The metis library can then be built from "
"$FOAM_SRC/parallel/decompose/metis and dynamically loading or linking"
" this library will add metis as a decomposition method.\n"
"Please be aware that there are license restrictions on using Metis.";

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace decompositionMethods
{
    defineTypeNameAndDebug(metis, 0);
    addToRunTimeSelectionTable(decompositionMethod, metis, decomposer);
}
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

Foam::label Foam::decompositionMethods::metis::decompose
(
    const List<label>& adjncy,
    const List<label>& xadj,
    const scalarField& cellWeights,
    List<label>& finalDecomp
)
{
    FatalErrorInFunction
        << notImplementedMessage << exit(FatalError);

    return -1;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::decompositionMethods::metis::metis
(
    const dictionary& decompositionDict,
    const dictionary& methodDict
)
:
    decompositionMethod(decompositionDict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

Foam::labelList Foam::decompositionMethods::metis::decompose
(
    const polyMesh& mesh,
    const pointField& points,
    const scalarField& pointWeights
)
{
    FatalErrorInFunction
        << notImplementedMessage << exit(FatalError);

    return labelList();
}


Foam::labelList Foam::decompositionMethods::metis::decompose
(
    const polyMesh& mesh,
    const labelList& agglom,
    const pointField& agglomPoints,
    const scalarField& agglomWeights
)
{
    FatalErrorInFunction
        << notImplementedMessage << exit(FatalError);

    return labelList();
}


Foam::labelList Foam::decompositionMethods::metis::decompose
(
    const labelListList& globalCellCells,
    const pointField& cellCentres,
    const scalarField& cellWeights
)
{
    FatalErrorInFunction
        << notImplementedMessage << exit(FatalError);

    return labelList();
}


// ************************************************************************* //
