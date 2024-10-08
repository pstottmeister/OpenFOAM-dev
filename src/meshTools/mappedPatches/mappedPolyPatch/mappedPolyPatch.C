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

#include "mappedPolyPatch.H"
#include "addToRunTimeSelectionTable.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
    defineTypeNameAndDebug(mappedPolyPatch, 0);

    addToRunTimeSelectionTable(polyPatch, mappedPolyPatch, word);
    addToRunTimeSelectionTable(polyPatch, mappedPolyPatch, dictionary);
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void Foam::mappedPolyPatch::calcGeometry(PstreamBuffers& pBufs)
{
    polyPatch::calcGeometry(pBufs);
    mappedPatchBase::clearOut(false);
}


void Foam::mappedPolyPatch::movePoints
(
    PstreamBuffers& pBufs,
    const pointField& p
)
{
    polyPatch::movePoints(pBufs, p);
    mappedPatchBase::clearOut(true);
}


void Foam::mappedPolyPatch::topoChange(PstreamBuffers& pBufs)
{
    polyPatch::topoChange(pBufs);
    mappedPatchBase::clearOut(false);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::mappedPolyPatch::mappedPolyPatch
(
    const word& name,
    const label size,
    const label start,
    const label index,
    const polyBoundaryMesh& bm,
    const word& patchType
)
:
    polyPatch(name, size, start, index, bm, patchType),
    mappedPatchBase(static_cast<const polyPatch&>(*this))
{
    //  mapped is not constraint type so add mapped group explicitly
    if (findIndex(inGroups(), typeName) == -1)
    {
        inGroups().append(typeName);
    }
}


Foam::mappedPolyPatch::mappedPolyPatch
(
    const word& name,
    const dictionary& dict,
    const label index,
    const polyBoundaryMesh& bm,
    const word& patchType
)
:
    polyPatch(name, dict, index, bm, patchType),
    mappedPatchBase(*this, dict, transformType::specified)
{
    //  mapped is not constraint type so add mapped group explicitly
    if (findIndex(inGroups(), typeName) == -1)
    {
        inGroups().append(typeName);
    }
}


Foam::mappedPolyPatch::mappedPolyPatch
(
    const mappedPolyPatch& pp,
    const polyBoundaryMesh& bm
)
:
    polyPatch(pp, bm),
    mappedPatchBase(*this, pp)
{}


Foam::mappedPolyPatch::mappedPolyPatch
(
    const mappedPolyPatch& pp,
    const polyBoundaryMesh& bm,
    const label index,
    const label newSize,
    const label newStart
)
:
    polyPatch(pp, bm, index, newSize, newStart),
    mappedPatchBase(*this, pp)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::mappedPolyPatch::~mappedPolyPatch()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void Foam::mappedPolyPatch::write(Ostream& os) const
{
    polyPatch::write(os);
    mappedPatchBase::write(os);
}


// ************************************************************************* //
