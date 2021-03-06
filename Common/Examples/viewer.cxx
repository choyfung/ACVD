/*=========================================================================

Program:   viewer : a simple mesh visualization example
Module:    vtkSurface
Language:  C++
Date:      2003/07
Author:   Sebastien Valette

=========================================================================*/

/* ---------------------------------------------------------------------

* Copyright (c) CREATIS-LRMN (Centre de Recherche en Imagerie Medicale)
* Author : Sebastien Valette
*
*  This software is governed by the CeCILL-B license under French law and 
*  abiding by the rules of distribution of free software. You can  use, 
*  modify and/ or redistribute the software under the terms of the CeCILL-B 
*  license as circulated by CEA, CNRS and INRIA at the following URL 
*  http://www.cecill.info/licences/Licence_CeCILL-B_V1-en.html 
*  or in the file LICENSE.txt.
*
*  As a counterpart to the access to the source code and  rights to copy,
*  modify and redistribute granted by the license, users are provided only
*  with a limited warranty  and the software's author,  the holder of the
*  economic rights,  and the successive licensors  have only  limited
*  liability. 
*
*  The fact that you are presently reading this means that you have had
*  knowledge of the CeCILL-B license and that you accept its terms.
* ------------------------------------------------------------------------ */  

// .NAME meshviewer 
// .SECTION Description

#include "vtkSurface.h"
#include "RenderWindow.h"

/// A simple example of mesh visualization
/// Usage : viewer mesh1 mesh2 .... meshN
/// where mesh1, mesh2, ... meshN are all mesh files. They will be displayed in different windows,
/// but the windows will have the same viewports

int main( int argc, char *argv[] )
{
	RenderWindow **Window=new RenderWindow*[argc-1];
	vtkSurface *Mesh;

	for (int i=0;i<argc-1;i++)
	{
	
		// Load the mesh and create the vtkSurface data structure
		Mesh=vtkSurface::New();
		cout <<"load : "<<argv[i+1]<<endl;
		Mesh->CreateFromFile(argv[i+1]);

		// prints to standard output the mesh caracteristics
		Mesh->DisplayMeshProperties();

		// Create a renderwindow
		Window[i]=RenderWindow::New();
		Window[i]->SetInputData(Mesh);

		// synchronize the viewport with the first created window		
		if (i>0)
			Window[i]->AttachToRenderWindow(Window[0]);

		Window[i]->Render();
		Window[i]->SetWindowName(argv[i+1]);
		Mesh->Delete();
	}

	// start interaction
	Window[0]->Interact();
	
	// Delete objects before exit
	for (int i=0;i<argc-1;i++)
		Window[i]->Delete();
	delete [] Window;

	return (0);
}
