﻿// guids.h: definitions of GUIDs/IIDs/CLSIDs used in this VsPackage

/*
Do not use #pragma once, as this file needs to be included twice.  Once to declare the externs
for the GUIDs, and again right after including initguid.h to actually define the GUIDs.
*/



// package guid
// { cf4a9039-b35f-4a77-becd-23f033739e8a }
#define guidmadhim_vspPkg { 0xCF4A9039, 0xB35F, 0x4A77, { 0xBE, 0xCD, 0x23, 0xF0, 0x33, 0x73, 0x9E, 0x8A } }
#ifdef DEFINE_GUID
DEFINE_GUID(CLSID_madhim_vsp,
0xCF4A9039, 0xB35F, 0x4A77, 0xBE, 0xCD, 0x23, 0xF0, 0x33, 0x73, 0x9E, 0x8A );
#endif

// Command set guid for our commands (used with IOleCommandTarget)
// { 63e48646-8acd-4ce2-8429-dd1d35abf05c }
#define guidmadhim_vspCmdSet { 0x63E48646, 0x8ACD, 0x4CE2, { 0x84, 0x29, 0xDD, 0x1D, 0x35, 0xAB, 0xF0, 0x5C } }
#ifdef DEFINE_GUID
DEFINE_GUID(CLSID_madhim_vspCmdSet, 
0x63E48646, 0x8ACD, 0x4CE2, 0x84, 0x29, 0xDD, 0x1D, 0x35, 0xAB, 0xF0, 0x5C );
#endif

//Guid for the image list referenced in the VSCT file
// { de0981d5-9ce4-46f7-9da4-5d15bf5f2e71 }
#define guidImages { 0xDE0981D5, 0x9CE4, 0x46F7, { 0x9D, 0xA4, 0x5D, 0x15, 0xBF, 0x5F, 0x2E, 0x71 } }
#ifdef DEFINE_GUID
DEFINE_GUID(CLSID_Images, 
0xDE0981D5, 0x9CE4, 0x46F7, 0x9D, 0xA4, 0x5D, 0x15, 0xBF, 0x5F, 0x2E, 0x71 );
#endif

