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

Application
    foamToGMV

Description
    Translates foam output to GMV readable files.

    A free post-processor with available binaries from
    http://www-xdiv.lanl.gov/XCM/gmv/

\*---------------------------------------------------------------------------*/

#include "argList.H"
#include "volFields.H"
#include "OFstream.H"
#include "instantList.H"
#include "IOobjectList.H"
#include "itoa.H"
#include "Cloud.H"
#include "passiveParticle.H"

using namespace Foam;

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //


int main(int argc, char *argv[])
{
    const label nTypes = 4;
    const word fieldTypes[] =
    {
        "volScalarField",
        "volVectorField",
        "surfaceScalarField",
        lagrangian::cloud::prefix
    };

    #include "setRootCase.H"

    #include "createTime.H"
    #include "createMeshNoChangers.H"

    #include "readConversionProperties.H"

    // get the available time-steps
    instantList TimeList = runTime.times();
    Info<< TimeList << endl;
    label nTimes = TimeList.size();

    for (label n=1; n < nTimes; n++)
    {
        if (TimeList[n].value() > startTime)
        {
            Info<< "Time = " << TimeList[n].value() << nl;

            // Set Time
            runTime.setTime(TimeList[n], n);
            word CurTime = runTime.name();

            IOobjectList objects(mesh, runTime.name());

            #include "moveMesh.H"

            // set the filename of the GMV file
            fileName gmvFileName = "plotGMV." + itoa(n);
            OFstream gmvFile(args.rootPath()/args.caseName()/gmvFileName);

            #include "gmvOutputHeader.H"
            #include "gmvOutput.H"
            #include "gmvOutputTail.H"
        }
    }

    Info<< "\nEnd\n" << endl;

    return 0;
}


// ************************************************************************* //
