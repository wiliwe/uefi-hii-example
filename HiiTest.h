/** @file HiiTest.h
   
  HII test application header

**/

/*=============================================================================
                              EDIT HISTORY

  $Header: 
  $DateTime: 2012-02-13 00:26:40 $ 
  $Author: William.L $ 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 02/13/12   William.L    Init.

=============================================================================*/

#ifndef _HII_TEST_H_
#define _HII_TEST_H_

/*=========================================================================
      Include Files
==========================================================================*/
#include <Uefi.h>

#include <Protocol/HiiConfigRouting.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>

#include <Guid/MdeModuleHii.h>

#include <Library/HiiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/DebugLib.h>   /* DEBUG macro */
#include <Library/PrintLib.h>   /* AsciiPrint */
#include <Library/TestInterface.h>

/*=========================================================================
      Type Definitions
==========================================================================*/
//
// This is the generated IFR binary data for each formset defined in VFR.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  HiiTestVfrBin[];  /* VFR-FileName+Bin[], VFR-FileName.vfr */

//
// This is the generated String package data for all .UNI files.
// This data array is ready to be used as input of HiiAddPackages() to
// create a packagelist (which contains Form packages, String packages, etc).
//
extern UINT8  HiiTestStrings[];  /* BASE_NAME+Strings[] , BASE_NAME is the one in INF file. */

EFI_HII_HANDLE gStringPackHandle;


/*=========================================================================
      Function Prototypes
==========================================================================*/


/*=========================================================================
      Functions
==========================================================================*/



#endif 
